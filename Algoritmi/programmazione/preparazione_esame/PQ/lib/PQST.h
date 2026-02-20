#ifndef PQST_H_DEFINED
#define PQST_H_DEFINED

#include <stdio.h>
#include <stdlib.h>

#include "ST.h"

typedef struct pqueue *PQ;
typedef struct element_s *element_t;
struct element_s{
    char *val;
    int prio;
};

PQ PQSTinit(int maxN);
void PQSTfree(PQ pq); 
int PQSTempty(PQ pq);
int PQSTsize(PQ pq);
element_t PQSTshowMax(PQ pq);
void PQSTdisplay(PQ pq); 
void PQSTinsert(PQ pq, element_t val);
element_t PQSTextractMax(PQ pq); // Using max_heap 
void PQSTchange(PQ pq, element_t val);

#endif // PQ_H_DEFINED