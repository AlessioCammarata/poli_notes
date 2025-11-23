#include "pgList.h"

// nodo privato per la lista (visibile solo in questo file) 
typedef struct pgNode_s *pgNode_t, pgNode_s; 
struct pgNode_s {
    pg_t data;   
    pgNode_t next;
};

struct pgList_s{
    pgNode_t head;
    pgNode_t tail;
    int n;
};

pgList_t pgList_init(){
    pgList_t tabPG = malloc(sizeof *tabPG);
    if (!tabPG) return NULL;
    tabPG->head = tabPG->tail = NULL;
    tabPG->n = 0;
    return tabPG;
}
void pgList_free(pgList_t pgList){
    if(!pgList) return;
    pgNode_t node = pgList->head;
    while (node) {
        pgNode_t next = node->next;
        pg_clean(&node->data);
        free(node);
        node = next;
    }
    free(pgList);
}

/* lettura e scrittura su file */
void pgList_read(FILE *fp, pgList_t pgList){
    if(!fp || !pgList) return;
    pg_t tmp;
    int i = 0;

    while(pg_read(fp,&tmp)){
        pgNode_t pnode = malloc(sizeof(pgNode_s));
        if(!pnode){ 
            perror("malloc");
            pgNode_t cur = pgList->head;
            while (cur) {
                pgNode_t nx = cur->next;
                pg_clean(&cur->data);
                free(cur);
                cur = nx;
            }
            pgList->head = pgList->tail = NULL;
            pgList->n = 0;
            return ;
        }
        pnode->data = tmp;
        pnode->next = NULL;

        if (pgList->head == NULL) {
            pgList->head = pgList->tail = pnode;
        } else {
            pgList->tail->next = pnode;
            pgList->tail = pnode;
        }
        i++;
    }

    pgList->n += i;
}
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    if(!fp || !pgList || !invArray) return;
    for(pgNode_t tmp = pgList->head; tmp != NULL; tmp = tmp->next){
        pg_print(fp, &tmp->data, invArray);
    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg){
    if(!pgList) return;
    if(pgList_searchByCode(pgList, pg.cod) != NULL){
        printf("Elemento già presente\n");
        return;
    }

    pgNode_t newNode = malloc(sizeof(pgNode_s));
    if(!newNode){ 
        perror("malloc");
        return ;
    }
    newNode->next = NULL;
    newNode->data = pg;

    if (pgList->head == NULL) {
        pgList->head = pgList->tail = newNode; //Lista vuota
    } else {
        pgList->tail->next = newNode;
        pgList->tail = newNode;
    }
    pgList->n += 1;
}
/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod){
    if(!pgList) return;
    pgNode_t prev = NULL;
    pgNode_t cur = pgList->head;
    while (cur != NULL && strcmp(cur->data.cod, cod) != 0) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) return ; // non trovato

    if (prev == NULL) pgList->head = cur->next;
    else prev->next = cur->next;

    if (cur == pgList->tail) pgList->tail = prev;

    pg_clean(&cur->data);
    free(cur);

    pgList->n -= 1;
    if (pgList->n == 0) pgList->head = pgList->tail = NULL;

    return ;
}
/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    if(!pgList) return NULL;
    for(pgNode_t p = pgList->head; p!=NULL; p = p->next)
        if(strcmp(p->data.cod,cod) == 0)
            return &p->data;
    return NULL;
}