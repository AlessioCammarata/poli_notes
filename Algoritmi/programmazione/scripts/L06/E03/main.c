#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"
#include "personaggi.h"

#define nfin1 "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L06/E03/pg.txt"
#define nfin2 "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L06/E03/inventario.txt"
#define MAXL 35

typedef enum {
    r_remove_player, r_add_player, r_add_equip, r_remove_equip, r_calc_stats, r_fine
} comando_e;

comando_e leggiComando (void);

int main(void){
    int end = 0;
    char ch;
    FILE *fin;
    inventory inv;
    tabPG players;
    comando_e act;
    
    if((fin = fopen(nfin1,"r")) == NULL){
        printf("Errore in apertura del file %s\n",nfin1);
        return 1;
    }

    if(leggiPlayers(fin, &players) == -1){
        printf("Errore in lettura del file %s\n",nfin1);
        fclose(fin);
        return 1;
    }
    fclose(fin);

    if((fin = fopen(nfin2,"r")) == NULL){
        printf("Errore in apertura del file %s\n",nfin2);
        free_players(&players);
        return 1;
    }

    fscanf(fin,"%d",&inv.n); //Presumo sia sempre presente
    inv.items = malloc(inv.n*sizeof(item));
    if(inv.items == NULL){
        perror("malloc");
        free_players(&players);
        fclose(fin);
        return 1;
    }

    if(!leggiinventory(fin,&inv)){
        printf("Errore in lettura del file %s\n",nfin2);
        free_players(&players);
        free(inv.items);
        fclose(fin);
        return 1;
    }
    fclose(fin);
    
    // players.head->next->p.bp.items[0] = &inv.items[2];
    // for (link p = players.head; p != NULL; p = p->next)
    //     print_player(stdout,&p->p);

    // for(int i = 0; i<inv.n; i++) print_item(stdout,&inv.items[i]);

    while (!end) {

        printf("Inserisci la tua scelta:\n");
        act = leggiComando();
        // Consuma e scarta tutti i caratteri rimanenti nel buffer di input fino al carattere di nuova linea ('\n') o alla fine del file (EOF).
        while ((ch = getchar()) != '\n' && ch != EOF);

        switch (act) {
            case r_remove_player:

                if(players.n > 0){
                    char id[MAX_ID];
                    printf("Inserisci l'id del personaggio da rimuovere\n");
                    scanf("%s",id);

                    if (!remove_player(&players,id)) printf("Elemento non trovato\n");
                    else printf("Elemento rimosso con successo\n");
                }else printf("Non ci sono abbastanza elementi per rimuovere\n");
    
                break;
            case r_add_player:
 

                break;  
            case r_add_equip:
                
            
                // if (!bp) return 0; // bp invalido
                // if (!bp->items) return 0; // items non inizializzato

                break;
            case r_remove_equip:
                
                break;
            case r_calc_stats:
                
                break;
            case r_fine:
                end = 1;
                break;
            default:
                printf("Errore, comando non valido.\n");
        }
    }

    
    free_players(&players);
    free(inv.items);
    return 0;
}

comando_e leggiComando (void) {
    comando_e c;
    char cmd[MAXL];
    char tabella[r_fine + 1][MAXL] = {
        "rimuovi_personaggio","aggiungi_personaggio","aggiungi_equipaggiamento","rimuovi_equipaggiamento","calcola_statisiche","fine"
    };

    printf("comando (inserimento_tastiera");
    printf("/rimuovi_personaggio/aggiungi_personaggio/aggiungi_equipaggiamento/rimuovi_equipaggiamento/calcola_statisiche/fine): ");
    scanf("%s",cmd); 
    c=r_remove_player;

    while(c<r_fine+1 && strcmp(cmd,tabella[c])!=0)
        c++;

    return (c);
}