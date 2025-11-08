#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <stdio.h>
#include <string.h>

#define NMAX 51

typedef struct{
    int hp, mp, atk, def, mag, spr;
} stat_t;

typedef struct{
    char name[NMAX], class[NMAX];
    stat_t stat;
} item;

typedef struct{
    item *items;
    int n;
} inventory;

int leggiinventory(FILE *fin, inventory *inv);
item *find_item(inventory *inv, char *name);
void print_item(FILE *fout, item *instance);

#endif // INVENTARIO_H