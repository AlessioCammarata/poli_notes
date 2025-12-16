#include "Titles.h"

struct Title_s{
    char *title;
    DailyQuoteCollection_t quotes;
    Title_t next;
};

struct TitleCollection_s{
    Title_t head;
    int n;
};

TitleCollection_t INITlist(){
    TitleCollection_t TC = malloc(sizeof *TC);
    TC->head = NULL;
    TC->n = 0;
    return TC;
}

Title_t searchTitle(TitleCollection_t TC, char *title) {
    for(Title_t tmp = TC->head; tmp != NULL; tmp = tmp->next) {
        int val = strcmp(tmp->title, title);
        if(val == 0) return tmp; // trovato
        if(val > 0) return NULL; // lista ordinata, non troveremo più
    }
    return NULL; // non trovato
}

Title_t addTitle(TitleCollection_t TC, char *title){
    Title_t existing = searchTitle(TC, title);
    if(existing){
        printf("Esiste già\n");
        return existing;
    }

    Title_t x = malloc(sizeof *x);
    x->title = title;        
    x->quotes = INITcollection();
    if(!TC->head){ 
        TC->head = x;
        x->next = NULL;
        TC->n++;
        return x;
    }
    //Inserimento in testa
    if(strcmp(TC->head->title,x->title) > 0 ){
        x->next = TC->head;
        TC->head = x;
        TC->n++;
        return x;
    }
    
    Title_t tmp;
    for(tmp = TC->head; tmp->next != NULL; tmp = tmp->next){
        //Inserimento in ordine
        int val = strcmp(tmp->next->title,x->title);
        if(val > 0){
            x->next = tmp->next;
            tmp->next = x;
            TC->n++;
            return x;
        }
    }
    // Inserimento in coda
    tmp->next = x;
    x->next = NULL;
    TC->n++;

    return x;
}

DailyQuoteCollection_t getCollection(Title_t title){
    return title->quotes;
}

void freeTC(TitleCollection_t TC){
    Title_t x = TC->head;
    while(x!=NULL){
        Title_t next = x->next;
        FREEcollection(x->quotes);
        free(x);
        x = next;
    }
    free(TC);
}