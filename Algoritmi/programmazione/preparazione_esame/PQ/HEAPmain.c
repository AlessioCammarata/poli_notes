#include <stdio.h>
#include <stdlib.h>

#include "lib/heap.h"

int main(void) {
    int dati[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int len = 10;

    heap_t h1 = HEAP_init(len);
    for(int i = 0; i<len; i++) add_val(h1, dati[i]);

    printf("\n--- TEST 1: HEAPmin ---\n");
    printf("Input: "); print_heap(h1);

    // Scommenta quando hai scritto le funzioni
    build_min_heap(h1);
    printf("Heap costruito: "); print_heap(h1);
    
    HEAPfree(h1);

    // CASO 2: Test per HEAPSORT (Array disordinato)
    heap_t h2 = HEAP_init(len);
    for(int i = 0; i<len; i++) add_val(h2, dati[i]);

    printf("\n--- TEST 2: HEAPSORT - max ---\n");
    printf("Input: "); print_heap(h2);

    // Scommenta quando hai scritto le funzioni
    build_max_heap(h2);
    printf("Heap costruito: "); print_heap(h2);
    
    heap_sort(h2);
    
    printf("Ordinato: "); print_heap(h2);
    // Risultato atteso: [ (1) (2) (3) (4) (7) (8) (9) (10) (14) (16) ]
    HEAPfree(h2);

    return 0;
}