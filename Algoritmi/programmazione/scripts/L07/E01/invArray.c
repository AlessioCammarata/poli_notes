#include "invArray.h"

struct invArray_s{
    inv_t *items;
    int n;
};

/* creatore e disruttore */
invArray_t invArray_init(){
    invArray_t inv = malloc(sizeof *inv);
    if (!inv) return NULL;
    inv->items = NULL;
    inv->n = 0;
    return inv;
}
void invArray_free(invArray_t invArray){
    if (!invArray) return;
    free(invArray->items);
    free(invArray);
}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray){
    int N;
    if (!invArray || !fp) return;
    if (fscanf(fp, "%d", &N) != 1 || N < 0) return;
    invArray->items = malloc(sizeof(inv_t) * N);
    if (!invArray->items) { 
        invArray->n = 0; 
        return; 
    }
    invArray->n = N;
    for(int i = 0; i<invArray->n; i++){
        inv_read(fp,&invArray->items[i]);
    }
}
void invArray_print(FILE *fp, invArray_t invArray){
    if (!invArray || !fp) return;
    for(int i = 0; i<invArray->n; i++){
        inv_print(fp,&invArray->items[i]);
        // fprintf(fp,"\n");
    }
}
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    if (!invArray || !fp) return;
    if (index < 0 || index >= invArray->n) return;
    inv_print(fp,&invArray->items[index]);
}
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    if (!invArray) return NULL;
    if (index < 0 || index >= invArray->n) return NULL;
    return &invArray->items[index];
}
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name){
    if (!invArray || !name) return -1;
    for (int i = 0; i < invArray->n; i++)
        if (strcmp(invArray->items[i].nome, name) == 0)
            return i;
    return -1;
}

