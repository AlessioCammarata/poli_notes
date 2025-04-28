/*
In un campionato n (max 20) squadre giocano per m (max 20) giornate. Sia data una matrice di n×m
numeri interi, ognuno dei quali può valere soltanto 0, 1 o 3. Ogni riga della matrice rappresenta i punti
acquisiti dalle n squadre nelle partite disputate nelle m giornate del campionato: 3 punti per le partite
vinte, 1 punto per quelle pareggiate e 0 punti per le sconfitte. I risultati della giornata k-esima sono
contenuti nelle righe della colonna di indice k. Si scriva un programma C che acquisisca i contenuti di
tale matrice da file e che, per ogni giornata del campionato, stampi l'indice (il numero di riga corrispondente) della squadra capolista. 
Si definisca un opportuno formato per il file (si fornisce un esempio di file, il cui formato tuttavia non è obbligatorio).
*/

#include <stdio.h>
#define TEAM 20
#define MATCH 20
#define nfin "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione6/campionato/mat.txt"
// #define nfin "./mat.txt"

int main(void) {
    int i = 0,j = 0, team, match, result;
    FILE *fin;

    if((fin = fopen(nfin,"r")) == NULL){
        printf("Errore nell'apertura del file");
        return 1;
    }

    fscanf(fin,"%d %d",&team, &match);
    // Supponendo che non siano 0 e che sia corretto il formato del file di input
    if(team > TEAM || match > MATCH){
        printf("Errore nell'inserimento dei dati nel file");
        return 1;
    }
    int M[team][match];

    while(fscanf(fin,"%d",&result) == 1){
        M[i][j] = result;
        j++;

        if(j == match){
            i++;
            j=0;
        }
        
    }

    // debug per vedere la matrice
    // for(i=0;i<team;i++){
    //     for(j=0;j<match;j++){
    //         printf("%d ",M[i][j]);
    //     }
    //     printf("\n");
    // }
            
    
    int val[team],max = 0,index;
    for(i=0;i<team;i++) val[i] = 0; // azzero tutti i punteggi

    for(j=0;j<match;j++){
        for(i=0;i<team;i++){
            val[i] += M[i][j];
            if(val[i] > max){ 
                max = val[i];
                index = i;
            }
            // printf("%d\t",M[i][j]);
            // printf("%d\n",val[i]);
        }
        printf("Giornata %d, la capolista è %d\n",j+1,index+1);
    }


    return 0;
}