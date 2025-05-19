#include <stdio.h>
#define n 10

void SelectionSort(int A[], int N) {
    int i, j, l=0, r=N-1, min;
    int temp;

    for (i = l; i < r; i++) {
        min = i;
        //Cerco il minimo nel sottovettore disordinato
        for (j = i+1; j <= r; j++)
            if (A[j] < A[min])
                min = j;

        //Se ho trovato il minimo ed è diverso da quello in cui sono ora (per forza perchè sto lavorando con gli indici) -> Scambia 
        if (min != i) {
            temp = A[i];
            A[i] = A[min];
            A[min] = temp; 
        } 
    }

    return; 
}

int main(void){
    int v[n] = {1,2,3,7,8,4,3,0,8,4};

    SelectionSort(v,n);

    for(int i = 0; i<n;i++) printf("%d",v[i]);

}