#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/graph.h"

int main(){
    // Crea un grafo con 5 vertici
    graph_t G = GRAPHinit(5);
    if(G == NULL){
        printf("Errore nella creazione del grafo\n");
        return 1;
    }

    // Alloca le stringhe manualmente (simula lettura da file)
    char *str0 = malloc(strlen("A") + 1);
    strcpy(str0, "A");
    char *str1 = malloc(strlen("B") + 1);
    strcpy(str1, "B");
    char *str2 = malloc(strlen("C") + 1);
    strcpy(str2, "C");
    char *str3 = malloc(strlen("D") + 1);
    strcpy(str3, "D");
    char *str4 = malloc(strlen("E") + 1);
    strcpy(str4, "E");
    
    // Crea i vertici (passando le stringhe già allocate)
    vertex_t v0 = NEW_vertex(0, str0);
    vertex_t v1 = NEW_vertex(1, str1);
    vertex_t v2 = NEW_vertex(2, str2);
    vertex_t v3 = NEW_vertex(3, str3);
    vertex_t v4 = NEW_vertex(4, str4);

    // Aggiungi i vertici al grafo tramite la funzione pubblica
    GRAPHaddVertex(G, v0);
    GRAPHaddVertex(G, v1);
    GRAPHaddVertex(G, v2);
    GRAPHaddVertex(G, v3);
    GRAPHaddVertex(G, v4);

    // Inserisci archi (grafo non orientato)
    printf("Creazione del grafo...\n");
    GRAPHinsertEdge(G, v0, v1, 1);  // A-B
    GRAPHinsertEdge(G, v0, v2, 1);  // A-C
    GRAPHinsertEdge(G, v1, v3, 1);  // B-D
    GRAPHinsertEdge(G, v2, v3, 1);  // C-D
    GRAPHinsertEdge(G, v3, v4, 1);  // D-E

    // Stampa il grafo
    printf("\nStruttura del grafo (liste di adiacenza):\n");
    GRAPHprint(G);

    // Esegui DFS
    printf("\n========== DFS (Depth-First Search) ==========\n");
    printf("Classificazione degli archi:\n");
    GRAPHdfs(G);

    // Esegui BFS
    printf("\n========== BFS (Breadth-First Search) ==========\n");
    printf("Esplorazione per livelli con tracciamento (pre, parent, dist):\n");
    GRAPHbfs(G);

    // Esegui Kruskal
    printf("\n========== KRUSKAL (Minimum Spanning Tree) ==========\n");
    edge_t *mst_kruskal = NULL;
    int mst_size = kruskal(G, &mst_kruskal);
    if(mst_size > 0){
        printf("MST trovato con %d archi:\n", mst_size);
        int total_weight = 0;
        for(int i = 0; i < mst_size; i++){
            printf("(%d-%d) weight: %d\n", 
                   mst_kruskal[i].node1->id, 
                   mst_kruskal[i].node2->id, 
                   mst_kruskal[i].weight);
            total_weight += mst_kruskal[i].weight;
        }
        printf("Peso totale MST (Kruskal): %d\n", total_weight);
        free(mst_kruskal);
    } else {
        printf("Errore nel calcolo di Kruskal\n");
    }

    // Esegui Prim
    printf("\n========== PRIM (Minimum Spanning Tree) ==========\n");
    Prim(G);


    // Libera memoria delle stringhe e dei vertici
    free(v0->val); free(v0);
    free(v1->val); free(v1);
    free(v2->val); free(v2);
    free(v3->val); free(v3);
    free(v4->val); free(v4);

    // Libera il grafo
    GRAPHfree(G);
    printf("\nGrafo liberato correttamente.\n");

    return 0;
}
