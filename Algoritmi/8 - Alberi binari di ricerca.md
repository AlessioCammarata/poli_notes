#### Alberi Binari
Definizione ricorsiva: 
Un albero binario T è: 
- un insieme vuoto di nodi vuoto 
- una terna formata da una radice, un sottoalbero binario sinistro eun sottoalbero binario destro.
```c
typedef structnode* link;
struct node { 
	Item item; 
	link left; 
	link right; 
};
```
>All’albero si accede tramite il puntatore h alla radice.
##### Calcolo di parametri
```c
int count(link root) { //Numero di nodi
	if (root == NULL) 
		return 0; 
	return count(root->left) + count(root->right) + 1;
} 
int height(link root) { //Altezza
	int u, v; 
	if (root == NULL) 
		return -1; 
	u = height(root->left); 
	v = height(root->right);
	if (u>v) 
		return u+1; 
	return v+1; 
}
```
##### Visite
Attraversamento o visita: elenco dei nodi secondo una strategia: 
- **pre-ordine**: root, Left(root), Right(root)
- **in-ordine**: Left(root), root, Right(root) 
- **post-ordine**: Left(root), Right(root), root
###### Pre-ordine
```c
void preOrder(link root){
	if (root == NULL)
		return; 
	printf("%s ",root->name);
	preOrder(root->left);
	preOrder(root->right);
}
```
###### In-ordine
```c
void inOrder(link root){
	if (root == NULL)
		return; 
	inOrder(root->left);
	printf("%s ",root->name);
	inOrder(root->right);
}	
```
###### Post-ordine
```c
void postOrder(link root){
	if (root == NULL) 
		return; 
	postOrder(root->left);
	postOrder(root->right);
	printf("%s ",root->name);
}
```
##### Analisi di complessità
Ipotesi 1: albero completamente bilanciato (pieno):  (Divide and Conquer)
- D(n) = (1), C(n) = (1) 
- a = 2, b = 2 (sottoproblemi di dimensione n-1, approssimati conservativamente a n) Equazione alla ricorrenze: 
	T(n) = 1 + 2T(n/2) n > 1 
	T(1) = 1 
	T(n) = O(n)

Ipotesi 2: albero totalmente sbilanciato (degenerato in una lista) : (Decrease and conquer)
- D(n) = (1), C(n) = (1) 
- a = 1, ki = 1 
Equazione alla ricorrenze: 
	T(n) = 1 + T(n-1) n > 1 
	T(1) = 1 
	T(n) = O(n)
	
---
#### Alberi binari esempi d'uso
	Slide 51

---
#### Alberi Binari di Ricerca (BST)
ADT albero binario con proprietà: $\forall$nodo x vale che: 
- $\forall$ nodo y $\in$Left(x), key[y] < key[x] 
- $\forall$ nodo y $\in$Right(x), key[y] > key[x]
>**Inoltre ogni nodo ha chiave univoca.**
##### Funzioni varie della ADT
```c
//BST.h
typedef struct binarysearchtree *BST; 
BST BSTinit(); 
void BSTfree(BST bst); 
int BSTcount(BST bst); 
int BSTempty(BST bst); 
Item BSTsearch(BST bst, Key k); 
void BSTinsert_leafI(BST bst, Item x); 
void BSTinsert_leafR(BST bst, Item x); 
void BSTinsert_root(BST bst, Item x); 
Item BSTmin(BST bst); 
Item BSTmax(BST bst); 
void BSTvisit(BST bst, int strategy);
```
Implementazione base:
```c
#include <stdlib.h> 
#include "Item.h" 
#include "BST.h" 
typedef struct BSTnode* link; 
struct BSTnode { 
	Item item; 
	link l; 
	link r;
}; 
struct binarysearchtree { //Identifica l'albero
	link root; //Radice
	link z; //Nodo sentinella
}; 

static link NEW(Item item, link l, link r) { 
	link x = malloc(sizeof *x); 
	x->item = item; 
	x->l = l; 
	x->r = r; 
	return x; 
} 

BST BSTinit( ) { 
	BST bst = malloc(sizeof *bst); 
	bst->root= (bst->z = NEW(ITEMsetVoid(), NULL, NULL));
	return bst; 
}

void BSTfree(BST bst) { 
	if (bst == NULL) 
		return; 
	treeFree(bst->root, bst->z); 
	free(bst->z); 
	free(bst); 
} 
//Funzione ricorsiva che cancella tutti i sottoalberi.
static void treeFree(link h, link z) { 
	if (h == z) 
		return; 
	treeFree(h->l, z); 
	treeFree(h->r, z); 
	free(h); 
}

static int countR(link h, link z) { 
	if (h == z) 
		return 0; 
	return countR(h->l, z) + countR(h->r, z) +1; 
} 

int BSTcount(BST bst) { //Wrapper poiche ADT I Classe
	return countR(bst->root, bst->z); 
} 

int BSTempty(BST bst) { 
	if (BSTcount(bst) == 0) 
		return 1; 
	return 0; 
}
```
>Il nodo sentinella serve a segnalare che un nodo è una foglia (Non ha nessun figlio).
>**Sia l che r saranno uguali a z.**
###### BSTsearch
Ricerca ricorsiva di un nodo che contiene un item con una chiave data: 
- percorrimento dell’albero dalla radice 
- terminazione: la chiave dell’item cercato è uguale alla chiave del nodo corrente (search hit) oppure si è giunti ad un albero vuoto (search miss) 
- ricorsione: dal nodo corrente 
	- su sottoalbero sinistro se la chiave dell’item cercato è < della chiave del nodo corrente 
	- su sottoalbero destro altrimenti
```c
Item searchR(link h, Key k, link z) { 
	int cmp; 
	if (h == z) 
		return ITEMsetVoid(); 
	cmp = KEYcmp(k, KEYget(h->item)); 
	if (cmp == 0) 
		return h->item; 
	if (cmp == -1) 
		return searchR(h->l, k, z); 
	return searchR(h->r, k, z); 
} 

Item BSTsearch(BST bst, Key k) { //Wrapper poiche ADT I Classe
	return searchR(bst->root, k, bst->z); 
}
```
###### BSTmin
Seguire il puntatore al sottoalbero sinistro finché si arriva al nodosentinella z:
```c
Item minR(link h, link z) { 
	if (h == z) 
		return ITEMsetVoid(); 
	if (h->l == z) 
		return (h->item); 
	return minR(h->l, z); 
} 

Item BSTmin(BST bst) { //Wrapper poiche ADT I Classe
	return minR(bst->root, bst->z); 
}
```
###### BSTmax
Seguire il puntatore al sottoalbero destro finché si arriva al nodosentinella z:
```c
Item maxR(link h, link z) { 
	if (h == z) 
		return ITEMsetVoid(); 
	if (h->r == z) 
		return (h->item); 
	return minR(h->r, z); 
} 

Item BSTmax(BST bst) { //Wrapper poiche ADT I Classe
	return maxR(bst->root, bst->z); 
}
```
###### BSTinsert (in foglia)
Inserire in un albero binario di ricerca un nodo che contiene un item -> mantenimento della proprietà: 
- se il BST è vuoto, creazione del nuovo albero 
- inserimento **ricorsivo** nel sottoalbero sinistro o destro a seconda del confronto tra la chiave dell’item e quella del nodo corrente 
- inserimento **iterativo**: prima si ricerca la posizione, poi si appende il nuovo nodo.
```c
//RICORSIVO
static link insertR(link h, Item x, link z) {
	if (h == z) 
		return NEW(x, z, z); 
	if (KEYcmp(KEYget(x), KEYget(h->item))==-1)
		h->l = insertR(h->l, x, z); 
	else 
		h->r = insertR(h->r, x, z); 
	return h; 
} 

void BSTinsert_leafR(BST bst, Item x) { 
	bst->root = insertR(bst->root, x, bst->z); 
}
```
---
```c
//ITERATIVO
void BSTinsert_leafI(BST bst, Item x) { 
	link p = bst->root, h = p; 
	if (bst->root == bst->z) { 
		bst->root = NEW(x, bst->z, bst->z); 
		return; 
	} 
	while (h != bst->z) { //Percorro l'albero finche non arrivo ad una foglia
		p = h; 
		h=(KEYcmp(KEYget(x),KEYget(h->item))==-1) ? h->l : h->r;
	} 
	h = NEW(x, bst->z, bst->z); 
	if (KEYcmp(KEYget(x), KEYget(p->item))==-1) 
		p->l = h; 
	else 
		p->r = h; 
}
```
**Complessità**:
Le operazioni hanno complessità==T(n) = O(h)==: 
- albero con n nodi completamente bilanciato 
	- altezza h = $\alpha(log_2 n)$ 
- albero con n nodi completamente sbilanciato ha 
	- altezza h = $\alpha$(n) 
- $O(logn) \le T(n) \le O(n)$
###### BSTvisit
Attraversamento in-ordine: **ordinamento crescente delle chiavi.**
>Stampa in ordine crescente le chiavi.

La chiave **mediana** (inferiore) di un insieme di n elementi è l’elemento che si trova in posizione $\lfloor \frac {n + 1} 2\rfloor$ nella sequenza ordinata degli elementi dell’insieme.
```c
static void treePrintR(link h, link z, int strategy) {
	if (h == z) 
		return; 
	if (strategy == PREORDER) 
		ITEMstore(h->item); 
	treePrintR(h->l, z, strategy); 
	if (strategy == INORDER) 
		ITEMstore(h->item); 
	treePrintR(h->r, z, strategy); 
	if (strategy == POSTORDER) 
		ITEMstore(h->item); 
	} 

void BSTvisit(BST bst, int strategy) { 
	if (BSTempty(bst)) 
		return; 
	treePrintR(bst->root, bst->z, strategy); 
}
```
###### Rotazione a destra di BST
```c
link rotR(link h) { 
	link x = h->l; 
	h->l = x->r; 
	x->r = h; 
	return x; 
}
```
###### Rotazione a sinistra di BST
```c
link rotL(link h) { 
	link x = h->r; 
	h->r = x->l; 
	x->l = h; 
	return x; 
}
```
###### BSTinsert (in radice)
- Inserimento dalle foglie a scelta e non obbligatorio 
- Nodi più recenti nella parte alta del BST 
- Inserimento ricorsivo alla radice: 
	- inserimento nel sottoalbero appropriato 
	- rotazione per farlo diventare radice dell’albero principale.
```c
static link insertT(link h, Item x, link z) {
	if (h == z) 
		return NEW(x, z, z); 
	if (KEYcmp(KEYget(x), KEYget(h->item))==-1) {
		h->l = insertT(h->l, x, z); 
		h = rotR(h); //Ruoto in risalita
	} else { 
		h->r = insertT(h->r, x, z); 
		h = rotL(h); //Ruoto in risalita
	} 
	return h; 
} 

void BSTinsert_root(BST bst, Item x) { 
	bst->root = insertT(bst->root, x, bst->z); 
}
```
#### Estensione dei BST elementari
Al nodo elementare si possono aggiungere informazioni che permettono lo sviluppo semplice di nuove funzioni: 
- **puntatore al padre** 
- **numero di nodi dell’albero radicato nel nodo corrente**. 
Queste informazioni devono ovviamente essere gestite (quando necessario) da tutte le funzioni già viste.

>Vantaggio poiche possiamo mettere nuove funzionalità, tipo il **bilanciamento dell'albero.**

Aggiungiamo le funzioni:
```c
//BST.h
void BSTdelete(BST bst, Key k); 
Item BSTselect(BST bst, int r); //(Order-Statistic BST)
Item BSTsucc(BST bst, Key k); 
Item BSTpred(BST bst, Key k); 
void BSTbalance(BST bst);
```
Le altre funzioni le lasciamo come erano.
```c
//BST.c
#include <stdlib.h>
#include "Item.h" 
#include "BST.h" 
typedef struct BSTnode* link; 
struct BSTnode {
	Item item;
	link p; //Puntatore al padre
	link l;
	link r;
	int N; //Dimensione sottoalbero
};
struct binarysearchtree { 
	link root; 
	link z; 
};

static link NEW(Item item, link p, link l, link r,int N){
	link x = malloc(sizeof *x); 
	x->item = item; 
	x->p = p; 
	x->l = l; 
	x->r = r; 
	x->N = N; 
	return x; 
}

BST BSTinit( ) { //Padre NULL e dimensione 0
	BST bst = malloc(sizeof *bst) ; 
	bst->root=(bst->z=NEW(ITEMsetVoid(), NULL, NULL, NULL, 0));
	return bst; 
}
```
###### Successore
Successore di un item: se esiste, nodo h con un item con la più piccola chiave > della chiave di item, altrimenti item vuoto. Due casi: 
- $\exists !$ Right(h): succ(key(h)) = min(Right(h)) 
- $\exists$ Right(h): succ(key(h)) = primo antenato di h il cui figlio sinistro è anche un antenato di h.
```c
Item searchSucc(link h, Key k, link z) { 
	link p; 
	if (h == z) 
		return ITEMsetVoid(); 
	if (KEYcmp(k, KEYget(h->item))==0) { 
		if (h->r != z) //Ha un figlio destro, percio cerco il min
			return minR(h->r, z); 
		else { // Non ha un figlio destro, percio devo risalire
			p = h->p; //Risalgo tramite il padre
			while (p != z && h == p->r) { 
				h = p; p = p->p; 
			} 
			return p->item; 
		} 
	} 
	if (KEYcmp(k, KEYget(h->item))==-1) 
		return searchSucc(h->l, k, z); 
	return searchSucc(h->r, k, z); 
}
 
Item BSTsucc(BST bst, Key k) { //Wrapper
	return searchSucc(bst->root, k, bst->z); 
}
```
###### Predecessore
Predecessore di un item: nodo h con item con la più grande chiave
Due casi: 
- $\exists !$ Left(h): pred(key(h)) = max(Left(h))
- $\exists$ Left(h): pred(key(h)) = primo antenato di h il cui figlio destro è anche un antenato di h.
```c
Item searchPred(link h, Key k, link z) {
	link p; 
	if (h == z) 
		return ITEMsetVoid(); 
	if (KEYcmp(k, KEYget(h->item))==0) { 
		if (h->l != z) //Ha un figlio sinistro, percio cerco il max
			return maxR(h->l, z); 
		else { // Non ha un figlio sinistro, percio devo risalire
			p = h->p; //Risalgo tramite il padre
			while (p != z && h == p->l) { 
				h = p; p = p->p; 
			} 
			return p->item; 
		} 
	} 
	if (KEYcmp(k, KEYget(h->item))==-1) 
		return searchSucc(h->l, k, z); 
	return searchSucc(h->r, k, z); 
}
 
Item BSTpred(BST bst, Key k) { //Wrapper
	return searchSucc(bst->root, k, bst->z); 
}
```
###### BSTinsert (in foglia)
```c
link insertR(link h, Item x, link z) { 
	if (h == z) 
		return NEW(x, z, z, z, 1); //Inserisco il primo nodo
	if (KEYcmp(KEYget(x), KEYget(h->item))==-1) {
		h->l = insertR(h->l, x, z); 
		h->l->p = h; //Dico al figlio sinistro che il padre è h
	} else { 
		h->r = insertR(h->r, x, z); 
		h->r->p = h; //Dico al figlio destro che il padre è h
	} 
	(h->N)++; //Incremento il numero di nodi
	return h; 
} 

void BSTinsert_leafR(BST bst, Item x) { 
	bst->root = insertR(bst->root, x, bst->z); 
}
```
###### BSTselect
Selezione dell’item con la r-esima chiave più piccola (rango r = chiave in posizione r nell’ordinamento, ad esempio se r=0 item con chiave minima): t è il numero di nodi del sottoalbero sinistro: 
- t = r: ritorno la radice del sottoalbero 
- t > r: ricorsione nel sottoalbero sinistro alla ricerca della k-esima chiave più piccola 
- t < r: ricorsione nel sottoalbero destro alla ricerca della (r-t-1)-esima chiave più piccola
```c
Item selectR(link h, int r, link z) { 
	int t; 
	if (h == z) 
		return ITEMsetVoid(); 
	t = h->l->N; 
	if (t > r) 
		return selectR(h->l, r, z); 
	if (t < r) 
		return selectR(h->r, r-t-1, z); 
	return h->item; 
} 

Item BSTselect(BST bst, int r) { 
	return selectR(bst->root, r, bst->z); 
}
```
###### Rotazione a destra di BST
```c
link rotR(link h) { 
	link x = h->l; 
	h->l = x->r; 
	x->r->p = h; // Il padre di r è h
	x->r = h; 
	x->p = h->p; //Il padre di x è quello di h, poi aggiorno h
	h->p = x; //aggiornamento puntatore al padre
	x->N = h->N; 
	h->N = 1;
	// aggiornamento dimensione sottoalberi
	h->N += (h->l) ? h->l->N : 0; 
	h->N += (h->r) ? h->r->N : 0; 
	return x; 
}
```
###### Rotazione a sinistra di BST
```c
link rotL(link h) { 
	link x = h->r; 
	h->r = x->l; 
	x->l->p = h; // Il padre di l è h
	x->l = h; 
	x->p = h->p; //Il padre di x è quello di h, poi aggiorno h
	h->p = x; //aggiornamento puntatore al padre
	x->N = h->N; 
	h->N = 1;
	// aggiornamento dimensione sottoalberi
	h->N += (h->l) ? h->l->N : 0; 
	h->N += (h->r) ? h->r->N : 0; 
	return x; 
}
```
###### BSTinsert (in radice)
```c
link insertT(link h, Item x, link z) { 
	if ( h == z) 
		return NEW(x, z, z, z, 1); 
	if (KEYcmp(KEYget(x), KEYget(h->item))==-1) { 
		h->l = insertT(h->l, x, z); 
		h = rotR(h); 
		h->N++; //Incremento il numero di nodi visti
	} else { 
		h->r = insertT(h->r, x, z); 
		h = rotL(h); 
		h->N++; //Incremento il numero di nodi visti
	} 
	return h; 
} 

void BSTinsert_root(BST bst, Item x) { 
	bst->root = insertT(bst->root, x, bst->z); 
}
```
###### BSTpartition
Riorganizza l’albero avendo l’item con la k-esima chiave più piccola nella radice: 
- porre il nodo come radice di un sottoalbero: 
	- t > k: **ricorsione** nel sottoalbero sinistro, partizionamento rispetto alla k-esima chiave più piccola, al termine rotazione a destra 
	- t < k: **ricorsione** nel sottoalbero destro, partizionamento rispetto alla (k-t-1)-esima chiave più piccola , al termine rotazione a sinistra 
Sovente il partizionamento si fa attorno alla chiave mediana.
```c
//La parte ricorsiva serve per trovare la chiave
link partR(link h, int r) { 
	int t = h->l->N; 
	if (t > r) { 
		h->l = partR(h->l, r); 
		h = rotR(h); //Rotazione in salita
	} 
	if (t < r) { 
		h->r = partR(h->r, r-t-1); 
		h = rotL(h); //Rotazione in salita
	} 
	return h; // t==r
}
```
###### BSTdelete
Per cancellare da un albero binario di ricerca un nodo con item con chiave k bisogna mantenere: 
- la proprietà dei BST 
- la struttura ad albero binario 
Passi: 
- controllare se il nodo con l’item da cancellare è in uno dei sottoalberi. Se sì, cancellazione ricorsiva nel sottoalbero 
- se è la radice, eliminarlo e ricombinare i 2 sottoalberi. La nuova radice è il successore o il predecessore dell’item cancellato.
```c
//Questa funzione serve a svolgere il link degli alberi separati e a mettere in alto il valore successore o predecessore tramite una partition
link joinLR(link a, link b, link z) { 
	if (b == z) 
		return a; 
	b = partR(b, 0); //Partition del successore (o pred) per portarlo in cima
	b->l = a; 
	a->p = b; //aggiornamento puntatore al padre
	b->N = a->N + b->r->N +1; //aggiornamento dimensione sottoalberi
	return b; 
}

//Scendo e cerco k, e intanto decremento N, quando lo trovo chiamo la funzione helper e dopodichè libero il nodo da cancellare.
link deleteR(link h, Key k, link z) { 
	link y, p; 
	if (h == z) 
		return z; 
	if (KEYcmp(k, KEYget(h->item))==-1) 
		h->l = deleteR(h->l, k, z); 
	if (KEYcmp(k, KEYget(h->item))==1) 
		h->r = deleteR(h->r, k, z); 
	(h->N)--; // aggiornamento numero di nodi
	if (KEYcmp(k, KEYget(h->item))==0) { 
		y = h; 
		p = h->p; // aggiornamento puntatore al padre
		h = joinLR(h->l, h->r, z); 
		h->p = p; 
		free(y); 
	} 
	return h; 
} 

void BSTdelete(BST bst, Key k) { 
	bst->root= deleteR(bst->root, k, bst->z); 
}
```
###### Bilanciamento
- A priori: vincoli che garantiscono un albero perfettamente bilanciato (B-tree) o con sbilanciamento limitato (alberi 2-3-4, RBtree) 
- Ribilanciamento a richiesta: 
	- partizionamento ricorsivo attorno alla chiave mediana inferiore (algoritmo semplice) 
	- algoritmo di Day, Stout e Warren, di complessità O(n) costruisce un albero quasi completo (tutti i livelli completi, tranne l’ultimo riempito da sinistra a destra, cfr heap) 
Bisogna valutare il rapporto tra costo e frequenza di ribilanciamento.
Esempio:
```c
static link balanceR(link h, link z) { 
	int r; 
	if (h == z) return z; 
	r = (h->N+1)/2-1; 
	h = partR(h, r); 
	h->l = balanceR(h->l, z); 
	h->r = balanceR(h->r, z); 
	return h; 
} 
void BSTbalance(BST bst) { 
	bst->root = balanceR(bst->root, bst->z); 
}
```

---
#### Interval BST

BST la cui chiave è un intervallo chiuso: coppia ordinata di reali [t1, t2], dove t1 $\le$ t2 e [t1 , t2 ] = ${t \in \Re: t_1 \le t \le t_2 }$. 
L’item intervallo [t1 , t2 ] può essere realizzato da una struct con campi low = t1 e high = t2. 
Procedura: 
1.***identificare la struttura dati candidata*** (**BST con inserzione secondo l'estremo inferiore**)
1. ***identificare le informazioni supplementari*** (max: massimo high del sottoalbero)
2. verificare di poter mantenere le informazioni supplementari senza alterare la complessità delle operazioni esistenti (O(1))
3.***sviluppare nuove operazioni.**** (Item IBSTsearch(BST, Item);)

>Serve un criterio di ordinamento, per esempio il primo estremo.
>Il massimo dei nodi sottostanti viene tenuto come informazione a livello superiore.

>**Criterio di sovrapposizione:** (caso a)
>	L[i]<H[i'] e L[i'] < H[i].
>In caso contrario allora siamo o nel caso in cui i' accade prima di i o viceversa.

caso b: i>i'
caso c: i'>i
```c
//Item.h
typedef struct item { 
	int low; 
	int high; 
} Item; 
Item ITEMscan(); 
Item ITEMsetVoid(); 
int ITEMcheckVoid(Item val); 
void ITEMstore(Item val); 
int ITEMhigh(); //Estremo superiore
int ITEMlow();  //Estremo inferiore
int ITEMoverlap(Item val1, Item val2); //Interserzione
int ITEMeq(Item val1, Item val2); //Uguale in inserzione
int ITEMlt(Item val1, Item val2); //Minore in inserzione
int ITEMlt_int(Item val1, int val2); // < in ricerca
```

```c
//item.c

#include #include #include #include 
#include "Item.h" 
Item ITEMscan() { //Acquisiamo low e high
	Item val; 
	printf("low = "); scanf("%d", &val.low); 
	printf("high = "); scanf("%d", &val.high); 
	return val; 
} 

void ITEMstore(Item val) { //Stampa
	printf("[%d, %d] ", val.low, val.high); 
} 

Item ITEMsetVoid() { 
	Item val = {-1, -1}; 
	return val; 
}

int ITEMcheckVoid(Item val) { //Vediamo se un item è nullo
	if ((val.low == -1) && (val.high == -1)) 
		return 1; 
	return 0; 
} 

int ITEMhigh(Item val) { 
	return val.high; 
} 

int ITEMlow(Item val) { 
	return val.low; 
} 

//Dice se c'è sovrapposizone, seguendo il criterio definito prima
int ITEMoverlap(Item val1, Item val2) { 
	if ((val1.low <= val2.high) && (val2.low<= val1.high)) 
		return 1; 
	return 0; 
}

//Confronto tra intervalli
int ITEMeq(Item val1, Item val2) { 
	if ((val1.low == val2.low) && (val1.high == val2.high))
		return 1; 
	return 0; 
} 
//Primo intervallo minore del secondo (Considerando low)
int ITEMlt(Item val1, Item val2) { 
	if ((val1.low < val2.low)) 
		return 1; 
	return 0; 
} 

int ITEMlt_int(Item val1, int val2) { 
	if ((val1.low < val2)) 
		return 1; 
	return 0; 
}
```
##### ADT I Classe Interval BST

```c
// IBST.h
typedef struct intervalbinarysearchtree *IBST; 
void IBSTinit(IBST ibst); //Modificata
void IBSTfree(IBST ibst); 
void BSTinsert(IBST ibst, Item x); //Modificata
void IBSTdelete(IBST ibst, Item x); //Modificata
Item IBSTsearch(IBST ibst, Item x); //Nuova
int IBSTcount(IBST ibst); //Modificata
int IBSTempty(IBST ibst); //Modificata
void IBSTvisit(IBST ibst, int strategy);
```

```c
#include #include 
#include "Item.h" 
#include "IBST.h“ 
typedef struct IBSTnode *link; 
struct IBSTnode {
	Item item; 
	link l, r; 
	int N; 
	int max; // max: massimo high del sottoalbero
}; 
struct intervalbinarysearchtree {
	link root;
	int size; // size: dimensione del sottoalbero
	link z;
}; 

//Inizializzazione dell'item
static link NEW(Item item, link l, link r, int N, int max) { 
	link x = malloc(sizeof *x); 
	x->item = item; 
	x->l = l; 
	x->r = r; 
	x->N = N; 
	x->max = max; 
	return x; 
}

static void NODEshow(link x) { 
	ITEMstore(x->item); 
	printf("max = %d\n", x->max); 
} 

IBST IBSTinit( ) { 
	IBST ibst = malloc(sizeof *ibst); 
	ibst->N = 0; 
	//0 come minimo e -1 come massimo della radice
	ibst->root=(ibst->z=NEW(ITEMsetNull(),NULL,NULL,0,-1));
	return ibst; 
} 

//Cancellare l'albero
void IBSTfree(IBST ibst) { 
	if (ibst == NULL) return; 
	treeFree(ibst->root, ibst->z); 
	free(ibst->z); 
	free(ibst); 
} 

//Ricorsione per cancellare l'albero
static void treeFree(link h, link z) {
	 if (h == z) return; 
	 treeFree(h->l, z); 
	 treeFree(h->r, z); 
	 free(h); 
}

//Ritorniamo il valore size
int IBSTcount(IBST ibst) { 
	return ibst->size; 
} 
//Ritorniamo se l'albero è vuoto
int IBSTempty(IBST ibst) { 
	if (IBSTcount(ibst) == 0) 
		return 1; 
	return 0; 
} 

//Stampa a seconda della strategia
static void treePrintR(link h, link z, int strategy) {
	if (h == z) return; 
	if (strategy == PREORDER) 
		NODEshow(h); 
	treePrintR(h->l, z, strategy); 
	if (strategy == INORDER) 
		NODEshow(h); 
	treePrintR(h->r, z, strategy); 
	if (strategy == POSTORDER) 
		NODEshow(h); 
} 
//Wrapper di stampa
void IBSTvisit(IBST ibst, int strategy) { 
	if (IBSTempty(ibst)) return; 
	treePrintR(ibst->root, ibst->z, strategy); 
}

//INSERT
link insertR(link h, Item item, link z) { 
	if (h == z) //Se usciamo inseriamo il valore high come alto
		return NEW(item, z, z, 1, ITEMhigh(item)); 
	if (ITEMlt(item, h->item)) { //Scendiamo a sinistra
		h->l = insertR(h->l, item, z); 
		h->max = max(h->max, h->l->max, h->r->max); 
	} else { //Scendiamo a destra
		h->r = insertR(h->r, item, z); 
		h->max = max(h->max, h->l->max, h->r->max); 
	} 
	(h->N)++; 
	return h; 
} 

void IBSTinsert(IBST ibst, Item item) { 
	//Modifica la radice se l'albero era vuoto
	ibst->root = insertR(ibst->root, item, ibst->z); 
	ibst->size++; //Aggiorniamo la dimensione dell'albero
}

//rotL/rotR
link rotL(link h) { 
	link x = h->r; //x è Figlio destro di h
	h->r = x->l; //Nuovo figlio uguale al figlio sinistro di x
	x->l = h; //Nuovo figlio sinsitro di x è h
	x->N = h->N; // Il numero di nodi di h (che aveva prima) diventa quello di x
	//Devo cambiare il numero di nodi attuale di h, sommo sinistra e destra piu se stesso
	h->N = h->l->N + h->r->N +1;
	//Aggiorno max sia di h che di x dato che ho ruotato
	h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
	x->max = max(ITEMhigh(x->item), x->l->max, x->r->max);
	return x; 
} 

//Come la rotazione a sinistra (speculare)
link rotR(link h) { 
	link x = h->l; 
	h->l = x->r; 
	x->r = h; 
	x->N = h->N; 
	h->N = h->r->N + h->l->N +1; 
	h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
	x->max = max(ITEMhigh(x->item), x->l->max, x->r->max);
	return x;
}

//Faccio risalire un nodo la cui chiave ha rango r (posizione r). Che diventerà la nuova radice dell'albero
link partR(link h, int r) { 
	int t = h->l->N; 
	if (t > r) { 
		h->l = partR(h->l, r); 
		h = rotR(h); 
	} 
	if (t < r) { 
		h->r = partR(h->r, r-t-1); 
		h = rotL(h); 
	} 
	return h; 
} 

//Unisce due nodi monchi (Per esempio quando cancelli la radice)
link joinLR(link a, link b, link z) { 
	if (b == z) 
		return a;
	//Partizione per portare in cima il successore della radice tolta
	b = partR(b, 0); 
	b->l = a; 
	b->N = a->N + b->r->N +1;
	//Aggiorno il max, prendendo il massimo tra b->l e b->r
	b->max = max(ITEMhigh(b->item), a->max, b->r->max);
	return b; 
}

//Delete
//Scendo a sinistra o a destra fino a trovare il nodo, dopodiché quando lo trovo cancello e faccio la join tra figli destri e sinistri del nodo, dopo aver cancellato devo aggiornare max
link deleteR(link h, Item item, link z) { 
	link x; 
	if (h == z) return z; 
	if (ITEMlt(item, h->item)) { 
		h->l = deleteR(h->l, item, z); 
		h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
	} 
	if (ITEMlt(h->item, item)) { 
		h->r = deleteR(h->r, item, z); 
		h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
	} 
	(h->N)--; 
	if (ITEMeq(item, h->item)) { 
		x = h; 
		h = joinLR(h->l, h->r, z); 
		free(x); //Libero il nodo
	} 
	return h; 
} 

void IBSTdelete(IBST ibst, Item item) { 
	ibst->root=deleteR(ibst->root,item,ibst->z); 
	ibst->size--; 
}
```
###### Search
Ricerca di un nodo h con intervallo che interseca l’intervallo i: 
- percorrimento dell’albero dalla radice 
- terminazione: trovato intervallo che interseca i oppure si è giunti ad un albero vuoto 
- Ricorsione: dal nodo h
	- su sottoalbero sinistro se 
		h->l->max ≥ low[i] 
	- su sottoalbero destro se 
		h->l->max < low[i]
```c
/*
Scendo a sinistra se so che il max del nodo è maggiore del low dell'intervallo che cerco. (h->l->max ≥ low[i])
Scendo sul sottoalbero destro se l'estremo inferiore dell'intervallo i è maggiore del massimo del sottoalbero sinistro.
Se max di sinistra è inferiore di max del mio intervallo che cerco scendo a destra.

Non è detto che si trovi un 'intersezione nell'albero (ritorno NULL)
*/
Item searchR(link h, Item item, link z) { 
	if (h == z) return ITEMsetNull(); 
	if (ITEMoverlap(item, h->item)) 
		return h->item; 
	if (ITEMlt_int(item, h->l->max)) 
		return searchR(h->l, item, z); 
	else 
		return searchR(h->r, item, z); 
} 

Item IBSTsearch(IBST ibst, Item item) { 
	return searchR(ibst->root, item, ibst->z);
}
```
- **Analisi** 
Ordinamento: T(n) = O(NlogN) 
**Se l’IBST è bilanciato:** 
- ogni inserzione/cancellazione di intervallo o ricerca del primo intervallo che interseca uno dato costa T(n) = O(logN), 
- la ricerca di tutti gli intervalli che intersecano un intervallo dato costa T(n) = O(RlogN) se R è il numero di intersezioni.