#ifndef ST_H_DEFINED
#define ST_H_DEFINED

#include <stdlib.h>
#include <string.h>

// ADT tabella di simboli
typedef struct st_s *st_t;

// Inizializza una tabella di simboli con capacità massima maxN
st_t STinit(int maxN);

// Inserisce un nome nella tabella e restituisce il suo indice
int STinsert(st_t st, char *name);

// Cerca un nome e restituisce il suo indice (-1 se non trovato)
int STsearch(st_t st, char *name);

// Restituisce il nome dato un indice (NULL se non valido)
char* STsearchByIndex(st_t st, int index);

// Restituisce il numero corrente di elementi
int STcount(st_t st);

// Libera la memoria della tabella
void STfree(st_t st);

#endif // ST_H_DEFINED
