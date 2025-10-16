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

    printf("Inserisci gli elementi dell'array (Naturali, >=0):\n");
    for(i=0; i<N; i++){
        printf("%d° valore da inserire: ",i+1);
        scanf("%d", &a[i]);
        while(a[i] < 0){
            printf("Reinserire il valore (Naturali, >=0): ");
            scanf("%d", &a[i]);
        }
    }
    
    printf("\nVettore: [");
    for(int i = 0; i<N-1; i++) printf("%d, ",a[i]);
    printf("%d].\n",a[N-1]);

    int result = majority(a, N);
    if(result != -1)
        printf("Il numero maggioritario è: %d\n", result);
    else 
        printf("Numero maggioritario inesistente\n");

    free(a);
    return 0;
}

/*
    Cerca candidati tra coppie adiacenti (a[i]==a[i+1]).
    Per ogni candidato conta le occorrenze nell'intero array e ritorna il valore se occ > N/2. 
    Se non ci sono coppie ed N è dispari, il codice controlla gli indici pari come caso speciale. 
    Ritorna -1 se non esiste maggioritario.
    Pero è iterativa non recursive.
*/
// int majority(int *a, int N){
//     int even = (N%2 != 0) ? 0 : 1;
//     int found = 0, i = 0, occ;

//     for(int j = 0; j < N -1; j++)
//         // Cerco una coppia, avevo pensato ad una funzione not_in ma non migliora le prestazioni in caso peggiore
//         if(a[j] == a[j+1]){ 
//             occ = 0;
//             for(int k = 0; k<N; k++) 
//                 if(a[k] == a[j]) occ++;
//             if (occ>N/2) return a[j]; // Se le occorrenze sono legittime torno il valore
//             else if (!even){ 
//                 for(int k = 0, occ = 0; k<N; k+=2) // Conto il caso speciale Es. 1 2 1 2 1
//                     if(a[k] == a[j]) occ++;
//                 if (occ>N/2) return a[j];
//             }
//         }

//     return -1;
// }

/*
    Divide and conquer, complessità O(NlogN).
    Mi riduco a singole coppie l ed r partendo da sinistra, dopcodiché prendo i valori e li confronto con 
    gli altri presenti nel vettore per contare quante occorrenze ci sono, e prendo come candidato quello >.
    Infine controllo se le occ che ho ottenuto siano maggiori di N/2 torno il valore relativo se si senno -1.
*/
int majority(int *a, int N){
    if (N <= 0) return -1;
    //Condizione di terminazione
    if (N == 1) return a[0];

    int leftN = N / 2;
    int rightN = N - leftN;

    int left = majority(a, leftN);
    int right = majority(a + leftN, rightN);

    if (left == right) return left; // Se i valori sono uguali

    int cL = 0, cR = 0;
    for(int i = 0; i<N; i++){
        if(a[i] == left) cL++;
        if(a[i] == right) cR++;
    }

    // Eseguo il controllo sulle occorrenze che ho contato prima
    if(cL>cR){ 
        return cL>N/2 ? left : -1;
    }else{
        return cR>N/2 ? right : -1;
    }

    
}