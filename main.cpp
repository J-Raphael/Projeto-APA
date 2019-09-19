#include "Vehicles.h"

#define AND &&

vector<vector<float>> Transpose(vector<vector<int>>& matrix, int dimension);

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
}

vector<vector<float>> Transpose(vector<vector<int>>& matrix, int dimension){

    int b = 0, a = 0, k = 0, o = 0;

    vector<vector<float>> transposed_matrix;
    for(k = 0; k < dimension; k++){
        vector<float> p;
        for (o = 0; o < dimension; o++){
            p.push_back(0.0);
        }
        transposed_matrix.push_back(p);
    }

    //---------------------------------------------------------
    transposed_matrix.at(0).at(0) = 0;
    cout << " " << transposed_matrix.at(a).at(b) << " ";
    while (a < dimension) {
        if(a == 0){
            b = 1;
        }
        while (b < dimension){
            transposed_matrix.at(a).at(b) = sqrt(pow(matrix[a][1] - matrix[b][1], 2) + pow(matrix[a][2] - matrix[b][2], 2));
            transposed_matrix[b][a] = transposed_matrix[a][b];
            cout << " " << transposed_matrix.at(a).at(b) << " ";
            if (a == b)
                transposed_matrix[a][b] = 0;
            b += 1;
        }
        cout << endl;
        a += 1;
        b = 0;
    }
    //---------------------------------------------------------

    for(k = 0; k < dimension; k++){
        for (o = 0; o < dimension; o++){
            cout << " " << transposed_matrix.at(k).at(o) << " ";
        }
        cout << "\n";
    }
    return transposed_matrix;
}