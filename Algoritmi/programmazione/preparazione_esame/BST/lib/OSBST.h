#ifndef OSBST_H_DEFINED
#define OSBST_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

typedef struct osbst_s *osbst_t;
//Usiamo lo stesso item

osbst_t OSBSTinit(); //Modificata
// Si utilizza BSTcount 
// Si utilizza BSTempty 
// Si utilizza BSTsearch
void OSBSTinsert_leafR(osbst_t bst, Item x); //Modificata
void OSBSTinsert_root(osbst_t bst, Item x);  //Modificata
//Si utilizza BSTmin
//Si utilizza BSTmax
//Si utilizza BSTvisit
//Si utilizza BSTfree

Item BSTsucc(osbst_t bst, int k); 
Item BSTpred(osbst_t bst, int k);
Item BSTselect(osbst_t bst, int r); //(Order-Statistic BST) 
void BSTdelete(osbst_t bst, int k); 
void BSTbalance(osbst_t bst);


#endif