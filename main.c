// * Bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// * Chamadas de funções
void readFile(FILE *file); // ? Função que ler os arquivos
void splitLine(char line[200]);

// * Variáveis booleanas
char name[255];
int dimension;
int vehicles;
int capacity;
int maxCapacity;
int demandSenction[50][2];
int edgeWeightSection[50][50];

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
    
    int x, y;
    for(x = 0; x < 19; x++)
    { 
        for(y = 0; y < 2; y++)
            printf("%d ", demandSenction[x][y]);

        printf("\n");
    }

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
    token = strtok(line, " ");
    int cargas = 0, arestas = 0;
    int x = 0, y = 0, z = 0;
    
    /* walk through other tokens */
    while( token != NULL ) {
        printf("Tokenn: %s\n", token);
       if(strcmp(token, "NAME:") == 0)
       {
           token = strtok(NULL, " ");
           strcpy(name, token);
       }
       else if(strcmp(token, "DIMENSION:") == 0)
       {
           token = strtok(NULL, " ");
           char aux[255];
           strcpy(aux, token);
           dimension = atoi(aux);
       }
       else if(strcmp(token, "CAPACITY:") == 0)
       {
           token = strtok(NULL, " ");
           char aux[255];
           strcpy(aux, token);
           maxCapacity = atol(aux);

       }
       else if(strcmp(token, "VEHICLES:") == 0)
       {
           token = strtok(NULL, " ");
           char aux[255];
           strcpy(aux, token);
           vehicles = atol(aux);
       }
       else if(strcmp(token, "DEMAND_SECTION:") == 0)
       {
            cargas = 1;   
       }
       else if(cargas)
       {
           demandSenction[x][0] = x;
           token = strtok(); 
           printf("Token: %s\n", token);
       }
       else
           token = strtok(NULL, line);
       
    }
}