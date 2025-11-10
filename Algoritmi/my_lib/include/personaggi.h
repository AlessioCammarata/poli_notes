#ifndef PERSONAGGI_H
#define PERSONAGGI_H

#include "inventario.h"
#include <stdlib.h>

#define MAX_ID 7
#define DEFAULT_VALUE 8

typedef struct node_p *link, node_p; 

typedef struct{
    item **items;
    item *act_item; //Item utilizzato
} backpack;

typedef struct{
    char id[MAX_ID], name[NMAX], class[NMAX];
    backpack bp;
    stat_t stat;
} player;

struct node_p{
    player p;
    link next;
};

typedef struct{
    link tail;
    link head;
    int n;
} tabPG;

int helper_bp(player *p);
link create_node();
int leggiPlayers(FILE *fin, tabPG *players);
void add_player(tabPG *players, node_p *node);
int remove_player(tabPG *players, char *id);
node_p *find_player(tabPG *players, char *id);
void print_player(FILE *fout, player *instance);
int add_equip(backpack *bp, item *instance);
int remove_equip(backpack *bp, item *instance);
void free_players(tabPG *players);

#endif //PERSONAGGI_H