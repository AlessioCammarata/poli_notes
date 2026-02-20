#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/PQHT.h"

element_t createElement(char *str, int prio) {
    element_t el = malloc(sizeof(struct element_s));
    if(el == NULL) return NULL;
    
    el->str = malloc(strlen(str) + 1);
    if(el->str == NULL) {
        free(el);
        return NULL;
    }
    strcpy(el->str, str);
    el->prio = prio;
    return el;
}

int main() {
    printf("=== Test Priority Queue con Hash Table ===\n\n");
    
    PQ pq = PQHTinit(10, 0.75);
    if(pq == NULL) {
        printf("Errore inizializzazione PQ\n");
        return 1;
    }
    
    printf("Priority Queue creata (maxN=10, r=0.75)\n");
    printf("PQ vuota? %s\n", PQHTempty(pq) ? "SI" : "NO");
    printf("Elementi: %d\n\n", PQHTsize(pq));
    
    printf("--- Test Inserimento ---\n");
    char *nomi[] = {"Alice", "Bob", "Charlie", "Diana", "Eve"};
    int prio[] = {5, 3, 8, 2, 7};
    
    for(int i = 0; i < 5; i++) {
        element_t el = createElement(nomi[i], prio[i]);
        PQHTinsert(pq, el);
        printf("Inserito '%s' con priorità %d\n", nomi[i], prio[i]);
    }
    
    printf("\nElementi dopo inserimento: %d\n", PQHTsize(pq));
    printf("PQ vuota? %s\n\n", PQHTempty(pq) ? "SI" : "NO");
    
    printf("--- Contenuto PQ (heap order) ---\n");
    PQHTdisplay(pq);
    
    printf("\n--- Test ShowMax ---\n");
    element_t max = PQHTshowMax(pq);
    if(max != NULL)
        printf("Elemento con priorità massima: '%s' (prio=%d)\n", max->str, max->prio);
    
    printf("\n--- Test Change Priority ---\n");
    element_t change_el = createElement("Bob", 10);
    printf("Cambio priorità di 'Bob' da 3 a 10\n");
    PQHTchange(pq, change_el);
    free(change_el->str);
    free(change_el);
    
    printf("\nContenuto dopo change:\n");
    PQHTdisplay(pq);
    
    max = PQHTshowMax(pq);
    if(max != NULL)
        printf("\nNuovo massimo: '%s' (prio=%d)\n", max->str, max->prio);
    
    printf("\n--- Test ExtractMax ---\n");
    for(int i = 0; i < 3; i++) {
        element_t extracted = PQHTextractMax(pq);
        if(extracted != NULL) {
            printf("Estratto: '%s' (prio=%d) - Rimangono %d elementi\n", 
                   extracted->str, extracted->prio, PQHTsize(pq));
            free(extracted->str);
            free(extracted);
        }
    }
    
    printf("\nContenuto dopo extractMax:\n");
    PQHTdisplay(pq);
    
    printf("\n--- Test Change su elemento non esistente ---\n");
    element_t fake = createElement("Frank", 5);
    PQHTchange(pq, fake);
    free(fake->str);
    free(fake);
    
    printf("\n--- Cleanup ---\n");
    PQHTfree(pq);
    printf("Priority Queue liberata\n");
    
    return 0;
}