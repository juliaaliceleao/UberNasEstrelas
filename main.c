// Agosto, 2022
// 
// Projeto: Viajando por uma galáxia muito muito distante
// 
// Alunos:	Artur Gonzaga, Guilherme Luiz, Julia Leão
// Profa.:	Virgínia Mota
// 
// Desenvolvimento de Sistemas - COLTEC UFMG

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

// Constantes
#define VERDADEIRO 1	// 1 == 1
#define FALSO 0			// !VERDADEIRO

#define SUCESSO 0

// Siglas dos planetas

#define T 84	// Tatooine 
#define H 72	// Hoth
#define E 69	// Endor
#define C 67	// Coruscant
#define B 66	// Bespin
#define A 65	// Alderaan


// Variáveis constantes do computador de bordo da nave

#define PLT 0	// Planetas
#define TMP 1	// Tempo de viagem

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* CÁLCULOS DO COMPUTADOR DE BORDO DA NAVE */


// O computador de bordo tem horario correnpondente ao ciclo de 24 horas
int regula_hora(int hora_p) {

	if (hora_p > 24) {

		
		do { hora_p -= 24; } while (hora_p > 24);
	}

	return hora_p;
}

int percorre_geracao(tree_var* tree_p, treeV_lst* lst_tree, lista_t* checklist, grafo* descricao_plt, lista_t* gen, int* plt_destino, int hora_atual) {

	int tmp_trajeto = 0;
	int tmp_descarga = 1;


	for (tree_var* tree_pointer = tree_p; tree_pointer != NULL; tree_pointer = tree_pointer->bro) {

		if (tree_pointer->son != NULL) {

			lst_tree = treeV_lst_insere(lst_tree, tree_pointer->son);
			gen = lst_push(gen, gen->info + 1, 0, 0);
		}

		if (lst_busca( checklist, tree_pointer->info) != NULL) {

			tmp_trajeto = gen->info + tmp_descarga;

			descricao_plt = grafo_busca_vtx(descricao_plt, tree_pointer->info);
			int horario_ini = descricao_plt->vtx_adj->peso_ini;
			int horario_fim = descricao_plt->vtx_adj->peso_fim;

			if (horario_ini < 12 && hora_atual >= 12) {

				tmp_trajeto += (24 - hora_atual) + horario_ini;

			}

			else if (hora_atual + tmp_trajeto < horario_ini) {

				// Incrementa tempo de aguardo para entrar no planeta
				tmp_trajeto += horario_ini - (hora_atual + gen->info);
			}

			// Tem mais alguma coisa ?

			if (tmp_trajeto < plt_destino[TMP]) {

				plt_destino[PLT] = tree_pointer->info;
				plt_destino[TMP] = tmp_trajeto;
			}

		}
	}
	return plt_destino;
}


void encontre_prox_planeta (grafo* rotas_hpe,  lista_t* checklist_planetas, int n_planetas, int planeta_atual, int hora_atual, int hora_total) {

	hora_atual = regula_hora(hora_atual);

	guia* guia_HDR = guia_cria(rotas_hpe, n_planetas, planeta_atual);
	tree_var* tree_HDR = grafo_bfs(rotas_hpe, guia_HDR, n_planetas);

	treeV_lst* ramos_to_go = treeV_lst_cria();
	ramos_to_go = treeV_lst_insere(ramos_to_go,tree_HDR);

	lista_t* gen = lst_cria(); // Gen de geracao (generation)
	gen = lst_insere(gen, 0, 0, 0);
	

	int* plt_destino = (int*) malloc (sizeof(int) * 2);

	// Testa alocacao
	if (plt_destino == NULL) {

		printf("Falha ao alocar memoria");
		return;
	}

	plt_destino[PLT] = planeta_atual;
	plt_destino[TMP] = 1000;

	while (ramos_to_go != NULL) {

		percorre_geracao(ramos_to_go->endereco_tree, ramos_to_go, checklist_planetas, rotas_hpe, gen, plt_destino, hora_atual);

		ramos_to_go = treeV_lst_remove(ramos_to_go);
		gen = lst_retira(gen);
	}
	
	hora_total += plt_destino[TMP];

	hora_atual += plt_destino[TMP];
	hora_atual = regula_hora(hora_atual);
	
	planeta_atual = plt_destino[PLT];

	printf(">>  Clones entregues em %c em %02d:00\n", plt_destino[PLT], hora_atual);
	
	tree_var_libera(tree_HDR);
	treeV_lst_libera(ramos_to_go);
	guia_libera(guia_HDR);
	lst_libera(gen);

	checklist_planetas = lst_retira_objetiva(checklist_planetas, plt_destino[PLT]);

	if (checklist_planetas != NULL) {

		free(plt_destino);

		encontre_prox_planeta(rotas_hpe, checklist_planetas, n_planetas, planeta_atual, hora_atual, hora_total);
	}
	else printf("\n!! Entregas concluidas em %d horas\n", hora_total);

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// main
int main (int argc, char** argv){

	int n_planetas = 6;

	lista_t* lst_planetas = lst_cria();
	grafo* rotas_hiperespaciais = grafo_cria(n_planetas);

	// Planetas e seus horarios de comercio
	lst_planetas = lst_insere(lst_planetas, T, 12, 18);		// Tatooine		entre 12 - 18h tem trafego liberado
	lst_planetas = lst_insere(lst_planetas, H, 21, 5);		// Hoth			entre 21 - 05h tem trafego liberado
	lst_planetas = lst_insere(lst_planetas, E, 9, 13);		// Endor		entre 09 - 13h tem trafego liberado
	lst_planetas = lst_insere(lst_planetas, C, 6, 10);		// Coruscant	entre 06 - 10h tem trafego liberado
	lst_planetas = lst_insere(lst_planetas, B, 2, 6);		// Bespin		entre 02 - 06h tem trafego liberado
	lst_planetas = lst_insere(lst_planetas, A, 16, 19);		// Alderaan		entre 16 - 19h tem trafego liberado

	rotas_hiperespaciais = grafo_insere_vtx(rotas_hiperespaciais, lst_planetas);

	grafo_nao_ordenado(rotas_hiperespaciais, T, C);

	grafo_nao_ordenado(rotas_hiperespaciais, C, H);

	grafo_nao_ordenado(rotas_hiperespaciais, A, B);
	grafo_nao_ordenado(rotas_hiperespaciais, A, C);
	grafo_nao_ordenado(rotas_hiperespaciais, A, H);

	grafo_nao_ordenado(rotas_hiperespaciais, E, H);

	grafo_imprime(rotas_hiperespaciais);
	printf("\n");


	// Apos localizar todas as rotas do hiperespaço entre todos os planetas a serem vizitados,
	// o computador de bordo passa a tracar rotas para as entregar dos clones. 

	// Defina o hora atual
	int hora_atual = 22;

	// Defina o hora total
	int hora_total = 0;

	// Defina o planeta de origem
	int plt_origem = B;

	encontre_prox_planeta(rotas_hiperespaciais, lst_planetas, n_planetas, plt_origem, hora_atual, hora_total);

	grafo_libera(rotas_hiperespaciais);

	return SUCESSO;
}
