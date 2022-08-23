// Agosto, 2022
// tree_var.c - Artur Gonzaga
// Desenvolvimento de Sistemas - COLTEC UFMG

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include "tree_var.h"


#define VERDADEIRO 1 // (1 == 1)
#define FALSO 0 // !VERDADEIRO

tree_var* tree_var_cria (void) { 

	return NULL; 
}

bool tree_var_vazia ( tree_var* tree_p ) {

	if (tree_p == NULL) return VERDADEIRO;	
	else return FALSO;
}

tree_var* tree_var_preenche (int info_p) {

	// Aloca
	tree_var* tree_aux = (tree_var*) malloc (sizeof (tree_var));

	// Erro ao alocar arvore
	if (tree_aux == NULL) return NULL;

	// Preenche
	tree_aux->info = info_p;
	tree_aux->bro = NULL;
	tree_aux->son = NULL;

	return tree_aux;
}

tree_var* tree_var_busca (tree_var* tree_p, int info_p ) {

	tree_var* i_pointer = tree_p;
	
	if (i_pointer == NULL) {

		return NULL; // Elemento nao encontrado
	}

	
	if (i_pointer->info != info_p ) { 

		if (i_pointer->bro != NULL) {
			
			tree_var_busca (i_pointer->bro, info_p);	
		}


		if (i_pointer->son != NULL) {
			
			tree_var_busca (i_pointer->son, info_p);	
		}
	}

	return i_pointer;
}

tree_var* tree_var_add_bro ( tree_var* tree_p, int info_p) {

	tree_var* i_pointer = tree_p;
	
	if (tree_var_vazia (i_pointer) == VERDADEIRO ) {

		i_pointer = tree_var_preenche(info_p);
		
		return i_pointer;
	}

	else {
	
		while (i_pointer->bro != NULL) i_pointer = i_pointer->bro;

		tree_var* tree_aux = tree_var_preenche (info_p);

		i_pointer->bro = tree_aux;
	}
	
	return tree_p;
}

tree_var* tree_var_add_son ( tree_var* tree_p, int info_p) {

	tree_var* i_pointer = tree_p;
	
	if (tree_var_vazia (i_pointer) == VERDADEIRO ) {

		i_pointer = tree_var_preenche (info_p);
		return i_pointer;
	}
	
	
	if (tree_var_vazia (i_pointer->son) == VERDADEIRO ) {
	
		i_pointer->son = tree_var_preenche (info_p);
	}
	else {
		
		i_pointer->son = tree_var_add_bro (i_pointer->son, info_p);
	}
	
	return i_pointer;
}

void tree_var_libera (tree_var* tree_p) {

	tree_var* i_pointer = tree_p;
	
	if (i_pointer->bro != NULL) tree_var_libera (i_pointer->bro);

	while (i_pointer != NULL) {
		
		tree_var* temp = i_pointer->son; 
		free(i_pointer);
		i_pointer = temp;

		if ( ( tree_var_vazia (i_pointer) == FALSO ) && (i_pointer->bro != NULL) ) tree_var_libera (i_pointer->bro);
	}
}
/* Funções para listas de arvores */

treeV_lst* treeV_lst_cria() {

	return NULL;
}

treeV_lst* treeV_lst_insere(treeV_lst* lst_tree, tree_var* tree_p) {

	treeV_lst* novo_endereco = (treeV_lst*) malloc (sizeof (treeV_lst));

	if (novo_endereco == NULL) {

		// Referenciamento a "novo_endereco == NULL"
		// Erro ao alocar espaco da memoria
		return NULL;
	}

	novo_endereco->endereco_tree = tree_p;
	novo_endereco->prox = NULL;

	treeV_lst* aux = lst_tree;

	if (aux == NULL) return novo_endereco;

	while (aux->prox != NULL) aux = aux->prox;
	aux->prox = novo_endereco;

	return lst_tree;
}

treeV_lst* treeV_lst_remove(treeV_lst* lst_tree) {

	if (lst_tree == NULL) return NULL;

	treeV_lst* aux = lst_tree->prox;

	return aux;
}

void treeV_lst_libera(treeV_lst* lst_tree) {

	treeV_lst* i_pointer = lst_tree;
	
	while (i_pointer != NULL) {
		
		treeV_lst* temp = i_pointer->prox; 
		free(i_pointer);
		i_pointer = temp;
	}
}
