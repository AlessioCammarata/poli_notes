#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;
struct node { 
	Item item; 
	link l; 
	link r; 
};

struct bst_s{
    link root;
    link z;
};

static link NEW(Item item, link l, link r) { 
	link x = malloc(sizeof *x); 
	x->item = item; 
	x->l = l; 
	x->r = r; 
	return x; 
}

bst_t BSTinit(){
    bst_t bst = malloc(sizeof(*bst));
    bst->z = NEW(NULL, NULL, NULL);
    bst->root = bst->z;
    return bst;
}

static int countR(link x, link z){
    if(x == z) return 0;
    return countR(x->l, z) + countR(x->r,z) + 1;
}

int BSTcount(bst_t bst){
    return countR(bst->root, bst->z);
}

int BSTempty(bst_t bst){
    return BSTcount(bst) == 0;
}

Item searchR(link x, link z, int k){
    if(x == z) return NULL;
    // int cmp; -> Utile se hai una chiave composta e devi fare KEYcmp
    if(x->item->id < k)
        return searchR(x->r,z,k);
    else if(x->item->id > k)
        return searchR(x->l,z,k);
    else
        return x->item;
}

Item BSTsearch(bst_t bst, int k){
    return searchR(bst->root, bst->z, k);
}

static link insertR(link x, Item item, link z){
    if(x == z)
        return NEW(item, z, z);
    
    if(x->item->id < item->id)
        x->r = insertR(x->r, item, z);
    else
        x->l = insertR(x->l, item, z);
    
    return x;
}

static void MYinsertR(link x, Item item, link z){
    if(x == z)
        return;
    
    if(x->item->id < item->id){
        if(x->r == z){
            link y = NEW(item, z, z);
            x->r = y;
            return;
        }
        MYinsertR(x->r, item, z);
    } else{
        if(x->l == z){
            link y = NEW(item, z, z);
            x->l = y;
            return;
        }
        MYinsertR(x->l, item, z);
    }
}

void BSTinsert_leafR(bst_t bst, Item x){
    bst->root = insertR(bst->root, x, bst->z);
    //Oppure
    // MYinsertR(bst->root, x, bst->z);
}

static link rotR(link h) { 
	link x = h->l; 
	h->l = x->r; 
	x->r = h; 
	return x; 
}

static link rotL(link h) { 
	link x = h->r; 
	h->r = x->l; 
	x->l = h; 
	return x; 
}

static link BSTinsertTr(link x, Item item, link z){
    if(x == z)
        return NEW(item, z, z);
    if(item->id > x->item->id){
        x->r = BSTinsertTr(x->r, item, z);
        x = rotL(x);
    }else{
        x->l = BSTinsertTr(x->l, item, z);
        x = rotR(x);
    }

    return x;
}

void BSTinsert_root(bst_t bst, Item x){
    bst->root = BSTinsertTr(bst->root, x, bst->z);
}

static Item findMinr(link x, link z){
    if(x == z) 
        return NULL;
    
    if(x->l == z)
        return x->item;
        
    return findMinr(x->l, z);
}

Item BSTmin(bst_t bst){
    return findMinr(bst->root, bst->z);
}

static Item findMaxr(link x, link z){
    if(x == z) 
        return NULL;
    
    if(x->r == z)
        return x->item;
        
    return findMaxr(x->r, z);
}

Item BSTmax(bst_t bst){
    return findMaxr(bst->root, bst->z);
}

static enum treeVisit{
    PRE, IN, POST
};

static void treePrintr(link x, link z, int strategy){
    if(x == z) return;
    if(strategy == PRE)
        printf("%d-%s\n",x->item->id, x->item->val); 
    
    treePrintr(x->l, z, strategy);
    if(strategy == IN)
        printf("%d-%s\n",x->item->id, x->item->val); 

    treePrintr(x->r, z, strategy);
    if(strategy == POST)
        printf("%d-%s\n",x->item->id, x->item->val); 
}

void BSTvisit(bst_t bst, int strategy){
    if(BSTempty(bst)) return;
    treePrintr(bst->root, bst->z, strategy);
}

//Funzione ricorsiva che cancella tutti i sottoalberi.
static void treeFree(link h, link z) { 
	if (h == z) 
		return; 
	treeFree(h->l, z); 
	treeFree(h->r, z); 
	free(h); 
}

void BSTfree(bst_t bst) { 
	if (bst == NULL) 
		return; 
	treeFree(bst->root, bst->z); 
	free(bst->z); 
	free(bst); 
} 
