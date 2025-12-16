#include "DailyQuote.h"

//BST - nodo
typedef struct BSTnode *link;
struct BSTnode { 
	DailyQuote_t item; 
	link l; 
	link r;
}; 
//BST ADT I classe
struct DailyQuoteCollection_s{
    link root;
    link z;
    // int size; //Numero di nodi
};

float CalcDailyQuote(DailyQuote_t quote){
    return quote->totTitles != 0 ? quote->WeightedSum/quote->totTitles : 0.0;
}

DailyQuoteCollection_t INITcollection(){
    DailyQuoteCollection_t x = malloc(sizeof *x);
    x->root = NULL;
    x->z = malloc(sizeof *x->z);
    x->z->l = x->z;    // sentinella punta a se stessa
    x->z->r = x->z;
    x->z->item = NULL;
    // x->size = 0;
    return x;
}

static link insertQuote(link x, DateTime_t day, float value, int quantity, link z){
    if(x == z){  
        link newNode = malloc(sizeof *newNode);
        newNode->item = malloc(sizeof *newNode->item);
        if(!newNode->item){
            free(newNode);
            return NULL;
        }
        newNode->l = newNode->r = z;
        newNode->item->day = day;
        newNode->item->totTitles = quantity;
        newNode->item->WeightedSum = quantity * value;
        return newNode; 
    }

    int cmp = cmpDate(day,x->item->day);

    if(cmp == 0){  // Aggiorna nodo esistente
        x->item->totTitles += quantity;
        x->item->WeightedSum += value * quantity;
    } else if(cmp > 0){ // newNode > x
        x->r = insertQuote(x->r,day,value,quantity,z);
    }else{ //  newNode < x
        x->l = insertQuote(x->l,day,value,quantity,z);
    }

    return x;
}

void insertQuoteInBST(DailyQuoteCollection_t DQ, DateTime_t day, float value, int quantity){
    DQ->root = insertQuote(DQ->root, day, value, quantity, DQ->z);
}

static void freeBST(link x, link z){
    if(x == z) return;

    freeBST(x->l,z);
    freeBST(x->r,z);
    free(x->item->day);
    free(x->item);
    free(x);
}

void FREEcollection(DailyQuoteCollection_t DQ){
    if(!DQ) return;
    //Elimina albero se esiste:
    if(DQ->root){
        freeBST(DQ->root, DQ->z);
    }
    free(DQ->z);
    free(DQ);
}