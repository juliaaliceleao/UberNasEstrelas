// Agosto, 2022
// tree_var.h - Artur Gonzaga
// Desenvolvimento de Sistemas - COLTEC UFMG

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t bool;

typedef struct tree_var_s {

    int info;

    struct tree_var_s* bro;
    struct tree_var_s* son;

}tree_var;

typedef struct treeV_lst_s {

    tree_var* endereco_tree;
    struct treeV_lst_s* prox;

} treeV_lst;

tree_var* tree_var_cria (void);

bool tree_var_vazia (tree_var* tree_p);
tree_var* tree_var_busca (tree_var* tree_p, int info_p);
tree_var* tree_var_preenche (int info_p);

tree_var* tree_var_add_bro (tree_var* tree_p, int info_p);
tree_var* tree_var_add_son (tree_var* tree_p, int info_p);

void tree_var_libera (tree_var* tree_p);

/* Funções para listas de arvores */

treeV_lst* treeV_lst_cria();

treeV_lst* treeV_lst_insere(treeV_lst* lst_tree, tree_var* tree_p);

treeV_lst* treeV_lst_remove (treeV_lst* lst_tree);

void treeV_lst_libera (treeV_lst* lst_tree);
