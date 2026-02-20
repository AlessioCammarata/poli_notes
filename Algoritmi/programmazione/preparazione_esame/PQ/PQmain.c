#include <stdio.h>
#include <stdlib.h>

#include "lib/PQ.h"

int main(void) {
    int dati[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int len = 10;

    PQ pq = PQinit(len);
    if(!pq){
        perror("malloc");
        return -1;
    }

    // Test 1: PQempty su una coda vuota
    printf("--- TEST: PQempty (coda vuota) ---\n");
    printf("PQ vuota? %s\n", PQempty(pq) ? "Sì" : "No");

    // Test 2: PQinsert - inserisci tutti i dati
    printf("\n--- TEST: PQinsert ---\n");
    for(int i = 0; i < len; i++) {
        PQinsert(pq, dati[i]);
        printf("Inserito %d\n", dati[i]);
    }

    // Test 3: PQsize e PQempty
    printf("\n--- TEST: PQsize e PQempty ---\n");
    printf("Dimensione PQ: %d\n", PQsize(pq));
    printf("PQ vuota? %s\n", PQempty(pq) ? "Sì" : "No");

    // Test 4: PQshowMax e PQdisplay
    printf("\n--- TEST: PQshowMax e PQdisplay ---\n");
    printf("Massimo (senza estrarre): %d\n", PQshowMax(pq));
    printf("Contenuto PQ: "); PQdisplay(pq); printf("\n");

    // Test 5: PQextractMax - estrai tutti gli elementi
    printf("\n--- TEST: PQextractMax ---\n");
    while(!PQempty(pq)) {
        int max = PQextractMax(pq);
        printf("Estratto: %d, Dimensione rimanente: %d, Contenuto: ", max, PQsize(pq));
        PQdisplay(pq);
        printf("\n");
    }

    // Test 6: PQempty su coda vuota
    printf("\n--- TEST: PQempty (dopo estrazioni) ---\n");
    printf("PQ vuota? %s\n", PQempty(pq) ? "Sì" : "No");

    PQfree(pq);
    printf("\nMemoria liberata.\n");

    // Test 7: PQchange - modifica la priorità di un elemento
    printf("\n--- TEST: PQchange ---\n");
    int dati2[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int len2 = 10;
    
    PQ pq2 = PQinit(len2);
    for(int i = 0; i < len2; i++) {
        PQinsert(pq2, dati2[i]);
    }
    
    printf("Heap iniziale: "); PQdisplay(pq2); printf("\n");
    printf("Massimo: %d\n", PQshowMax(pq2));
    
    // Cambio 8 → 15
    printf("\nCambio 8 → 15\n");
    PQchange(pq2, 8, 15);
    printf("Heap dopo cambio: "); PQdisplay(pq2); printf("\n");
    printf("Nuovo massimo: %d\n", PQshowMax(pq2));
    
    // Cambio 1 → 20
    printf("\nCambio 1 → 20\n");
    PQchange(pq2, 1, 20);
    printf("Heap dopo cambio: "); PQdisplay(pq2); printf("\n");
    printf("Nuovo massimo: %d\n", PQshowMax(pq2));
    
    // Prova a cambiare un elemento inesistente
    printf("\nProvo a cambiare elemento non presente: 100 → 50\n");
    PQchange(pq2, 100, 50);

    PQfree(pq2);
    printf("\nMemoria liberata.\n");

    return 0;
}