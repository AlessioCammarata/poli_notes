#include "grafo.h"
#include <string.h>

struct graph_s{
    int V, E, n;
    int **madj;
	vertex_t *nodes;
    st_t tab;
};

int **MATRIXint(int r, int c, int val) {
	int i, j; 
	int **t = malloc(r * sizeof(int *)); 
	for (i=0; i < r; i++) 
		t[i] = malloc(c * sizeof(int));
	for (i=0; i < r; i++) 
		for (j=0; j < c; j++) 
			t[i][j] = val; 
	return t; 
}

vertex_t NEW_vertex(char *id){
	vertex_t x = malloc(sizeof *x);
	strcpy(x->id, id); 
	return x; 
}

edge_t EDGEcreate(vertex_t v, vertex_t w, int weight) {
	edge_t e; 
	e.node1 = v; 
	e.node2 = w; 
	e.weight = weight; 
	return e; 
}

graph_t GRAPHinit(int V) {
	graph_t G = malloc(sizeof *G); 
	G->V = V; 
	G->E = 0;
	G->n = 0;
	G->nodes = calloc(V, sizeof *G->nodes);
	G->madj = MATRIXint(V, V, 0);
	G->tab = STinit(V); 
	return G; 
}

void GRAPHfree(graph_t G) { 
	int i; 
	for (i=0; i<G->V; i++) 
		free(G->madj[i]); 
	free(G->madj);
	
	//Rimuovi i vertex
	for (i = 0; i < G->V; i++) {
		if (G->nodes[i]) free(G->nodes[i]);
	}
	free(G->nodes);

	STfree(G->tab);
	free(G); 
}

void GRAPHinsertEdge(graph_t G, vertex_t v, vertex_t w, int weight) {
    // Ricerca
    int i = STsearch(G->tab, v->id);
    int j = STsearch(G->tab, w->id);

    // Se i nodi non sono nella tabella, aggiungili
    if (i < 0) {
        i = STinsert(G->tab, v->id);
        G->nodes[i] = malloc(sizeof(struct vertex_s));
        strcpy(G->nodes[i]->id, v->id);
    }
    if (j < 0) {
        j = STinsert(G->tab, w->id);
        G->nodes[j] = malloc(sizeof(struct vertex_s));
        strcpy(G->nodes[j]->id, w->id);
    }

    // Inserisci l'arco nella matrice di adiacenza
    if (i >= 0 && j >= 0 && i < G->V && j < G->V) {
        G->madj[i][j] = weight;
        G->E++;
    }
}

static int findEdge(graph_t G, edge_t *edges, int nEdges, int v, int u) {
    for (int i = 0; i < nEdges; i++) {
        int v_idx = STsearch(G->tab, edges[i].node1->id);
        int u_idx = STsearch(G->tab, edges[i].node2->id);
        if (v_idx == v && u_idx == u) {
            return i;
        }
    }
    return -1; // non trovato
}

static void dfsClassifyEdges(graph_t G, edge_t *edges, int nEdges, int v, int *state, int *time, int *pre, int *post) {
    state[v] = 0;  // GRAY -> in visita
    pre[v] = (*time)++;
    
    for (int u = 0; u < G->V; u++) {
        if (G->madj[v][u] != 0) {
            // Trova l'arco corrispondente in edges[]
            int edgeIdx = findEdge(G, edges, nEdges, v, u);
            
            if (state[u] == -1) {  // WHITE -> non visitato
                edges[edgeIdx].type = Tree;
                dfsClassifyEdges(G, edges, nEdges, u, state, time, pre, post);
            }
            else if (state[u] == 0) {  // GRAY -> back edge
                edges[edgeIdx].type = Back;
            }
            else {  // BLACK -> visitato
                if (pre[v] < pre[u])
                    edges[edgeIdx].type = Forward;
                else
                    edges[edgeIdx].type = Cross;
            }
        }
    }
    
    state[v] = 1;  // BLACK - visitato
    post[v] = (*time)++;
}

void ClassifyEdges(graph_t G, edge_t *edges){
	int *state = malloc(G->V * sizeof(int));
    int *pre = malloc(G->V * sizeof(int));
    int *post = malloc(G->V * sizeof(int));
    int time = 0;

	// Inizializza tutti i nodi come non visitati
	for(int v = 0; v < G->V; v++) state[v] = -1;

    dfsClassifyEdges(G, edges, G->E, 0, state, &time, pre, post);
    
    free(state); free(pre); free(post);
}

static int dfsDAG(graph_t G, int v, int *state){
	state[v] = 0;
	for (int u = 0; u < G->V; u++) {
        if (G->madj[v][u] != 0) { // c'è un arco da v a u
            if (state[u] == 0) return 1; // ciclo trovato
            if (state[u] == -1 && dfsDAG(G, u, state)) return 1;
        }
    }
    state[v] = 1; // finito
    return 0;
}

int isDAG(graph_t G){
	int *state = malloc(G->V * sizeof(int));
	for (int v = 0; v < G->V; v++) state[v] = -1;
    for (int v = 0; v < G->V; v++)
        if (state[v] == -1 && dfsDAG(G, v, state)) {
            free(state);
            return 1; // ciclo trovato
        }
    free(state);
    return 0; // aciclico
}

int GRAPHisDAGwithout(graph_t G, edge_t *edges, int *excludeIndices, int nExclude) {
    // Grafo temporaneo senza gli archi esclusi
    graph_t temp = GRAPHinit(G->V);
    
    for (int i = 0; i < G->E; i++) {
        int skip = 0;
        for (int j = 0; j < nExclude; j++) {
            if (i == excludeIndices[j]) {
                skip = 1;
                break;
            }
        }
        if (!skip) { //Escludo l'arco
            GRAPHinsertEdge(temp, edges[i].node1, edges[i].node2, edges[i].weight);
        }
    }
    
    int result = isDAG(temp);
    GRAPHfree(temp);
    return !result; // 1 se è DAG
}

int getEdgeWeight(graph_t G, int i, int j){
	return (i < G->V && j < G->V) ? G->madj[i][j] : 0;
}

static void TSdfsR(graph_t D, int v, int *ts, int *pre, int *time) { 
	pre[v] = 1; // visitato
	for (int w = 0; w < D->V; w++) 
		if (D->madj[v][w] != 0)  // archi uscenti da v
			if (pre[w] == -1) 
				TSdfsR(D, w, ts, pre, time); 
	ts[(*time)++] = v; // metto v dopo aver visitato tutti i discendenti
}

int *topologicalSort(graph_t dag){
	int v, time = 0;
	int *pre = malloc(dag->V * sizeof(int));
	int *ts = malloc(dag->V * sizeof(int));
	
	for (v = 0; v < dag->V; v++) { 
		pre[v] = -1;
		ts[v] = -1;
	}
	
	// Esplora tutte le componenti connesse
	for (v = 0; v < dag->V; v++) 
		if (pre[v] == -1) 
			TSdfsR(dag, v, ts, pre, &time);
	
	free(pre);
	return ts;
}