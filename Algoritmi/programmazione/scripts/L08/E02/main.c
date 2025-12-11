// <id_elab1> <id_rete1> <id_elab2> <id_rete2> <flusso>
/*
- i nomi dei singoli nodi sono univoci all'interno del grafo
- non sono ammessi cappi
- tra due nodi c'è al massimo un arco (non è un multigrafo)
- le sotto-reti sono sotto-grafi non necessariamente connessi.

- il grafo sia implementato come ADT di I classe, predisposto in modo tale da poter contenere sia
la matrice sia le liste di adiacenza. Nella fase di caricamento dei dati da file si generi solamente la
matrice di adiacenza, su comando esplicito va generata anche la lista di adiacenza
- si utilizzi una tabella di simboli tale da fornire corrispondenze “da nome a indice” e “da indice a
nome”. 
DOPO:
- elencare in ordine alfabetico i vertici e per ogni vertice gli archi che su di esso insistono, sempre
in ordine alfabetico
- dati 3 vertici i cui nomi sono letti da tastiera, verificare se essi sono adiacenti a coppie, cioè se
formano un sottografo completo. Tale funzione sia implementata sia per la rappresentazione con
matrice delle adiacenze, sia per la rappresentazione con lista delle adiacenze
- generare la rappresentazione a lista di adiacenza, SENZA leggere nuovamente il file, a partire da
quella a matrice di adiacenza. 

*/
#include <stdio.h>
#include <stdlib.h>

#define nfin ""
#define NMAX 30

int main(void){
    FILE *fin;

    if((fin = fopen(nfin,"r")) == NULL){
        perror("Apertura file");
        return 1;
    }


    return 0;
}