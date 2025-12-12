#ifndef GRAFO_H_DEFINED
#define GRAFO_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "st.h"

#define NMAX 30

// ADT I classe
typedef struct graph_s *graph_t;
typedef struct vertex_s *vertex_t;
// Metadati per vertice (nome e rete) indicizzati 0..V-1
struct vertex_s {
    char elab[NMAX];
    char net[NMAX];
};

typedef struct node_s *node_t; 
struct node_s{
    vertex_t info;
    int flow;        // peso dell'arco (usato nelle liste di adiacenza)
    node_t next;
};
typedef struct edge_s{
    vertex_t node1, node2; //Due nodi connessi
    int flow; //Peso
} edge_t;

edge_t EDGEcreate(vertex_t v, vertex_t w, int flow);
node_t NEW(vertex_t vertex, int flow, node_t next);
vertex_t NEW_vertex(char *name, char *net);
static int **MATRIXint(int r, int c, int val);

graph_t GRAPHinit(int V);
void GRAPHfree(graph_t G);

/* lettura e scrittura su file */
void GRAPHinsertEdge(graph_t G, vertex_t v, vertex_t w, int flow);
void ORDERprint(FILE *fp, graph_t G); // elencare in ordine alfabetico i vertici e per ogni vertice gli archi che su di esso insistono, sempre in ordine alfabetico

int ExistName(graph_t G, char *name);
int ExistList(graph_t G);

/*
dati 3 vertici i cui nomi sono letti da tastiera, verificare se essi sono adiacenti a coppie, cioè se
formano un sottografo completo. Tale funzione sia implementata sia per la rappresentazione con
matrice delle adiacenze, sia per la rappresentazione con lista delle adiacenze
*/
int subGraph(graph_t G, char **names, int n);
/*
generare la rappresentazione a lista di adiacenza, SENZA leggere nuovamente il file, a partire da
quella a matrice di adiacenza. 
*/
void GRAPHinitList(graph_t G);
void GRAPHinsertEdgeList(graph_t G);

#endif // GRAFO_H_DEFINED