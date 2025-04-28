/*
Sequenze numeriche in vettore
Sia V un vettore di N interi (con N30). Si scriva un programma in C che, una volta acquisito da tastiera (o da file, la scelta è libera) il contenuto del vettore, chiami una funzione avente prototipo
sottoSequenze(int V[], int N);
La funzione visualizzi tutti i sottovettori di dimensione massima formati da celle contigue, contenenti
dati non nulli.
Esempio:
dato il vettore [1 3 4 0 1 0 9 4 2 0], i due sottovettori di dimensione massima (3) contenenti
dati non nulli sono [1 3 4] e [9 4 2].
*/
#include <stdio.h>

void sottoSequenze(int V[], int N);

int main(void){
    int N =30,i=0;
    int V[N];

    printf("Inserire la sequenza di numeri, e la quantità di numeri inseriti (123456).\nScrivere una carattere per confermare\n");
    // Usa scanf per leggere i numeri uno per uno
    while (scanf("%d", &V[i]) == 1 && i<N) {  // Continua fino a quando non ci sono più numeri
        // printf("Numero estratto: %d\n", V[i]);
        i++;
    }

    // Aggiungi un printf di debug per vedere il valore di i
    printf("Numero di valori letti: %d\n", i);

    // Verifica che i numeri siano stati letti correttamente
    if (i > 0) {
        sottoSequenze(V, i);
    } else {
        printf("Nessun numero inserito.\n");
    }


    return 0;
}

void sottoSequenze(int V[], int N){
    int c=0,incr = 0;
    int result[N],temp[N];

    for(int i=0;i<N;i++){
        // printf("%d",V[i]);
        temp[i] = 1;
        if(V[i] != 0) c++;
        else{
            incr = incr>c ? incr : c; // se è minore di c inserisci c
            c = 0;
        }
    }
    incr = incr > c ? incr : c;
    printf("La lunghezza della sequenza più lunga di numeri non zero è: %d\n", incr);
    c = 0;
    for (int i = 0; i < N; i++) {
        if (V[i] != 0) {
            temp[c++] = V[i];  // Aggiungi il numero alla sottosequenza corrente

        } else {
            c = 0;  // Reset della sequenza corrente
        }

        if (c == incr) {  // Se la sequenza corrente ha la lunghezza massima
            // Stampa la sottosequenza
            printf("[%d",temp[0]);
            for (int j = 1; j < c; j++) {
                printf(", %d", temp[j]);
            }
            printf("]\n");
        }
    }
    
}