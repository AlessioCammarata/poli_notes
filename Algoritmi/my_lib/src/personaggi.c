#include "personaggi.h"

int helper_bp(player *p){ //Inizializza lo zaino
    p->bp.items = malloc(DEFAULT_VALUE*sizeof(item *));
    if(!p->bp.items){
        perror("malloc");
        return 0;
    }
    for(int k = 0; k<DEFAULT_VALUE; k++) p->bp.items[k] = NULL;
    p->bp.act_item = NULL;
    return 1;
}

int leggiPlayers(FILE *fin, tabPG *players){
    int i = 0;
    link pnode = malloc(sizeof(node_p));
    if(!pnode){
        perror("malloc");
        return -1;
    }
    link last = NULL;
    players->head = pnode;

    while(fscanf(fin,"%6s %50s %50s %d %d %d %d %d %d",pnode->p.id,pnode->p.name,pnode->p.class,&pnode->p.stat.hp,
                                                    &pnode->p.stat.mp,&pnode->p.stat.atk,&pnode->p.stat.def,
                                                    &pnode->p.stat.mag,&pnode->p.stat.spr) == 9){
        i++;
        last = pnode;
        pnode->next = malloc(sizeof(node_p));
        if(!pnode->next || !helper_bp(&pnode->p)){ //Inizializzo il bp
            perror("malloc");
            link cur = players->head;
            while (cur) {
                link tmp = cur->next;
                if (cur->p.bp.items) {
                    free(cur->p.bp.items);
                    cur->p.bp.items = NULL;
                }
                free(cur);
                cur = tmp;
            }
            players->head = players->tail = NULL;
            players->n = 0;
            return -1;
        }
        pnode = pnode->next;
    }

    if(i!= 0){
        last->next = NULL;
        players->tail = last;
    }else{
        players->head = players->tail = NULL;
    }
    players->n = i;
    free(pnode);

    return 0;
}

void add_player(tabPG *players, node_p *node){
    node->next = NULL;

    if (players->head == NULL) {
        players->head = players->tail = node; //Lista vuota
    } else {
        players->tail->next = node;
        players->tail = node;
    }
    players->n += 1;

}

int remove_player(tabPG *players, char *id){
    link prev = NULL;
    link cur = players->head;
    while (cur != NULL && strcmp(cur->p.id, id) != 0) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) return 0; // non trovato

    if (prev == NULL) players->head = cur->next;
    else prev->next = cur->next;

    if (cur == players->tail) players->tail = prev;

    if (cur->p.bp.items) {
        free(cur->p.bp.items);
        cur->p.bp.items = NULL;
    }

    free(cur);
    players->n -= 1;
    if (players->n == 0) players->head = players->tail = NULL;

    return 1;
}

node_p *find_player(tabPG *players, char *id){
    for(link p = players->head; p!=NULL; p = p->next)
        if(strcmp(p->p.id+2,id+2) == 0)
            return p;
    return NULL;
}

void print_player(FILE *fout, player *instance){
    fprintf(fout,"%s %s %d %d %d %d %d %d\n",instance->name,instance->class,instance->stat.hp,
                                            instance->stat.mp,instance->stat.atk,instance->stat.def,
                                            instance->stat.mag,instance->stat.spr);
    if(instance->bp.items != NULL){
        for(int i = 0; i<DEFAULT_VALUE; i++)
            if(instance->bp.items[i] != NULL){
                printf(" -"); print_item(fout,instance->bp.items[i]);
            }
    }
}

int add_equip(backpack *bp, item *instance){
    for (int i =0; i < DEFAULT_VALUE; i++)
        if (bp->items[i] == instance) return 1; //Elemento gia presente

    for (int i = 0; i < DEFAULT_VALUE; i++) {
        if (bp->items[i] == NULL) {
            bp->items[i] = instance;
            return 1; // oggetto messo nello zaino
        }
    }

    return 0; //Zaino pieno
}

int remove_equip(backpack *bp, item *instance){
    if(bp->act_item == instance) bp->act_item == NULL; // Tolgo l'elemento se presente anche dalla mano

    for (int i = 0; i < DEFAULT_VALUE; i++)
        if (bp->items[i] == instance){
            bp->items[i] = NULL;
            return 1; // oggetto rimosso
        }

    return 0; //Oggetto non trovato
}

void free_players(tabPG *players){
    link cur = players->head;
    while (cur != NULL) {
        link next = cur->next;

        if (cur->p.bp.items) {
            free(cur->p.bp.items); //Libero i link items
            cur->p.bp.items = NULL;
        }

        free(cur);
        cur = next;
    }
    players->head = players->tail = NULL;
    players->n = 0;
}