#include <stdio.h>
#define n 10

void InsertionSort(int A[], int N) {
    int i, j, l=0, r=N-1, x;
    
    for (i = l+1; i <= r; i++) {
        x = A[i];  // prendo il primo elemento del sottovettore non ordinato
        j = i - 1; // assegno j, con la posizione dell'ultimo elemento del sottovettore ordinato

        while (j >= l && x < A[j]){ // Controllo che j sia piu grande di l che vale 0, e che x sia minore dell'ultimo elemento del sottovettore ordinato
            A[j+1] = A[j]; // scambio la posizione dei valori
            j--;
        }
        A[j+1] = x; // scambio finale, con il valore che sto controllando, nell'indice identificato
    }
}

int main(void){
    int v[n] = {1,2,3,7,8,4,3,0,8,4};

    InsertionSort(v,n);

    for(int i = 0; i<n;i++) printf("%d",v[i]);

}