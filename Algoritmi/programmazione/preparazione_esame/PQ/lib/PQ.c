#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

struct pqueue{
    int *values;
    int heapsize;
};

static int LEFT(int i) { return (i*2 + 1); }
static int RIGHT(int i) { return (i*2 + 2); }
static int PARENT(int i) { return ((i-1)/2); }

PQ PQinit(int maxN){
    PQ pq = malloc(sizeof(*pq));
    if(pq == NULL) return NULL;
    pq->values = malloc(maxN*sizeof(pq->values));
    if(pq->values == NULL){
        free(pq);
        return NULL;
    }
    pq->heapsize = 0;

    return pq;
}

void PQfree(PQ pq){
    free(pq->values);
    free(pq);
}

int PQempty(PQ pq){
    return pq->heapsize == 0;
}

int PQsize(PQ pq){
    return pq->heapsize;
}

int PQshowMax(PQ pq){
    return pq->values[0];
}

void PQdisplay(PQ pq){
    for(int i = 0; i<pq->heapsize; i++)
        printf("%d ",pq->values[i]);
}

void PQinsert(PQ pq, int val){
    int i = pq->heapsize++; //BAsta aggiungere un nuovo spazio per creare la foglia, verra poi riempito dal while
    while( i>=1 &&  pq->values[PARENT(i)] < val){
        pq->values[i] = pq->values[PARENT(i)]; //Fai scendere il genitore di un livello
        i = PARENT(i); //Salva la i corrente
    }
    pq->values[i] = val; //Inserisci val al posto giusto
}

// swap e max_heapify sono già definite in heap.c
// Rendiamo queste versioni static per PQ se necessarie
static void pq_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void pq_max_heapify(PQ pq, int i){
    int l, r, largest;
    l = LEFT(i);
    r = RIGHT(i);
    if(l<pq->heapsize && pq->values[l] > pq->values[i])
        largest = l;
    else
        largest = i;
    if(r<pq->heapsize && pq->values[r] > pq->values[largest])
        largest = r;
    if(largest != i){
        pq_swap(&pq->values[i], &pq->values[largest]);
        pq_max_heapify(pq, largest);
    }
}

int PQextractMax(PQ pq){
    int max = pq->values[0];

    pq_swap(&pq->values[0], &pq->values[pq->heapsize-1]);
    pq->heapsize--;
    pq_max_heapify(pq, 0);

    return max;
} 

void PQchange(PQ pq, int val, int newval){
    int i;
    for(i = 0; i< pq->heapsize; i++)
        if(pq->values[i] == val)
            break;
    if(i != pq->heapsize){ //Means found
        pq->values[i] = newval;
        
        // Se newval è maggiore del padre, salire
        while(i > 0 && pq->values[PARENT(i)] < pq->values[i]){
            pq_swap(&pq->values[i], &pq->values[PARENT(i)]);
            // pq->values[i] = pq->values[PARENT(i)];
            i = PARENT(i);
        }
        // Se newval è minore dei figli, scendere
        pq_max_heapify(pq, i);
    } else{
        printf("Key not found\n");
    }
}

/*
void PQchange(PQ pq, int val, int newval){
    int i;
    for(i = 0; i< pq->heapsize; i++)
        if(pq->values[i] == val)
            break;
    if(i != pq->heapsize){ //Means found
        
        
        // Se newval è maggiore del padre, salire
        while(i > 0 && pq->values[PARENT(i)] < newval){
            pq_swap(&pq->values[i], &pq->values[PARENT(i)]);
            i = PARENT(i);
        }

        pq->values[i] = newval;
        // Se newval è minore dei figli, scendere
        pq_max_heapify(pq, i);
    } else{
        printf("Key not found\n");
    }
}
*/