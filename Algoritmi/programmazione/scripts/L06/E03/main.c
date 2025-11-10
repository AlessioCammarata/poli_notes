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

    link p;
    item *item_link;
    stat_t stats;
    char id[MAX_ID];
    char name[NMAX];
                
    while (!end) {
        for (p = players.head; p != NULL; p = p->next)//Stampa per vedere se hai fatto qualcosa
            print_player(stdout,&p->p);


        printf("\n\nInserisci la tua scelta:\n");
        act = leggiComando();
        // Consuma e scarta tutti i caratteri rimanenti nel buffer di input fino al carattere di nuova linea ('\n') o alla fine del file (EOF).
        while ((ch = getchar()) != '\n' && ch != EOF);

        switch (act) {
            case r_remove_player:

                if(players.n > 0){
                    
                    printf("Inserisci l'id del personaggio da rimuovere\n");
                    scanf("%6s",id);

                    if (!remove_player(&players,id)) printf("Elemento non trovato\n");
                    else printf("Elemento rimosso con successo\n");
                }else printf("Non ci sono abbastanza elementi per rimuovere\n");
    
                break;
            case r_add_player:
                link newNode = create_node();
                if(!newNode){
                    printf("Errore nell'inizializzazione del nodo\n");
                    break;
                }
                printf("Inserisci l'id del personaggio\n");
                scanf("%6s",newNode->p.id);
                if(find_player(&players,newNode->p.id) != NULL){
                    printf("Elemento già presente\n");
                    free(newNode->p.bp.items);
                    free(newNode);
                    break;
                }
                
                printf("Inserire il nome del personaggio:\n");
                scanf("%50s",newNode->p.name);
                printf("Inserire la classe del personaggio:\n");
                scanf("%50s",newNode->p.class);
                printf("Inserire le statistiche:\n <hp> <mp> <atk> <def> <mag> <spr>\n\n");
                if(scanf(" %d %d %d %d %d %d",&newNode->p.stat.hp,&newNode->p.stat.mp,&newNode->p.stat.atk,&newNode->p.stat.def,&newNode->p.stat.mag,&newNode->p.stat.spr) != 6){
                    free(newNode->p.bp.items);
                    free(newNode);
                    break;
                }
                add_player(&players,newNode);

                break;
            case r_add_equip:
                
                printf("Inserisci l'id del personaggio a cui si vuole aggiungere un oggetto\n");
                scanf("%6s",id);

                p = find_player(&players, id);
                if (p == NULL) {
                    printf("Elemento non trovato\n");
                    break;
                }
                if (p->p.bp.items == NULL) {
                    printf("Inventario del personaggio non inizializzato\n");
                    break;
                }

                printf("Inserire il nome dell'oggetto da assegnargli\n");
                scanf("%50s",name);

                item_link = find_item(&inv,name);
                if(!item_link){
                    printf("Elemento non trovato\n");
                    break;
                }
                add_equip(&p->p.bp,item_link);

                break;
            case r_remove_equip:

                printf("Inserisci l'id del personaggio a cui si vuole rimuovere un oggetto\n");
                scanf("%6s",id);

                p = find_player(&players, id);
                if (p == NULL) {
                    printf("Elemento non trovato\n");
                    break;
                }

                printf("Inserire il nome dell'oggetto da rimuovere\n");
                scanf("%50s",name);

                item_link = find_item(&inv,name);
                if(!item_link){
                    printf("Elemento non trovato\n");
                    break;
                }
                if(!remove_equip(&p->p.bp,item_link)) printf("Elemento non trovato\n");
                else printf("Elemento rimosso con successo\n");

                break;
            case r_calc_stats:
                printf("Inserisci l'id del personaggio di cui si vuole calcolare il punteggio\n");
                scanf("%6s",id);

                p = find_player(&players, id);
                if (p == NULL) {
                    printf("Elemento non trovato\n");
                    break;
                }
                //Standard Value
                stats.hp = p->p.stat.hp;
                stats.mp = p->p.stat.mp;
                stats.atk = p->p.stat.atk;
                stats.def = p->p.stat.def;
                stats.mag = p->p.stat.mag;
                stats.spr = p->p.stat.spr;

                for(int i = 0; i<DEFAULT_VALUE; i++){
                    if(p->p.bp.items[i] != NULL){
                        stats.hp  += p->p.bp.items[i]->stat.hp;
                        stats.mp  += p->p.bp.items[i]->stat.mp;
                        stats.atk += p->p.bp.items[i]->stat.atk;
                        stats.def += p->p.bp.items[i]->stat.def;
                        stats.mag += p->p.bp.items[i]->stat.mag;
                        stats.spr += p->p.bp.items[i]->stat.spr;
                    }
                }
                stats.hp  = stats.hp  < 0 ? 0 : stats.hp; 
                stats.mp  = stats.mp  < 0 ? 0 : stats.mp;
                stats.atk = stats.atk < 0 ? 0 : stats.atk;
                stats.def = stats.def < 0 ? 0 : stats.def;
                stats.mag = stats.mag < 0 ? 0 : stats.mag;
                stats.spr = stats.spr < 0 ? 0 : stats.spr;
                printf("Statistiche calcolate:\n");
                printf("%s %s %d %d %d %d %d %d\n",p->p.name,p->p.class,stats.hp,stats.mp,stats.atk,stats.def,stats.mag,stats.spr);
                
                break;
            case r_fine:
                end = 1;
                break;
            default:
                printf("Errore, comando non valido.\n");
        }
        printf("\n");
    }

    
    free_players(&players);
    free(inv.items);
    return 0;
}

comando_e leggiComando (void) {
    comando_e c;
    char cmd[MAXL];
    char tabella[r_fine + 1][MAXL] = {
        "rimuovi_personaggio","aggiungi_personaggio","aggiungi_equipaggiamento","rimuovi_equipaggiamento","calcola_statistiche","fine"
    };

    printf("comando (rimuovi_personaggio");
    printf("/aggiungi_personaggio/aggiungi_equipaggiamento/rimuovi_equipaggiamento/calcola_statistiche/fine): ");
    scanf("%34s",cmd); 
    c=r_remove_player;

    while(c<r_fine+1 && strcmp(cmd,tabella[c])!=0)
        c++;

    return (c);
}