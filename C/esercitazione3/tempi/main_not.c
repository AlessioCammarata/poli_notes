#include <stdio.h>

// somma a T1 il tempo contenuto in T2 (il risultato va in T1)
void sommaTempi(int T1[3], int T2[3]);
// divide il tempo T per n
void dividiTempo(int T[3], int n);

int main(void){
    FILE *file;
    int n = 0, T[3] = {0}, T1[3]; 

    if ((file = fopen("C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione3/tempi/tempi.txt", "r")) == NULL){
        printf("Errore in apertura del file\n");
        return 1;
    }

    while(fscanf(file, "%d:%d:%d",&T1[0], &T1[1], &T1[2]) == 3){
        sommaTempi(T,T1);
        n++;
    }
    if (n>0) dividiTempo(T,n);
    else printf("NON PUOI DIVIDERE PER ZERO   \n");
    printf("Il tempo medio è di %d ore, %d minuti, %d secondi -- %d\n",T[0],T[1],T[2],n);

    fclose(file);
    return 0;

}

void sommaTempi(int T1[3], int T2[3]){
    T1[0] += T2[0];
    T1[1] += T2[1]%60;
    T1[2] += T2[2]%60;

    if(T1[2]/60 > 0) { 
        T1[1] += T1[2]/60;
        T1[2] = T1[2]%60;    
    }

    if(T1[1]/60 > 0) { 
        T1[0] += T1[1]/60;
        T1[1] = T1[1]%60;    
    }
}

void dividiTempo(int T[3], int n){
    T[2] = (T[2]+(T[1]+T[0]%n*60)%n*60)/n;
    T[1] = (T[1]+T[0]%n*60)/n;
    T[0] /= n;    
    
}