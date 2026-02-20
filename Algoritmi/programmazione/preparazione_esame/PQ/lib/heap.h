#ifndef HEAP_H_DEFINED
#define HEAP_H_DEFINED

#include <stdio.h>
#include <stdlib.h>

// Calcolano la posizione dei figli e del padre nel vettore
#define LEFT(i)   ((2 * (i)) + 1)
#define RIGHT(i)  ((2 * (i)) + 2)
#define PARENT(i) (((i) - 1) / 2)

typedef struct Heap *heap_t;

heap_t HEAP_init(int size);
void add_val(heap_t h, int val);
void swap(int *a, int *b);
void print_heap(heap_t h);
void max_heapify(heap_t h, int i);
void min_heapify(heap_t h, int i);
void build_min_heap(heap_t h);
void build_max_heap(heap_t h);
void heap_sort(heap_t h);
void HEAPfree(heap_t h);

#endif // HEAP_H_DEFINED