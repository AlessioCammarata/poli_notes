#ifndef PQHT_H_DEFINED
#define PQHT_H_DEFINED

#include <stdio.h>
#include <stdlib.h>

#include "HT.h"

typedef struct pqueue *PQ;
typedef struct element_s {
    char *str;
    int prio;
} *element_t;

PQ PQHTinit(int maxN, float r);
void PQHTfree(PQ pq); 
int PQHTempty(PQ pq);
int PQHTsize(PQ pq);
element_t PQHTshowMax(PQ pq);
void PQHTdisplay(PQ pq); 
void PQHTinsert(PQ pq, element_t val);
element_t PQHTextractMax(PQ pq); // Using max_heap 
void PQHTchange(PQ pq, element_t val);

#endif // PQHT_H_DEFINED