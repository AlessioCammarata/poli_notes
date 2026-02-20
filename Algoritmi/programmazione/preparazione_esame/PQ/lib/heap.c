#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

struct Heap{
    int *array;     // Il puntatore ai dati
    int heap_size;  // Quanti elementi dell'array fanno parte dell'heap attivo
    int length;     // Dimensione totale allocata dell'array
};

heap_t HEAP_init(int size){
    heap_t h = malloc(sizeof(*h));
    if(h==NULL) return NULL;
    h->array = malloc(size*sizeof(int));
    if(h->array == NULL){
        free(h);
        return NULL;
    }
    h->heap_size = 0;
    h->length = size;
    return h;
}

void add_val(heap_t h, int val){
    if(h->heap_size >= h->length) return;
    h->array[h->heap_size++] = val;
}

// Scambia due interi (passati per riferimento)
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Stampa il vettore
void print_heap(heap_t h) {
    printf("[ ");
    for (int i = 0; i < h->heap_size; i++) {
        printf("%d ", h->array[i]);
    }
    printf("]\n");
}

// --- SPAZIO PER I TUOI METODI (ESERCIZIO) ---

/* * ESERCIZIO 1: Max-Heapify
 * Scopo: Assumendo che i figli di 'i' siano già heap, fai scendere A[i] 
 * finché non rispetta la proprietà (Padre >= Figli).
 */
void max_heapify(heap_t h, int i) {
    int l, r, largest;
    l = LEFT(i);
    r = RIGHT(i);
    if(l<h->heap_size && h->array[i] < h->array[l])
        largest = l;
    else 
        largest = i;
    if(r<h->heap_size && h->array[largest] < h->array[r])
        largest = r;
    if(largest != i){
        swap(&h->array[i], &h->array[largest]);
        max_heapify(h,largest);
    }

}

void min_heapify(heap_t h, int i) {
    int l, r, smallest;
    l = LEFT(i);
    r = RIGHT(i);
    if(l<h->heap_size && h->array[i] > h->array[l])
        smallest = l;
    else 
        smallest = i;
    if(r<h->heap_size && h->array[smallest] > h->array[r])
        smallest = r;
    if(smallest != i){
        swap(&h->array[i], &h->array[smallest]);
        min_heapify(h,smallest);
    }

}

void build_min_heap(heap_t h){
    int i;
    for(i = (h->heap_size/2) - 1; i>=0; i--){
        min_heapify(h,i);
    }
}

/* * ESERCIZIO 2: Build-Max-Heap
 * Scopo: Trasforma un array disordinato in un Max-Heap.
 * Logica: Chiama heapify partendo da metà array indietro fino a 0.
 */
void build_max_heap(heap_t h) {
    int i;
    for(i = (h->heap_size/2) -1;i>=0;i-- ){
        max_heapify(h,i);
    }
}

/* * ESERCIZIO 3: Heapsort
 * Scopo: Ordina l'array usando le funzioni precedenti.
 */
void heap_sort(heap_t h) {
    int i,j;
    build_max_heap(h);
    j = h->heap_size;
    for(i = h->heap_size-1; i>0; i--){
        swap(&h->array[i], &h->array[0]);
        h->heap_size--;
        max_heapify(h,0);
    }
    h->heap_size = j; //Ristabilisco la size
}

void HEAPfree(heap_t h){
    free(h->array);
    free(h);
}