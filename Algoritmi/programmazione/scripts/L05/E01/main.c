#include <stdio.h>
#include <stdlib.h>

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L05/E01/att1.txt"

typedef struct {
    int start_t, end_t;
} att;

int leggiFile(FILE *fin, att *activities, int n);
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

    // for(int i = 0; i<n; i++) printf("%d - %d\n",activities[i].end_t,activities[i].start_t);
    attSel(n, activities);

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

//Controllo l'intersezione
int intercept(att act1, att act2){
    return act1.start_t < act2.end_t && act2.start_t < act1.end_t;
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
void comp_seq(int pos, int sum, int len, int last_idx, att *V, att *seq, int n, int *b_len, att *b_seq, int *b_sum){
    if(pos==n){
        //Trovato un nuovo max
        if(sum > *b_sum){
            *b_sum = sum;
            *b_len = len;
            for(int i = 0; i<len; i++){
                b_seq[i] = seq[i]; //Copio la sequenza
                printf("%d - %d\n",b_seq[i].start_t,b_seq[i].end_t);
            }
            printf("\n\n");
        }
        return;
    }

    comp_seq(pos+1, sum, len, last_idx, V, seq, n, b_len, b_seq, b_sum);
    
    if(last_idx == -1 || !intercept(V[last_idx],V[pos])){
        seq[len] = V[pos]; // Inserisco in ordine nella seq che sto analizzando

        sum += (V[pos].end_t-V[pos].start_t);
        comp_seq(pos+1, sum, len + 1, pos, V, seq, n, b_len, b_seq, b_sum);
    }
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
    comp_seq(0, 0, 0, -1, V, seq, N, &b_len, b_seq, &b_sum);

    printf("La sequenza massima ha durata %d:\n\n",b_sum);
    printf("Sequenza (len=%d):\n", b_len);
    for(int i = 0; i<b_len; i++){
        printf("%d - %d\n",b_seq[i].start_t,b_seq[i].end_t);
    }

    free(b_seq);
    free(seq);
}