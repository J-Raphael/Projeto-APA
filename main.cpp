// * Bibliotecas utilizadas
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

using namespace std;

// * Funções utilizadas
void readFile(FILE *file);
void splitLine(char line[200]);

// * Variáveis booleanas
char name[255];
int dimension;
int vehicles;
int capacity;
int maxCapacity;
int *demandSenction;
int **edgeWeightSection;
int result;

int main()
{
    setlocale(LC_ALL, "Portuguese");

    FILE *file;
    

    file = fopen("files/P-n19-k2.txt", "r+");
    if(file == NULL)
    {
        printf("Problemas na abertura do arquivo.\n");
        return -1;
    }

    readFile(file);

    fclose(file);
    return 0;


}


void readFile(FILE *file)
{
    char line[200];
    char *result;
    int i = 1;
    while (!feof(file))
    {
        result = fgets(line, 200, file);

        int k = 0;
        int active = 0;

        if(result)
        {
            splitLine(line);
        }
        i++;
    }
}

void splitLine(char *line)
{
    char *token;
    int keys = 0, x = 0, linha = 0, coluna = 0;
    int newLine = -38;

    token = strtok(line, " ");

    while (token != NULL)
    {
        cout << "KEY: " << keys << endl;
        cout << "Token: " << token << endl; 
        int x = token[0] - '0';
        cout << "Token X: " << x << endl; 
        if(newLine != x)
        {
            cout << "ENTREEEIII " <<endl;
            switch (keys)
            {
            case 1:
                strcpy(name,token);
                break;
           case 2:
                cout << "ENTREEEIII 2" <<endl;
                dimension = atoi(token);
                edgeWeightSection[linha] = (int*)malloc(sizeof(int)*dimension);
                break;
            case 3:
                vehicles = atoi(token);
                break;
            case 4:
                capacity = atoi(token);
                break;
            case 5:
                demandSenction[x] = atoi(token);
                x ++;
                break;
            case 6:
                edgeWeightSection[linha][coluna] = atoi(token);
                coluna ++;
                break;        
            default:
                break;
            }

            if(strcmp("NAME:", token) == 0) keys = 1;
            else if(strcmp("DIMENSION:", token) == 0) keys = 2;
            else if(strcmp("VEHICLES:", token) == 0) keys = 3;
            else if(strcmp("CAPACITY:", token) == 0) keys = 4;
            else if(strcmp("DEMAND_SECTION:", token) == 0) keys = 5; 
            else if(strcmp("EDGE_WEIGHT_SECTION:", token) == 0) keys = 6;
            else keys = keys;
        }
        else{
            if(keys == 6){
                linha ++;
                coluna = 0;
                edgeWeightSection[linha] = (int*)malloc(sizeof(int)*dimension);
            }
        }

        token = strtok(NULL, " ");
        cout << "Token 2: " << token << endl;
    }
}