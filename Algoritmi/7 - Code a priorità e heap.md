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
Modifica la **priorità** di un elemento, la cui posizione (indice nello heap) viene calcolata con una scansione di costo lineare 
- o risale dalla posizione data fino al più alla radice confrontando la chiave del padre con la chiave modificata, facendo scendere la chiave del padre nel figlio se la chiave modificata è maggiore, altrimenti la inserisce nel nodo corrente (fixup)
- o applica HEAPify a partire dalla posizione data. (fixdown)
Complessità: **T(n) = O(n) + O(lg n) = O(n).**
```c
void PQchange (PQ pq, Item val) { 
	int i, found = 0, pos; 
	for (i = 0; i < pq->heapsize && found == 0; i++) 
		if (NAMEcmp(NAMEget(&(pq->A[i])), NAMEget(&val))==0) {
			found = 1; 
			pos = i; 
		} 
	if (found==1) { 
		while(pos>=1 && PRIOget(pq->A[PARENT(pos)])<PRIOget(val)){
			pq->A[pos] = pq->A[PARENT(pos)]; 
			pos = (pos-1)/2; 
		} 
		pq->A[pos] = val; 
		Heapify(pq, pos); 
	} else printf("key not found!\n"); 
	return; 
}
```
>È utile avere una struttura accessoria (tabella di simboli) che specifica dove trovare il valore, accesso diretto, in modo da togliere la parte di ricerca lineare all'inizio della funzione.

La complessità della PQchange dipende dalla ricerca dell’item nella coda. 
Occorre fare in modo che NON si debba cercare l’item nella coda. 
Soluzione: deve essere noto «dove» l’item si trova nella coda (gestito dalle operazioni su PQ). 
Vi sono diverse alternative per localizzare l’item: 
1. la PQ non contiene gli item (dati) ma puntatori agli item
2. la PQ non contiene gli item (dati) ma indici che permettono di reperire il dato. Se la chiave dell’item è univoca, la si usa come riferimento tramite una tabella di simboli efficiente.
###### Soluzione 1
- in coda si inseriscono solo «riferimenti» ad item (es. puntatori) 
- l’item ha un campo pos (posizione in PQ) 
- il modulo Item fornisce le operazioni ITEMsetPos e ITEMgetPos che permettono di ottenere la posizione di un item con costo O(1)
###### Soluzione 2
- la chiave dell’item deve essere univoca, senza possibili duplicati 
- il modulo PQ usa la chiave dell’item per gestire una corrispondenza chiave-indice mediante una tabella di simboli efficiente (es. Hash table O(1), BST bilanciato O(lg(n)) 
- lo **heap che realizza la coda a priorità contiene dati di un tipo heapItem interno alla PQ formato da coppie** (indice, priorità). Si adotta la versione di «chiave affiancata al dato» (la priorità è un parametro aggiuntivo) invece che «chiave parte del dato» 
- la PQ contiene Il vettore pq->qp (posizione in coda) serve per implementare una PQchange efficiente, identificando la posizione dell’elemento nello heap con costo O(1) (l’elemento è un indice) senza bisogno di una scansione lineare.

L’ADT PQ è una struct con: 
1. la tabella di hash pq->hash con dati di tipo Item gestisce la corrispondenza indice/dato e dato/indice con costo in media O(1) 
2. la coda a priorità come heap implementato come vettore pq->A di dati di tipo heapItem 
3. heapsize: intero per la dimensione corrente dello heap 
4. il vettore pq->qp per memorizzare a quale indice nello heap si trova un dato di tipo heapItem
>serve per implementare PQchange identificando la posizione dell’elemento nello heap.
###### Funzione PQInsert
Procede come nel caso di PQ di item: 
- si inserisce l’elemento in pq->hash, ricavando il suo indice e la sua priorità 
- si inseriscono indice e priorità in pq->heap, risalendo dal nodo corrente (inizialmente la foglia appena creata) finoal più alla radice in base al confronto tra priorità 
- si mantiene aggiornato il vettore pq->qp. 
Complessità: **T(n) = O(lg n).**
```c
void PQinsert (PQ pq, Item item){ 
	int i, index, prio; 
	index =STinsert(pq->hash, item); //inserisco il dato nella tabella di hash
	prio = STgetPrio(pq->hash, index); 
	i = pq->heapsize++; 
	while((i>=1) && (pq->heap[PARENT(i)].prio)<prio){ 
		//risalgo nello heap cercando la posizione corretta
		pq->heap[i] = pq->heap[PARENT(i)]; 
		pq->qp[pq->heap[i].index] = i; 
		i = PARENT(i); 
	} 
	pq->heap[i].index = index; //memorizzo il dato nella posizione corretta
	pq->heap[i].prio = prio; 
	pq->qp[index] = i; // aggiorno pq->qp
}

static void Swap(PQ pq, int pos1, int pos2){ 
	heapItem temp; 
	int index1, index2; 
	temp = pq->heap[pos1]; 
	pq->heap[pos1] = pq->heap[pos2]; 
	pq->heap[pos2] = temp; 
	// update correspondence index-pos 
	index1 = pq->heap[pos1].index; 
	index2 = pq->heap[pos2].index; 
	pq->qp[index1] = pos1; 
	pq->qp[index2] = pos2; 
}

static void Heapify(PQ pq, int i) { 
	int l, r, largest; 
	l = LEFT(i); r = RIGHT(i); 
	if (l<pq->heapsize && (pq->heap[l].prio>pq->heap[i].prio))
		largest = l; 
	else 
		largest = i; 
	if (r<pq->heapsize && (pq->heap[r].prio>pq->heap[largest].prio))
		largest = r; 
	if (largest != i) { 
		Swap(pq, i, largest); 
		Heapify(pq, largest); 
	} 
}
//Il cambiamento piu importante lo abbiamo qui:
void PQchange (PQ pq, Item item) { 
	int index, prio, pos; 
	heapItem temp; 
	index = STsearch(pq->hash, item); //indice in pq->hash
	if (index == -1) { 
		printf("Item not found!\n"); 
		return; 
	}else printf("found at index %d\n", index); 
	prio = PRIOget(item); 
	STchangePrio(pq->hash, index, prio); //Cambio priorità
	
	pos = pq->qp[index]; //posizione in pq->heap
	temp = pq->heap[pos]; 
	temp.prio = prio; // new prio 
	//Posizionamento corretto in risalita
	while ((pos>=1) && (pq->heap[PARENT(pos)].index < prio)) {
		pq->heap[pos] = pq->heap[PARENT(pos)]; 
		pq->qp[pq->heap[pos].index] = pos; 
		pos = PARENT(pos); 
	} 
	//aggiornamento di pq->heap e pq->qp
	pq->heap[pos] = temp; 
	pq->qp[index] = pos; 
	Heapify(pq, pos); //Posizionamento corretto in discesa
}

```