#ifndef VEHICLES_H
#define VEHICLES_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits.h>
#include <random>
#include <time.h>
#include <algorithm>

using namespace std;

vector<float> GreedyDistanceFunction(vector<vector<int>> greedy_solution, vector<vector<float>> matrix, int vehicles, int dimension);
vector<float> VNDFunction(vector<vector<int>>& vnd_solution, vector<vector<float>>& matrix, int vehicles, int interations, int capacity, vector<vector<int>>& swap_solution, vector<vector<int> >& twoOpt_solution, vector<vector<int> >& inverter_solution, vector<vector<int> >& temp_solution, vector<float>& temp_distance);
vector<float> SwapFunction( vector<vector<int>>& solution, vector<vector<int>>& swap_solution, vector<vector<float> >& matrix, int vehicles, int randomizer);
vector<float > TwoOptFunction(vector<vector<int>>& solution, vector<vector<int>>& twoOpt_solution, vector<vector<float> >& matrix, int vehicles, int randomizer);
vector<float > InverterFunction(vector<vector<int>>& solution, vector<vector<int>>& inverter_solution, vector<vector<float> >& matrix, int vehicles, int randomizer);
void DisturbanceFunction(vector<vector<int> >& solution, vector<vector<int> >& swap_solution, vector<vector<int> >& twoOpt_solution, vector<vector<int> >& inverter_solution,vector<vector<float> >& matrix, int vehicles, int i, vector<float>& final_route);

vector<vector<int>> ILS(
    vector<vector<int>>& greedy_solution,
    vector<float>& greedy_distance,
    vector<vector<float>>& matrix,
    const int vehicles, const int dimension, const int interations, const int capacity,
    vector<vector<int> >& vnd_solution,
    vector<float>& final_route,
    vector<int>& demand,
    vector<vector<int> >& swap_solution, 
    vector<vector<int> >& twoOpt_solution, 
    vector<vector<int> >& inverter_solution
)
{
    // Calcula a distância encontrada na construção gulosa
    greedy_distance = GreedyDistanceFunction(greedy_solution, matrix, vehicles, dimension);

    // Chama o algoritimo VND
    final_route = VNDFunction(vnd_solution,matrix, vehicles, 1000, capacity, swap_solution, twoOpt_solution, inverter_solution,greedy_solution, greedy_distance);

    vector<vector<int>> solution = vnd_solution;
    vector<vector<int>> temp_solution;
    vector<float>temp_distance;

    int i;
    for (i = 0; i < interations; i++)
    {
        DisturbanceFunction(solution, swap_solution, twoOpt_solution, inverter_solution, matrix, vehicles, i+220, final_route);
        final_route = VNDFunction(solution,matrix, vehicles, 10, capacity, swap_solution, twoOpt_solution, inverter_solution,solution, final_route);
    }

    return solution;
}

void DisturbanceFunction(vector<vector<int> >& solution, vector<vector<int> >& swap_solution, vector<vector<int> >& twoOpt_solution, vector<vector<int> >& inverter_solution,vector<vector<float> >& matrix, int vehicles, int i, vector<float>& final_route){

    srand(i);
    int a = rand() % 3;
    vector<float> temp_distance;
    vector<vector<int>> temp_solution;

    if (a == 0){
        temp_distance = SwapFunction(solution, swap_solution, matrix, vehicles, i+100000);
        temp_solution = swap_solution;
    }
    else if (a == 1){
        temp_distance = TwoOptFunction(solution, twoOpt_solution, matrix, vehicles, i+10000);
        temp_solution = twoOpt_solution; 
    }
    else if (a == 2){
        temp_distance = InverterFunction(solution, inverter_solution, matrix, vehicles, i+0);
        temp_solution = inverter_solution;
    }

    for (int j = 0; j < vehicles; j++)
    {
       if(temp_distance[j] <= final_route[j]){

           final_route[j] = temp_distance[j];
           solution[j].clear();
           solution[j] = temp_solution[j];
    
       }   
    }
    
}

vector<float> GreedyDistanceFunction(
    vector<vector<int>> greedy_solution, 
    vector<vector<float>> matrix, 
    int vehicles, int dimension)
{
    int i, j, k = 0;
    vector<float> sum;

    for(i = 0; i < vehicles; i ++)
        sum.push_back(0);

    for( i = 0; i < vehicles; i ++)
    {
        k = 0;
        for(j = 0; j < greedy_solution[i].size(); j ++)
        {
            if(greedy_solution[i][j] != 0 || j == 0 )
            {
                sum[i] +=  matrix[k][greedy_solution[i][j]];
                k = greedy_solution[i][j];                   
            }
        }
        sum[i] += matrix[k][0];
    }

    return sum;
}

vector<float> VNDFunction(
    vector<vector<int>>& vnd_solution, 
    vector<vector<float>>& matrix, 
    int vehicles, int interations, int capacity,
    vector<vector<int>>& swap_solution,
    vector<vector<int> >& twoOpt_solution, 
    vector<vector<int> >& inverter_solution, 
    vector<vector<int> >& temp_solution,
    vector<float>& temp_distance
    )
{
    int i = 0, k = 0, o = 0, j;
    vector<float> temb_route;
    vector<float> best_route;
    float min_route = 0;

    // Três formas de swaps para a solução gulosa
    // Faz os swaps das cidades adjacentes, nas rotas obtidas na construção gulosa 
    vector<float> swap_distance = SwapFunction(temp_solution, swap_solution, matrix, vehicles, i + 1000);

    // Faz os swaps das cidades em posições , nas rotas obtidas na construção gulosa
    vector<float> twoOpt_distance = TwoOptFunction(temp_solution, twoOpt_solution, matrix, vehicles,i+10000);
	
    // Faz os swaps das cidades em posições contrárias, nas rotas obtidas na construção gulosa
    vector<float> inverter_distance = InverterFunction(temp_solution, inverter_solution, matrix, vehicles, i+0);
   
    vector<int> aux;

    for (j = 0; j < vehicles; j++)
	{
		min_route = min(temp_distance[j],swap_distance[j]);
		min_route = min(min_route, inverter_distance[j]);
		min_route = min(min_route, twoOpt_distance[j]); 

		if(swap_distance[j] == min_route){

			for(k = 0; k < swap_solution.at(j).size(); k++)
				aux.push_back(swap_solution[j][k]);

		}

		else if(twoOpt_distance[j] == min_route) {

			for(k = 0; k < twoOpt_solution.at(j).size(); k++)
				aux.push_back(swap_solution[j][k]);

		}

		else if (inverter_distance[j] == min_route){

			for(k = 0; k < inverter_solution.at(j).size(); k++)
				aux.push_back(inverter_solution[j][k]);

		}

		else if(temp_distance[j] ==  min_route){

			for(k = 0; k < temp_solution.at(j).size(); k++)
				aux.push_back(temp_solution[j][k]);
			
		}
			
		vnd_solution.push_back(aux);
		best_route.push_back(min_route);
		aux.clear();

	}

    return best_route;
}


vector<float> SwapFunction(
    vector<vector<int>>& solution, 
    vector<vector<int>>& swap_solution, 
    vector<vector<float> >& matrix, 
    int vehicles, int randomizer
){
    cout << endl << endl << "SWAP" << endl;
    
    // Passa a solução encontrada na construção gulosa, para ser tratado os swaps
    swap_solution = solution;
    
    vector<float> new_distance;
    int i = 0, k = 0, o = 0;
    float distances = 0;
    int index = 1;

    srand(randomizer);
    double adj[] = {0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    int a = sizeof(adj)/sizeof(*adj);
    double swap_adjuster = 0;
    int new_adjuster = 0;

    for (k = 0; k < vehicles;k++)
    {
        swap_adjuster = adj[rand() % a];
        new_adjuster = (int) (swap_adjuster * swap_solution.at(k).size());
        
        // Faz os swaps dos elementos adjacentes do certificado
        while (index < new_adjuster && index)
        {
            if ((index+1) == 0)
                break;
            
            // Faz a troca entre as posições dos certificados
            swap(swap_solution[k][index], swap_solution[k][index+1]);
            index += 2;
        }
        
        cout << "The New_adjuster is: " << swap_adjuster << endl;

        // Calcula a nova distância do certificado
        while (i < swap_solution[k].size()-1)
        {
            distances += matrix[swap_solution.at(k).at(i)][swap_solution.at(k).at(i+1)];
            i += 1;
        }

        new_distance.push_back(distances);
        distances = 0;
        i = 0;
        index = 1;
    }

    return new_distance;

}

vector<float > TwoOptFunction(
    vector<vector<int>>& solution, 
    vector<vector<int>>& twoOpt_solution, 
    vector<vector<float> >& matrix, 
    int vehicles, int randomizer
){

    twoOpt_solution = solution;
    vector<float> new_distance;
    
    int i = 0, k =0, index_dist = 0, o = 0;
    float distances = 0;
    int index = 1;
    
    srand(randomizer);
    
    double adj[] = {0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};

    int a = sizeof(adj)/sizeof(*adj);
    double swap_adjuster = 0;
    int new_adjuster = 0;

    for (k = 0; k < vehicles; k++) {
        swap_adjuster = adj[rand() % a];
        new_adjuster = (int) (swap_adjuster * twoOpt_solution.at(k).size());

        while (index < new_adjuster) {

            if(twoOpt_solution[k][index + 2] != 0)
                break;                
            
            swap(twoOpt_solution[k][index], twoOpt_solution[k][index + 2]);
            index += 3;
            
        }
        
        while (i < twoOpt_solution[k].size() - 1) {
            distances += matrix[twoOpt_solution[k][i]][twoOpt_solution[k][i + 1]];
            i += 1;
        }

        new_distance.push_back(distances);
        distances = 0;
        i = 0;
        index_dist += 1;
        index = 1;
    }

    return new_distance;

}

vector<float > InverterFunction(
    vector<vector<int>>& solution, 
    vector<vector<int>>& inverter_solution, 
    vector<vector<float> >& matrix, 
    int vehicles, int randomizer
){

    inverter_solution = solution;
    vector<float> new_distance;

    int i = 0,k =0, index_dist = 0;
    float distances = 0;
    int index = 1;
    srand(randomizer);

    double adj[] = {0.4, 0.5, 0.6, 0.7, 0.8};
    int a = sizeof(adj)/sizeof(*adj), b = 0;
    double swap_adjuster = 0;
    int new_adjuster = 0;

    for (k = 0; k < vehicles; k++)
    {
        swap_adjuster = adj[rand() % a];
        new_adjuster = (int) floor((swap_adjuster * inverter_solution.at(k).size()));
        b = new_adjuster;

        while (index < new_adjuster)
        {
            swap(inverter_solution[k][index], inverter_solution[k][b]);
            index += 1;
            b -= 1;
            if(index == b)
                break;

            if (index > inverter_solution[k].size() - 1)
                break;
        }

        while (i < inverter_solution[k].size()-1)
        {
            distances += matrix[inverter_solution[k][i]][inverter_solution[k][i+1]];
            i += 1;
        }
        new_distance.push_back(distances);
        distances = 0;
        i = 0;
        index_dist += 1;
        index = 1;
    }

    return new_distance;
}

#endif // VEHICLES_H