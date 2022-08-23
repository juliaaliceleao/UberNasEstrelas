// Junho, 2022
// listas.c - Artur Gonzaga
// Desenvolvimento de Sistemas - COLTEC UFMG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "listas_adj.h"

#define VERDADEIRO 1	// 1 == 1
#define FALSO 0			// !VERDADEIRO
#define ERRO 1

lista_t* lst_cria(){

	return NULL;
}

bool_t lst_vazia (lista_t* lista_p){
	
	if (lista_p == NULL){
		
		return VERDADEIRO;
	}
	else { return FALSO; }
}

lista_t* lst_insere (lista_t* lista_p, int info_p, int ini_p, int fim_p){

	lista_t* novo_elem = (lista_t*) malloc ( sizeof (lista_t) );

	// Caso a alocacao tenha falhada, memoria insuficiente
	if (novo_elem == NULL) return NULL;

	novo_elem->info = info_p;

	novo_elem->peso_ini = ini_p;
	novo_elem->peso_fim = fim_p;

	novo_elem->prox = lista_p;
	
	return novo_elem;
}

// Insere como se fosse uma pilha
lista_t* lst_push(lista_t* lista_p, int info_p, int ini_p, int fim_p) {

	lista_t* lista_aux = lista_p;
	while (lista_aux->prox != NULL) lista_aux = lista_aux->prox;

	lista_t* novo_elem = (lista_t*)malloc(sizeof(lista_t));

	// Caso a alocacao tenha falhada, memoria insuficiente
	if (novo_elem == NULL) return NULL;

	novo_elem->info = info_p;

	novo_elem->peso_ini = ini_p;
	novo_elem->peso_fim = fim_p;

	novo_elem->prox = NULL;

	
	lista_aux->prox = novo_elem;

	return lista_p;

}

lista_t* lst_retira(lista_t* lista_p) {

	if (lst_vazia(lista_p) == VERDADEIRO) return; // Ao retornar para main, pedir para verificar ERRO
	
	lista_t* remover_elem = lista_p;

	lista_p = lista_p->prox;

	free(remover_elem);

	return lista_p;
}

lista_t* lst_retira_objetiva(lista_t* lista_p, int rmv_info) {

	if (lst_vazia(lista_p) == VERDADEIRO) return NULL;

	lista_t* rmv_elem = lista_p;
	lista_t* pre_elem = NULL;

	while ( (rmv_elem->info != rmv_info) && (rmv_elem != NULL) ) {
		pre_elem = rmv_elem;
		rmv_elem = rmv_elem->prox;
	}

	if ( rmv_elem == NULL); // Elemento nao encontrado
	
	if ( pre_elem == NULL ) {

		lista_p = rmv_elem->prox;
	}
	else {

		pre_elem->prox = rmv_elem->prox;
	}

	free(rmv_elem);
	return lista_p;
}

lista_t* lst_busca(lista_t* lista_p, int info_alvo){
	
	lista_t* i_ponteiro;
	
	for (i_ponteiro = lista_p; i_ponteiro != NULL; i_ponteiro = i_ponteiro->prox){
		
		if (i_ponteiro->info == info_alvo){
			
			return i_ponteiro;
		}
	}

	return NULL;
}

void lst_imprime(lista_t* lista_p){
	
	lista_t* i_ponteiro;
	
	for (i_ponteiro = lista_p; i_ponteiro != NULL; i_ponteiro = i_ponteiro->prox){
		
		printf("\t%d\n",i_ponteiro->info);
	}

	free(i_ponteiro);
}

void lst_libera(lista_t* lista_p) {

	lista_t* i_ponteiro = lista_p;

	while (i_ponteiro != NULL) {
		
		lista_t* temp = i_ponteiro->prox;
		free(i_ponteiro);
		i_ponteiro = temp;
	}
}
