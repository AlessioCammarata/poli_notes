#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

#include <stdio.h>
#include <stdlib.h>

typedef struct pqueue *PQ; 

PQ PQinit(int maxN);
void PQfree(PQ pq); 
int PQempty(PQ pq);
int PQsize(PQ pq);
int PQshowMax(PQ pq);
void PQdisplay(PQ pq); 
void PQinsert(PQ pq, int val);
int PQextractMax(PQ pq); // Using max_heap 
void PQchange(PQ pq, int val, int newval); //Discussione a parte

#endif // PQ_H_DEFINED