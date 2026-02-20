#include "ST.h"
#include "PQST.h"

struct pqueue{
    element_t *elements;
    st_t st;
    int heapsize;
};

static int LEFT(int i) { return (i*2 + 1); }
static int RIGHT(int i) { return (i*2 + 2); }
static int PARENT(int i) { return ((i-1)/2); }

PQ PQSTinit(int maxN){
    PQ pq = malloc(sizeof(*pq));
    if(pq == NULL) return NULL;
    pq->elements = malloc(maxN*sizeof(*pq->elements));
    if(pq->elements == NULL){
        free(pq);
        return NULL;
    }
    pq->st = STinit(maxN);
    if(pq->st == NULL){
        free(pq->elements);
        free(pq);
        return NULL;
    }
    pq->heapsize = 0;

    return pq;
}

void PQSTfree(PQ pq){
    STfree(pq->st);
    free(pq->elements);
    free(pq);
}

int PQSTempty(PQ pq){
    return pq->heapsize == 0;
}

int PQSTsize(PQ pq){
    return pq->heapsize;
}

element_t PQSTshowMax(PQ pq){
    return pq->elements[0];
}

void PQSTdisplay(PQ pq){
    for(int i = 0; i<pq->heapsize; i++)
        printf("%s (prio %d)\n", pq->elements[i]->val, pq->elements[i]->prio);
}

void PQSTinsert(PQ pq, element_t val){
    int i = pq->heapsize++; //BAsta aggiungere un nuovo spazio per creare la foglia, verra poi riempito dal while
    while( i>=1 &&  pq->elements[PARENT(i)]->prio < val->prio){
        pq->elements[i] = pq->elements[PARENT(i)]; //Fai scendere il genitore di un livello
        i = PARENT(i); //Salva la i corrente
    }
    pq->elements[i] = val; //Inserisci val al posto giusto
    STinsert(pq->st, val->val);
}

// swap e max_heapify sono già definite in heap.c
// Rendiamo queste versioni static per PQ se necessarie
static void pq_swap(element_t *a, element_t *b) {
    element_t temp = *a;
    *a = *b;
    *b = temp;
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
        pq_swap(&pq->elements[i], &pq->elements[largest]);
        pq_max_heapify(pq, largest);
    }
}

element_t PQSTextractMax(PQ pq){
    element_t max = pq->elements[0];

    pq_swap(&pq->elements[0], &pq->elements[pq->heapsize-1]);
    pq->heapsize--;
    pq_max_heapify(pq, 0);

    return max;
} 

void PQSTchange(PQ pq, element_t val){
    int i = STsearch(pq->st, val->val);
    
    if(i != -1){  // trovato
        pq->elements[i]->prio = val->prio;
        
        // Se newval è maggiore del padre, salire
        while(i > 0 && pq->elements[PARENT(i)]->prio < pq->elements[i]->prio){
            pq_swap(&pq->elements[i], &pq->elements[PARENT(i)]);
            i = PARENT(i);
        }
        // Se newval è minore dei figli, scendere
        pq_max_heapify(pq, i);
    } else{
        printf("Key not found\n");
    }
}