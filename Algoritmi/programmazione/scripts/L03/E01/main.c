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
    a[i] = -1; //Condizione di terminazione
    
    int result = majority(a, N);
    if(result != -1)
        printf("Il numero maggioritario è: %d\n", result);
    else 
        printf("Numero maggioritario inesistente\n");

    free(a);
    return 0;
}

// int majority(int *a, int N){
//     if (N <= 0) return -1;
//     if (majority(a+1,N) == -1) return *(a-1);

//     return *a;
// }

int majority(int *a, int N){
    for(int i = 0; i<N; i++){
        
    }
}