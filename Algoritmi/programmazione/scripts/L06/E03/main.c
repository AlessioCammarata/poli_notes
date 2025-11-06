#include <stdio.h>
#include <stdlib.h>

#define nfin1 "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L06/E03/pg.txt"
#define nfin2 "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L06/E03/inventario.txt"
#define NMAX 51
#define MAX_ID 7
#define DEFAULT_VALUE 8

typedef struct{
    char id[MAX_ID], name[NMAX], class[NMAX];
    int hp, mp, atk, def, mag, spr;
} player;

typedef struct{
    char name[NMAX], class[NMAX];
    int hp, mp, atk, def, mag, spr;
} oggetto;

typedef struct{
    oggetto *items;
    int n;
} inventario;

int leggiPlayers(FILE *fin, player **pp, int *maxn);
int leggiInventario(FILE *fin, inventario inv);

int main(void){
    int n, maxn = DEFAULT_VALUE;
    FILE *fin;
    inventario inv;
    player *players = malloc(DEFAULT_VALUE*sizeof(player));
    if(players == NULL){
        perror("malloc");
        return 1;
    }
    
    if((fin = fopen(nfin1,"r")) == NULL){
        printf("Errore in apertura del file %s\n",nfin1);
        free(players);
        return 1;
    }

    n = leggiPlayers(fin, &players, &maxn);
    if(n == -1){
        printf("Errore in lettura del file %s\n",nfin1);
        fclose(fin);
        free(players);
        return 1;
    }
    fclose(fin);

    // for(int i = 0; i<n; i++) printf("%s\n", players[i].id);
    if((fin = fopen(nfin2,"r")) == NULL){
        printf("Errore in apertura del file %s\n",nfin2);
        free(players);
        return 1;
    }

    fscanf(fin,"%d",&inv.n); //Presumo sia sempre presente
    inv.items = malloc(inv.n*sizeof(oggetto));
    if(inv.items == NULL){
        perror("malloc");
        free(players);
        fclose(fin);
        return 1;
    }

    if(!leggiInventario(fin,inv)){
        printf("Errore in lettura del file %s\n",nfin2);
        free(players);
        free(inv.items);
        fclose(fin);
        return 1;
    }
    fclose(fin);
    
    // for(int i = 0; i<inv.n; i++) printf("%s\n", inv.items[i].name);
    
    free(players);
    free(inv.items);
    return 0;
}

int leggiPlayers(FILE *fin, player **pp, int *maxn){
    int i = 0;
    player *p = *pp;
    while(fscanf(fin,"%6s %50s %50s %d %d %d %d %d %d",p[i].id,p[i].name,p[i].class,&p[i].hp,&p[i].mp,&p[i].atk,&p[i].def,&p[i].mag,&p[i].spr) == 9){
        i++;
        if(i >= *maxn){ 
            *maxn *= 2;
            p = realloc(p, (*maxn)*sizeof(player));
            if(p == NULL){
                perror("realloc");
                return -1;
            }
            *pp = p;
        }
    }

    return i;
}

int leggiInventario(FILE *fin, inventario inv){
    int i;
    for(i = 0; i<inv.n; i++){
        if(fscanf(fin,"%50s %50s %d %d %d %d %d %d",inv.items[i].name,inv.items[i].class,&inv.items[i].hp,&inv.items[i].mp,&inv.items[i].atk,&inv.items[i].def,&inv.items[i].mag,&inv.items[i].spr) != 8) 
            break;
    }

    return i==inv.n;
}