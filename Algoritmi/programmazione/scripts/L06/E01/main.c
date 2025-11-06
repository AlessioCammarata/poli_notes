#include <stdio.h>
#include <stdlib.h>

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L06/E01/att.txt"
// #define nfin "./att1.txt"
/*
Passo 1: dimostrazione di applicabilità

La soluzione dinamica pretende l'ordinamento delle attività rispettando il criterio della non intersezione dal secondo estremo. percio (1,2)-(2,3) va bene ma (1,4)-(2,3) no
Ci sono 3 castistiche:
    - L'estremo 1 è uguale: in quel caso prendo quello con il secondo piu grande
    - L'estremo 2 è uguale: in quel caso prendo quello con il primo piu grande
    - Entrambi gli estremi sono piu piccoli: in questo caso prendo quello che li ha piu grandi.
    - L'estremo 1 è maggiore ma il 2 è minore (o viceversa): in questo caso devo considerare la lunghezza, tengo l'attività piu lunga, pero considerando che non deve oltrepassare k+1 
                                                            in quel caso preferisco k[i-1]+k[i+1] a k[i]+k[i+1] se la lunghezza di k[i-1]+k[i+1] > k[i] altrimenti prendo solo B.

Percio partendo dal primo valore che inserisco, Confronto con gli altri, partendo da estremo 1 = k incrementando sino all'estremo 1 n-esimo.
Quando incontro una che non è presente la inserisco, se invece confrontando sono in una casistica di sopra scambio.
*/

typedef struct {
    int start_t, end_t;
} att;

int leggiFile(FILE *fin, att *activities, int n);
int intercept(att *act1, att *act2);
void comp_seq(int pos, int sum, int len, int last_idx, att *V, att *seq, int n, int *b_len, att *b_seq, int *b_sum);
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

/*
Devo trovare le sequenza compatibili, quando ne trovo una esco
pos -> poszione attuale
sum -> somma attuale
len -> lunghezza attuale
last_idx -> Indice dell'ultimo valore messo in sequenza
V -> vettore iniziale
seq -> vettore che contiene la seq corrente
n -> totale valori
b_len -> best len
b_seq -> best sequence
b_sum -> max
*/
// void comp_seq(int pos, int sum, int len, int last_idx, att *V, att *seq, int n, int *b_len, att *b_seq, int *b_sum){
//     if(pos==n){
//         //Trovato un nuovo max
//         if(sum > *b_sum){
//             *b_sum = sum;
//             *b_len = len;
//             for(int i = 0; i<len; i++){
//                 b_seq[i] = seq[i]; //Copio la sequenza
//             }
//         }
//         return;
//     }

//     comp_seq(pos+1, sum, len, last_idx, V, seq, n, b_len, b_seq, b_sum);
    
//     if(last_idx == -1 || !intercept(&V[last_idx],&V[pos])){
//         seq[len] = V[pos]; // Inserisco in ordine nella seq che sto analizzando

//         sum += (V[pos].end_t-V[pos].start_t);
//         comp_seq(pos+1, sum, len + 1, pos, V, seq, n, b_len, b_seq, b_sum);
//     }
// }

int cmp_intervals(const void *a, const void *b) { //qsort necessità const void e il cast interno
    att *x = (att *)a;
    att *y = (att *)b;

    if (x->end_t != y->end_t)
        return x->end_t - y->end_t;   // ordina per fine
    return x->start_t - y->start_t;   // poi per inizio 
}

void copy(int *v, int *copy, int n){
    for(int i = 0; i<n; i++)
        copy[i] = v[i];
}

//Wrapper
void attSel(int N, att *V){
    att *seq = malloc(N * sizeof(att));
    att *b_seq = malloc(N * sizeof(att));
    if(!b_seq || !seq){
        perror("malloc");
        free(b_seq);
        free(seq);
        return;
    }
    int b_len, b_sum;
    b_len = b_sum = 0;

    //pos, sum, len, last_idx, V, seq, n, b_len, b_seq, b_sum
    // comp_seq(0, 0, 0, -1, V, seq, N, &b_len, b_seq, &b_sum);
    //Programmazione dinamica
    int last_c , max = 0, *dp = malloc(N*sizeof(int)), *dp_best = malloc(N*sizeof(int));
    qsort(V, N, sizeof(V), cmp_intervals);
    for(int i = 0; i<N; i++) printf("(%d - %d) ", V[i].start_t, V[i].end_t);
    for(int j = 0; j<N; j++){
        last_c = 0; //Ultimo preso
        dp[0] = V[j].end_t - V[j].start_t; // Valore iniziale
        printf("%d\n",dp[last_c]);
        for(int i = 1; i<N; i++){ 
            // printf("(%d - %d) ", V[i].start_t, V[i].end_t);
            dp[i] = dp[last_c];
            if(!intercept(&V[j],&V[i])){
                // if(V[i].end_t - V[i].start_t > dp[i]){ //Se la durata è maggiore del valore dp, la sommo
                if(intercept(&V[last_c],&V[i]) ){ //Devi controllare se la durata sia del tipo 2-3 o 2-5 quindi prendi quello con durata maggiore
                    dp[i] += V[i].end_t - V[i].start_t;
                    last_c = i;
                }
            }
            printf("%d ",dp[i]);
        }
        printf(", %d\n\n",dp[N-1]);
        if(dp[N-1] > max){
            copy(dp, dp_best, N);
        }
    }
    // printf("%d",dp_best[N-1]);

    printf("\nLa sequenza massima ha durata %d:\n\n",b_sum);
    printf("Sequenza (len=%d):\n", b_len);
    for(int i = 0; i<b_len; i++){
        printf("%d - %d\n",b_seq[i].start_t,b_seq[i].end_t);
    }

    free(b_seq);
    free(seq);
}