#include "DailyQuote.h"
#include <stdio.h>

//BST - nodo
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
    x->z = malloc(sizeof *x->z);
    x->z->l = x->z;    // sentinella punta a se stessa
    x->z->r = x->z;
    x->z->item = NULL;
    x->root = x->z;
    x->size = 0;
    return x;
}

void printDQrecursive(link x, link z){
    if(x == z) return;
    printf(" %.2f:%d:%d\n",x->item->WeightedSum,x->item->totTitles,x->item->day->day);
    printDQrecursive(x->l, z);
    printDQrecursive(x->r, z);
}

void printDQ(DailyQuoteCollection_t DQ){
    printDQrecursive(DQ->root,DQ->z);
}

link findDQfromDate(DailyQuoteCollection_t DQ, DateTime_t date){
    int cmp;
    for(link x = DQ->root; x != DQ->z;){
        cmp = cmpDate(date,x->item->day);
        if(cmp == 0){ // Find
            return x;
        }else if(cmp >0){//date>x->date
            x = x->r;
        }else{ //date<x->date
            x = x->l;
        }
    }

    return NULL; //Sentinella
}

float getDQvalue(DailyQuoteCollection_t DQ, DateTime_t date){ //Wrapper per la get
    link x = findDQfromDate(DQ,date);
    return x != NULL ? x->item->WeightedSum : -1;
}

static void recursiveMINMAX(link x, link z, DateTime_t start, DateTime_t end, float *min, float *max){
    if(x == z) return;

    if(cmpDate(x->item->day, start) < 0) recursiveMINMAX(x->r,z,start,end,min,max);
    else if (cmpDate(x->item->day, end) > 0) recursiveMINMAX(x->l,z,start,end,min,max);
    else{
        //Nodo nell'intervallo
        if(x->item->WeightedSum > *max) *max = x->item->WeightedSum;
        if(x->item->WeightedSum < *min) *min = x->item->WeightedSum;
        recursiveMINMAX(x->l,z,start,end,min,max);
        recursiveMINMAX(x->r,z,start,end,min,max);
    }

}

void getDQvalueInterval(DailyQuoteCollection_t DQ, DateTime_t date1, DateTime_t date2, float *min, float *max){ //Wrapper
    recursiveMINMAX(DQ->root,DQ->z,date1,date2,min,max);
}

int maxDepth(link x, link z){
    if(x == z) return 0;
    int l = maxDepth(x->l, z);
    int r = maxDepth(x->r, z);
    return 1 + (l>r ? l : r);
}

int minDepth(link x, link z){
    if(x == z) return 0;
    int l = minDepth(x->l, z);
    int r = minDepth(x->r, z);
    // Se uno dei due sottoalberi è vuoto, considera solo l'altro
    if (l == 0 || r == 0) return 1 + (l > r ? l : r);
    return 1 + (l>r ? r : l);
}

/*
bilanciamento dell'albero di quotazioni se il rapporto tra il cammino più lungo e più corto 
nell'albero supera una certa soglia S.
Nota: si ricorda che è possibile bilanciare un dato BST mediante applicazione ricorsiva
del partizionamento rispetto alla chiave mediana. 
*/
static void recursiveVISIT(link x, link z, link *vet, int counter){
    if(x==z) return;
    
    recursiveVISIT(x->l,z,vet,counter);
    vet[counter++] = x;
    recursiveVISIT(x->r,z,vet,counter);
}
static link recursiveBUILD(link z, link *vet, int l, int r){
    if(l>r) return z;
    int mid = (l+r)/2;
    link root = vet[mid];
    root->l = recursiveBUILD(z,vet,l,mid-1);
    root->r = recursiveBUILD(z,vet,mid+1,r);
    return root;
}
/*
    Visita in-order l’albero e salva i nodi in un array ordinato.
    Ricostruisci ricorsivamente il BST scegliendo sempre il nodo mediano come radice (così ottieni un albero perfettamente bilanciato).
    Sostituisci il vecchio albero con quello nuovo.
    Non devi implementare rotazioni singole (left/right rotation), ma una vera e propria “ricostruzione” dell’albero a partire dai dati ordinati.
*/
void balanceBST(DailyQuoteCollection_t DQ, int threshold){
    int max, min;
    max = maxDepth(DQ->root, DQ->z);
    min = minDepth(DQ->root, DQ->z);

    if(max/min > threshold){
        link *nodeVet = malloc(DQ->size * sizeof(link)); 
        recursiveVISIT(DQ->root,DQ->z, nodeVet, 0);
        DQ->root = recursiveBUILD(DQ->z, nodeVet, 0, DQ->size-1);
        free(nodeVet);
    }
}

static link insertQuote(link x, DateTime_t day, float value, int quantity, link z, int *size){
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
        (*size)++;
        // printf("%d\n",newNode->item->totTitles);
        return newNode; 
    }

    int cmp = cmpDate(day,x->item->day);

    if(cmp == 0){  // Aggiorna nodo esistente
        x->item->totTitles += quantity;
        x->item->WeightedSum += value * quantity;
    } else if(cmp > 0){ // newNode > x
        x->r = insertQuote(x->r,day,value,quantity,z, size);
    }else{ //  newNode < x
        x->l = insertQuote(x->l,day,value,quantity,z, size);
    }

    return x;
}

void insertQuoteInBST(DailyQuoteCollection_t DQ, DateTime_t day, float value, int quantity){
    DQ->root = insertQuote(DQ->root, day, value, quantity, DQ->z, &DQ->size);
    printf("%d\n",DQ->size);
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