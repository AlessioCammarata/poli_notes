#include "invArray.h"
#include "equipArray.h"

struct equipArray_s{
    int items[EQUIP_SLOT];
    int item; //Indice item utilizzato
};

/* creatore e disruttore */
equipArray_t equipArray_init(){
    equipArray_t backpack = malloc(sizeof *backpack);
    if (backpack == NULL) return NULL;
    for (int i = 0; i < EQUIP_SLOT; i++) backpack->items[i] = -1;
    backpack->item = -1;
    return backpack;
}
void equipArray_free(equipArray_t equipArray){
    if (equipArray == NULL) return;
    free(equipArray);
}

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray){
    if(!equipArray) return -1;
    int count = 0;
    for(int i = 0; i<EQUIP_SLOT; i++) if(equipArray->items[i] != -1) count++;
    return count;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    if (!equipArray || !invArray || !fp) return;

    for(int i = 0; i<EQUIP_SLOT; i++)
        if (equipArray->items[i] != -1) {
            inv_t *it = invArray_getByIndex(invArray, equipArray->items[i]);
            if (it){
                fprintf(fp,"- ");
                inv_print(fp, it);
            }
    }
}

/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    if (!equipArray || !invArray) return;
    char leave[LEN], insert[LEN];
    int i,index_l,index_i;
    printf("Inserisci il valore da togliere: [(+) se si vuole aggiungere un oggetto nuovo]\n");
    scanf("%99s",leave);

    printf("Inserisci il valore da mettere:\n");
    scanf("%99s",insert);

    if(strcmp(leave,"+") == 0){
        if(equipArray_inUse(equipArray) == EQUIP_SLOT){
            printf("Non puoi aggiungere altri elementi, zaino pieno\n");
            return;
        }
        index_i = invArray_searchByName(invArray,insert);
        if(index_i != -1){
            for(i = 0; i<EQUIP_SLOT && equipArray->items[i] != -1; i++); //Trova primo slot libero
            if (i < EQUIP_SLOT) equipArray->items[i] = index_i;
        } else printf("Errore elemento da aggiungere non trovato\n");
    }else{
        index_l = invArray_searchByName(invArray,leave);
        if(index_l == -1){
            printf("Errore elemento da togliere non trovato\n");
            return;
        }

        index_i = invArray_searchByName(invArray,insert);
        if(index_i == -1){
            printf("Errore elemento da aggiungere non trovato\n");
            return;
        }

        for(i = 0; i<EQUIP_SLOT && equipArray->items[i] != index_l; i++); //Trova lo slot del valore
        if (i < EQUIP_SLOT) equipArray->items[i] = index_i;
    }

}
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    if (!equipArray ) return -1;
    if (index < 0 || index >= EQUIP_SLOT) return -1;
    return equipArray->items[index];
}


