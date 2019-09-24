#include "Vehicles.h"

vector<vector<float>> Transpose(vector<vector<int>>& matrix, int dimension);
void ConstrucaoGulosa(vector<vector<float>> matrix, vector<int> demand, int vehicles, int dimension, const int capacityTotal, vector<vector<int>>& greedy_solution);

vector<float> greedy_distance;


int main()
{
    char file[] = "./cvrp-cup/cvrp1.txt";
    cout << file << endl;

    ifstream arq(file);
    string buffer;

    int dimension;
    int vehicles;
    int capacity;
    vector<int> demand_section;
    vector<vector<int>> coordinates;

    int count = 0, valor;
    char linha[100], *token;

    vector<vector<int>> vnd_solution;
    vector<vector<int>> swap_solution;
    vector<vector<int>> twoOpt_solution;
    vector<vector<int>> inverter_solution;
    vector<float> final_route;

    // Leitura do arquivo das istâncias
    if(arq)
    {
        while (getline(arq, buffer))
        {
            if(count == 1){
                strcpy(linha, buffer.c_str());
                token = strchr(linha, ' ');
                dimension = atoi(token++);
                cout << "Dimension: " << dimension << endl;
            }

            else if(count == 2){
                strcpy(linha, buffer.c_str());
                token = strchr(linha, ' ');
                vehicles = atoi(token++);
                cout << "Vehicles: " << vehicles << endl;
            }

            else if(count == 3){
                strcpy(linha, buffer.c_str());
                token = strchr(linha, ' ');
                capacity = atoi(token++);
                cout << "Capacity: " << capacity << endl;
            }


            else if(count >= 5 && count < (dimension + 5)){
                strcpy(linha, buffer.c_str());
                token = strchr(linha, ' ');
                demand_section.push_back(atoi(token++));
            }

            else if(count >= (dimension + 7) && count < (dimension*2 + 7)){
                coordinates.push_back(vector<int>());

                stringstream split(buffer);
                
                while (split >> valor)
                    coordinates.back().push_back(valor);
            }

            count ++;
        }
        
    }
    
    // Chama a função Transpose para criar uma matrix das distancias de cada ciadde
    vector<vector<float>> matrix = Transpose(coordinates, dimension);

    // Primeira Construção: utiliza um algoritmo guloso para criar a primeira solução
    vector<vector<int>> greedy_solution;
    ConstrucaoGulosa(matrix, demand_section, vehicles, dimension, capacity, greedy_solution);
    
    

    // E lá vms nos para encontrarmos a solução final
    vector<vector<int>> final_solution = ILS(greedy_solution, greedy_distance, matrix, vehicles, dimension, 1, capacity, vnd_solution, final_route, demand_section, swap_solution, twoOpt_solution, inverter_solution);
    float final_distance = 0;
    float init_distance = 0;
    
    cout << endl << endl;
    // Faz o print das soluções encontradas na construção gulosa.
    int i, j, k = 0;
    for( i = 0; i < vehicles; i ++ ){
        for( j = 0; j < greedy_solution[i].size(); j++){
            cout << greedy_solution[i][j] << ", ";
            init_distance += matrix[k][greedy_solution[i][j]];
            k = greedy_solution[i][j];
        }
        cout << endl;
    }

    k = 0;
    cout << endl << endl;
    for( i = 0; i < vehicles; i++){
        for(j = 0; j < final_solution[i].size(); j++){
            cout << final_solution[i][j] << ", ";
            final_distance += matrix[k][final_solution[i][j]];
            k = final_solution[i][j];
        }
        cout << endl;
    }

    

    cout << endl;
    cout << "Distância inicial: " << init_distance << endl;
    cout << "Distância Atualizada: " << final_distance << endl;
}


// Função de transposição das coordenadas para a matrix
// Como é dado os pontos para cada cidade é feito a distância euclidiana para cada uma delas
vector<vector<float>> Transpose(vector<vector<int>>& matrix, int dimension)
{

    int i = 0, j = 0, k = 0, o = 0;

    vector<vector<float>> matrix_return;

    // Inicia a matrix
    for(k = 0; k < dimension; k++){
        vector<float> p;
        for (o = 0; o < dimension; o++){
            p.push_back(0.0);
        }
        matrix_return.push_back(p);
    }

    // Pecorre os elementos da matrix e os preenche com a distância euclidiana entre as cidades
    while (i < dimension) {
        while (j < dimension){
            matrix_return.at(i).at(j) = sqrt(pow(matrix[i][1] - matrix[j][1], 2) + pow(matrix[i][2] - matrix[j][2], 2));
            j += 1;
        }
        i += 1;
        j = 0;
    }

    return matrix_return;
}

void ConstrucaoGulosa(vector<vector<float>> matrix, vector<int> demand, int vehicles, int dimension, const int capacityTotal, vector<vector<int>>& greedy_solution)
{
    vector<int> routes;
    vector<int> line0;
    int l;
    for(l = 0; l < dimension; l++)
        line0.push_back(l);

    int minimun = INT_MAX, i = 0, j = 1, k = 0, line = 0, colum = 0, o = 0;
    int capacityAtual = capacityTotal, value;
    
    for(line = 0; line < vehicles; line++){
        colum = 0;
        k = 0;
        
        // Conta quantas cidades ainda estão disponíveis
        int kk = 0;
        for(o = 0; o < dimension; o ++){
            if(demand[o] != 0)
                kk ++;
        }

        routes.push_back(0);

        capacityAtual = capacityTotal; 
       
        while(capacityAtual > 0 && kk > 0){    
            minimun = INT_MAX;
            j = 1;
            colum += 1;

            while (j < dimension)
            {
                int aux = capacityAtual - demand[j];
                if((matrix[i][j] < minimun) && (i != j) && (aux >= 0) && (demand[j] != 0)){
                    k = j;
                    value = demand[k];
                    minimun = matrix[i][j];
                }
                j++;
            }
            
            int ant = i;
            if(i == k)
                break;
            else
                i = k; 

            routes.push_back(k);
            demand[k] = 0;
            
            capacityAtual -= value; 
        }

        routes.push_back(0);
        greedy_solution.push_back(routes);
        routes.clear();

    }

}


