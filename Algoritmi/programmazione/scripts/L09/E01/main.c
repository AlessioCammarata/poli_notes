/*
Un grafo pesato, orientato e connesso è memorizzato in un file di testo grafo.txt con il seguente
formato:
 sulla prima riga un intero N rappresenta il numero di vertici del grafo
 seguono N righe ciascuna delle quali contiene una stringa alfanumerica, di al massimo 30
caratteri rappresentante l’identificatore univoco del nodo
 seguono un numero indefinito di terne <id_1> <id_2> <peso_arco> a rappresentare gli
archi orientati del grafo. Il peso è un valore intero non negativo.
Si scriva un programma C che svolga le seguenti operazioni:
 individuazione di tutti gli insiemi di archi di cardinalità minima la cui rimozione renda il grafo
originale un DAG
 costruzione di un DAG rimuovendo, tra tutti gli insiemi di archi generati al passo precedente,
quelli dell’insieme a peso massimo. Il peso di un insieme di archi è definito come la somma dei
pesi degli archi in esso contenuti
 calcolo delle distanze massime da ogni nodo sorgente verso ogni nodo del DAG costruito al
passo precedente (cfr lucidi cap. 14).
*/
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L09/E01/grafo3.txt"
#define NMAX 30

static int find(vertex_t *nodes, int nn, char *id) {
    for (int i = 0; i < nn; i++) {
        if (strcmp(nodes[i]->id, id) == 0) return i;
    }
    return -1;
}

static void combinations(int *arr, int n, int k, int start, int *current, int idx, 
    edge_t *edges, graph_t graph, int ***solutions, int *nSol, int *minCard);
static void findMinimalSets(edge_t *edges, int nEdges, graph_t graph, int ***solutions, int *nSol, int *minCard, graph_t *dag);

int main(void){
    FILE *fin;
    char id1[NMAX], id2[NMAX];
    int nEdges = 0, nNodes, val;

    if((fin = fopen(nfin,"r")) == NULL){
        perror("Apertura file");
        return 1;
    }
    if(fscanf(fin,"%d",&nNodes) != 1){
        perror("Formato del file errato");
        fclose(fin);
        return 1;
    }

    // dimensione massima stimata
    edge_t *edges = malloc(sizeof(edge_t) * nNodes * 2);
    vertex_t *nodes = malloc(sizeof(vertex_t) * nNodes);  // Array di puntatori a nodi
    if (!edges || !nodes) { 
        perror("malloc"); 
        return 1; 
    }

    //Leggo i nodi
    for(int i = 0; i<nNodes; i++) 
        if(fscanf(fin,"%s",id1) == 1){
            nodes[i] = NEW_vertex(id1);
        }

    //Leggo gli edge
    while(fscanf(fin,"%s %s %d\n",id1,id2,&val) == 3) {

        int u = find(nodes, nNodes, id1);
        int v = find(nodes, nNodes, id2);
        if (u < 0 || v < 0) {
            perror("Formato del file errato");
            fclose(fin);
            free(nodes); free(edges);
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
        GRAPHinsertEdge(graph, edges[i].node1, edges[i].node2, edges[i].weight);
    }

    ClassifyEdges(graph, edges);
    graph_t dag = NULL;
    int end = 0, choose, nSol = 0, minCard = 0, **solutions = NULL;
    while(!end){
        printf("Cosa vuoi fare?\n");
        printf("0. Esci\n");
        printf("1. Individua DAG\n");
        printf("2. Costruisci DAG\n");
        printf("3. Distanze massime\n");
        scanf("%d",&choose);

        switch (choose){
            case 0:
                end = 1;
                break;
            case 1:
                printf("Individuazione insiemi DAG:\n");
                nSol = 0;
                minCard = 0;
                solutions = NULL;
                findMinimalSets(edges, nEdges, graph, &solutions, &nSol, &minCard, &dag);
                break;
            case 2:
                if (nSol == 0) {
                    printf("Esegui prima il case 1\n");
                    break;
                }

                if(dag){
                    printf("DAG gia creato!");
                    break;
                }

                //Soluzione a peso massimo
                int maxWeight = 0, maxIndex = 0;
                for(int i = 0; i<nSol; i++){
                    int w = 0;
                    for(int j = 0; j < minCard; j++){
                        w += edges[solutions[i][j]].weight;
                    }
                    if(w > maxWeight){
                        maxWeight = w;
                        maxIndex = i;
                    }
                }

                //Costruzione DAG
                dag = GRAPHinit(nNodes);
                for (int i = 0; i < nEdges; i++) {
                    int skip = 0;
                    for (int j = 0; j < minCard; j++) {
                        if (i == solutions[maxIndex][j]) {
                            skip = 1;
                            break;
                        }
                    }
                    if (!skip) { //Escludo l'arco
                        GRAPHinsertEdge(dag, edges[i].node1, edges[i].node2, edges[i].weight);
                    }
                }
                printf("DAG costruito rimuovendo soluzione %d (peso %d)\n", maxIndex+1, maxWeight);

                break;
            case 3:
                if (!dag) {
                    printf("Esegui prima il case 2!\n");
                    break;
                }

                //Ordinamento topologico
                int *topoOrder = topologicalSort(dag);

                for(int i = 0; i<nNodes; i++){
                    int *dist = malloc(nNodes * sizeof(int));

                    for(int j = 0; j<nNodes; j++) dist[j] = INT_MIN;
                    dist[i] = 0;

                    for(int j = 0; j<nNodes; j++){
                        int v = topoOrder[j];
                        if(dist[v] != INT_MIN){
                            for(int k = 0; k<nNodes; k++){
                                int weight = getEdgeWeight(dag, v, k);
                                if(weight > 0)
                                    dist[k] = (dist[k] < dist[v] + weight) ? dist[v] + weight : dist[k];
                            }
                        }
                    }

                    printf("Distanze massime da %s:\n", nodes[i]->id);
                    for(int j = 0; j < nNodes; j++)
                        if(dist[j] != INT_MIN && j != i)
                            printf(" -> %s: %d", nodes[j]->id, dist[j]);
                    printf("\n");
                    free(dist);
                }
                free(topoOrder);
                break;
            default:
                printf("Inserisci un valore valido\n");
        }
        printf("\n");
    }

    // cleanup
    GRAPHfree(graph);
    if(dag) GRAPHfree(dag);
    // Libera tutti i vertex_t creati con NEW_vertex
    for (int i = 0; i < nNodes; i++) {
        if (nodes[i]) free(nodes[i]); // FIX: libera ogni struct vertex_s
    }
    free(nodes);
    free(edges);
    for(int i = 0; i<nSol; i++){
        free(solutions[i]);
    }
    free(solutions);
    return 0;
}

// Genera combinazioni di k elementi da un array
static void combinations(int *arr, int n, int k, int start, int *current, int idx,
                         edge_t *edges, graph_t graph, int ***solutions, int *nSol, int *minCard) {
    if (idx == k) {
        // Verifica se rimuovendo questi archi il grafo diventa DAG
        if (GRAPHisDAGwithout(graph, edges, current, k)) {
            // Salva questa soluzione
            *solutions = realloc(*solutions, (*nSol + 1) * sizeof(int*));
            (*solutions)[*nSol] = malloc(k * sizeof(int));
            for (int i = 0; i < k; i++) {
                (*solutions)[*nSol][i] = current[i];
            }
            (*nSol)++;
            *minCard = k;
        }
        return;
    }
    
    for (int i = start; i <= n - k + idx; i++) {
        current[idx] = arr[i];
        combinations(arr, n, k, i + 1, current, idx + 1, edges, graph, solutions, nSol, minCard);
    }
}

static void findMinimalSets(edge_t *edges, int nEdges, graph_t graph, int ***solutions, int *nSol, int *minCard, graph_t *dag) {
    int *backEdges = malloc(nEdges * sizeof(int));
    int nBack = 0;
    
    for (int i = 0; i < nEdges; i++)
        if(edges[i].type == Back) 
            backEdges[nBack++] = i; //Mi salvo gli indici dei B edges e li conto
    
    if (nBack == 0) {
        printf("\nIl grafo è già un DAG!\n");
        free(backEdges);
        *dag = graph;
        return;
    }
    
    printf("\nBack edges trovati: %d \n", nBack);
    
    // Prova cardinalità crescente
    int *current = malloc(nBack * sizeof(int));
    
    for (int k = 1; k <= nBack && *nSol == 0; k++) {
        combinations(backEdges, nEdges, k, 0, current, 0, edges, graph, solutions, nSol, minCard);
    }
    
    if (*nSol > 0) {
        printf("\n");
        printf("Cardinalità minima: %d archi\n", *minCard);
        printf("Numero di soluzioni trovate: %d\n\n", *nSol);
        
        for (int i = 0; i < *nSol; i++) {
            printf("Soluzione %d:\n", i + 1);
            int totalWeight = 0;
            for (int j = 0; j < *minCard; j++) {
                int idx = (*solutions)[i][j];
                printf("  - %s -> %s (peso %d)\n", 
                       edges[idx].node1->id, edges[idx].node2->id, edges[idx].weight);
                totalWeight += edges[idx].weight;
            }
            printf("Peso totale: %d\n\n", totalWeight);
        }
    } else {
        printf("\nNessuna soluzione trovata.\n");
    }
    
    free(current);
    free(backEdges);
}