// Agosto, 2022
// grafos.c - Artur Gonzaga
// Desenvolvimento de Sistemas - COLTEC UFMG

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

#define VERDADEIRO 1 // 1 == 1
#define FALSO 0 // !VERDADEIRO

#define K 1
#define P 2
#define C 3
#define VTX 0 // Linha dos vertices na matriz de guia
#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define GUIA_N_LINHAS 4


grafo* grafo_cria(int n_vtx) {

	grafo* grafo_aux = (grafo*) malloc(sizeof(grafo));
	grafo_aux->vtx_adj = lst_cria();
	
	if (n_vtx > 1) {

		n_vtx--;
		grafo_aux->next = grafo_cria (n_vtx);
	}
	else grafo_aux->next = NULL;

	return grafo_aux;
}

grafo* grafo_insere_vtx (grafo* grafo_p,lista_t* valores) {

	if (grafo_p->next != NULL) {

		grafo_p->next = grafo_insere_vtx(grafo_p->next, valores->prox);
	}

	grafo_p->vtx_adj = lst_insere(grafo_p->vtx_adj, valores->info, valores->peso_ini,valores->peso_fim);
	valores = valores->prox;

	return grafo_p;
}

grafo* grafo_busca_vtx(grafo* grafo_p, int vtx_p) {

	grafo* i_pointer = grafo_p;

	while ((i_pointer->vtx_adj->info != vtx_p) && (i_pointer != NULL) ) {

		i_pointer = i_pointer->next;
	}
	
	if (i_pointer == NULL) printf ("Vertex %c inextistente", vtx_p);

	return i_pointer;
}

lista_t* grafo_busca_no_vtx(grafo* grafo_p, int vtx_p, int info_p) {

	if (grafo_busca_vtx(grafo_p, vtx_p) == NULL) return NULL;
	
	grafo* i_pointer = grafo_busca_vtx (grafo_p, vtx_p);
	lista_t* lista_aux = i_pointer->vtx_adj->prox;

	while ( lista_aux != NULL ) {

		if (lista_aux->info == info_p) return lista_aux;

		lista_aux = lista_aux->prox;
	}
	
	// se chegou aqui,
	// info_p nao encontrada no vertice vtx_p
	return NULL;
}

grafo* grafo_insere_adj(grafo* grafo_p, int vtx, int adj) {

	if (grafo_busca_vtx(grafo_p, vtx) != NULL) {

		grafo* grafo_aux = grafo_busca_vtx(grafo_p, vtx);
		grafo* grafo_sec = grafo_busca_vtx(grafo_p, adj);

		grafo_aux->vtx_adj = lst_push(grafo_aux->vtx_adj, adj, grafo_sec->vtx_adj->peso_ini, grafo_sec->vtx_adj->peso_fim);
	}

	return grafo_p;
}

int grafo_obter_grau(grafo* grafo_p, int vtx_p) {

	int grau = 0;
	grafo* i_pointer = grafo_busca_vtx(grafo_p, vtx_p);
	lista_t* lista_aux = i_pointer->vtx_adj->prox;

	while (lista_aux != NULL) {

		grau++;
		lista_aux = lista_aux->prox;
	}
	return grau;
}

void grafo_nao_ordenado(grafo* grafo_p, int vtx_a, int vtx_b) {

	grafo_p = grafo_insere_adj(grafo_p, vtx_a, vtx_b);
	grafo_p = grafo_insere_adj(grafo_p, vtx_b, vtx_a);
}

void grafo_imprime(grafo* grafo_p) {

	grafo* i_pointer = grafo_p;
	grafo* j_pointer;

	printf("    ");

	while (i_pointer != NULL) {

		printf("%c   ", i_pointer->vtx_adj->info);
		i_pointer = i_pointer->next;
	}

	i_pointer = grafo_p;

	while (i_pointer != NULL) {

		printf("\n%c   ", i_pointer->vtx_adj->info);
		
		j_pointer = grafo_p;

		while (j_pointer != NULL) {

			if (lst_busca(i_pointer->vtx_adj->prox, j_pointer->vtx_adj->info) != NULL) {

				printf("1   ");
			}
			
			else printf("0   ");

			j_pointer = j_pointer->next;
		}

		i_pointer = i_pointer->next;
	}

	printf("\n");
}


void grafo_libera(grafo* grafo_p) {

	grafo* i_pointer = grafo_p;

	while (i_pointer != NULL) {

		grafo* tmp = i_pointer->next;

		lst_libera(i_pointer->vtx_adj);
		free(i_pointer);

		i_pointer = tmp;
	}
}

/* Funcoes para busca em grafos */

guia* guia_cria (grafo* grafo_p, int n_vtx, int fonte_s ) {

	int n_colunas = n_vtx + 1;
    guia* guia_aux = (guia*) malloc (sizeof (guia));

    guia_aux->matriz = (int**) calloc ( GUIA_N_LINHAS, sizeof(int*)); // Aloca linhas
    
    for (int i = 0; i < GUIA_N_LINHAS; i++){

        guia_aux->matriz[i] = (int*) calloc ( n_colunas, sizeof(int)); // Aloca colunas
    }
    
    guia_aux->Q = lst_cria();

    guia_aux->matriz[K][0] = 107;   // k, distancia da fonte_s
    guia_aux->matriz[P][0] = 112;   // p, pai da arvore de descoberta (eh o PI)
    guia_aux->matriz[C][0] = 99;    // c, cor do vertice (0 = branco, 1 = cinza, 2 = preto)

	for (int j = 1; j <= n_vtx ; j++)  guia_aux->matriz[2][j] = 63;		// pais desconhecidos inicialmente


    guia_aux->matriz[VTX][0] = fonte_s;	// [0][0] eh a posicao da fonte_s	
    grafo* i_pointer = grafo_p;

    for (int i = 1; i < n_colunas; i++) {

        guia_aux->matriz[VTX][i] = i_pointer->vtx_adj->info;
        i_pointer = i_pointer->next;
    }

    return guia_aux;
}

void guia_imprime(guia* guia_p, int n_vtx) {


	for (int i = 0; i < GUIA_N_LINHAS; i++) {

		for (int j = 0; j < n_vtx + 1; j++) {

			switch (i) {

				case 0:
						
									
					if (j == 0)  {
						
						printf("    ");

					}
					else if (guia_p->matriz[i][j] == guia_p->matriz[0][0]) {

						printf("\033[0;32m"); // Deixa saida de texto verde
						printf("%c   ", guia_p->matriz[i][j]);
						printf("\033[0;37m"); // Volta a deixar saida de texto branca
					}
					else printf("%c   ", guia_p->matriz[i][j]);

				break;
				
				case 2:

					if (j == 0) {

						printf("\033[1;33m"); // Deixa saida de texto amarela
						printf("%c   ", guia_p->matriz[i][j]);
						printf("\033[0;37m"); // Volta a deixar saida de texto branca
					}
					else printf("%c   ", guia_p->matriz[i][j]);

				break;

				default:

					if (j == 0) {

						printf("\033[1;33m"); // Deixa saida de texto amarela
						printf("%c   ", guia_p->matriz[i][j]);
						printf("\033[0;37m"); // Volta a deixar saida de texto branca
					}
					else printf("%d   ", guia_p->matriz[i][j]);

				break; 

			}
		}
		printf("\n");
	}
	printf("\n");
}


void guia_libera (guia* guia_p) {

	for (int i = 0; i < GUIA_N_LINHAS; i++) {

		free(guia_p->matriz[i]);
	}

	free(guia_p->matriz);
	lst_libera (guia_p->Q);

	free(guia_p);
}


int guia_obtem_coluna (guia* guia_p, int info_p) {

	int i;
	for ( i = 1; guia_p->matriz [VTX][i] != info_p ; i++);

	return i;
}

int guia_obtem_cor (guia* guia_p, int info_p) {

	int coluna = guia_obtem_coluna (guia_p, info_p);

	return guia_p->matriz[C][coluna];
}

void guia_atualiza (grafo* grafo_p, guia* guia_p, int coluna_p) {


	for (lista_t* j_pointer = grafo_p->vtx_adj->prox; j_pointer != NULL; j_pointer = j_pointer->prox) {

		// Evita que se tenha elementos repetidos em Q
		if ( (lst_busca(guia_p->Q, j_pointer->info) == NULL) && (guia_obtem_cor(guia_p, j_pointer->info) != PRETO) ){ 
		 
			// Se chegou aqui, insere na lista Q e atualiza guia
			guia_p->Q = lst_insere (guia_p->Q, j_pointer->info, j_pointer->peso_ini, j_pointer->peso_fim);	

			int coluna_aux = guia_obtem_coluna (guia_p, j_pointer->info);

			// Set distacia da fonte
			guia_p->matriz[K][coluna_aux] = guia_p->matriz[K][coluna_p] + 1;
			// Set pai da arvore de descoberta
			guia_p->matriz[P][coluna_aux] = grafo_p->vtx_adj->info;
			// Set cor
			guia_p->matriz[C][coluna_aux] ++;

		}
	}
}

void guia_atualiza_arv(guia* guia_p, tree_var* tree_p, grafo* grafo_p, int n_vtx, int fonte_s) {

	guia* guia_aux = guia_p;

	for (int i = 1; i <= n_vtx; i++) {

		if (guia_aux->matriz[P][i] == fonte_s) {

			tree_p = tree_var_add_son(tree_p, guia_aux->matriz[VTX][i]);

			// Reaproveitamento da lista Q
			if ( lst_busca(guia_aux->Q, guia_aux->matriz[VTX][i]) == NULL) { 

				grafo* grafo_aux = grafo_busca_vtx(grafo_p, guia_aux->matriz[VTX][i]);
				guia_aux->Q = lst_insere(guia_aux->Q,grafo_aux->vtx_adj->info, grafo_aux->vtx_adj->peso_ini, grafo_aux->vtx_adj->peso_fim);
			}
		} 
	}
}

void guia_preenche_arvore (tree_var* tree_origem, treeV_lst* lst_tree, guia* guia_p,grafo* grafo_p, int n_vtx) {

	for (tree_var* tree_pointer = tree_origem->son; tree_pointer != NULL; tree_pointer = tree_pointer->son) {

		int tmp_source = guia_p->Q->info;

		if (tree_pointer->info != tmp_source && tree_pointer->bro != NULL ) {

			for (tree_var* aux = tree_pointer->bro; aux != NULL; aux = aux->bro) {

				if (lst_busca(guia_p->Q, aux->info) != NULL) {

					int aux_source = aux->info;

					guia_atualiza_arv(guia_p, aux, grafo_p, n_vtx, aux_source);
					guia_p->Q = lst_retira_objetiva(guia_p->Q, aux_source);

					lst_tree = treeV_lst_insere(lst_tree, aux);
				}
			}
		}

		if (lst_busca(guia_p->Q, tree_pointer->info) != NULL) {

			tmp_source = tree_pointer->info;

			guia_atualiza_arv(guia_p, tree_pointer, grafo_p, n_vtx, tmp_source);
			guia_p->Q = lst_retira_objetiva(guia_p->Q, tmp_source);

			lst_tree = treeV_lst_insere(lst_tree, tree_pointer);
		}
	}
}

tree_var* grafo_bfs (grafo* grafo_p, guia* guia_p, int n_vtx) {

	int coluna = 0;
	int coluna_aux = 0;
	int fonte_s = guia_p->matriz[VTX][0];

	grafo* i_pointer = grafo_busca_vtx (grafo_p, fonte_s);
	coluna = guia_obtem_coluna (guia_p, i_pointer->vtx_adj->info);

	guia_atualiza (i_pointer, guia_p, coluna);
	
	guia_p->matriz[C][coluna] = PRETO; // Raiz preta, raiz concluida

	while ( guia_p->Q != NULL ) {

		i_pointer = grafo_busca_vtx (grafo_p, guia_p->Q->info);
		coluna = guia_obtem_coluna (guia_p, i_pointer->vtx_adj->info);

		guia_atualiza (i_pointer, guia_p, coluna);
	
		guia_p->matriz[C][coluna]++;
		guia_p->Q = lst_retira_objetiva (guia_p->Q, i_pointer->vtx_adj->info);
	}

	// Desenvolve arvore de descoberta

	tree_var* tree_descoberta = tree_var_cria();
	tree_descoberta = tree_var_preenche (fonte_s);

	treeV_lst* tree_pendentes = treeV_lst_cria();

	// Estabelece raiz da arvore
	guia_atualiza_arv(guia_p, tree_descoberta, grafo_p, n_vtx, fonte_s);

	tree_pendentes = treeV_lst_insere(tree_pendentes, tree_descoberta);

	while (tree_pendentes != NULL && guia_p->Q != NULL) {

		guia_preenche_arvore(tree_pendentes->endereco_tree, tree_pendentes, guia_p, grafo_p, n_vtx);
		tree_pendentes = treeV_lst_remove(tree_pendentes);
	}

	treeV_lst_libera(tree_pendentes);
	return tree_descoberta;
}