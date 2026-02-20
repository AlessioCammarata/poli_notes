#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "graph.h"

typedef struct st_s *st_t;

typedef struct node_s *link; 
struct node_s{
    vertex_t info;
    int weight;        // peso dell'arco (usato nelle liste di adiacenza)
    edge_type type; //Tipo di arco   
    link next;
};

struct graph_s
{
    int V, E;
    vertex_t *nodes;
    link *ladj;
    link z; // sentinalle
    st_t tab;
};


graph_t GRAPHinit(int V){
    graph_t G = malloc(sizeof(*G));
    if(G == NULL) return NULL;
    G->V = V;
    G->E = 0;
    G->ladj = malloc(V*sizeof(*G->ladj));
    G->nodes = malloc(V*sizeof(*G->nodes));
    G->z = NULL; //Sentinella
    for(int i = 0; i<V; i++)
        G->ladj[i] = G->z;

    return G;
}

vertex_t NEW_vertex(int id, char *val){
    if(val == NULL) return NULL;
    vertex_t x = malloc(sizeof(*x));
    if(x == NULL) return NULL;
    x->id = id;
    x->val = val;  
    return x;
}

edge_t EDGEcreate(vertex_t v, vertex_t w, int weight){
    edge_t x;
    x.node1 = v;
    x.node2 = w;
    x.weight = weight;
    return x;
}

void GRAPHinsertEdge(graph_t G, vertex_t v, vertex_t w, int weight){
    if(G == NULL || v == NULL || w == NULL) return;

    link x = malloc(sizeof(*x));
    x->info = w;
    x->next = G->ladj[v->id];
    x->weight = weight;
    G->ladj[v->id] = x;

    //Se non orientato
    link y = malloc(sizeof(*y));
    y->info = v;
    y->next = G->ladj[w->id];
    y->weight = weight;
    G->ladj[w->id] = y;

    G->E++;
}

vertex_t GRAPHsearch(graph_t G, int id){
    if(G == NULL || id < 0 || id >= G->V) return NULL;
    return G->nodes[id];
}

void GRAPHaddVertex(graph_t G, vertex_t v){
    if(G == NULL || v == NULL || v->id < 0 || v->id >= G->V) return;
    G->nodes[v->id] = v;
}

void GRAPHprint(graph_t G){
    for(int i = 0; i<G->V; i++){
        printf("Nodo %d: [",i);
        for(link x = G->ladj[i]; x != G->z; x = x->next){
            printf("%d ",x->info->id);
        }
        printf("]\n");
    }
}

static void dfs(link *list, link z, int id, int parent, int visited[], int discovery[], int finish_time[], int *time){
    visited[id] = 1;
    discovery[id] = (*time)++;
    printf("Visita nodo %d (discovery: %d)\n", id, discovery[id]);
    
    for(link x = list[id]; x != z; x = x->next){
        int w = x->info->id;
        if(w == parent) continue; //Grafi non orientati

        if(!visited[w]){
            x->type = Tree;
            printf("  Arco (%d->%d): TREE\n", id, w);
            dfs(list, z, w, id, visited, discovery, finish_time, time);
        } else if(finish_time[w] == 0){
            x->type = Back;
            printf("  Arco (%d->%d): BACK\n", id, w);
        } else if(discovery[w] > discovery[id]){
            x->type = Forward;
            printf("  Arco (%d->%d): FORWARD\n", id, w);
        }else{
            x->type = Cross;
            printf("  Arco (%d->%d): CROSS\n", id, w);
        }
    }

    finish_time[id] = (*time)++;
    printf("Completamento nodo %d (finish: %d)\n", id, finish_time[id]);
}

void GRAPHdfs(graph_t G){
    if(G == NULL) return ;
    int time = 0;
    int *visited = calloc(G->V,sizeof(int)); 
    int *discovery = calloc(G->V,sizeof(int)); 
    int *finish_time = calloc(G->V,sizeof(int)); 
    if(visited == NULL || discovery == NULL || finish_time == NULL) return;
    
    for(int i = 0; i<G->V; i++)
        if(!visited[i])
            dfs(G->ladj, G->z, i, -1, visited, discovery, finish_time, &time);

    free(visited); free(discovery); free(finish_time);
}

/*
BFS necessità di una coda, la implemento internamente solo per questa funzione
*/
typedef struct qNode_s *qNode_t;
struct qNode_s{
    int data;
    qNode_t next;
};

typedef struct queue_s{
    qNode_t head, tail;
} *queue_t;

static queue_t queue_init(){
    queue_t q = malloc(sizeof(*q));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

static void qput(queue_t q, int id){
    qNode_t x = malloc(sizeof(*x));
    x->data = id;
    x->next = NULL;

    if(q->tail == NULL){
        q->head = q->tail = x;
    }else{
        q->tail->next = x;
        q->tail = x;
    }
}

static int qget(queue_t q){
    qNode_t x;
    x = q->head;
    int id = x->data;
    q->head = q->head->next;
    if(q->head == NULL)
        q->tail = NULL;
    free(x);
    return id;
}

static int queue_empty(queue_t q) {
    return q->head == NULL;
}

static void qFree(queue_t q){
    qNode_t t;
    for(qNode_t x = q->head; x != NULL; x = t){
        t = x->next;
        free(x);
    }
    free(q);
}

static void bfs(link *list, link z, int id, int st[], int dist[], int pre[], int *time){
    queue_t q = queue_init();
    dist[id] = 0;  // Distanza 0 dal nodo di partenza
    pre[id] = (*time)++;  // Discovery time
    st[id] = -1;  // Parent (se stesso per la radice)
    printf("Inizio BFS dal nodo %d (pre: %d, dist: %d)\n", id, pre[id], dist[id]);
    qput(q, id);
    
    while(!queue_empty(q)){
        int v = qget(q);
        
        for(link x = list[v]; x != z; x = x->next){
            int w = x->info->id;
            
            if(pre[w] == -1){  // Non visitato
                pre[w] = (*time)++;  // Assegna discovery time
                st[w] = v;  // Parent è v
                dist[w] = dist[v] + 1;  // Distanza = parent + 1
                qput(q, w);
            }
        }
    }
    qFree(q);
}

void GRAPHbfs(graph_t G){
    if(G == NULL) return;
    int time = 0;
    int *st = calloc(G->V, sizeof(int));
    int *dist = calloc(G->V, sizeof(int));
    int *pre = calloc(G->V, sizeof(int));
    if(st == NULL || dist == NULL || pre == NULL) return;
    
    // Inizializza i vettori
    for(int v = 0; v < G->V; v++){
        pre[v] = -1;      // Non visitato
        st[v] = -1;       // Nessun parent
        dist[v] = INT_MAX;  // Distanza infinita
    }
    
    // BFS da ogni componente connessa
    for(int i = 0; i < G->V; i++){
        if(pre[i] == -1)  // Se non ancora visitato
            bfs(G->ladj, G->z, i, st, dist, pre, &time);
    }
    
    // Stampa risultati
    printf("\nRisultati BFS (pre, parent, dist):\n");
    for(int i = 0; i < G->V; i++){
        printf("Nodo %d: pre=%d, parent=%d, dist=%d\n", i, pre[i], st[i], dist[i]);
    }
    
    free(st);
    free(dist);
    free(pre);
}

/*Kruskal*/
/*Serve implementazione UF*/
typedef struct UnionFind *UF;
struct UnionFind{
    int *st; //Padre o rappresentante
    int *dim; //Dimensioni
};

static UF UFinit(int N){
    UF uf = malloc(sizeof(*uf));
    uf->st = malloc(N*sizeof(int));
    uf->dim = malloc(N*sizeof(int));
    
    if(uf == NULL || uf->st == NULL || uf->dim == NULL) 
        return NULL;

    for(int i = 0; i<N; i++){
        uf->st[i] = i;  // Inizialmente ogni elemento è padre di se stesso
        uf->dim[i] = 1;
    }

    return uf;
}

static int find(UF uf, int x){
    int i = x;
    while (i != uf->st[i])
        i = uf->st[i];
    return i;
}

static int UFfind(UF uf, int p, int q){
    return find(uf, p) == find(uf, q);
}

static void UFunion(UF uf, int p, int q){
    int x = find(uf, p);
    int y = find(uf, q);
    if(x == y) return; //Stesso padre

    if(uf->dim[x] > uf->dim[y]){
        uf->st[y] = x;
        uf->dim[x] += uf->dim[y];
    }else{
        uf->st[x] = y;
        uf->dim[y] += uf->dim[x];
    }

}

static void UFfree(UF uf){
    free(uf->st); free(uf->dim);
    free(uf);
}

/*Ordinamento*/
static int compare_edges(const void *a, const void *b) {
    edge_t *e1 = (edge_t *)a;
    edge_t *e2 = (edge_t *)b;
    return e1->weight - e2->weight;
}

/*kruskal*/
int kruskal(graph_t G, edge_t **sol){
    if(G==NULL || sol==NULL) return -1;

    //Estrazione degli archi e ordinamento per peso
    edge_t *edges = malloc(G->E*sizeof(edge_t));
    if(edges == NULL) return -1;
    
    int count = 0, k = 0;
    for(int i = 0; i<G->V; i++){
        for(link x = G->ladj[i]; x != G->z; x = x->next){
            if(i < x->info->id){ //Grafo non orientato
                edges[count].node1 = G->nodes[i];
                edges[count].node2 = x->info;
                edges[count].weight = x->weight;
                count++;
            }
        }
    }

    qsort(edges, count, sizeof(edge_t), compare_edges);
    UF uf = UFinit(G->V);
    if(uf == NULL) {
        free(edges);
        return -1;
    }
    
    // Alloca la soluzione con la dimensione corretta
    *sol = malloc((G->V - 1) * sizeof(edge_t));
    if(*sol == NULL) {
        free(edges);
        UFfree(uf);
        return -1;
    }
    
    //Algoritmo kruskal
    for(int i = 0; i<count; i++){
        if(!UFfind(uf, edges[i].node1->id, edges[i].node2->id)){
            UFunion(uf, edges[i].node1->id, edges[i].node2->id);
            (*sol)[k++] = edges[i];
        }
    }

    free(edges); UFfree(uf);
    return k;
}

/*PRIM*/
static void mstV(graph_t G, int *st, int *wt){
    int v, w, min;
    int *fr = malloc(G->V*sizeof(int));
    if(fr == NULL) return;
    
    for(v = 0; v<G->V; v++){
        st[v] = -1;
        wt[v] = INT_MAX;
        fr[v] = v;
    }
    
    st[0] = 0;
    wt[0] = 0;
    
    // Ciclo principale: V iterazioni, una per ogni nodo
    for(min = 0; min < G->V;){
        if(min == G->V) break;  // Nessun nodo non visitato trovato
        
        st[min] = fr[min];  // Aggiungi alla MST
        
        // Itera su tutti gli archi del nodo min
        for(link x = G->ladj[min]; x != G->z; x = x->next){
            w = x->info->id;
            if(st[w] == -1 && x->weight < wt[w]){
                wt[w] = x->weight;
                fr[w] = min;
            }
        }
        
        min = G->V;  // Reset sentinella all'inizio di ogni ciclo
        
        // Trova il nodo non visitato con peso minimo
        for(w = 0; w < G->V; w++){
            if(st[w] == -1 && (min == G->V || wt[w] < wt[min])){
                min = w;
            }
        }
    }
    
    free(fr);
}

void Prim(graph_t G){
    if(G == NULL) return;
    
    int v, *st, *wt, weight = 0;
    st = malloc(G->V*sizeof(int));
    wt = malloc(G->V*sizeof(int));
    if(st == NULL || wt == NULL){
        free(st);
        free(wt);
        return;
    }

    mstV(G, st, wt);

    printf("\nEdges in the MST (Prim):\n");
    for(v = 0; v < G->V; v++){
        if(st[v] != v){
            printf("(%d-%d) weight: %d\n", st[v], v, wt[v]);
            weight += wt[v];
        }
    }
    printf("Minimum weight: %d\n", weight);
    
    free(st);
    free(wt);
}

/*Djikstra*/
typedef struct pqueue *PQ;

void GRAPHspD(graph_t G, int id) { 
	int v; 
	link t; 
	PQ pq = PQinit(G->V); // PQ con priorità in d
	int *st, *d; 
	st = malloc(G->V*sizeof(int)); // tante celle quanti sono i nodi
	d = malloc(G->V*sizeof(int)); // tante celle quanti sono i nodi
	for (v = 0; v < G->V; v++){ 
		st[v] = -1; //Nessuno ha il predecessore
		d[v] = INT_MAX; //Metto infinito
		PQinsert(pq, d, v); //Inserisco il nodo nella PQ
	} 
	d[id] = 0; 
	st[id] = id; 
	PQchange(pq, d, id);
	
	//Dijkstra
	while (!PQempty(pq)) { 
		if (d[v = PQextractMin(pq, d)] != INT_MAX) //Estre dalla testa di PQ
			//Lista di adiacenza del nodo
			 for (t=G->ladj[v]; t!=G->z ; t=t->next) 
				 if (d[v] + t->weight < d[t->info->id]) { //Se miglioro la stima
					 d[t->info->id] = d[v] + t->weight; //Riscrvii la stima su v
					 // riposiziona il nodo successivo nella PQ
					 PQchange(pq, d, t->info->id); 
					 st[t->info->id] = v; //Assegna il predecessore a v
				} 
	} 
	// Stampa risultato
	printf("\n Shortest path tree\n"); 
	for (v = 0; v < G->V; v++) 
		printf("parent of %s is %s \n", STsearchByIndex(G->tab, v),STsearchByIndex (G->tab, st[v])); 
    
	printf("\n Min.dist. from %s\n", STsearchByIndex(G->tab, id));
	for (v = 0; v < G->V; v++) 
		printf("%s: %d\n", STsearchByIndex(G->tab, v), d[v]);

    free(st); free(d);
	Pqfree(pq); 
}

/*Bellman-ford*/
void GRAPHspBF(graph_t G, int id){ 
	int v, i, negcycfound; 
	link t; 
	int *st, *d; 
	st = malloc(G->V*sizeof(int)); 
	d = malloc(G->V*sizeof(int)); 
	for (v = 0; v < G->V; v++) { 
		st[v]= -1; 
		d[v] = INT_MAX; 
	} 
	d[id] = 0; 
	st[id] = id;
	for (i=0; i<G->V-1; i++) 
		for (v=0; v<G->V; v++) //Scorro tutti i nodi
			if (d[v] < INT_MAX) 
				for (t=G->ladj[v]; t!=G->z ; t=t->next) //Lista di adj
					if (d[t->info->id] > d[v] + t->weight) { 
						d[t->info->id] = d[v] + t->weight; 
						st[t->info->id] = v; 
					}
	//V-esimo passaggio 
	negcycfound = 0; 
	for (v=0; v<G->V; v++) 
		if (d[v] < INT_MAX) 
			for (t=G->ladj[v]; t!=G->z ; t=t->next) 
				if (d[t->info->id] > d[v] + t->weight) 
					negcycfound = 1;
					
	if (negcycfound == 0) {
		 printf("\n Shortest path tree\n"); 
		 for (v = 0; v < G->V; v++) 
			 printf("Parent of %s is %s \n", 
				 STsearchByIndex(G->tab, v), 
				 STsearchByIndex (G->tab, st[v])); 
		printf("\n Min.dist. from %s\n", STsearchByIndex (G->tab, id));
		for (v = 0; v < G->V; v++) 
			printf("%s: %d\n", STsearchByIndex (G->tab, v), d[v]);
	} else 
		printf("\n Negative cycle found!\n"); 
}

void GRAPHfree(graph_t G){
    link t;
    for(int i = 0; i<G->V; i++)
        for(link x = G->ladj[i]; x != G->z; x = t){
            t = x->next;
            free(x);
        }
    free(G->ladj);
    free(G);
}