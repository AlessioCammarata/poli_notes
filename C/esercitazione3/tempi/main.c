#include <stdio.h>

// somma a T1 il tempo contenuto in T2 (il risultato va in T1)
void sommaTempi(int T1[3], int T2[3]);
// divide il tempo T per n
void dividiTempo(int T[3], int n);

int main(void){
    FILE *file;
    int n = 0, T1[3], T[3] = {0};


    if((file = fopen("C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione3/tempi/tempi.txt", "r")) == NULL){
        printf("Error opening file\n");
        return 1;
    }

    while(fscanf(file, "%d:%d:%d",&T1[0], &T1[1], &T1[2]) == 3){
        sommaTempi(T,T1);
        n++;
    }
    if(n>0)
        dividiTempo(T, n);
    printf("Il tempo medio è di %d ore, %d minuti, %d secondi\n",T[0],T[1],T[2]);
    fclose(file);
}

void sommaTempi(int T1[3], int T2[3]){
    T1[0] += T2[0];
    T1[1] += T2[1];
    T1[2] += T2[2];
}


void dividiTempo(int T[3], int n){
    int s = (T[0]*3600 + T[1]*60 + T[2])/n;
    // printf("%d",s);
    T[0] = s/3600;
    // printf("%d",s%3600);
    T[1] = (s%3600)/60;
    T[2] = (s%3600)%60;
   
}