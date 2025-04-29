/*
Si scriva un programma C che permetta all’utente di eseguire in sequenza operazioni di rotazione di P
posizioni su righe e/o colonne specificate di una matrice di interi. Le rotazioni sono da intendersi come
circolari sia sulle righe, sia sulle colonne (cfr. definizione data in Lab. 0 es. 3). Le righe e le colonne
sono numerate a partire da 1 (attenzione: il C numera a partire da 0).

Il programma:
• legge da file, il cui nome di al massimo 20 caratteri è acquisito da tastiera, la matrice (max 30 x 30).
Il formato del file prevede sulla prima riga 2 interi che indicano il numero di righe nr e di colonne
nc, seguita da nr righe contenenti ciascuna nc interi
• acquisisce ripetutamente da tastiera una stringa (al massimo di 100 caratteri, contenente eventuali
spazi), nella forma
<selettore> <indice> <direzione> <posizioni>
Il selettore indica se si vuole operare su una riga (“riga”), su una colonna (“colonna”), o
terminare (“fine”). Seguono l’indice della riga (colonna) selezionata, la direzione (“destra”
o “sinistra”, oppure “su” o “giu”) e il numero di posizioni. Dopo ogni comando la patrice
va visualizzata.
Le rotazioni siano eseguite da una funzione che generalizza quanto sviluppato per l’esercizio 2 del laboratorio 5. 
*/


#include <stdio.h>
#include <string.h>
#define dir "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione6/matrix_rotation/"
// #define nfin "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione6/matrix_rotation/mat.txt"
// #define nfin "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione6/matrix_rotation/mat1.txt"
#define MaxChar 20
#define MaxInput 100
#define N 30
#define MAX_RIGA 10

// Definisco gli enum per i selettori e le direzioni
typedef enum {
    RIGA,
    COLONNA,
    FINE
} Selettore;

typedef enum {
    DESTRA,
    SINISTRA,
    GIU,
    SU
} Direzione;

void leggiFile(FILE *fin, int row, int column, int Matrix[][column]);
void stampa_matrice(int row,int column, int Matrix[][column]);
void ruotaMatrice(int row,int column, int Matrix[][column],int selettore,int indice,int direzione,int P);

int main(void){
    FILE *fin;
    char nfin[MaxChar+1],riga[MaxInput];
    int n,m;
    
    do{
        printf("Inserire il nome del file (max 20 caratteri):\n");
        scanf("%s",nfin);
    }while(strlen(nfin)>20);
    
    // Concatenazione del percorso 'dir' con il nome del file || ho bisogno di tutto ciò
    char fullPath[strlen(dir) + strlen(nfin) + 1]; // Spazio per dir + nome del file + terminatore '\0'
    strcpy(fullPath, dir);    // Copia il percorso 'dir' nella stringa 'fullPath'
    strcat(fullPath, nfin);   // Concatenazione del nome del file al percorso
    strcat(fullPath,".txt");

    if ((fin = fopen(fullPath, "r")) == NULL){
        printf("Errore nell'apertura di uno dei file\n");
        return 1;
    }

    fscanf(fin,"%d %d",&n,&m);
    int Matrix[n][m];
    leggiFile(fin,n,m,Matrix);
    stampa_matrice(n,m,Matrix);

    char selettoreInput[MAX_RIGA], direzioneInput[MAX_RIGA];
    Selettore selettore;
    Direzione direzione;
    int indice, posizioni;

    printf("Inserire il comando (<selettore> <indice> <direzione> <posizioni>):\n");
    printf("Selettori possibili: riga, colonna, fine\n");
    printf("Direzioni possibili: destra, sinistra, su, giu\n");
    while(scanf("%s %d %s %d",selettoreInput,&indice,direzioneInput,&posizioni) == 4 && strcmp(selettoreInput, "fine") != 0){
       
        indice--;  
        // Determina il tipo di selettore
        if (strcmp(selettoreInput, "riga") == 0) {
            selettore = RIGA;
        } else if (strcmp(selettoreInput, "colonna") == 0) {
            selettore = COLONNA;
        } else {
            printf("Selettore non valido!\n");
            continue;
        }

        // Verifica la direzione in base al selettore
        if (selettore == RIGA) {
            // Se selezione è "riga", le direzioni valide sono "destra" e "sinistra"
            if (strcmp(direzioneInput, "destra") == 0) {
                direzione = DESTRA;
            } else if (strcmp(direzioneInput, "sinistra") == 0) {
                direzione = SINISTRA;
            } else {
                printf("Direzione non valida per la riga! Solo 'destra' o 'sinistra' sono validi.\n");
                continue;
            }

            if(indice >= n || indice < 0){
                printf("Indice non valido per le righe\n");
                continue;
            }
        } else if (selettore == COLONNA) {
            // Se selezione è "colonna", le direzioni valide sono "su" e "giu"
            if (strcmp(direzioneInput, "su") == 0) {
                direzione = SU;
            } else if (strcmp(direzioneInput, "giu") == 0) {
                direzione = GIU;
            } else {
                printf("Direzione non valida per la colonna! Solo 'su' o 'giu' sono validi.\n");
                continue;
            }

            if(indice >= m || indice < 0){
                printf("Indice non valido per le colonne\n");
                continue;
            }
        }
        
        if(posizioni < 0){
            printf("L'indice deve essere positivo!!\n");   
            continue;
        }
        
        ruotaMatrice(n,m,Matrix,selettore,indice,direzione,posizioni);

        stampa_matrice(n,m,Matrix);
        printf("\n");
    }


    fclose(fin);
    return 0;
}

void leggiFile(FILE *fin, int row, int column, int Matrix[][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            fscanf(fin, "%d", &Matrix[i][j]);
        }
    }
}

void stampa_matrice(int row,int column, int Matrix[][column]){
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            printf("%d ",Matrix[i][j]);
        }
        printf("\n");
    }
}

void ruotaMatrice(int row, int column, int Matrix[][column],int selettore,int indice,int direzione,int P){

    int i,j,last;

    if(selettore == 0){
        if(direzione == 0){
            for(i=0;i<P;i++){
                last = Matrix[indice][column-1];
                for(int j = 1;j<column;j++){
                    Matrix[indice][column-j] = Matrix[indice][column-(j+1)];
                }
                Matrix[indice][0] = last;
            }
            
        }else{
            for(i=0;i<P;i++){
                last = Matrix[indice][0];
                for(int j = 0;j<column-1;j++){
                    Matrix[indice][j] = Matrix[indice][j+1];
                }
                Matrix[indice][column-1] = last;
            }
        }
    }else{
        if(direzione == 2){
            for(i=0;i<P;i++){
                last = Matrix[row-1][indice];
                for(int j = 1;j<row;j++){
                    Matrix[row-j][indice] = Matrix[row-(j+1)][indice];
                }
                Matrix[0][indice] = last;
            }
            
        }else{
            for(i=0;i<P;i++){
                last = Matrix[indice][0];
                for(int j = 0;j<row-1;j++){
                    Matrix[j][indice] = Matrix[j+1][indice];
                }
                Matrix[row-1][indice] = last;
            }
        }
    }
}