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
    int size; //Numero di nodi
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
    x->size = 0;
    return x;
}

void addDailyQuote(DailyQuoteCollection_t DQ){
    //
}

void insertQuoteInBST(DailyQuoteCollection_t DQ, DateTime_t day, float value, int quantity){

}

void FREEcollection(DailyQuoteCollection_t DQ){
    free(DQ->z);
    //Elimina albero se esiste:

    free(DQ);
}