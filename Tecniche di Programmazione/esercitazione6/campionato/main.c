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

void leggiFile(FILE *fin, int match, int Matrix[][match]);

int cercaMax(int match, int team, int Matrix[team][match], int punti[team], int giornata);

int main(void) {
    int team, match;
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
    leggiFile(fin,match,M);
    

    // debug per vedere la matrice
    // for(int i=0;i<team;i++){
    //     for(int j=0;j<match;j++){
    //         printf("%d ",M[i][j]);
    //     }
    //     printf("\n");
    // }
            
    
    int punti[team],capolista;
    for(int i=0;i<team;i++) punti[i] = 0; // azzero tutti i punteggi
    for(int j=0;j<match;j++){
        capolista = cercaMax(match, team, M, punti, j);
        printf("Giornata %d, la capolista è %d\n",j+1,capolista+1);
    }

    return 0;
}

void leggiFile(FILE *fin, int match , int Matrix[][match] ){
    int j = 0, i = 0, result;

    while(fscanf(fin,"%d",&result) == 1){
        Matrix[i][j] = result;
        j++;

        if(j == match){
            i++;
            j=0;
        }
        
    }
}

int cercaMax(int match, int team, int Matrix[team][match], int punti[team], int giornata){
    int i,index = 0,max = 0;

    
    for(i=0;i<team;i++){
        punti[i] += Matrix[i][giornata];
        if(punti[i] > max){ 
            max = punti[i];
            index = i;
        }
        // printf("%d\t",M[i][j]);
        // printf("%d\n",val[i]);
    }

    return index;
}