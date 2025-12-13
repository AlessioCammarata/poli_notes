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

#define NMAX 30

static int find_or_add(vertex_t *nodes, int *nn, char *name, char *net) {
    for (int i = 0; i < *nn; i++) {
        if (strcmp(nodes[i]->elab, name) == 0) return i;
    }
    // add: crea nuovo nodo con NEW
    nodes[*nn] = NEW_vertex(name, net); // flow=0 per i nodi puri
    return (*nn)++;
}

int main(int argc, char *argv[]){
    FILE *fin;
    char net1[NMAX], net2[NMAX], id1[NMAX], id2[NMAX];
    int eval = 0, nEdges = 0, nNodes = 0, val;

    if (argc < 2) {
        fprintf(stderr, "Uso: %s come file_grafo\n", argv[0]);
        return 1;
    }
    fprintf(stderr, "Uso: %s come file_grafo\n", argv[1]);
    const char *nfin = argv[1];

    if((fin = fopen(nfin,"r")) == NULL){
        perror("Apertura file");
        return 1;
    }
    while(fscanf(fin,"%s %s %s %s %d\n",id1,net1,id2,net2,&val) == 5) eval++;
    fclose(fin);

    if((fin = fopen(nfin,"r")) == NULL){
        perror("Apertura file");
        return 1;
    }

    // dimensione massima stimata; se serve usa realloc
    edge_t *edges = malloc(sizeof(edge_t) * eval * 2);
    vertex_t *nodes = malloc(sizeof(vertex_t) * eval * 2);  // Array di puntatori a nodi
    if (!edges || !nodes) { 
        perror("malloc"); 
        return 1; 
    }

    while(fscanf(fin,"%s %s %s %s %d\n",id1,net1,id2,net2,&val) == 5) {

        int u = find_or_add(nodes, &nNodes, id1, net1);
        int v = find_or_add(nodes, &nNodes, id2, net2);
        if (u < 0 || v < 0) { 
            fclose(fin); 
            return 1; 
        }
        if (u == v) continue; // niente cappi

        edges[nEdges] = EDGEcreate(nodes[u], nodes[v], val);
        nEdges++;

    }
    fclose(fin);

    graph_t graph = GRAPHinit(nNodes);
    // Inserisci gli archi nella matrice di adiacenza dell'ADT
    for (int i = 0; i < nEdges; i++) {
        GRAPHinsertEdge(graph, edges[i].node1, edges[i].node2, edges[i].flow);
    }

    int end = 0, choose;
    while(!end){
        printf("Cosa vuoi fare?\n");
        printf("0. Esci\n");
        printf("1. Stampa in ordine\n");
        printf("2. Verifica adiacenza a coppie\n");
        printf("3. Genera le liste di adiacenza\n");
        scanf("%d",&choose);

        switch (choose)
        {
        case 0:
            end = 1;
            break;
        case 1:
            ORDERprint(stdout,graph);
            break;
        case 2:
            int n = 3;
            char **names = malloc(n* sizeof(char*));
            for(int i = 0; i<n; i++){
                names[i] = malloc(NMAX*sizeof(char));
                printf("Inserisci il valore del nodo %d\n",i+1);
                scanf("%29s",names[i]);
                while(ExistName(graph,names[i]) == -1){
                    printf("Reinserisci il valore del nodo %d\n",i+1);
                    scanf("%29s",names[i]);
                }
            }
            if(subGraph(graph, names, n)) printf("I %d nodi formano un sottografo completo\n",n);
            else printf("I %d nodi non formano un sottografo completo\n",n);

            for(int i = 0; i<n; i++) free(names[i]);
            free(names);
            break;
        case 3:
            GRAPHinitList(graph);
            GRAPHinsertEdgeList(graph);
            printf("Liste di adiacenza create con successo!\n");
            break;
        default:
            printf("Inserisci un valore valido\n");
        }
        printf("\n");
    }

    // cleanup
    GRAPHfree(graph);
    // Libera tutti i vertex_t creati con NEW_vertex
    for (int i = 0; i < nNodes; i++) {
        if (nodes[i]) free(nodes[i]); // FIX: libera ogni struct vertex_s
    }
    free(nodes);
    free(edges);
    return 0;
}