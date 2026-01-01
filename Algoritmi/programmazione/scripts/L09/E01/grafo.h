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
    char id[NMAX];
};

typedef enum{
    Tree,     //archi dell'albero della visita in profondità (Tree)
    Back,     //Backward, connettono un vertice w ad un suo antenato v nell’albero
    Forward,  //Forward, connettono un vertice w ad un suo discendente v nell’albero
    Cross     //Cross, archi rimanenti
} edge_type;

typedef struct edge_s{
    vertex_t node1, node2; //Due nodi connessi
    int weight;       //Peso
    edge_type type; //Tipo di arco   
} edge_t;

edge_t EDGEcreate(vertex_t v, vertex_t w, int weight);
vertex_t NEW_vertex(char *id);
static int **MATRIXint(int r, int c, int val);

graph_t GRAPHinit(int V);
void GRAPHfree(graph_t G);

/* lettura e scrittura su file */
void GRAPHinsertEdge(graph_t G, vertex_t v, vertex_t w, int weight);

int isDAG(graph_t G);
void ClassifyEdges(graph_t G, edge_t *edges);

int GRAPHisDAGwithout(graph_t G, edge_t *edges, int *excludeIndices, int nExclude);
int *topologicalSort(graph_t G);
int getEdgeWeight(graph_t G, int i, int j);

#endif // GRAFO_H_DEFINED