#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp){
    if(!pgp || !fp) return 0;
    if(fscanf(fp," %99s %99s %99s ", pgp->cod, pgp->nome, pgp->classe) != 3) return 0;
    stat_read(fp,&pgp->b_stat); //Inserisco le statistiche base
    
    pgp->equip = equipArray_init(); //Inizializzo lo zaino
    if(!pgp->equip) return 0;
    return 1;
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    if (!pgp || !invArray || !fp) return;

    fprintf(fp,"%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp,&pgp->b_stat,MIN_STAT);
    // fprintf(fp,"\n");
    equipArray_print(fp, pgp->equip, invArray);
    // fprintf(fp,"\n");
}
/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp){
    if(pgp->equip == NULL) return;
    equipArray_free(pgp->equip);
    pgp->equip = NULL;
}

/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    if (!pgp || !invArray) return;
    equipArray_update(pgp->equip, invArray);
}