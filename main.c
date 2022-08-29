// Agosto, 2022
// 
// Projeto: Viajando por uma galáxia muito muito distante
// 
// Alunos:	Artur Gonzaga, Guilherme Luiz, Julia Leão
// Profa.:	Virginia Mota
// 
// Desenvolvimento de Sistemas - COLTEC UFMG

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafos.h"

// Constantes
#define VERDADEIRO 1	// 1 == 1
#define FALSO 0			// !VERDADEIRO

#define ERROR 0
#define NENHUM 0

#define TAM_MAX 100 + 1

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

	if (hora_p >= 24) {

		
		do { hora_p -= 24; } while (hora_p >= 24);
	}

	return hora_p;
}

char* descreve_planeta(int num_planeta) {

	char* nome_planeta = (char*)calloc(TAM_MAX, sizeof(char));
	FILE* entrada = fopen("PlanetasStarWars.txt", "r");

	if (entrada == NULL) {

		printf("Erro ao abrir arquivo.");
		return ERROR;
	}

	char test = 'a';

	//fseek(entrada, 0, SEEK_SET);


	for (int i = num_planeta; i > 0; i--) {

		do {

			test = getc(entrada);
		} while (test != '\n');
	}

	if (feof(entrada)) nome_planeta = "Planeta desconhecido";

	else {

		int j = 0;
		test = getc(entrada);
		while (test != '\n') {

			nome_planeta[j] = test;
			test = getc(entrada);
			j++;
		}

	}

	fclose(entrada);
	return nome_planeta;
}


void percorre_geracao(tree_var* tree_p, treeV_lst* lst_tree, lista_t* checklist, grafo* descricao_plt, lista_t* gen, int* plt_destino, int hora_atual) {

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

			int chegada = hora_atual + gen->info;
			chegada = regula_hora(chegada);

			if (hora_atual > horario_ini) {


				// Quer dizer que a entrega ocorrera no proximo ciclo de 24h
				if (chegada != 0) {
					tmp_trajeto += (24 - hora_atual) + horario_ini;
				}
				else tmp_trajeto += horario_ini;
			}

			else if (chegada < horario_ini) {

				// Incrementa tempo de aguardo para entrar no planeta
				tmp_trajeto += (horario_ini - chegada);
			}

			// Tem mais alguma coisa ?

			if (tmp_trajeto < plt_destino[TMP]) {

				plt_destino[PLT] = tree_pointer->info;
				plt_destino[TMP] = tmp_trajeto;
			}

		}
	}
}

void encontre_prox_planeta (grafo* rotas_hpe,  lista_t* checklist_planetas, int n_planetas, int planeta_atual, int hora_atual, int hora_total,int origem) {

	hora_atual = regula_hora(hora_atual);

	guia* guia_HDR = guia_cria(rotas_hpe, n_planetas, planeta_atual);
	tree_var* tree_HDR = grafo_bfs(rotas_hpe, guia_HDR, n_planetas);

	treeV_lst* ramos_to_go = treeV_lst_cria();
	ramos_to_go = treeV_lst_insere(ramos_to_go,tree_HDR);

	lista_t* gen = lst_cria(); // Gen de geracao (generation)
	gen = lst_insere(gen, 0, 0, 0);
	
	char* plt_destino_nome;

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

	plt_destino_nome = descreve_planeta(plt_destino[PLT]);
	printf("\n> \033[1;35m%02d:00\033[0;37m, clones entregues em \033[0;33m%s\033[0;37m", hora_atual, plt_destino_nome);
	
	checklist_planetas = lst_retira_objetiva(checklist_planetas, plt_destino[PLT]);

	treeV_lst_libera(ramos_to_go);
	tree_var_libera(tree_HDR);
	guia_libera(guia_HDR);
	lst_libera(gen);
	free(plt_destino_nome);
	free(plt_destino);

	if (checklist_planetas != NULL) {

		encontre_prox_planeta(rotas_hpe, checklist_planetas, n_planetas, planeta_atual, hora_atual, hora_total, origem);
	}
	else {

		printf("\n\n\033[0;32m!! Entregas concluidas em %d horas\033[0;37m\n", hora_total);

		printf("\n>> Retorno para o planeta de origem...\n");

		checklist_planetas = lst_insere(checklist_planetas, origem, 0, 0);

		guia* guia_NEW = guia_cria(rotas_hpe, n_planetas, planeta_atual);
		tree_var* tree_FINAL = grafo_bfs(rotas_hpe, guia_NEW, n_planetas);

		treeV_lst* ramos_to_final = treeV_lst_cria();
		ramos_to_final = treeV_lst_insere(ramos_to_final,tree_FINAL);

		lista_t* new_gen = lst_cria(); // Gen de geracao (new_generation)
		new_gen = lst_insere(new_gen, 0, 0, 0);
		

		int* plt_home = (int*) malloc (sizeof(int) * 2);

		// Testa alocacao
		if (plt_home == NULL) {

			printf("Falha ao alocar memoria");
			return;
		}

		plt_home[PLT] = planeta_atual;
		plt_home[TMP] = 1000;

		while (ramos_to_final != NULL) {

			percorre_geracao(ramos_to_final->endereco_tree, ramos_to_final, checklist_planetas, rotas_hpe, new_gen, plt_home, hora_atual);

			ramos_to_final = treeV_lst_remove(ramos_to_final);
			new_gen = lst_retira(new_gen);
		}
		
		plt_home[TMP] --;	// Nao precisa entregar os clones, entao nao ha mais tempo de descarga

		hora_total += plt_home[TMP];

		hora_atual += plt_home[TMP];
		hora_atual = regula_hora(hora_atual);
		
		planeta_atual = plt_home[PLT];

		checklist_planetas = lst_retira_objetiva(checklist_planetas, plt_home[PLT]);

		printf("\n\033[0;32m!! Chegada ao planeta de origem %cs %02d:00, tempo total da viagem: %d horas.\033[0;37m\n\n\n", 133, hora_atual, hora_total);

		treeV_lst_libera(ramos_to_final);
		tree_var_libera(tree_FINAL);
		guia_libera(guia_NEW);
		lst_libera(new_gen);
		free(plt_home);

	}
}
void grafo_imprime_int(grafo* grafo_p) {

	grafo* i_pointer = grafo_p;
	grafo* j_pointer;

	printf("    ");
	printf("\033[1;36m");	// saida verde

	while (i_pointer != NULL) {

		printf("%02d  ", i_pointer->vtx_adj->info);
		i_pointer = i_pointer->next;
	}

	printf("\033[0;37m");	// saida branca

	i_pointer = grafo_p;

	while (i_pointer != NULL) {

		printf("\033[1;36m");	// saida verde
		printf("\n%02d  ", i_pointer->vtx_adj->info);
		printf("\033[0;37m");	// saida branca
		
		j_pointer = grafo_p;

		while (j_pointer != NULL) {

			if (lst_busca(i_pointer->vtx_adj->prox, j_pointer->vtx_adj->info) != NULL) {

				printf("\033[1;34m");	// saida amarela
				printf("01  ");
				printf("\033[0;37m");	// saida branca
			}
			
			else {

				printf("00  ");
			
			}
			j_pointer = j_pointer->next;
		}

		i_pointer = i_pointer->next;
	}

	printf("\n");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void ascii_art() {


	char nave[101];
	FILE* entradapre = fopen("ascii_art.txt", "r");
	while (!feof(entradapre))
	{
		fgets(nave, 100, entradapre);
		printf("%s", nave);
	}
	fclose(entradapre);
	printf("\n \n");

}

// main
int main (int argc, char** argv){

	// Configura funcoes aleatorias 
	srand((unsigned)time(NULL));

	// Imprime ascii art
	printf("\033[1;35m"); // saida roxa
	ascii_art();
	printf("\033[0;37m"); // saida branca


	int n_planetas = 0;
	lista_t* lst_planetas = lst_cria();

	//Leitura
	printf("Quantidade de planetas [MAX. 55]\n> ");

	printf("\033[1;33m");
	scanf (" %d", &n_planetas);
	getchar();
	printf("\033[0;37m");
	grafo* rotas_hiperespaciais = grafo_cria(n_planetas);

	//Verificacao de Leitura
	//NumPlanetas <= NENHUM quando NumPlanetas < 0
	//56 == Numero maximo de Planetas
	if (n_planetas <= NENHUM || n_planetas > 55)
	{
		printf("\n\033[1;31m** Tamanho invalido, viajante\033[0;37m\n");
		return ERROR;
	}


	for (int i = 0; i < n_planetas; i++) {

		int hora_ini, hora_fim;
		char* nome_plt = descreve_planeta(i);
		
		hora_ini = rand()%24;

		do {

			hora_fim = rand() % 6;
		} while (hora_fim == 0);

		hora_fim = hora_ini + hora_fim;
		hora_fim = regula_hora(hora_fim);

		lst_planetas = lst_insere(lst_planetas, i, hora_ini, hora_fim);

		printf("\nPlaneta %02d: \033[0;33m%s\033[0;37m\n> Aberto entre \033[0;32m%02d:00\033[0;37m e \033[1;31m%02d:00\033[0;37m\n", i, nome_plt, hora_ini, hora_fim);
	}

	rotas_hiperespaciais = grafo_insere_vtx(rotas_hiperespaciais, lst_planetas);

	for (grafo* aux_pointer = rotas_hiperespaciais; aux_pointer != NULL; aux_pointer = aux_pointer->next) {


		int n_relacoes = rand() % n_planetas;

		for (int i = 1; i <= n_relacoes; i++) {

			int plt = aux_pointer->vtx_adj->info;

			int n_adj = 0;
			for (lista_t* aux_lst = aux_pointer->vtx_adj; aux_lst != NULL; aux_lst = aux_lst->prox) n_adj++;

			if (n_adj < n_planetas) {

				while (lst_busca(aux_pointer->vtx_adj, plt) != NULL) {

					plt = rand() % n_planetas;
				}

				grafo_nao_ordenado(rotas_hiperespaciais, aux_pointer->vtx_adj->info, plt);
			}
		}

	}
	printf("\n");
	grafo_imprime_int(rotas_hiperespaciais);
	printf("\n");


	// Apos localizar todas as rotas do hiperespaço entre todos os planetas a serem vizitados,
	// o computador de bordo passa a tracar rotas para as entregar dos clones. 

	// Defina o hora atual
	int hora_atual = rand()%25;
	hora_atual = regula_hora(hora_atual);

	// Defina o hora total
	int hora_total = 0;

	// Defina o planeta de origem
	int plt_origem = rand()%n_planetas;

	char* nome_plt_origem = descreve_planeta(plt_origem);
	printf("\n> \033[1;35m%02d:00\033[0;37m, nave inicia o trajeto em \033[0;33m%s\033[0;37m\n\n", hora_atual, nome_plt_origem);
	free(nome_plt_origem);

	encontre_prox_planeta(rotas_hiperespaciais, lst_planetas, n_planetas, plt_origem, hora_atual, hora_total, plt_origem);

	grafo_libera(rotas_hiperespaciais);

	return SUCESSO;
}
