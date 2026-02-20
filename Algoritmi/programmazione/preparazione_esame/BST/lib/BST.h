#ifndef BST_H_DEFINED
#define BST_H_DEFINED

#include <stdio.h>
#include <stdlib.h>

typedef struct bst_s *bst_t;
typedef struct item_s{
    int id;
    char *val;
} *Item;

bst_t BSTinit();
int BSTcount(bst_t bst); 
int BSTempty(bst_t bst); 
Item BSTsearch(bst_t bst, int k); 
void BSTinsert_leafR(bst_t bst, Item x); 
void BSTinsert_root(bst_t bst, Item x); 
Item BSTmin(bst_t bst); 
Item BSTmax(bst_t bst); 
void BSTvisit(bst_t bst, int strategy);
void BSTfree(bst_t bst);

#endif