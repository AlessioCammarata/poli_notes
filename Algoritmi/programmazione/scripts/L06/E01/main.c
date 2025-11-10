#include <stdio.h>
#include <stdlib.h>

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L06/E01/att1.txt"
// #define nfin "./att1.txt"

/*
Passo 1: dimostrazione di applicabilità
Ordinando le attività seguendo un ordine cronologico, ci rendiamo conto che vige un criterio di componibilità delle soluzioni, in quanto è possibile sommare la 
durata di attività compatibili prese seguendo l'ordine temporale.

d(n) = durata(n) + d(k) se compatibili le attività n e k, dove d è la funzione che restituisce la durata totale fino a k. Per ottenere la migliore basta cercare il massimo.

Perciò esiste una sottostruttura ottima e dunque possiamo applicare la programmazione dinamica.

Passo 2: calcolo ricorsivo del valore ottimo
Implementata già nell'esercizio 1 del laboratorio 5.

Passo 3 e Passo 4: calcolo con programmazione dinamica bottom-up del valore ottimo e della soluzione ottima

Vengono eseguiti in questo codice.
*/

typedef struct {
    int start_t, end_t;
} att;

int leggiFile(FILE *fin, att *activities, int n);
int intercept(att *act1, att *act2);
void attSel(int N, att *V); 

int main(void){
    FILE *fin;
    att *activities;
    int n;

    if((fin = fopen(nfin,"r")) == NULL){
        printf("Errore in apertura del file\n");
        return 1;
    }

    if(fscanf(fin,"%d",&n) != 1){
        printf("Errore nel file: manca il numero di valori\n");
        fclose(fin);
        return 1;
    }

    activities = malloc(n*sizeof(att));
    if(activities == NULL){
        perror("malloc");
        fclose(fin);
        return 1;
    }

    if (!leggiFile(fin, activities, n)){
        printf("Errore in lettura del file\n");
        free(activities);
        fclose(fin);
        return 1;
    }
    fclose(fin);

    attSel(n, activities); //Lancio il wrapper

    free(activities);
    return 0;
}

int leggiFile(FILE *fin, att *activities, int n){
    int i;
    for(i = 0; i<n; i++){
        if(fscanf(fin,"%d %d",&activities[i].start_t,&activities[i].end_t) != 2){
            break;
        }
    }

    return n==i;
}

//Controllo l'intersezione, implementata per modularità
int intercept(att *act1, att *act2){
    return act1->start_t < act2->end_t && act2->start_t < act1->end_t;
}

int cmp_intervals(const void *a, const void *b) { //qsort necessità const void e il cast interno
    att *x = (att *)a;
    att *y = (att *)b;

    if (x->end_t != y->end_t)
        return x->end_t - y->end_t;   // ordina per fine
    return x->start_t - y->start_t;   // poi per inizio 
}

//Wrapper
void attSel(int N, att *V){

    //Programmazione dinamica
    int val, start = 0, *dp = malloc(N*sizeof(int)), *b_seq = malloc(N*sizeof(int));
    qsort(V, N, sizeof(*V), cmp_intervals);
    for (int j = 0; j < N; j++) b_seq[j] = -1;  //Metto un valore sentinella

    for(int j = N-1; j>=0; j--){
        dp[j] = V[j].end_t - V[j].start_t; // Valore iniziale che indica la durata della j-attività

        for(int i = j + 1; i<N; i++){
            if(!intercept(&V[j],&V[i])){ //Guardo se è compatibile
                val = V[j].end_t - V[j].start_t + dp[i]; //Sommo al valore quello del valore compatibile gia calcolato
                if(val > dp[j]){ // Se il valore è maggiore della durata gia presente in quella casella lo tengo senno no
                    dp[j] = val;
                    b_seq[j] = i;
                }

            }
        }
    }
    for(int i = 1; i<N; i++) if(dp[i] > dp[start]) start = i;  //Trovo la chiave da cui iniziare
    
    printf("La sequenza massima ha durata %d:\n",dp[start]);
    for(int i = start; i!=-1; i = b_seq[i]){
        printf("(%d-%d) ",V[i].start_t,V[i].end_t);
    }

    free(b_seq);
    free(dp);
}