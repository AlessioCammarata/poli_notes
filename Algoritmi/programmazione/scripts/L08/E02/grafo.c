#include "grafo.h"
#include <string.h>

struct graph_s{
    int V, E;
    int **madj;
	node_t *ladj; //Vettore di linked list, di dimensione V
	node_t z; // sentinalle
    st_t tab;
	int flag_list;
};

static int **MATRIXint(int r, int c, int val) {
	int i, j; 
	int **t = malloc(r * sizeof(int *)); 
	for (i=0; i < r; i++) 
		t[i] = malloc(c * sizeof(int));
	for (i=0; i < r; i++) 
		for (j=0; j < c; j++) 
			t[i][j] = val; 
	return t; 
}

//Inserimento in testa all'interno di una linked list
static node_t NEW(char *name, char *net, node_t next) { 
	node_t x = malloc(sizeof *x); 
	strcpy(x->elab, name); 
	strcpy(x->net, net); 
	x->next = next; 
	return x; 
} 

static edge_t EDGEcreate(node_t v, node_t w, int flow) {
	edge_t e; 
	e.node1 = v; 
	e.node2 = w; 
	e.flow = flow; 
	return e; 
}

graph_t GRAPHinit(int V, int flag_list) {
	graph_t G = malloc(sizeof *G); 
	G->flag_list = flag_list;
	G->V = V; 
	G->E = 0; 
	G->madj = MATRIXint(V, V, 0);
	if(G->flag_list){
		G->z = NEW("", "", NULL); // -1 è il peso standard (wt)
		G->ladj = malloc(G->V*sizeof(node_t)); 
		for (int v = 0; v < G->V; v++) 
			G->ladj[v] = G->z; 
	}
	G->tab = STinit(V); 
	return G; 
} 


void GRAPHfree(graph_t G) { 
	int i; 
	for (i=0; i<G->V; i++) 
		free(G->madj[i]); 
	free(G->madj);
	//Rimuovi la lista se inizializzata
	if(G->flag_list){
		int v; 
		node_t t, next; 
		for (v=0; v < G->V; v++) 
			for (t=G->ladj[v]; t != G->z; t = next) { 
				next = t->next; 
				free(t); 
			}
		free(G->ladj); free(G->z);
	}
	STfree(G->tab);
	free(G); 
}