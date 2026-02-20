#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/HT.h"

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
    el->heap_pos = -1;
    return el;
}

int main() {
    printf("=== Test Hash Table con Double Hashing ===\n\n");
    
    // Inizializza hash table: maxN=10, load factor r=0.75
    ht_t ht = HTinit(10, 0.75);
    if(ht == NULL) {
        printf("Errore: impossibile creare hash table\n");
        return 1;
    }
    
    printf("Hash table creata (maxN=10, r=0.75)\n");
    printf("Tabella vuota? %s\n", HTempty(ht) ? "SI" : "NO");
    printf("Elementi: %d\n\n", HTcount(ht));
    
    // Test inserimento
    printf("--- Test Inserimento ---\n");
    char *nomi[] = {"Alice", "Bob", "Charlie", "Diana", "Eve"};
    int prio[] = {5, 3, 8, 2, 7};
    
    for(int i = 0; i < 5; i++) {
        element_t el = createElement(nomi[i], prio[i]);
        if(el == NULL) {
            printf("Errore allocazione per %s\n", nomi[i]);
            continue;
        }
        
        int index = HTinsert(ht, el);
        if(index >= 0) {
            printf("Inserito '%s' (prio=%d) all'indice %d\n", nomi[i], prio[i], index);
        } else {
            printf("Errore inserimento '%s'\n", nomi[i]);
            free(el->str);
            free(el);
        }
    }
    
    printf("\nElementi dopo inserimento: %d\n", HTcount(ht));
    printf("Tabella vuota? %s\n\n", HTempty(ht) ? "SI" : "NO");
    
    // Test ricerca
    printf("--- Test Ricerca ---\n");
    char *cerca[] = {"Alice", "Bob", "Frank", "Eve"};
    
    for(int i = 0; i < 4; i++) {
        int index = HTsearch(ht, cerca[i]);
        if(index >= 0) {
            printf("'%s' trovato all'indice %d\n", cerca[i], index);
        } else {
            printf("'%s' NON trovato\n", cerca[i]);
        }
    }
    
    // Test ricerca per indice
    printf("\n--- Test Ricerca per Indice ---\n");
    for(int i = 0; i < 5; i++) {
        element_t el = HTsearchByIndex(ht, i);
        if(el != NULL) {
            printf("Indice %d: '%s'\n", i, el->str);
        } else {
            printf("Indice %d: vuoto\n", i);
        }
    }
    
    // Test inserimento duplicato
    printf("\n--- Test Duplicato ---\n");
    element_t dup = createElement("Alice", 10);
    int index = HTinsert(ht, dup);
    if(index < 0) {
        printf("'Alice' già presente (corretto)\n");
        free(dup->str);
        free(dup);
    } else {
        printf("ERRORE: duplicato inserito!\n");
    }
    
    // Cleanup
    printf("\n--- Cleanup ---\n");
    HTfree(ht);
    printf("Hash table liberata\n");
    
    return 0;
}
