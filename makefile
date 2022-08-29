
UBER_ON_STARS: main.o grafos.o tree_var.o lista_adj.o
	gcc main.o grafos.o tree_var.o lista_adj.o

main.o: main.c
	gcc main.c

grafos.o: grafos.c
	gcc grafos.c

tree_var.o: tree_var.c
	gcc tree_var.c

listas_adj.o: listas_adj.c
	gcc listas_adj.c
