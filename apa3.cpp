//Bibliotecas!
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

using namespace std;


int* construcaoGulosa(int **matriz, int *solucao, int dimensao)  //Algorítmo guloso
{
    int custMenor = INT_MAX, menorInd = 0, cont = 0, linha, coluna = 2, i = 0;  //custo menor do caminho, cidade equivale à linha nesse caso

    while (cont < (dimensao-1))
    {
        for (linha = 0; linha < dimensao; linha++)
        {
            if((matriz[linha][coluna] < custMenor) && (linha != coluna))
            {
                custMenor = matriz[linha][coluna];
                menorInd = linha;
                cont++;
            }
        }
        coluna = linha;
        solucao[i++] = menorInd;
    }     
    return solucao;
}


int main()
{
    FILE *arq; //Variável que receberá o endereço do arquivo caso esse seja aberto sem dificuldades
    int count, dimensao = 0, veiculos, capacidade, temp = 0;//Contador para pegar os dados de dimensão, veículos e capacidade do arquivo
    char Linha[100], *strDimensao, *strVeiculos, *strCapacidade, *strDemanda, *result;//Buffer que terá a linha do arquivo a cada vez no loop, e ponteiros que receberão os dados do arquivo que serão em string.
    int linha = 0, coluna = 0, num_linha = 0, indice = 0;
    int **matriz, *demanda, *solucao;

    //abrindo o arquivo
    arq = fopen("P-n16-k8.txt", "r"); 
    if(arq == NULL) //verificando se tudo ocorreu corretamente
    {
        cout <<"Problemas em abrir o arquivo\n";
        return 0;
    }
    //leitura do arquivo e imprimi-lo todo na tela
    count = 0;
    while (!feof(arq))
    {
        fgets(Linha, 100, arq);//ler linha a linha
        Linha[strlen(Linha) - 1] = '\0';
       /* if(Linha) verificar a linha
        {
            cout << Linha << endl; //imprimir a linha
        }
        guardar as variáveis de dimensão. veículos e capacidade */

        count++;
        if(count == 2)//Caso esteja na segunda linha
        {
            strDimensao = strchr(Linha, ' '); //pegue toda informação a partir do primeiro ' '(espaço)
            strDimensao++; //pegue tudo dpś do primeiro ' '(espaço)
            dimensao = atoi(strDimensao); //transforme essa string em inteiro
            matriz = (int**)malloc(sizeof(int*)*dimensao);
        
        }
        if(count == 3)//Caso esteja na terceira linha
        {
            strVeiculos = strchr(Linha, ' ');
            strVeiculos++;
            veiculos = atoi(strVeiculos);
        }
        if(count == 4)//Caso esteja na quarta linha
        {
            strCapacidade = strchr(Linha, ' ');
            strCapacidade++;
            capacidade =  atoi(strCapacidade);
        }
        if((count > 5) && (count < (dimensao+6)))
        {
            strDemanda = strchr(Linha, ' ');
            strDemanda++;
            demanda[indice++] = atoi(strDemanda);
        }
        
        temp = dimensao - 1; //0-15, com isso 16 é a dimensão.

        if((count > (dimensao + 7)) && (count << (dimensao*2 + 7))){
            //tratando os espaços
            char *token;
            token = strtok(Linha, " ");
            matriz[num_linha++] = (int*)malloc(sizeof(int)*dimensao);

            while(token != NULL)
            {
                //percorre a linha pesquisando cada número
                
                matriz[linha][coluna] = atoi(token); //guarda os números como inteiros na matriz
                //printf("%s\n", token);
                token = strtok(NULL, " ");
                //cout << "Coluna:"<< coluna << endl;
                coluna++;
            }
            linha++; //pulando pra próxima linha da matriz a ser preenchida
        }
        coluna = 0;//voltando para 1º coluna quando começar a atribuição na matriz da nova linha
        //cout << "Linha: " << linha << endl;
    }


    cout << endl; 
    cout << "1.Dimensão:" << dimensao << endl; //imprimir a dimensão.
    cout << "2.Veiculos:" << veiculos << endl; //imprimir a quantidade de veículos.
    cout << "3.Capacidade:" << capacidade << endl; //imprimir a capacidade
    cout << "4.Demanda: " << endl;
    for(int i = 0; i < dimensao; i++)
    {
        cout << i <<"->" << demanda[i] << endl;
    }
 
    coluna = 0;
    linha = 0;
    
    for (linha = 0; linha < dimensao; linha++)
    {
        for (coluna = 0; coluna < dimensao; coluna++)
        {
            cout << matriz[linha][coluna] << " ";
        }
        cout << endl;
    }
    cout << "Matriz: A[15][14]=" << matriz[15][14]; //teste se a matriz ta certa
   
    //construcaoGulosa(matriz, solucao, dimensao);
   
    fclose(arq);
    return 0;
}