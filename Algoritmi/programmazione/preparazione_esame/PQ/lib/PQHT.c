#include "HT.h"
#include "PQHT.h"

struct pqueue{
    ht_t ht;
    element_t *elements;
    int heapsize;
    int maxSize;
};

static int LEFT(int i){ return i*2 + 1;}
static int RIGHT(int i){ return i*2 + 2;}
static int PARENT(int i){ return (i-1)/2;}

// swap e max_heapify sono già definite in heap.c
// Rendiamo queste versioni static per PQ se necessarie
static void pq_swap(PQ pq, int i, int j) {
    element_t temp = pq->elements[i];
    pq->elements[i] = pq->elements[j];
    pq->elements[j] = temp;
    
    // Aggiorna HT con nuove posizioni
    HTupdate(pq->ht, pq->elements[i]->str, i);
    HTupdate(pq->ht, pq->elements[j]->str, j);
}

static void pq_max_heapify(PQ pq, int i){
    int l, r, largest;
    l = LEFT(i);
    r = RIGHT(i);
    if(l<pq->heapsize && pq->elements[l]->prio > pq->elements[i]->prio)
        largest = l;
    else
        largest = i;
    if(r<pq->heapsize && pq->elements[r]->prio > pq->elements[largest]->prio)
        largest = r;
    if(largest != i){
        pq_swap(pq, i, largest);
        pq_max_heapify(pq, largest);
    }
}

PQ PQHTinit(int maxN, float r){
    PQ pq = malloc(sizeof(*pq));
    if(pq == NULL) return NULL;

    pq->ht = HTinit(maxN,r);
    if(pq->ht == NULL){
        free(pq);
        return NULL;
    }
    pq->heapsize = 0;
    pq->maxSize = maxN;
    pq->elements = malloc(maxN*sizeof(*pq->elements));
    if(pq->elements == NULL){
        HTfree(pq->ht);
        free(pq);
        return NULL;
    }
    return pq;
}

void PQHTfree(PQ pq){
    if(pq == NULL) return;
    
    for(int i = 0; i < pq->heapsize; i++){
        free(pq->elements[i]->str);
        free(pq->elements[i]);
    }
    free(pq->elements);
    HTfree(pq->ht);
    free(pq);
}

int PQHTempty(PQ pq){
    return pq->heapsize == 0;
}

int PQHTsize(PQ pq){
    return pq->heapsize;
}

element_t PQHTshowMax(PQ pq){
    if(pq->heapsize == 0) return NULL;
    return pq->elements[0];
}

void PQHTdisplay(PQ pq){
    for(int i = 0; i < pq->heapsize; i++)
        printf("%s (prio %d)\n", pq->elements[i]->str, pq->elements[i]->prio);
}

void PQHTinsert(PQ pq, element_t val){
    if(pq == NULL || val == NULL) return;
    if(pq->heapsize >= pq->maxSize) return;

    int i = pq->heapsize;
    if(HTinsert(pq->ht, val->str, i) == -1){
        return;  // duplicato
    }

    pq->heapsize++;
    
    // Bubble up
    while(i >= 1 && pq->elements[PARENT(i)]->prio < val->prio){
        pq->elements[i] = pq->elements[PARENT(i)];
        HTupdate(pq->ht, pq->elements[i]->str, i);  // aggiorna posizione
        i = PARENT(i);
    }
    pq->elements[i] = val;
    HTupdate(pq->ht, val->str, i);  // posizione finale
}


element_t PQHTextractMax(PQ pq){
    if(pq->heapsize == 0) return NULL;
    
    element_t max = pq->elements[0];
    
    HTdelete(pq->ht, max->str);  // rimuovi da HT
    
    pq->heapsize--;
    if(pq->heapsize > 0){
        pq->elements[0] = pq->elements[pq->heapsize];
        HTupdate(pq->ht, pq->elements[0]->str, 0);
        pq_max_heapify(pq, 0);
    }
    
    return max;
}

void PQHTchange(PQ pq, element_t val){
    // Usa HT per trovare se esiste, poi usa heap_pos per accedere O(1)
    int i = HTsearch(pq->ht, val->str);

    if(i == -1){
        printf("Key not found\n");
        return;
    }

    pq->elements[i]->prio = val->prio;

    // Se newval è maggiore del padre, salire
    while(i > 0 && pq->elements[PARENT(i)]->prio < pq->elements[i]->prio){
        pq_swap(pq, i, PARENT(i));
        i = PARENT(i);
    }
    // Se newval è minore dei figli, scendere
    pq_max_heapify(pq, i);
}