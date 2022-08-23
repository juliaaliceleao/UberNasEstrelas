#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR 0
#define NENHUM 0

//struct da GALAXIA (MATRIZ DE ADJACENCIAS)
struct matriz_adjacencia
{
    struct Planeta ** Planetas;
    int ** h_ini; 
    int ** h_fim; 
    int ** peso;
    
};
typedef struct matriz_adjacencia Galaxia;

//struct para cada planeta
struct Planeta
{
    int vertices;       //informacao do vertice
    int * arestas;
    int RestricaoTempo; //restricao de tempo de um determinado planeta
};
typedef struct Planeta Planeta;



/*  FUNCAO QUE CRIA OS PLANETAS(Vertices) e espaço para armazenar 
    uma matriz de adjacencias sobre cada um
    - retorno: um ponteiro para eles
    - parametro: 
                 * ponteiro para a matriz do tipo struct Planeta (PlanetasP)
                 * numero de planetas(NumPlanetas) 
*/

int ** criaPlanetas(Planeta ** PlanetasP, int NumPlanetas)
{
    //Aloca espaco p/ NumPlanetas(Vertices)
    PlanetasP = (Planeta ** )calloc(NumPlanetas, sizeof(Planeta * ));
    
    for (int i = 0; i < NumPlanetas; i++)
    { PlanetasP[i].vertices = i+1; } //armazena a informacao de cada vertice

    return PlanetasP;
}


/*  FUNCAO QUE CRIA ARESTAS(Vertices) preenchendo uma matriz de adjacencias
    parametro: ponteiro para a matriz do tipo struct Planeta (PlanetasP)
               e o numero de planetas(NumPlanetas) */
               
void criaCaminhosAleatorio(Planeta ** PlanetasP, int NumPlanetas)
{
    //Aloca espaco p/ Adjacencias(arestas) dos Planetas(Vertices)
    for (int i = 0; i < NumPlanetas; i++)
    { PlanetasP[i].arestas = (Planeta *)calloc(NumPlanetas, sizeof(Planeta)); }

    /*Insercao das Arestas em uma matriz de adjacencias*/
    int resposta = 1;
    
    //Leitura Arestas
    for(int i = 0; i < NumVertices; i++)
    { 
        Planetas[i].arestas = (int *) malloc(sizeof(int) * NumVertices);
    }
    
    //Inserindo as Arestas - inserção aleatoria 
    for(int i = 0; i < NumVertices; i++)
    {
        for(int j = 0; j < NumVertices; j++)
        {
            resposta = resposta * (-1);
                
            if(resposta == 1)
            {
                /*insercao do elemento na lista de adjacencias 
                dos dois vertice pois o grafo nao e orientado*/
                Grafo[i].arestas[j] = 1;
            }
        }
    }
}
    //Cria Arestas
    do
    {
        cont++;
        int PlanetaSource = 0;
        int PlanetaDestino = 0;
        
        printf("Digite o Numero do Planeta: ");
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
int main (int argc, char** argv)
{
    //Variaveis
    int NumPlanetas;
    matriz_adj * adj_main;
    
    
    //Leitura
    //Lendo quantidade de planetas
    printf("Quantidade de Planetas[MAX. 56]\n >");
    scanf(" %d", &NumPlanetas);

    //Verificacao de Leitura
    //NumPlanetas <= NENHUM quando NumPlanetas < 0
    //56 == Numero maximo de Planetas
    if (NumPlanetas <= NENHUM || NumPlanetas >= 56)
    {
        printf("** Tamanho invalido, viajante");
        return ERROR;
    }
    
    //Criando um Grafo com tamanho NumPlanetas
    adj_main->Planetas = criaPlanetas(adj_main->Planetas, NumPlanetas);
    
    criaCaminhosAleatorio(adj_main->Planetas, NumPlanetas);
    
    imprime_matriz(adj_main->Planetas, NumPlanetas);
    busca_em_profundidade1(adj_main->Planetas, NumPlanetas);
    
    //caso tenha ocorrido tudo joia, o programa retorna SUCCESS
	return SUCCESS;
}