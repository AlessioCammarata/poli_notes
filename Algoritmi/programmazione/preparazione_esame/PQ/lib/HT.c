#include "HT.h"
#include <stdio.h>

struct ht_s{
    ht_entry_t *table;
    int heapsize;
    int maxSize;
};

static int hash1(char *key, int tableSize){
    int h = 0, base = 127; 
    for ( ; *key != '\0'; key++) 
        h = (base * h + *key) % tableSize; 
    return h;
}

// Funzione hash secondaria per double hashing
static int hash2(char *key, int tableSize){
    int h = 0, base = 31;  // base diversa
    for ( ; *key != '\0'; key++) 
        h = (base * h + *key);
    h = (h % (tableSize - 2)) + 1;   // valore tra 1 e tableSize-2
    return h;
}

static int HTsizeSet(int maxN, float r) { 
    int primes[16]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
    int i = 0; 
    int size = (int)(maxN / r); 
    if (size < primes[15]) { 
        for (i = 0; i < 16; i++) 
            if (size <= primes[i]) 
                return primes[i]; 
    } else 
        printf("Too many entries!\n"); 
    return -1; 
}

ht_t HTinit(int maxN, float r){
    ht_t ht = malloc(sizeof(*ht));
    if(ht == NULL) return NULL;
    ht->heapsize = 0;
    ht->maxSize = HTsizeSet(maxN, r);
    ht->table = malloc(ht->maxSize * sizeof(*ht->table));
    if(ht->table == NULL){
        free(ht);
        return NULL;
    }
    for(int i = 0; i < ht->maxSize; i++){
        ht->table[i].key = NULL;
        ht->table[i].heap_pos = -1;
        ht->table[i].occupied = 0;
    }
    return ht;
}

int HTinsert(ht_t ht, char *key, int heap_pos){
    if(ht == NULL || key == NULL) return -1;
    if(HTcount(ht) >= ht->maxSize) return -1;

    int i = hash1(key, ht->maxSize);
    int j = hash2(key, ht->maxSize);

    int attempts = 0;
    while(ht->table[i].occupied && attempts < ht->maxSize){
        if(strcmp(ht->table[i].key, key) == 0)
            return -1; // duplicato
        i = (i + j) % ht->maxSize;
        attempts++;
    }
    if(attempts >= ht->maxSize) return -1;

    ht->table[i].key = malloc(strlen(key) + 1);
    strcpy(ht->table[i].key, key);
    ht->table[i].heap_pos = heap_pos;
    ht->table[i].occupied = 1;
    ht->heapsize++;
    return i;
}

int HTsearch(ht_t ht, char *key){
    if(ht == NULL || key == NULL) return -1;

    int i = hash1(key, ht->maxSize); 
    int j = hash2(key, ht->maxSize);

    int attempts = 0;
    while(ht->table[i].occupied && attempts < ht->maxSize){
        if(strcmp(ht->table[i].key, key) == 0)
            return ht->table[i].heap_pos;
        i = (i + j) % ht->maxSize;
        attempts++;
    }
    return -1;
}

void HTupdate(ht_t ht, char *key, int new_heap_pos){
    if(ht == NULL || key == NULL) return;

    int i = hash1(key, ht->maxSize); 
    int j = hash2(key, ht->maxSize);

    int attempts = 0;
    while(ht->table[i].occupied && attempts < ht->maxSize){
        if(strcmp(ht->table[i].key, key) == 0){
            ht->table[i].heap_pos = new_heap_pos;
            return;
        }
        i = (i + j) % ht->maxSize;
        attempts++;
    }
}

void HTdelete(ht_t ht, char *key){
    if(ht == NULL || key == NULL) return;

    int i = hash1(key, ht->maxSize); 
    int j = hash2(key, ht->maxSize);

    int attempts = 0;
    while(ht->table[i].occupied && attempts < ht->maxSize){
        if(strcmp(ht->table[i].key, key) == 0){
            free(ht->table[i].key);
            ht->table[i].key = NULL;
            ht->table[i].heap_pos = -1;
            ht->table[i].occupied = 0;
            ht->heapsize--;
            return;
        }
        i = (i + j) % ht->maxSize;
        attempts++;
    }
}

int HTempty(ht_t ht){
    return (HTcount(ht) == 0);
}

int HTcount(ht_t ht){
    if(ht == NULL) return 0;
    return ht->heapsize;
}

int HTfull(ht_t ht){
    return ht->maxSize == ht->heapsize;
}

void HTfree(ht_t ht){
    if(ht == NULL) return;
    for(int i = 0; i < ht->maxSize; i++){
        if(ht->table[i].occupied)
            free(ht->table[i].key);
    }
    free(ht->table);
    free(ht);
}