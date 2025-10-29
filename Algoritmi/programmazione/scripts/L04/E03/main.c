#include <stdio.h>
#include <stdlib.h>

// #define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L04/E03/easy_test_set.txt"
#define nfin "./hard_test_set.txt"
#define Nstones 4

typedef enum{
    Z,R,T,S
}stones;

void free_vet(int **vet, int n);
int leggiFile(FILE *fin, int **all_stones, int n);
int necklace_maker(int *stones, int pos);

int main(void){
    FILE *fin;
    int len = 0, n, **all_stones;

    if((fin = fopen(nfin,"r")) == NULL){
        printf("Errore in apertura del file\n");
        return 1;
    }

    if(fscanf(fin,"%d",&n) != 1){
        printf("Manca il numero di collane");
        fclose(fin);
        return 1;
    }

    all_stones = malloc(n*sizeof(int *));
    if (all_stones == NULL) {
        perror("malloc");
        fclose(fin);
        return 1; //Fermo la lettura e do errore.
    }

    if (!leggiFile(fin, all_stones, n)) { // Leggo i dati e li metto in playlist
        free(all_stones);
        fclose(fin);
        return 1;
    }
    fclose(fin);

    for(int k = 0, start; k<n; k++){
        printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n",all_stones[k][Z],all_stones[k][R],all_stones[k][T],all_stones[k][S],all_stones[k][Z]+all_stones[k][R]+all_stones[k][T]+all_stones[k][S]);
        // start: se R/T entrambi zero, la len è il massimo tra Z ed S
        if (all_stones[k][R] == 0 && all_stones[k][T] == 0) {
            start = (all_stones[k][Z] > 0) ? Z : S;
            len = all_stones[k][start];
        } else {
            start = (all_stones[k][R] > all_stones[k][T]) ? R : T;
            len = necklace_maker(all_stones[k], start);
        }

        printf("Collana massima di lunghezza %d\n",len);
        //Libero la memora appena letta
        free(all_stones[k]);
    }
    
    free(all_stones);
    return 0;
}

void free_vet(int **vet, int n){
    for (int i = 0; i < n; i++) { 
        free(vet[i]); 
    }
}

int leggiFile(FILE *fin, int **all_stones, int n){
    int i, j;
    for(i = 0; i < n; i++){

        all_stones[i] = malloc(Nstones*sizeof(int));
        if (all_stones[i] == NULL) {
            perror("malloc");
            free_vet(all_stones, i);
            return 0; //Fermo la lettura e do errore.
        }

        // leggo le pietre
        for (j = 0; j < Nstones; j++) {
            if (fscanf(fin,"%d",&all_stones[i][j]) != 1) {
                printf("Errore in lettura delle pietre alla voce %d\n",i);
                // cleanup completo (incl. corrente i)
                free_vet(all_stones, i + 1);
                return 0;
            }
        }
        
    }

    return 1;
}

// Ordine: z, r, t, s
int next_stones_avaibility(int *stones, int pos){
    if(pos == Z) pos = stones[Z] == 0 ? R : Z; //Finisco gli zaffiri e passo ai rubini
    else if(pos == R) pos = stones[T] > 1 && (stones[R] != 0) ? T : S; //Finche ci sono topazi e rubini il prossimo è topazio
    else if(pos == T) pos = stones[R] > 1 && (stones[T] != 0)? R : Z; //Finche ci sono rubini e topazi il prossimo è rubino
    else if(pos == S) pos = stones[S] == 0 ? T : S; // Finisco gli smeraldi poi passo ai topzai

    return pos;
}

// Disposizioni ripetute con criterio
//Parto o dai rubini o dai topazi perche formano un ciclo tra di loro, se non ci sono il caso è banale
int necklace_maker(int *stones, int pos){
    int len = 0;

    if(stones[pos] <= 0){
        return len;
    }
    stones[pos]--;

    pos = next_stones_avaibility(stones,pos);
    len = necklace_maker(stones, pos) + 1;

    return len;

}