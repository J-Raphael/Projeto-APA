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
    

    file = fopen("files/P-n20-k2.txt", "r+");
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
    token = strtok(line, " ");
    int cargas = 0, arestas = 0;
    int x = 0, y = 0, z = 0;
    
    char enter = 13;
    printf("Enter: %c", enter);

    /* walk through other tokens */
    while( token != NULL ) {
        int x = token[0] - '0';
        if(-38 != x){
            printf("Tokenn: %d\n", x);
            printf("Tokenn: %s\n", token);
        }
        token = strtok(NULL, " ");
       
    }
}