#include <stdio.h>
#include <stdlib.h>

void MergeSort(int *v, int n);
void MergeSortR(int *v, int *b, int l, int r);
void Merge(int *v, int *b, int l, int q, int r);

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

    MergeSort(arr,n);

    printf("Vettore ordinato: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void MergeSort(int *v, int n){
    int *av = malloc(n*sizeof(int));
    if(!av){
        perror("malloc");
        return;
    }
    MergeSortR(v, av, 0, n-1);
}

void MergeSortR(int *v, int *b, int l, int r){
    int q;
    if(l >= r) return;
    q = (l+r)/2;
    MergeSortR(v, b, l, q); //Sinistra
    MergeSortR(v, b, q+1, r); //Destra
    Merge(v, b, l, q, r);
}

void Merge(int *v, int *b, int l, int q, int r){
    int i,j;
    i = l;
    j = q + 1;
    for(int k = l; k<=r; k++){
        if(i>q)
            b[k] = v[j++]; // se siamo oltre il limite sinistro q siamo a destra -> Incremento j
        else if (j>r)
            b[k] = v[i++];
        else if (v[i] <= v[j])
            b[k] = v[i++];
        else
            b[k] = v[j++];
    }
    for(int k = l; k<=r; k++)
        v[k] = b[k];
}