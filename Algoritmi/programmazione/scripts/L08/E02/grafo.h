#ifndef GRAFO_H_DEFINED
#define GRAFO_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "st.h"

#define NMAX 30

// ADT I classe
typedef struct graph_s *graph_t;
typedef struct node_s *node_t; 
struct node_s{
    char elab[NMAX], net[NMAX];
    node_t next;
};
typedef struct edge_s{
    node_t node1, node2; //Due nodi connessi
    int flow; //Peso
} edge_t;

graph_t graph_init(int V, int flag_list);
void graph_free(graph_t graph);

/* lettura e scrittura su file */
void graph_read(FILE *fp, graph_t graph);
void graph_print(FILE *fp, graph_t graph); // elencare in ordine alfabetico i vertici e per ogni vertice gli archi che su di esso insistono, sempre in ordine alfabetico

/* inserimento di un nuovo personaggio */
void graph_insert(graph_t graph, node_t pg); 

/* ricerca per nome, ritornando il puntatore */
node_t *pgList_searchByCode(graph_t graph, char* name);

/*
dati 3 vertici i cui nomi sono letti da tastiera, verificare se essi sono adiacenti a coppie, cioè se
formano un sottografo completo. Tale funzione sia implementata sia per la rappresentazione con
matrice delle adiacenze, sia per la rappresentazione con lista delle adiacenze
*/
int subGraph();
/*
generare la rappresentazione a lista di adiacenza, SENZA leggere nuovamente il file, a partire da
quella a matrice di adiacenza. 
*/
void generate_adjList(graph_t graph);

#endif // GRAFO_H_DEFINED