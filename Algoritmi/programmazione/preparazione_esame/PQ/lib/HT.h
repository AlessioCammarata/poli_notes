#ifndef HT_H_DEFINED
#define HT_H_DEFINED

#include <stdlib.h>
#include <string.h>

// ADT tabella hash con double hashing
typedef struct ht_s *ht_t;
// Entry nella hash table: nome → posizione heap
typedef struct ht_entry_s {
    char *key;
    int heap_pos;
    int occupied;  // 1 se occupata, 0 se libera
} ht_entry_t;

ht_t HTinit(int maxN, float r);
int HTinsert(ht_t ht, char *key, int heap_pos);
int HTsearch(ht_t ht, char *key);  // ritorna heap_pos o -1
void HTupdate(ht_t ht, char *key, int new_heap_pos);
void HTdelete(ht_t ht, char *key);
int HTempty(ht_t ht);
int HTcount(ht_t ht);
int HTfull(ht_t ht);
void HTfree(ht_t ht);


#endif // HT_H_DEFINED
