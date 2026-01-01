#include "st.h"

struct st_s{
    char **id; // Array di nomi (indice → nome)
    int n;     // Numero corrente di elementi
    int N;     // Capacità massima
};

st_t STinit(int maxN) { 
    st_t st; 
    int i; 
    st = malloc(sizeof(*st)); 
    st->id = malloc(maxN * sizeof(char*)); 
    for (i = 0; i < maxN; i++) 
        st->id[i] = NULL; 
    st->N = maxN; 
    st->n = 0; 
    return st; 
}

int STinsert(st_t st, char *name) {
    int index;
    // Verifica se il nome esiste già
    index = STsearch(st, name);
    if (index != -1)
        return index; // Nome già presente
    
    // Verifica capacità
    if (st->n >= st->N)
        return -1; // Tabella piena
    
    // Inserisce il nuovo nome
    st->id[st->n] = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(st->id[st->n], name);
    return st->n++;
}

int STsearch(st_t st, char *name) {
    int i;
    for (i = 0; i < st->n; i++) {
        if (strcmp(st->id[i], name) == 0)
            return i;
    }
    return -1; // Non trovato
}

char* STsearchByIndex(st_t st, int index) {
    if (index < 0 || index >= st->n)
        return NULL;
    return st->id[index];
}

int STcount(st_t st) {
    return st->n;
}

void STfree(st_t st) {
    int i;
    for (i = 0; i < st->n; i++) {
        free(st->id[i]);
    }
    free(st->id);
    free(st);
}
