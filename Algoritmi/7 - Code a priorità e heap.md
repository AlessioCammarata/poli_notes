#### ADT heap
**Albero binario con 
- **proprietà strutturale:** completo a sinistra (tutti i livelli completi, tranne eventualmente l’ultimo, riempito da SX a DX) -> bilanciato 
- **proprietà funzionale**: $\forall i$ != r key(parent(i)) >= key(i) 

Conseguenza: chiave max nella radice 
Implementazione: **mediante vettore**.

Operazioni: (Che faremo)
- **HEAPify**(Heap h, int i); 
- **HEAPbuild**(Heap h); 
- **HEAPsort**(Heap h);
Funzioni di servizio 
- HEAPinit(int maxN); 
- HEAPfree(Heap h); 
- HEAPfill(Heap h, Item val); 
- HEAPdisplay(Heap h);

```c
// heap.h, ADT di I classe
typedef struct heap *Heap;

Heap HEAPinit(int maxN); 
void HEAPfree(Heap h); 
void HEAPfill(Heap h, Item val); 
void HEAPsort(Heap h); 
void HEAPdisplay(Heap h);
```
Modulo:
```c
//heap.c
#include <stdio.h>
#include <stdlib.h>
#include "Item.h" 
#include "Heap.h" 
struct heap { 
	Item *A; 
	int heapsize; 
}; 
int LEFT(int i) { 
	return (i*2 + 1); 
} 
int RIGHT(int i) { 
	return (i*2 + 2); 
} 
int PARENT(int i) { 
	return ((i-1)/2); 
} 
Heap HEAPinit(int maxN) { 
	Heap h; 
	h = malloc(sizeof(*h)); 
	h->A = malloc(maxN*sizeof(Item)); 
	h->heapsize = 0; 
	return h; 
}

void HEAPfree(Heap h) { 
	free(h->A); 
	free(h); 
} 
//usata per inserire valori, non necessariamente il risultato sarà uno heap
void HEAPfill(Heap h, Item item) { 
	int i; 
	i = h->heapsize++; 
	h->A[i] = item; 
	return; 
} 
void HEAPdisplay(Heap h) { 
	int i; 
	for (i = 0; i < h->heapsize; i++) 
		ITEMstore(h->A[i]); 
}
```
###### Funzione HEAPify
Cosa fa?
- Trasforma in heap i, LEFT(i), RIGHT(i), dove LEFT(i) e RIGHT(i) sono già heap 
- assegna ad A[i] il max tra A[i], A[LEFT(i)] e A[RIGHT(i)] 
- se c’è stato scambio A[i] <-> A[LEFT(i)], applica ricorsivamente HEAPify su sottoalbero con radice LEFT(i) 
- analogamente per scambio A[i] <-> A[RIGHT(i)].
- Complessità: **T(n) = O(lg n).**
```c
void HEAPify(Heap h, int i) { 
	int l, r, largest; 
	l = LEFT(i); 
	r = RIGHT(i); 
	if ((lheapsize) && KEYcmp(KEYget(h->A[l]),KEYget(h->A[i]))==1) 
		largest = l; 
	else 
		largest = i; 
	if ((rheapsize) && KEYcmp(KEYget(h->A[r]), KEYget(h->A[largest]))==1)
		largest = r; 
	if (largest != i) { 
		Swap(h, i,largest); 
		HEAPify(h, largest); 
	} 
}
```
###### Funzione HEAPbuild
Cosa fa?
***Trasforma un albero binario memorizzato in vettore A in uno heap:***
- le foglie sono heap 
- applica HEAPify a partire dal padre dell’ultima foglia o coppia di foglie fino alla radice.
```c
void HEAPbuild (Heap h) { 
	int i; 
	for (i=(h->heapsize)/2-1; i >= 0; i--) 
		HEAPify(h, i); 
}
```

**Analisi di complessità**: 
intuitiva ed imprecisa: n passi ciascuno di costo logn, quindi T(n) = O(n lg n) 
precisa: T(n) = O(n). 

**Risoluzione per sviluppo (unfolding):** 
>2 sottoalberi + Heapify.
$$
\begin{align}
& T(n) = 2T(\frac n 2) + log_2 (n) \\ 
& T(\frac n 2) = 2T(\frac n 4) + log_2 (\frac n 2) \\
& T(\frac n 4) = 2T(\frac n 8) + log_2 (\frac n 4)
\end{align}
$$

Sostituendo in T(n): 
	$T(n) = \sum_{i=0}^{log_2 n} 2^i log_2 (\frac n {2^i})$ 
		$= log_2 n \sum_{i=0}^{log_2 n} 2^i - \sum_{i=0}^{log_2 n} i2^i$ 
		$= log_2n(2n-1) -2(1-(log_2n+1)n+2nlog_2n)$
		$= 2n –log_2n -2$ 
		$= O(n)$.
###### Funzione HEAPsort
- Trasforma il vettore in uno heap mediante HEAPbuild 
- Scambia il primo e ultimo elemento 
- Riduce la dimensione dello heap di 1 
- Ripristina la proprietà di heap 
- Ripete fino a esaurimento dello heap. 
***Caratteristiche***: 
- complessità: **T(n)= O(n lg n)**. 
- in loco 
- non stabile
```c
void HEAPsort(Heap h) { 
	int i, j; 
	HEAPbuild(h); 
	j = h->heapsize; 
	for (i = h->heapsize-1; i > 0; i--) { 
		Swap (h,0,i); 
		h->heapsize--; 
		HEAPify(h,0); 
	} 
	h->heapsize = j; 
}
```
#### Coda a priorità
Definizione: 
- struttura dati PQ per **mantenere un set di elementi di tipo Item, ciascuno dei quali include un campo priorità**.
- operazioni principali: inserzione, estrazione del massimo, lettura del massimo, cambio di priorità.

>Coda a priorità con ADT di I classe:
```c 
//pq.h
typedef struct pqueue *PQ; 

PQ PQinit(int maxN); 
void PQfree(PQ pq); 
int PQempty(PQ pq); 
void PQinsert(PQ pq, Item val); 
Item PQextractMax(PQ pq); 
Item PQshowMax(PQ pq); 
void PQdisplay(PQ pq); 
int PQsize(PQ pq); 
void PQchange(PQ pq, Item val); //Discussione a parte
```
Implementazione della struttura dati: 
- vettore/lista non ordinato 
- vettore/lista ordinato
- **heap di dati/indici.**
##### Cosa contiene la ADT?

 La coda a priorità contiene **dati** (lo heap che realizza la coda a priorità contiene i dati), l’ADT è una struct con: 
 1. la coda a priorità: vettore (heap) pq->A di dati di tipo Item (quasi ADT, tipologia 3) 
 2. heapsize: intero
```c
#include 
#include "Item.h" 
#include "PQ.h" 
struct pqueue { 
	Item *A; 
	int heapsize; 
}; 
static int LEFT(int i) { 
	return (i*2 + 1); 
} 
static int RIGHT(int i) { 
	return (i*2 + 2); 
} 
static int PARENT(int i) { 
	return ((i-1)/2); 
} 
PQ PQinit(int maxN){ 
	PQ pq = malloc(sizeof(*pq)); 
	pq->A = (Item *)malloc(maxN*sizeof(Item)); 
	pq->heapsize = 0; 
	return pq; 
}

void PQfree(PQ pq){ 
	free(pq->A); 
	free(pq); 
} 
int PQempty(PQ pq) { 
	return pq->heapsize == 0; 
} 
int PQsize(PQ pq) { 
	return pq->heapsize; 
} 
Item PQshowMax(PQ pq) { 
	return pq->A[0]; 
} 
void PQdisplay(PQ pq) { 
	int i; 
	for (i = 0; i < pq->heapsize; i++) 
		ITEMstore(pq->A[i]); 
}
```
##### Funzione PQinsert
- Aggiunge una foglia all’albero (cresce per livelli da SX a DX, rispettando la proprietà strutturale) 
- Risale dal nodo corrente (inizialmente la foglia appena creata) fino al più alla radice. Confronta la chiave del datocontenuto nel padre con la chiave del dato da inserire, facendo scendere il dato del padre nel figlio se la chiave da inserire è maggiore, altrimenti inserisce il dato nel nodo corrente. 
Complessità: **T(n) = O(lg n)**.
```c
void PQinsert (PQ pq, Item val) { 
	int i; 
	i = pq->heapsize++; 
	while((i>=1) && (KEYcmp(KEYget(pq->A[PARENT(i)]),KEYget(val))==-1)){
		pq->A[i] = pq->A[PARENT(i)]; 
		i = (i-1)/2;
	} 
	pq->A[i] = val; 
	return; 
}
```
##### Funzione PQextractMax
- Modifica lo heap, estraendone il valore massimo, che è contenuto nella radice: 
- scambia la radice con l'ultima delle foglie (quella più a destra nell'ultimo livello) 
- riduce di 1 della dimensione dello heap 
- ripristina le proprietà dello heap mediante applicazione di HEAPify. 
Complessità: T(n) = O(lg n).
```c
Item PQextractMax(PQ pq) { 
	Item val; 
	Swap (pq, 0,pq->heapsize-1); 
	val = pq->A[pq->heapsize-1]; 
	pq->heapsize--; 
	HEAPify(pq, 0); 
	return val; 
}
```
##### Funzione PQchange
