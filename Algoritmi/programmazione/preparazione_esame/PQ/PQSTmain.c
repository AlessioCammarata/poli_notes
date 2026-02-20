#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/ST.h"
#include "lib/PQST.h"

int main(void) {
    
    PQ pq = PQSTinit(10);
    if(!pq){
        perror("malloc");
        return -1;
    }

    // Test 1: PQempty su una coda vuota
    printf("--- TEST: PQempty (coda vuota) ---\n");
    printf("PQ vuota? %s\n\n", PQSTempty(pq) ? "Sì" : "No");

    // Test 2: PQinsert - inserisci elementi
    printf("--- TEST: PQinsert ---\n");
    
    element_t elem1 = malloc(sizeof(struct element_s));
    elem1->val = "Alice";
    elem1->prio = 5;
    PQSTinsert(pq, elem1);
    printf("Inserito: %s (priorità %d)\n", elem1->val, elem1->prio);
    
    element_t elem2 = malloc(sizeof(struct element_s));
    elem2->val = "Bob";
    elem2->prio = 10;
    PQSTinsert(pq, elem2);
    printf("Inserito: %s (priorità %d)\n", elem2->val, elem2->prio);
    
    element_t elem3 = malloc(sizeof(struct element_s));
    elem3->val = "Charlie";
    elem3->prio = 3;
    PQSTinsert(pq, elem3);
    printf("Inserito: %s (priorità %d)\n", elem3->val, elem3->prio);
    
    element_t elem4 = malloc(sizeof(struct element_s));
    elem4->val = "Diana";
    elem4->prio = 8;
    PQSTinsert(pq, elem4);
    printf("Inserito: %s (priorità %d)\n\n", elem4->val, elem4->prio);

    // Test 3: PQsize e PQempty
    printf("--- TEST: PQsize e PQempty ---\n");
    printf("Dimensione PQ: %d\n", PQSTsize(pq));
    printf("PQ vuota? %s\n\n", PQSTempty(pq) ? "Sì" : "No");

    // Test 4: PQshowMax e PQdisplay
    printf("--- TEST: PQshowMax e PQdisplay ---\n");
    element_t maxElem = PQSTshowMax(pq);
    printf("Massimo (senza estrarre): %s (priorità %d)\n", maxElem->val, maxElem->prio);
    printf("Contenuto PQ:\n");
    PQSTdisplay(pq);
    printf("\n");

    // Test 5: PQchange - modifica priorità
    printf("--- TEST: PQchange ---\n");
    element_t changeElem = malloc(sizeof(struct element_s));
    changeElem->val = "Charlie";
    changeElem->prio = 12;  // Aumenta da 3 a 12
    printf("Cambio priorità di Charlie: 3 → 12\n");
    PQSTchange(pq, changeElem);
    printf("Nuovo massimo: %s (priorità %d)\n", PQSTshowMax(pq)->val, PQSTshowMax(pq)->prio);
    printf("Contenuto PQ dopo cambio:\n");
    PQSTdisplay(pq);
    printf("\n");
    free(changeElem);

    // Test 6: PQextractMax - estrai tutti gli elementi
    printf("--- TEST: PQextractMax ---\n");
    while(!PQSTempty(pq)) {
        element_t extracted = PQSTextractMax(pq);
        printf("Estratto: %s (priorità %d), Dimensione rimanente: %d\n", 
               extracted->val, extracted->prio, PQSTsize(pq));
    }
    printf("\n");

    // Test 7: PQempty dopo estrazioni
    printf("--- TEST: PQempty (dopo estrazioni) ---\n");
    printf("PQ vuota? %s\n\n", PQSTempty(pq) ? "Sì" : "No");

    PQSTfree(pq);
    printf("Memoria liberata.\n");

    return 0;
}
