#include "inv.h"

/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp,"%d %d %d %d %d %d",&statp->hp,&statp->mp,&statp->atk,&statp->def,&statp->mag,&statp->spr);
}
void stat_print(FILE *fp, stat_t *statp, int soglia){
    fprintf(fp,"%d %d %d %d %d %d",statp->hp,statp->mp,statp->atk,statp->def,statp->mag,statp->spr);
}

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp,"%50s %50s %d %d %d %d %d %d",invp->nome,invp->tipo);
    stat_read(fp,&invp->stat);
}
void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp,"%s %s ",invp->nome,invp->tipo);
    stat_print(fp,&invp->stat,0);
}

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}

// int leggiinventory(FILE *fin, inventory *inv){
//     int i;
//     for(i = 0; i<inv->n; i++){
//         if(fscanf(fin,"%50s %50s %d %d %d %d %d %d",inv->items[i].name,inv->items[i].class,&inv->items[i].stat.hp,
//                                             &inv->items[i].stat.mp,&inv->items[i].stat.atk,&inv->items[i].stat.def,
//                                             &inv->items[i].stat.mag,&inv->items[i].stat.spr) != 8) 
//             break;
//     }

//     return i==inv->n;
// }

// item *find_item(inventory *inv, char *name){
//     for(int i = 0; i<inv->n; i++){
//         if(strcmp(inv->items[i].name,name) == 0){
//             return &inv->items[i];
//         }
//     }
//     return NULL;
// }

// void print_item(FILE *fout, item *instance){
//     fprintf(fout,"%s %s %d %d %d %d %d %d\n",instance->name,instance->class,instance->stat.hp,
//                                             instance->stat.mp,instance->stat.atk,instance->stat.def,
//                                             instance->stat.mag,instance->stat.spr);
// }