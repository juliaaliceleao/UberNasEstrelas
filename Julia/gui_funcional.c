#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR 0
#define NENHUM 0

struct matriz_adjacencia
{
    int ** vertices;
    int ** h_ini; 
    int ** h_fim; 
    int ** peso;
    int RestricaoTempo;
};

typedef struct matriz_adjacencia matriz_adj;

int ** cria_matriz(int ** matriz, int NumPlanetas)
{
    //Variaveis
    int play = 1, cont = 0;

    //Aloca espaco p/ NumPlanetas(Vertices)
    matriz = (int ** )calloc(NumPlanetas, sizeof(int * ));

    //Aloca espaco p/ Adjacencias(arestas) dos Planetas(Vertices)
    for (int i = 0; i < NumPlanetas; i++)
    { matriz[i] = (int*)calloc(NumPlanetas, sizeof(int)); }

    //Cria arestas
    do
    {
        cont++;
        int PlanetaSource = 0;
        int PlanetaDestino = 0;
        
        printf("Digite o numero do Planeta: ");
        scanf("%d", &PlanetaSource);
        printf("Digite o numero doPlaneta destino: ");
        scanf("%d", &PlanetaDestino);
        matriz[PlanetaSource][PlanetaDestino] = 1;
        printf("\n");
        printf("Continuar: ");
        scanf(" %d", &play);

    } while ((play == 1) && (cont < (NumPlanetas*NumPlanetas)));

    return matriz;
}

void imprime_matriz(int ** matriz, int tam)
{
    int soma, i, j;

    //Imprimindo valores das arestas

    printf("Matriz\n ");
    for (i = 0; i < tam; i++)
    {
        printf("%d", i);
    }
    printf("\n");

    for (i = 0; i < tam; i++)
    {
        printf("%d", i);
        for (j = 0; j < tam; j++) printf("%d", matriz[i][j]);

        printf("\n");
    }
    printf("\n");
}

int * busca_em_profundidade2 (int * * matriz, int inicio, int * entregues, int tam) 
{
    int i;
    int cont = 0;

    
    entregues++;
    printf("-> %d", inicio);

    for (i = 0; i < tam; i++) 
    {
        if ((matriz[inicio][i] == 1) && (entregues[i] == 0))
        {
            cont++;
            entregues = busca_em_profundidade2(matriz, i, entregues, tam);
            printf("-> %d", inicio);
        }
    }
    if (cont == 0) 
    {
        printf("-> %d", inicio);
    }

    return entregues;
}

void busca_em_profundidade1(int **matriz, int tam)
{
    int* entregues = (int*)calloc(tam, sizeof(int));
    int i;

    printf("Caminho a ser percorrido \n");
    for (int i = 0; i < tam; i++) 
    {
        if (entregues[i] == 0) 
        {
            printf("Planeta origem %d: ", i);
            entregues = busca_em_profundidade2(matriz, i, entregues, tam);
            printf("\n");
        }
    }
    printf("\n");
}

//Inicio do Programa
int main(int argc, char** argv)
{
    //Variaveis
    int NumPlanetas;
    matriz_adj * adj_main;
    
    
    //Leitura
    //Lendo quantidade de planetas
    printf("Quantidade de Planetas[MAX. 56]\n >");
    scanf("%d", &NumPlanetas);
    getchar();


    //Verificacao de Leitura
    //NumPlanetas <= NENHUM quando NumPlanetas < 0
    //56 == Numero maximo de Planetas
    if (NumPlanetas <= NENHUM || NumPlanetas >= 56)
    {
        printf("** Tamanho invalido, viajante");
        return ERROR;
    }
    
    /*  Arquivos Necessarios - 
    - arquivo entrada: Nome dos Planetas (PlanetasStarWars.txt )*/
	
    //Criando um Grafo com tamanho NumPlanetas
    adj_main->vertices = cria_matriz(adj_main->vertices, NumPlanetas);
    imprime_matriz(adj_main->vertices, NumPlanetas);
    busca_em_profundidade1(adj_main->vertices, NumPlanetas);
    

    //caso tenha ocorrido tudo joia, o programa retorna SUCCESS
	return SUCCESS;
}