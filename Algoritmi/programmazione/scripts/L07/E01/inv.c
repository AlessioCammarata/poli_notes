#include "inv.h"

/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp,"%d %d %d %d %d %d",&statp->hp,&statp->mp,&statp->atk,&statp->def,&statp->mag,&statp->spr);
}
void stat_print(FILE *fp, stat_t *statp, int soglia){
    fprintf(fp,"%d %d %d %d %d %d\n", statp->hp  > MIN_STAT ? statp->hp : MIN_STAT,
                                    statp->mp  > MIN_STAT ? statp->mp : MIN_STAT,
                                    statp->atk > MIN_STAT ? statp->atk : MIN_STAT,
                                    statp->def > MIN_STAT ? statp->def : MIN_STAT,
                                    statp->mag > MIN_STAT ? statp->mag : MIN_STAT,
                                    statp->spr > MIN_STAT ? statp->spr : MIN_STAT);
}

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp){
    // leggere nome e tipo; le statistiche vengono lette da stat_read
    if (fscanf(fp, "%99s %99s", invp->nome, invp->tipo) != 2) {
        invp->nome[0] = '\0';
        invp->tipo[0] = '\0';
    }
    stat_read(fp,&invp->stat);
}
void inv_print(FILE *fp, inv_t *invp){
    if(!invp) return;
    fprintf(fp,"%s %s ",invp->nome,invp->tipo);
    stat_print(fp,&invp->stat,MIN_STAT);
}

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}