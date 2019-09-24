vector<vector<int> >ILS(vector<float >& greedy_distance,
vector<float>& final_route,
 vector<vector<int> >& vnd_solution,
  vector<vector<float> >& matrix, 
  int vehicles, int interations, int capacity, 
  vector<int>& demand, 
  vector<vector<int> >& swap_solution, 
  vector<vector<int> >& twoOpt_solution, 
  vector<vector<int> >& inverter_solution, 
  vector<vector<int> >& greedy_solution){
    int i = 0;     
    greedy_distance = GreedyFunction(matrix, vehicles, capacity, i+135, demand, greedy_solution);
    final_route = VndFunction(vnd_solution,matrix, vehicles, 10, capacity, swap_solution, twoOpt_solution, inverter_solution,greedy_solution, greedy_distance);
                
    vector<vector<int>> solution = vnd_solution;
    vector<vector<int>> temp_solution;
    vector<float>temp_distance;


    for (i = 0; i < interations; i++)
    {
        DisturbanceFunction(solution, swap_solution, twoOpt_solution, inverter_solution, matrix, vehicles, i+220, final_route);
        final_route = VndFunction(solution,matrix, vehicles, 10, capacity, swap_solution, twoOpt_solution, inverter_solution,solution, final_route);

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

vector<float> GreedyFunction(vector<vector<float> >& cities, int vehicles, int capacity, int randomizer, vector<int>& demand, vector<vector<int>>& greddy_solution){
   

    vector<int> vehicle_route, vehicle_all;
    srand(randomizer);
    int sum_distances = 0, count2 = 0, i = 0, a = 0, ra = 0, suma = 0, vehicle_counter = 0, ind_menor, j = 0, ai = 0;
    float menor = INT_MAX;
    vector<float> total_distances;
    int buf_demand = 0, flag = 0;
    vehicle_all.push_back(0);

    while (vehicle_counter < vehicles) {
        //first ocurrence is always 0
        vehicle_route.push_back(a);
        cout << "[" << vehicle_route[0];
            while (count2 < cities.size()) {
                for (j = 0; j < cities.size(); j++) {
                        if(count2 == 0) {
                            j = rand() % (cities.size()-1);
                                if (find(vehicle_all.begin(), vehicle_all.end(), j) == vehicle_all.end()) {
                                    ra = vehicle_route[0];
                                    menor = cities[ra][j];
                                    ind_menor = j;
                                    break;
                               }
                        }

                    if (count2 == cities.size() - 1) {
                        menor = cities[i][a];
                        ind_menor = a;
                        //break;
                    }

                    if (cities[i][j] != 0 && cities[i][j] < menor) {
                        if (find(vehicle_all.begin(), vehicle_all.end(), j) == vehicle_all.end()) {
                            if (demand[j] < (capacity - buf_demand)) {
                                    menor = cities[i][j];
                                    ind_menor = j;
                            } else {
                                    menor = cities[i][a];
                                    ind_menor = 0;
                                    flag = 1;
                                    }
                            }
                        }
                    }
                    if(flag == 1) {
                        vehicle_route.push_back(0);
                        //sum_distances += menor;
                        sum_distances += cities[vehicle_route.at(count2)][vehicle_route.at(count2+1)];
                        i = ind_menor;
                        menor = INT_MAX;
                        cout << " -> " << vehicle_route.back();
                        break;
                    }
                    vehicle_route.push_back(ind_menor);
                    vehicle_all.push_back(ind_menor);
                    //sum_distances += menor;
                    i = ind_menor;
                    menor = INT_MAX;
                    cout << " -> " << ind_menor;
                    sum_distances += cities[vehicle_route.at(count2)][vehicle_route.at(count2+1)];
                    count2++;
                    buf_demand += demand[ind_menor];
            }
            cout << " ]" << endl;
            count2 = 0;
            ai = 0;
            greddy_solution.push_back(vehicle_route);
            vehicle_route.clear();
            cout << "Vehicle capacity left: " << (capacity-buf_demand) << endl;
            cout << "\nTotal distance: " << sum_distances << ", of the vehicle: " << vehicle_counter << endl;
            total_distances.push_back(sum_distances);
            sum_distances = 0;
            buf_demand = 0;
            vehicle_counter += 1;
            flag = 0;
    }

    int k;
cout << "############################################################################################################"<<endl;
cout << "############################################################################################################"<<endl;
cout << "############################################################################################################"<<endl;
    for (k = 0; k < vehicles; k++){
        cout << "[ ";
        for (i = 0; i < (greddy_solution[k].size()); i++)
        {
            if (i < (greddy_solution[k].size() - 1))
                cout  << greddy_solution[k][i]  << " -> ";
            else
                cout << greddy_solution[k][i];
        }
        cout << "] " << endl;

        cout << "New distance after greedy: " << total_distances[k] << endl << endl;
    }

cout << "############################################################################################################"<<endl;
cout << "############################################################################################################"<<endl;
cout << "############################################################################################################"<<endl;

    return total_distances;

}

vector<float> VndFunction(vector<vector<int> >& vnd_solution, vector<vector<float> >& matrix, int vehicles, int iterations, int capacity, vector<vector<int> >& swap_solution, vector<vector<int> >& twoOpt_solution, vector<vector<int> >& inverter_solution, vector<vector<int> >& temp_solution,vector<float>& temp_distance){

 	int i = 0, k = 0, o = 0, j;
 	vector<float> temb_route;
 	vector<float> best_route;
 	float min_route = 0;

 	vector<int> aux;

	vector<float> swap_distance = SwapFunction(temp_solution, swap_solution, matrix, vehicles, i+100000);
	vector<float> twoOpt_distance = TwoOptFunction(temp_solution, twoOpt_solution, matrix, vehicles,i+10000);
	vector<float> inverter_distance = InverterFunction(temp_solution, inverter_solution, matrix, vehicles, i+0);


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
/*
	cout << "###########################################################################################################################################"<<endl;

    for (int m = 0; m < vehicles; m++)
    {
         for (int n = 0; n < final_solution.at(m).size(); n++)
         {
             cout << final_solution[m][n] << " ";
         }

         cout << endl;
         cout << "Melhor solucao: " << best_route[m] << endl << endl;
    }
*/
	return best_route;
 }

 vector<float > InverterFunction(vector<vector<int>>& solution, vector<vector<int>>& inverter_solution, vector<vector<float> >& matrix, int vehicles, int randomizer){

    inverter_solution = solution;
    cout << "=================================================================" << endl;
    cout << "INVERT" << endl;
    //vector<vector<int>> Inverter = solution;
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
        cout << "The New_adjuster is: " << swap_adjuster << endl;
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

    for (k = 0; k < vehicles; k++){
        cout << "[ ";
        for (i = 0; i < (inverter_solution[k].size()); i++)
        {
            if (i < (inverter_solution[k].size() - 1))
                cout  << inverter_solution[k][i]  << " -> ";
            else
                cout << inverter_solution[k][i];
        }
        cout << "] " << endl;
        cout << "New distance after Inversion: " << new_distance[k] << endl << endl;
    }

   /* cout << "##########################################################################"<< endl;
     for (int m = 0; m < vehicles; m++)
    {
        //cout << "[ ";
        for (int n = 0; n < inverter_solution.at(m).size(); n++)
        {
            if(n == inverter_solution.at(m).size()-1) {
                cout << inverter_solution[m][n];
                break;
            }
            cout << inverter_solution[m][n] << ", ";

        }
        cout << "; " << endl;
        //cout << "Best solution: " << final_route[m] << ", vehicle: " << m << endl;
        //cout << "---------------------------" << endl;
    }
    cout << "##########################################################################"<< endl;
    */
    return new_distance;
}


vector<float > TwoOptFunction(vector<vector<int>>& solution, vector<vector<int>>& twoOpt_solution, vector<vector<float> >& matrix, int vehicles, int randomizer){
    
    cout << "=================================================================" << endl;
    cout << "TWO-OPT NUMBERED: " << endl;
    srand(time(NULL));

    twoOpt_solution = solution;
    vector<float> new_distance;
    int i = 0, k =0, index_dist = 0, o = 0;
    float distances = 0;
    int index = 1;
    // MIN swap_adjuster = solution.size()-2
    srand(randomizer);
    double adj[] = {0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};

    int a = sizeof(adj)/sizeof(*adj);
    double swap_adjuster = 0;
    int new_adjuster = 0;

    for (k = 0; k < vehicles; k++) {
        swap_adjuster = adj[rand() % a];
        new_adjuster = (int) (swap_adjuster * twoOpt_solution.at(k).size());


        cout << "*" << endl<< "*" << endl<< "*" << endl<< "*" << endl<< "*" << endl<< "*" << endl<< "*" << endl<< "*" << endl<< "*" << endl<< "*" << endl;
        cout << "INDEX: " << index << "NEW: " << new_adjuster << endl;
        while (index < new_adjuster) {

            if(twoOpt_solution[k][index + 2] != 0){
                cout << "oooooooooo" << endl;
                break;                
            }
            cout << twoOpt_solution[k][index + 2] << ", ";
            swap(twoOpt_solution[k][index], twoOpt_solution[k][index + 2]);
            index += 3;
            
        }
        cout << "++" << endl<< "++" << endl<< "++" << endl<< "++" << endl<< "++" << endl<< "++" << endl<< "++" << endl<< "++" << endl<< "++" << endl;

        cout << "The New_adjuster is: " << swap_adjuster << endl;
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

    for (k = 0; k < vehicles; k++){
        cout << "[ ";
        for (i = 0; i < (twoOpt_solution[k].size()); i++)
        {
            if (i < (twoOpt_solution[k].size() - 1))
                cout  << twoOpt_solution[k][i]  << " -> ";
            else
                cout << twoOpt_solution[k][i];
        }
        cout << "] " << endl;
        cout << "New distance after 2opt: " << new_distance[k] << endl << endl;
    }

    
    return new_distance;
}



vector<float > SwapFunction(vector<vector<int>>& solution, vector<vector<int>>& swap_solution, vector<vector<float> >& matrix, int vehicles, int randomizer){

    cout << "=================================================================" << endl;
    cout << "SWAP" << endl;
    swap_solution = solution;
    vector<float> new_distance;
    int i = 0, k = 0, o = 0;
    float distances = 0;
    int index = 1;

    srand(randomizer);
    double adj[] = {0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    // MIN swap_adjuster = solution.size()-2
    int a = sizeof(adj)/sizeof(*adj);
    double swap_adjuster = 0;
    int new_adjuster = 0;


    for (k = 0; k < vehicles;k++)
    {

        swap_adjuster = adj[rand() % a];
        new_adjuster = (int) (swap_adjuster * swap_solution.at(k).size());
        while (index < new_adjuster && index)
        {
            if ((index+1) == 0)
                break;
            swap(swap_solution[k][index], swap_solution[k][index+1]);
            index += 2;
        }
        cout << "The New_adjuster is: " << swap_adjuster << endl;
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

    for (k = 0; k < vehicles; k++){
        cout << "[ ";
        for (i = 0; i < (swap_solution[k].size()); i++)
        {
            if (i < (swap_solution[k].size() - 1))
                cout  << swap_solution[k][i]  << " -> ";
            else
                cout << swap_solution[k][i];
        }
        cout << "] " << endl;

        cout << "New distance after SWAP: " << new_distance[k] << endl << endl;
    }
    return new_distance;
}