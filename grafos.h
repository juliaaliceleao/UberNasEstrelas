// Agosto, 2022
// grafos.h - Artur Gonzaga
// Desenvolvimento de Sistemas - COLTEC UFMG

// Bibliotecas
#include <stdint.h>
#include "listas_adj.h"
#include "tree_var.h"


typedef uint8_t bool;

typedef struct grafo_s {

	lista_t* vtx_adj;
	struct grafo_s* next;
} grafo;

typedef struct guia_busca {

    int** matriz;
    lista_t* Q;

} guia;


grafo* grafo_cria(int n_vtx); 

grafo* grafo_insere_vtx(grafo* grafo_p, lista_t* valores); 

grafo* grafo_busca_vtx(grafo* grafo_p, int vtx_p); 

lista_t* grafo_busca_no_vtx(grafo* grafo_p, int vtx_p, int info_p);

grafo* grafo_insere_adj(grafo* grafo_p, int vtx_p, int info_p); 

int grafo_obter_grau(grafo* grafo_p, int vtx_p);

void grafo_nao_ordenado(grafo* grafo_p, int vtx_a, int vtx_b);

void grafo_imprime(grafo* grafo_p);

void grafo_libera(grafo* grafo_p); 

guia* guia_cria (grafo* grafo_p, int n_vtx, int fonte_s);

void guia_imprime(guia* guia_p, int n_vtx);

void guia_libera (guia* guia_p);

tree_var* grafo_bfs (grafo* grafo_p, guia* guia_p, int n_vtx);