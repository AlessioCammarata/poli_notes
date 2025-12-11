// <id_elab1> <id_rete1> <id_elab2> <id_rete2> <flusso>
/*
- i nomi dei singoli nodi sono univoci all'interno del grafo
- non sono ammessi cappi
- tra due nodi c'è al massimo un arco (non è un multigrafo)
- le sotto-reti sono sotto-grafi non necessariamente connessi.

- il grafo sia implementato come ADT di I classe, predisposto in modo tale da poter contenere sia
la matrice sia le liste di adiacenza. Nella fase di caricamento dei dati da file si generi solamente la
matrice di adiacenza, su comando esplicito va generata anche la lista di adiacenza
- si utilizzi una tabella di simboli tale da fornire corrispondenze “da nome a indice” e “da indice a
nome”. 
DOPO:
- elencare in ordine alfabetico i vertici e per ogni vertice gli archi che su di esso insistono, sempre
in ordine alfabetico
- dati 3 vertici i cui nomi sono letti da tastiera, verificare se essi sono adiacenti a coppie, cioè se
formano un sottografo completo. Tale funzione sia implementata sia per la rappresentazione con
matrice delle adiacenze, sia per la rappresentazione con lista delle adiacenze
- generare la rappresentazione a lista di adiacenza, SENZA leggere nuovamente il file, a partire da
quella a matrice di adiacenza. 

*/
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define nfin "./grafo.txt"
#define NMAX 30

typedef struct {
    int u, v;
    int w;
} Edge;

static int find_or_add(char **nodes, int *nn, const char *name) {
    for (int i = 0; i < *nn; i++) {
        if (strcmp(nodes[i], name) == 0) return i;
    }
    // add: duplica la stringa e salva il puntatore
    nodes[*nn] = _strdup(name);              // su Windows; su POSIX usa strdup
    if (!nodes[*nn]) { perror("strdup"); return -1; }
    return (*nn)++;
}

int main(void){
    FILE *fin;
    char net1[NMAX], net2[NMAX], id1[NMAX], id2[NMAX];
    int val, nEdges = 0, nNodes = 0;;

    if((fin = fopen(nfin,"r")) == NULL){
        perror("Apertura file");
        return 1;
    }

    // dimensione massima stimata; se serve usa realloc
    Edge *edges = malloc(sizeof(Edge) * 1024);
    char **nodes = calloc(1024, sizeof(char*));        // array di stringhe
    if (!edges || !nodes) { 
        perror("malloc"); 
        return 1; 
    }

    while(fscanf(fin,"%s %s %s %s %d\n",id1,net1,id2,net2,&val) == 5) {

        int u = find_or_add(nodes, &nNodes, id1);
        int v = find_or_add(nodes, &nNodes, id2);
        if (u < 0 || v < 0) { 
            fclose(fin); 
            return 1; 
        }
        if (u == v) continue; // niente cappi

        edges[nEdges++] = (Edge){ u, v, val };
        edges[nEdges++] = (Edge){ v, u, val }; //Arco inverso
    }
    fclose(fin);

    graph_t graph = graph_init(nNodes,0);
    // inserisci gli archi nella matrice di adiacenza dell'ADT
    for (int i = 0; i < nEdges; i++) {
        graph_insert(graph, edges[i].u, edges[i].v, edges[i].w);
    }

    // cleanup
    for (int i = 0; i < nNodes; i++) free(nodes[i]);
    free(nodes);
    free(edges);
    return 0;
}