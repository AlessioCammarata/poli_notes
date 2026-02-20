/*
Dato un grafo non orientato e pesato G = (V,E), si definisce k-capacitated tree partition una collezione E1, E2, ... En di sottoinsiemi di E disgiunti per vertici, 
tali per cui per ogni E_i il grafo indotto è un albero di almeno k vertici. 
Tutti i vertici del grafo originale devono appartenere a uno dei grafi indotti. 

Per gli scopi del problema si è interessati all'individuazione di un partizionamento tale per cui valga , dove  rappresenta il peso del generico arco .
 
Sia k un parametro del problema.
*/


/*
Strutture dati e acquisizione

Scrivere qui la definizione e implementazione delle strutture dati reputate necessarie a modellare le informazioni del problema, 
quali il grafo e il relativo tree partitioning, e le funzioni di acquisizione dei dati stessi. 
In caso di organizzazione delle strutture dati su più file, indicare esplicitamente il modulo di riferimento.
Si assuma che il grafo in input sia riportato in un file di nome grafo.txt, organizzato come segue:

Sulla prima riga appare il numero V di vertici
Seguono un numero indefinito di righe riportanti coppie (u,v) di interi, con 0 <= u,v < V a rappresentare gli archi del grafo, e il relativo peso w.
*/
#include <stdio.h>
#include <stdlib.h>

//treePart.h
typedef struct treePart *TP;
struct treePart{
    int **treeID; //Ogni id ha un padre
    int *treeIdsize;
    int n; //Numero di partition
};

//graph.c
typedef struct node *link;
struct node{
    int v;
    int weight;
    link next;
};

typedef struct graph_s *graph_t;
struct graph_s{
    int V, E, k;
    link *ladj;
    link z;
    int *vertex; //Id dei vertici
    TP tp;
};

graph_t readFile(FILE *f){
    //Ricevi il file gia aperto
    int V;
    if(fscanf(f, "%d", &V) != 1) 
        return NULL;

    graph_t g = graphInit(V);
    if(g == NULL) 
        return NULL;

    for(int i = 0; i<V; i++)
        addVertex(g, i);

    int countE = 0;
    int u, v, w;
    while(fscanf(f, "%d %d %d", &u, &v, &w) == 3){
        addEdge(g, u, v, w);
        countE++;
    }

    return g;
}

/*
Data una soluzione proposta, verificare che questa rappresenti effettivamente un k-capacitated tree partitioning, 
tenendo in considerazione la definizione teorica proposta in precedenza. Si trascuri la richiesta di minimalità della 
somma complessiva dei pesi per gli archi scelti.

La soluzione proposta deve essere letta da file il cui nome e formato è a discrezione del candidato, 
che è tenuto a fornire anche una breve spiegazione dei contenuti del file stesso.
*/

int dfs(graph_t g, int id, int parent, int *visited, int *in_subset){
    int count = 1;
    visited[id] = 1;
    
    for(link x = g->ladj[id]; x != g->z; x = x->next){
        if(!in_subset[x->v]) continue;
        if(x->v == parent) continue;

        if(visited[x->v]) 
            return -1;
        
        int res = dfs(g, x->v, id, visited, in_subset);
        if(res == -1)
            return -1;

        count += res;
    }

    return count;
}

int checkTree(graph_t g, int *ids, int size){
    int *visited = malloc(g->V*sizeof(int));
    int *in_subset = malloc(g->V*sizeof(int));

    for(int i = 0; i<g->V; i++){
        visited[i] = 0;
        in_subset[i] = 0;
    }
    for(int i = 0; i<size; i++)
        in_subset[ids[i]] = 1;

    int count = dfs(g, ids[0], -1, visited, in_subset);
    free(visited);
    free(in_subset);
    
    if(count != size)
        return 0;

    return 1;
}

int checkTreeK(FILE *f, graph_t g, int k){
    if(g == NULL || f == NULL) return 0;
    int n;
    if(fscanf(f, "%d", &n) != 1) 
        return 0;

    TP tp = malloc(sizeof(*tp));
    if(tp == NULL) 
        return 0;
    tp->treeID = malloc(n*sizeof(*tp->treeID));
    if(tp->treeID == NULL){
        free(tp);
        return 0;
    }
    tp->treeIdsize = malloc(n*sizeof(int));
    if(tp->treeIdsize == NULL){
        free(tp->treeID);
        free(tp);
        return 0;
    }
    tp->n = n;
    
    int *found = calloc(g->V,sizeof(int));
    if(found == NULL){
        free(tp->treeIdsize);
        free(tp->treeID);
        free(tp);
        return 0;
    }

    //Lettura da file
    for(int i = 0; i<n; i++){
        int n2;
        //Controllo per vedere se ha almeno k elementi
        if(fscanf(f, "%d", &n2) != 1 || n2 < k){
            for(int x = 0; x<i; x++)
                free(tp->treeID[x]);
            free(tp->treeIdsize); free(tp->treeID); free(tp);
            free(found);
            return 0;
        }
        tp->treeIdsize[i] = n2;
        tp->treeID[i] = malloc(n2*sizeof(int));
        for(int j = 0; j<n2; j++){
            fscanf(f, "%d", &tp->treeID[i][j]);
            if(found[tp->treeID[i][j]]){ //Intercept
                for(int x = 0; x<i+1; x++)
                    free(tp->treeID[x]);
                
                free(tp->treeIdsize); free(tp->treeID); free(tp);
                free(found);
                return 0;
            }
            found[tp->treeID[i][j]] = 1;
        }
    }

    for(int i = 0; i<g->V; i++)
        if(!found[i]){
            free(found);
            for(int i = 0; i<n; i++)
                free(tp->treeID[i]);
            free(tp->treeIdsize); free(tp->treeID); free(tp);
            return 0;
        }
    free(found);

    for(int i = 0; i<n; i++){
        if(!checkTree(g, tp->treeID[i], tp->treeIdsize[i])){
            for(int i = 0; i<n; i++)
                free(tp->treeID[i]);
            free(tp->treeIdsize); free(tp->treeID); free(tp);
            return 0;
        }
    }


    for(int i = 0; i<n; i++)
        free(tp->treeID[i]);
    free(tp->treeIdsize); free(tp->treeID); free(tp);
    return 1;
}

/*
Identificare, se possibile, un k-capacitated tree partitioning 
che rispetti anche la condizione di minimalità della somma dei pesi per gli archi scelti, 
per il grafo dato in input e il relativo parametro k passato come argomento.
*/

typedef struct {
    int u, v, weight;
} Edge;

// Funzione di comparazione per qsort (ordina per peso crescente)
int cmpEdges(const void *a, const void *b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Trova la radice dell'albero (senza path compression per non "sporcare" lo stato durante la ricorsione)
int UF_find(int *parent, int i) {
    while (parent[i] != i) {
        i = parent[i];
    }
    return i;
}

void partR(Edge *edges, int E, int V, int pos, int weight, int k, int *sol, int *best_sol, int *best_wt, int *parent, int *sz){
    if(weight > *best_wt) return;
    
    if(pos >= E){
        int is_valid = 1;
        for(int i = 0; i<V; i++){
            int root = UF_find(parent, i);
            if (sz[root] < k) {
                is_valid = 0;
                break;
            }
        }

        // Aggiornamento dell'ottimo
        if (is_valid) {
            *best_wt = weight;
            for (int i = 0; i < E; i++)
                best_sol[i] = sol[i];
        }
        return;
    }

    int u = edges[pos].u;
    int v = edges[pos].v;
    int root_u = UF_find(parent, u);
    int root_v = UF_find(parent, v);

    if(root_u != root_v){
        int *next_parent = malloc(V * sizeof(int));
        int *next_sz = malloc(V * sizeof(int));
        for (int i = 0; i < V; i++) {
            next_parent[i] = parent[i];
            next_sz[i] = sz[i];
        }

        //UFunion
        next_parent[root_v] = root_u;
        next_sz[root_u] += next_sz[root_v];

        sol[pos] = 1;
        partR(edges, E, V, pos + 1, weight + edges[pos].weight, k, sol, best_sol, best_wt, next_parent, next_sz);
        sol[pos] = 0;
        free(next_parent); free(next_sz);
    }

    partR(edges, E, V, pos + 1, weight, k, sol, best_sol, best_wt, parent, sz);
}

void findBestKTreePart(graph_t g, Edge *edges, int k){
    int *best_sol = calloc(g->E, sizeof(int));
    int *sol = calloc(g->E, sizeof(int));
    int *parent = malloc(g->V * sizeof(int));
    int *sz = malloc(g->V * sizeof(int));
    int best_wt = INT_MAX;

    for (int i = 0; i < g->V; i++) {
        sz[i] = 1;
        parent[i] = i;
    }

    qsort(edges, g->E, sizeof(Edge), cmpEdges);

    partR(edges, g->E, g->V, 0, 0, k, sol, best_sol, &best_wt, parent, sz);

    if (best_wt == INT_MAX) {
        printf("Nessuna soluzione valida trovata per k = %d\n", k);
    } else {
        printf("Soluzione ottima trovata! Peso totale: %d\n", best_wt);
        for (int i = 0; i < g->V; i++) {
            parent[i] = i;
        }

        for (int i = 0; i < g->E; i++) {
            if (best_sol[i] == 1) {
                int root_u = UF_find(parent, edges[i].u);
                int root_v = UF_find(parent, edges[i].v);
                if (root_u != root_v) {
                    parent[root_v] = root_u; // Union
                }
            }
        }

        int *stampato = calloc(g->V, sizeof(int));
        int contatore_partizioni = 1;

        for (int i = 0; i < g->V; i++) {
            if (!stampato[i]) {
                // Trovo la radice di questo vertice (sarà l'ID della sua partizione)
                int radice_attuale = UF_find(parent, i); 
                
                printf("Partizione %d: { ", contatore_partizioni++);
                
                // Cerco tutti gli altri vertici con la stessa radice
                for (int j = i; j < g->V; j++) {
                    if (!stampato[j] && UF_find(parent, j) == radice_attuale) {
                        printf("%d ", j);
                        stampato[j] = 1; // Lo segno come stampato per non ripeterlo
                    }
                }
                printf("}\n");
            }
        }
        free(stampato);
    }

    free(sol); free(best_sol);
    free(parent); free(sz);
}