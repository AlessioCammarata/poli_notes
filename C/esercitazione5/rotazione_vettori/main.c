// Il main:
// 1. acquisisca da tastiera N (N  maxN con maxN pari a 30)
// 2. acquisisca da tastiera il vettore V
// 3. effettui ripetutamente delle rotazioni, acquisendo ciascuna volta P (P < N, P=0 per terminare) e la
// direzione (dir =-1 per rotazione a destra, dir = 1 per rotazione a sinistra) e stampi il vettore risultante.

#include <stdio.h>
#define maxN 30

void ruota(int v[maxN], int N, int P, int dir);

// pulisci il buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int abs(int val){
    if (val<0) val * -1;
    return val;
}

int main(void){
    int i=0,n,P;

    printf("Inserire la dimensione del vettore:\n");
    while(scanf("%d",&n) != 1 || n>maxN || n<=0){
        
        printf("ERRORE, reinserire la dimensione del vettore:\n");
        clear_input_buffer();
    }

    int v[n];
    printf("Inserire la sequenza di numeri, e la quantità di numeri inseriti (1 2 3 4 5 6).\nScrivere un carattere per confermare\n");
    while(scanf("%d",&v[i]) == 1 && i<n){
        printf("%d",v[i]);
        i++;
    }
    clear_input_buffer();

    printf("Inserire il numero di scambi indicando col segno - per andare a sinistra, + se si vuole andare a destra.\nScrivere un carattere per confermare\n");
    while(scanf("%d",&P) == 1 && P != 0){
        if(abs(P) <= n){
            //dir equivale al segno del valore che inserisco
            ruota(v,n,abs(P),P/abs(P));
        }else{
            printf("Numero troppo grande\n");
        }

        for(i = 0;i<n;i++){
            printf("%d",v[i]);
        }
        printf("\n");
    }

    return 0;
}

void ruota(int v[maxN], int N, int P, int dir){
    int i,j,last;

    if(dir > 0){
        for(i=0;i<P;i++){
            last =v[N-1];
            for(int j = 1;j<N;j++){
                v[N-j] = v[N-(j+1)];
            }
            v[0] = last;
        }
        
    }else{
        for(i=0;i<P;i++){
            last =v[0];
            for(int j = 0;j<N-1;j++){
                v[j] = v[j+1];
            }
            v[N-1] = last;
        }
    }
}