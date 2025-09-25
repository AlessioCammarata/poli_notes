/*
Si considerino i seguenti algoritmi di ordinamento per ordinare in maniera ascendente vettori di interi:
• Selection Sort
• Insertion Sort
• Shell Sort

Si scriva un programma in C che per ogni sequenza numerica acquisita da file (sort.txt) invochi
tutti gli algoritmi di ordinamento sopra indicati e stampi a video:
• il numero di scambi
• il numero di iterazioni del ciclo esterno
• per ogni passo del ciclo esterno il numero di iterazioni del ciclo interno
• il numero totale di iterazioni.

Il file sort.txt è caratterizzato dal seguente formato:
• sulla prima riga appare il numero S di sequenze numeriche
• seguono S righe nella forma <lunghezza><sequenza> dove <lunghezza> è un intero non
negativo (al massimo 100) a rappresentare la lunghezza della sequenza riportata su tale riga, e
<sequenza> sono <lunghezza> numeri separati da uno spazio.
*/
#include <stdio.h>
#include <string.h>

#define nfin "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione8/valuta_alg/sort1.txt"
// #define nfin "./sort1.txt"
#define L 100

void SelectionSort(int A[], int N, int *cnti, int *cntj, int *cntswap) {
    int i, j, l=0, r=N-1, min, J=0, swap = 0;
    int temp, temp_A[N];

    memcpy(temp_A, A, N * sizeof(int)); // Copio il vettore in uno temporaneo

    for (i = l; i < r; i++) {
        min = i;
        //Cerco il minimo nel sottovettore disordinato
        for (j = i+1; j <= r; j++){
            J++;
            if (temp_A[j] < temp_A[min])
                min = j;
        }
        //Se ho trovato il minimo ed è diverso da quello in cui sono ora (per forza perchè sto lavorando con gli indici) -> Scambia 
        if (min != i) {
            temp = temp_A[i];
            temp_A[i] = temp_A[min];
            temp_A[min] = temp; 
            swap++;
        } 
    }

    *cnti = i;
    *cntj = J;
    *cntswap = swap;
}

void InsertionSort(int A[], int N,int *cnti, int *cntj, int *cntswap) {
    int i, j, l=0, r=N-1, x, swap = 0;
    int temp_A[N];

    memcpy(temp_A, A, N * sizeof(int)); // Copio il vettore in uno temporaneo

    
    for (i = l+1; i <= r; i++) {
        x = temp_A[i];  // prendo il primo elemento del sottovettore non ordinato
        j = i - 1; // assegno j, con la posizione dell'ultimo elemento del sottovettore ordinato

        while (j >= l && x < temp_A[j]){ // Controllo che j sia piu grande di l che vale 0, e che x sia minore dell'ultimo elemento del sottovettore ordinato
            temp_A[j+1] = temp_A[j]; // scambio la posizione dei valori
            j--;
            swap++;
        }
        temp_A[j+1] = x; // scambio finale, con il valore che sto controllando, nell'indice identificato
    }

    *cnti = i;
    *cntj = swap;
    *cntswap = swap+i;
}

void ShellSort(int A[], int N, int *cnti, int *cntj, int *cntswap) {
    int i, j, z = 1, x, l=0, r=N-1, h=1, J, swap = 0;
    int temp_A[N];

    memcpy(temp_A, A, N * sizeof(int)); // Copio il vettore in uno temporaneo

    
    // Utilizzando la sequenza di shell: h = 2^(x-1) - inizializzando h a N/2 e dividendo per 2 ad ogni iterazione fino ad arrivare a 2
    for (h = N/2; h >= 1; h /= 2) {
        // 2) Insertion‐sort “saltando” di h posizioni
        for (i = h; i < N; i++) {
            x = temp_A[i];
            j = i;
            while (j >= h && temp_A[j-h] > x) {
                temp_A[j] = temp_A[j-h];
                j -= h;
                swap++;
            }
            temp_A[j] = x;
        }
        z++;
    }


    *cnti = z;
    *cntj = N + swap;
    *cntswap = swap+N;
}

int main(void){
    FILE *fin;
    int ns,n,vet[L],cnti = 0,cntj = 0,cntswap = 0;

    if((fin = fopen(nfin,"r")) == NULL){
        printf("ERRORE enll'apertura file\n");
        return 1;
    }

    fscanf(fin,"%d",&ns);

    for(int i = 0; i<ns; i++){
        printf("------------------------------------------------------\nSequenza N°%d\n\n",i+1);
        fscanf(fin,"%d",&n);
        for(int j = 0; j<n; j++) fscanf(fin,"%d",&vet[j]);

        SelectionSort(vet, n, &cnti, &cntj, &cntswap);
        printf("Numero scambi Selection-sort:\n Ciclo esterno %d \n Ciclo interno %d \n Scambi attuati %d\n Tot iterazioni %d\n\n",cnti,cntj,cntswap,cnti+cntj);

        InsertionSort(vet, n, &cnti, &cntj, &cntswap);
        printf("Numero scambi Insertion-sort:\n Ciclo esterno %d \n Ciclo interno %d \n Scambi attuati %d\n Tot iterazioni %d\n\n",cnti,cntj,cntswap,cnti+cntj);

        ShellSort(vet, n, &cnti, &cntj, &cntswap);
        printf("Numero scambi Shell-sort:\n Ciclo esterno %d \n Ciclo interno %d \n Scambi attuati %d\n Tot iterazioni %d\n\n",cnti,cntj,cntswap,cnti+cntj);

        // int h = n/2;
        // printf("%d",h*(n/h -1) + n%h);

        // for(int z = 0; z<n;z++) printf("%d ",vet[z]);
        // printf("\n");
    }

    fclose(fin);
    return 0;
}