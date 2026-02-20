#ifndef GRAPH_H_DEFINED
#define GRAPH_H_DEFINED

typedef struct graph_s *graph_t;
typedef struct vertex_s{
    int id;
    char *val;
} *vertex_t;

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

graph_t GRAPHinit(int V);
vertex_t NEW_vertex(int id, char *val);
edge_t EDGEcreate(vertex_t v, vertex_t w, int weight);
void GRAPHinsertEdge(graph_t G, vertex_t v, vertex_t w, int weight);
vertex_t GRAPHsearch(graph_t G, int id);
void GRAPHaddVertex(graph_t G, vertex_t v);
void GRAPHprint(graph_t G);
void GRAPHdfs(graph_t G);
void GRAPHbfs(graph_t G);
int kruskal(graph_t G, edge_t **sol);
void Prim(graph_t G);
void GRAPHfree(graph_t G);

#endif