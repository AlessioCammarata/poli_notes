#include "BST.h"
#include "OSBST.h"

typedef struct BSTnode* link; 
struct BSTnode {
	Item item;
	link p; //Puntatore al padre
	link l;
	link r;
	int N; //Dimensione sottoalbero
};
struct osbst_s{ 
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

osbst_t OSBSTinit( ) { //Padre NULL e dimensione 0
	osbst_t bst = malloc(sizeof *bst) ; 
	bst->root=(bst->z=NEW(NULL, NULL, NULL, NULL, 0));
	return bst; 
}

static link insertR(link x, Item item, link z){
    if(x == z)
        return NEW(item, z, z, z, 1);
    
    if(x->item->id < item->id){
        x->r = insertR(x->r, item, z);
        x->r->p = x; //Assegno il padre in risalita
    } else{
        x->l = insertR(x->l, item, z);
        x->l->p = x; //Assegno il padre in risalita
    }
    (x->N)++; //Incremento il numero di nodi
    return x;
}

void OSBSTinsert_leafR(osbst_t bst, Item x){
    bst->root = insertR(bst->root, x, bst->z);
}

static Item findMinr(link x, link z){
    if(x == z) 
        return NULL;
    
    if(x->l == z)
        return x->item;
        
    return findMinr(x->l, z);
}

static Item searchSucc(link h, int k, link z) { 
	link p; 
	if (h == z) 
		return NULL; 
	if (h->item->id == k) { 
		if (h->r != z) //Ha un figlio destro, percio cerco il min
			return findMinr(h->r, z); 
		else { // Non ha un figlio destro, percio devo risalire
			p = h->p; //Risalgo tramite il padre
			while (p != z && h == p->r) { 
				h = p; p = p->p; 
			} 
			return p->item; 
		} 
	} 
	if (k < h->item->id) 
		return searchSucc(h->l, k, z); 
	return searchSucc(h->r, k, z); 
}
 
Item BSTsucc(osbst_t bst, int k) { //Wrapper
	return searchSucc(bst->root, k, bst->z); 
}

static Item findMaxr(link x, link z){
    if(x == z) 
        return NULL;
    
    if(x->r == z)
        return x->item;
        
    return findMaxr(x->r, z);
}

static Item searchPred(link h, int k, link z) { 
	link p; 
	if (h == z) 
		return NULL; 
	if (h->item->id == k) { 
		if (h->l != z)
			return findMaxr(h->l, z); 
		else {
			p = h->p; //Risalgo tramite il padre
			while (p != z && h == p->l) { 
				h = p; p = p->p; 
			} 
			return p->item; 
		} 
	} 
	if (k < h->item->id) 
		return searchPred(h->l, k, z); 
	return searchPred(h->r, k, z); 
}
 
Item BSTpred(osbst_t bst, int k) { //Wrapper
	return searchPred(bst->root, k, bst->z); 
}

static Item selectR(link x, int r, link z){
    int t;
    if(x == z)
        return NULL;
    t = x->l->N;
    if(t > r)
        return selectR(x->l, r, z);
    if(t < r)
        return selectR(x->r, r-t-1, z);
    
    return x->item;
}

Item BSTselect(osbst_t bst, int r){
    return selectR(bst->root, r, bst->z);
}

static link rotR(link h) { 
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

static link rotL(link h) { 
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

static link OSBSTinsertTr(link x, Item item, link z){
    if(x == z)
        return NEW(item, z, z, z, 1);
    if(item->id > x->item->id){
        x->r = OSBSTinsertTr(x->r, item, z);
        x = rotL(x);
        x->N++; //Incremento il numero di nodi visti
    }else{
        x->l = OSBSTinsertTr(x->l, item, z);
        x = rotR(x);
        x->N++; //Incremento il numero di nodi visti
    }

    return x;
}

void OSBSTinsert_root(osbst_t bst, Item x){
    bst->root = OSBSTinsertTr(bst->root, x, bst->z);
}

//La parte ricorsiva serve per trovare la chiave
static link partR(link h, int r) { 
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

//Questa funzione serve a svolgere il link degli alberi separati e a mettere in alto il valore successore o predecessore tramite una partition
static link joinLR(link a, link b, link z) { 
	if (b == z) 
		return a; 
	b = partR(b, 0); //Partition del successore (o pred) per portarlo in cima
	b->l = a; 
	a->p = b; //aggiornamento puntatore al padre
	b->N = a->N + b->r->N +1; //aggiornamento dimensione sottoalberi
	return b; 
}

static link deleteR(link x, int key, link z){
    link y, p;
    if(x == z)
        return z;

    if(key > x->item->id)
        x->r = deleteR(x->r, key, z);
    else if(key < x->item->id)
        x->l = deleteR(x->l, key, z);
    (x->N)--;
    if(key == x->item->id){
        y = x;
        p = x->p;
        x = joinLR(x->l, x->r, z);
        x->p = p;
        free(y);
    }

    return x;
}

void BSTdelete(osbst_t bst, int k){
    bst->root= deleteR(bst->root, k, bst->z);
}

static link balanceR(link x, link z){
    int r;
    if(x == z)
        return z;
    r = (x->N+1)/2 -1; //Chiave mediana
    x = partR(x, r);
    x->l = balanceR(x->l, z);
    x->r = balanceR(x->r, z);
    return x;
}

void BSTbalance(osbst_t bst){
	bst->root = balanceR(bst->root, bst->z); 
}