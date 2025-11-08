#include "inventario.h"

int leggiinventory(FILE *fin, inventory *inv){
    int i;
    for(i = 0; i<inv->n; i++){
        if(fscanf(fin,"%50s %50s %d %d %d %d %d %d",inv->items[i].name,inv->items[i].class,&inv->items[i].stat.hp,
                                            &inv->items[i].stat.mp,&inv->items[i].stat.atk,&inv->items[i].stat.def,
                                            &inv->items[i].stat.mag,&inv->items[i].stat.spr) != 8) 
            break;
    }

    return i==inv->n;
}

item *find_item(inventory *inv, char *name){
    for(int i = 0; i<inv->n; i++){
        if(strcmp(inv->items[i].name,name) == 0){
            return &inv->items[i];
        }
    }
    return NULL;
}

void print_item(FILE *fout, item *instance){
    fprintf(fout,"%s %s %d %d %d %d %d %d\n",instance->name,instance->class,instance->stat.hp,
                                            instance->stat.mp,instance->stat.atk,instance->stat.def,
                                            instance->stat.mag,instance->stat.spr);
}