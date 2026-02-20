#include <stdio.h>
#include <stdlib.h>

void QuickSort(int *v, int n);
void QuickSortR(int *v, int l, int r);
int partition(int *v, int l, int r);
void Swap(int *v, int n1, int n2);

int main(){
    // Vettore disordinato di 7 elementi
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    
    // Calcolo della dimensione n
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Vettore disordinato: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    QuickSort(arr,n);

    printf("Vettore ordinato: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void QuickSort(int *v, int n){
    QuickSortR(v, 0, n-1);
}

void QuickSortR(int *v, int l, int r){
    int q;
    if(l >= r) return;
    q = partition(v, l , r);
    QuickSortR(v, l, q-1);
    QuickSortR(v, q+1, r);
}

int partition(int *v, int l, int r){
    int i = l-1, j = r;
    int x = v[r]; //pivot definito
    for(; ; ){
        while(v[++i] < x); //Scorro gli elementi di v con indice i finche non ne trovo uno maggiore del pivot -> avrà indice i
        while(v[--j] > x); //Scorro gli elementi di v al contrario con indice j finche non ne trovo uno minore del pivot -> avrà indice j
        if(i>=j) break; //Se c'è overlap fermo tutto
        Swap(v, i, j);
    }
    Swap(v, i, r);
    return i;
}

void Swap(int *v, int n1, int n2){
    int temp;
    temp = v[n1];
    v[n1] = v[n2];
    v[n2] = temp;
}