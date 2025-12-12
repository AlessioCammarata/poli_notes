#include "grafo.h"
#include <string.h>

struct graph_s{
    int V, E, n;
    int **madj;
	vertex_t *nodes;
	node_t *ladj; //Vettore di linked list, di dimensione V
	node_t z; // sentinalle
    st_t tab;
	int flag_list;
	int flag_list_populated;
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

vertex_t NEW_vertex(char *name, char *net){
	vertex_t x = malloc(sizeof *x);
	strcpy(x->elab, name); 
	strcpy(x->net, net); 
	return x; 
}

//Inserimento in testa all'interno di una linked list
node_t NEW(vertex_t vertex, int flow, node_t next) { 
	node_t x = malloc(sizeof *x);
	x->info = vertex;
	x->flow = flow; 
	x->next = next; 
	return x; 
} 

edge_t EDGEcreate(vertex_t v, vertex_t w, int flow) {
	edge_t e; 
	e.node1 = v; 
	e.node2 = w; 
	e.flow = flow; 
	return e; 
}

graph_t GRAPHinit(int V) {
	graph_t G = malloc(sizeof *G); 
	G->flag_list = 0;
	G->flag_list_populated = 0;
	G->V = V; 
	G->E = 0;
	G->n = 0;
	G->nodes = calloc(V, sizeof *G->nodes);
	G->madj = MATRIXint(V, V, 0);
	G->tab = STinit(V); 
	return G; 
}

// Inizializza le liste di adiacenza su richiesta.
void GRAPHinitList(graph_t G) {
	if (G == NULL || G->flag_list) return;

	G->z = NEW(NULL, 0, NULL); // nodo sentinella
	G->ladj = malloc(G->V * sizeof(node_t));
	if (!G->ladj) {
		free(G->z);
		G->z = NULL;
		return;
	}
	for (int v = 0; v < G->V; v++)
		G->ladj[v] = G->z;

	G->flag_list = 1;
}

void GRAPHinsertEdgeList(graph_t G){
	if (G == NULL || !G->flag_list) return;
	if (G->flag_list_populated) return;

	for(int i = 0; i<G->V; i++)
		for(int j = i+1; j<G->V; j++){
			if (G->madj[i][j] != 0){
				G->ladj[i] = NEW(G->nodes[j], G->madj[i][j], G->ladj[i]);
				G->ladj[j] = NEW(G->nodes[i], G->madj[i][j], G->ladj[j]); // Grafi non orientati
			}
		}
	G->flag_list_populated = 1; 
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
	//Rimuovi i vertex
	for (i = 0; i < G->V; i++) {
		if (G->nodes[i]) free(G->nodes[i]);
	}
	free(G->nodes);

	STfree(G->tab);
	free(G); 
}

void GRAPHinsertEdge(graph_t G, vertex_t v, vertex_t w, int flow) {
    // Ricerca
    int i = STsearch(G->tab, v->elab);
    int j = STsearch(G->tab, w->elab);

    // Se i nodi non sono nella tabella, aggiungili
    if (i < 0) {
        i = STinsert(G->tab, v->elab);
        G->nodes[i] = malloc(sizeof(struct vertex_s));
        strcpy(G->nodes[i]->elab, v->elab);
        strcpy(G->nodes[i]->net,  v->net);
    }
    if (j < 0) {
        j = STinsert(G->tab, w->elab);
        G->nodes[j] = malloc(sizeof(struct vertex_s));
        strcpy(G->nodes[j]->elab, w->elab);
        strcpy(G->nodes[j]->net,  w->net); 
    }

    // Inserisci l'arco nella matrice di adiacenza
    if (i >= 0 && j >= 0 && i < G->V && j < G->V) {
        G->madj[i][j] = flow;
		G->madj[j][i] = flow; // Grafo non orientato
        G->E++;
    }
}

int cmp_name(const void* a, const void* b) { 
    const char* ea = *(const char**)a;
    const char* eb = *(const char**)b;
    return strcmp(ea, eb); // ordine alfabetico crescente (A->Z)
}

void ORDERprint(FILE *fp, graph_t G){
	int n = STcount(G->tab);
	char **vet = malloc(n * sizeof(char*));
	for(int i = 0; i<n; i++) vet[i] = STsearchByIndex(G->tab,i);

	qsort(vet, n, sizeof(char*), cmp_name); //Ottengo i nomi in ordine
	
	// Precalcolo gli indici per evitare STsearch ripetute
	int *ids = malloc(n * sizeof(int));
	for(int i = 0; i<n; i++) ids[i] = STsearch(G->tab, vet[i]);
	
	for(int i = 0; i<n; i++){
		fprintf(fp,"%s:\n", vet[i]);
		int id = ids[i];
		for(int j = 0; j<n; j++){
			int id2 = ids[j];
			if(id2 != id && G->madj[id][id2] != 0) 
				fprintf(fp,"  - %s (flusso: %d)\n", vet[j], G->madj[id][id2]);
		}
		fprintf(fp,"\n");
	}
	
	free(ids);
	free(vet);
}

int ExistName(graph_t G, char *name){
	return STsearch(G->tab,name);
}

int ExistList(graph_t G){
	return G->flag_list;
}

/*
dati 3 vertici i cui nomi sono letti da tastiera, verificare se essi sono adiacenti a coppie, cioè se
formano un sottografo completo. Tale funzione sia implementata sia per la rappresentazione con
matrice delle adiacenze, sia per la rappresentazione con lista delle adiacenze
*/
int subGraph(graph_t G, char **names, int n){
	int result = 1;
	int *id = malloc(n * sizeof *id);
	for(int i = 0; i<n; i++) id[i] = STsearch(G->tab,names[i]);
	
	if(G->flag_list){
		//Liste di adiacenze
		//Siccome non è orientato controllo semplicemente due vettori, se trovo corrispondenza per gli altri 2 è sottografo
		for(int i = 0; i<n-1; i++){
            int found = 0;
            for(node_t x = G->ladj[id[i]]; x != G->z; x = x->next){
                // Confronto diretto di puntatori
                if (x->info == G->nodes[id[(i+1)%n]]) found++;
                if (i == 0 && x->info == G->nodes[id[2]]) found++;
                else if (i != 0 && x->info == G->nodes[id[i-1]]) found++;
            }
            result = result && (found == n-1); // Se ne ho trovati 2 in entrambi i casi resta 1
        }
	}else{
		//Matrice di adiacenza
		result = 	G->madj[id[0]][id[1]] != 0 && 
					G->madj[id[0]][id[2]] != 0 && 
					G->madj[id[1]][id[2]] != 0; 
	}

	free(id);
	return result;
}


		// 	for(int j = 0; j<G->V; j++)
		// 		printf("%d ",G->madj[i][j]);
		// 	printf("\n");
		// }