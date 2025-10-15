#include <stdio.h>
#include <stdlib.h>

int majority( int *a, int N); 

int main(void){
    int N, *a, i;
    printf("Inserisci il numero di elementi dell'array: ");
    scanf("%d", &N);
    a = (int *) malloc(N * sizeof(int));
    if(a == NULL){
        printf("Errore di allocazione della memoria\n");
        return 1;
    }

    printf("Inserisci gli elementi dell'array: ");
    for(i=0; i<N; i++){
        scanf("%d", &a[i]);
    }
    
    int result = majority(a, N);
    if(result != -1)
        printf("Il numero maggioritario è: %d\n", result);
    else 
        printf("Numero maggioritario inesistente\n");

    free(a);
    return 0;
}

int majority(int *a, int N){

    if (N <= 0) return -1;

    /* base case */
    if (N == 1) return a[0];

    int leftN = N / 2;
    int rightN = N - leftN;

    /* recursive calls on subarrays using same function signature */
    int left = majority(a, leftN);
    int right = majority(a + leftN, rightN);

    if (left == right) return left;

    /* count occurrences of left and right in the whole segment */
    int countL = 0, countR = 0;
    for (int i = 0; i < N; ++i) {
        if (a[i] == left) ++countL;
        if (a[i] == right) ++countR;
    }

    int cand = (countL > countR) ? left : right;

    /* final verification: candidate must appear > N/2 times */
    int occ = 0;
    for (int i = 0; i < N; ++i) if (a[i] == cand) ++occ;

    return (occ > N / 2) ? cand : -1;
}
