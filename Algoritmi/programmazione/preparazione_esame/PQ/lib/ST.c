#include "ST.h"

struct st_s{
    char **str; //vettore di stringhe
    int size;
    int size_max;
};

st_t STinit(int maxN){
    
    st_t st = malloc(sizeof(*st));
    if(st == NULL) return NULL;
    
    st->str = malloc(maxN*sizeof(*st->str));
    if(st->str == NULL) return NULL;
    for(int i = 0; i<maxN; i++){
        st->str[i] = NULL;
    }

    st->size = 0;
    st->size_max = maxN;
    
    return st;
}

int STinsert(st_t st, char *name){
    if(st->size >= st->size_max) return -1;
    
    st->str[st->size] = strdup(name);  // Copia la stringa
    if(st->str[st->size] == NULL) return -1;  // Controllo malloc
    
    st->size++;
    return st->size;
}

int STsearch(st_t st, char *name){
    for(int i = 0; i<st->size; i++)
        if(strcmp(st->str[i],name) == 0)
            return i;
    return -1;
}

char* STsearchByIndex(st_t st, int index){
    if(index < 0 || index > st->size_max -1) return NULL;
    return st->str[index];
}

int STcount(st_t st){
    return st->size;
}

void STfree(st_t st){
    for(int i = 0; i < st->size; i++)
        free(st->str[i]);
    free(st->str);
    free(st);
}