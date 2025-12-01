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