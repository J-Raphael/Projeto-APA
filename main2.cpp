#include "Vehicles.h"

vector<vector<float>> Transpose(vector<vector<int>>& matrix, int dimension);
vector<vector<int>> ConstrucaoGulosa(vector<vector<float>> matrix, vector<int> demand, int vehicles, int dimension, const int capacityTotal);

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
    


    vector<vector<float>> matrix = Transpose(coordinates, dimension);
    // Primeira Construção
    vector<vector<int>> solucoes = ConstrucaoGulosa(matrix, demand_section, vehicles, dimension, capacity);

}

vector<vector<float>> Transpose(vector<vector<int>>& matrix, int dimension){

    int i = 0, j = 0, k = 0, o = 0;

    vector<vector<float>> matrix_return;

    for(k = 0; k < dimension; k++){
        vector<float> p;
        for (o = 0; o < dimension; o++){
            p.push_back(0.0);
        }
        matrix_return.push_back(p);
    }
    cout << endl;
    while (i < dimension) {

        while (j < dimension){
            matrix_return.at(i).at(j) = sqrt(pow(matrix[i][1] - matrix[j][1], 2) + pow(matrix[i][2] - matrix[j][2], 2));
            ////cout << " " << matrix_return[i][j];
            j += 1;
        }
        i += 1;
        j = 0;
        //cout << endl;
    }

    return matrix_return;
}

vector<vector<int>> ConstrucaoGulosa(vector<vector<float>> matrix, vector<int> demand, int vehicles, int dimension, const int capacityTotal)
{
    vector<vector<int>> solucoes;
    list<int> cidadesVizinhas;
    int minimun = INT_MAX, i = 0, j = 1, k = 0, line = 0, colum = 0, o = 0;
    int capacityAtual = capacityTotal, value;

    for(k = 0; k < dimension; k++){
        vector<int> p;
        for (o = 0; o < dimension; o++){
            p.push_back(0);
        }
        solucoes.push_back(p);
    }

    k = 0;
    for(line = 0; line < vehicles; line++){
        colum = 0;
        int kk = 0;
        for(o = 0; o < dimension; o ++){
            if(demand[o] != 0)
                kk ++;
        }

        solucoes.at(line).at(colum) = 0;

        capacityAtual = capacityTotal; 
        cout << "Quantidades de cidades: " << kk << endl;    
        cout << "Solução " << line << ": " << solucoes[line][colum] << ", " << capacityAtual << "  " ;

        while(capacityAtual > 0){    
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
                    cidadesVizinhas.push_back(j);
                }
                j++;
            }
            
            if(i == k)
                break;
            else
                i = k; 

            solucoes.at(line).at(colum) = k;
            demand[k] = 0;
            
            capacityAtual -= value; 

            cout << solucoes[line][colum] << ", " << capacityAtual << "  ";       
                
        }

        cout << endl;
    }

    return solucoes;
}