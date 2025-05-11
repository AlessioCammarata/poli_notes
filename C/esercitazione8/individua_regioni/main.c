/*
Un file di testo contiene una matrice di interi (0 o 1) con il seguente formato:
• la prima riga del file specifica le dimensioni reali della matrice (numero di righe nr e numero di
colonne nc). Si assuma che entrambi i valori siano al più pari a 50
• ciascuna delle nr righe successive contiene gli nc valori corrispondenti a una riga della
matrice, separati da uno o più spazi
• ogni cella può contenere solamente il valore 0 (associato al colore bianco) o il valore 1
(associato al colore nero)
• le celle nere sono organizzate in modo da formare regioni rettangolari (ogni regione nera è
circondata da una cornice di celle bianche, oppure da bordo/i della matrice). A tal fine, si
consideri che l'adiacenza delle celle è considerata solo lungo i quattro punti cardinali principali
(Nord, Sud, Ovest, Est), non in diagonale.
Si scriva un programma C che:
• legga la matrice dal file di ingresso (il file non contiene errori, quindi ci sono solo rettangoli
neri che rispettano i vincoli)
• individui le regioni nere più grandi per altezza, larghezza e area totale
• in caso di parità, si riporti una tra le regioni individuate che soddisfano un certo criterio
• per ognuna di tali regioni produca in output le coordinate dell’estremo superiore sinistro e le sue
caratteristiche (altezza, larghezza, area totale)
*/
#include <stdio.h>

#define nfin "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione8/individua_regioni/mappa.txt"
// #define nfin "./mappa.txt"
#define MAXdim 50

typedef struct {
    int base, area, altezza, estr_sx_x, estr_sx_y;
}rect;

typedef enum{
    white,black
} color;

void leggiFile(FILE *fin, int nc, int matrix[][nc]);
int trovaRegioni(int nr, int nc, int matrix[][nc], rect vet[nc*nr/2]);

int main(void){
    FILE *fin;
    int nr,nc,maxH = 0,maxA = 0,maxB = 0, indexH = 0,indexA = 0,indexB = 0;
    // rect vet[MAXdim]; // Ci sono al massimo 50 aree (sono di meno)
    // int matrix[MAXdim][MAXdim];

    if((fin = fopen(nfin,"r")) == NULL){
        printf("Errore nell'apertura del file\n");
        return 1;
    }

    fscanf(fin,"%d %d",&nr,&nc);
    int matrix[nr][nc];
    rect vet[nr*nc/2];
    leggiFile(fin,nc,matrix);
    // for(int i = 0; i<nr;i++){
    //     for(int j = 0; j<nc; j++){
    //         printf("%d ",matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    int nRect = trovaRegioni(nr, nc, matrix, vet);
    // for(int i = 0; i<nRect;i++) 
    //     printf("Area: %d - Base: %d - Altezza: %d estr_SX <%d,%d>\n",vet[i].area,vet[i].base,vet[i].altezza,vet[i].estr_sx_x,vet[i].estr_sx_y);
    for(int i = 0; i<nRect;i++){
        // printf("Area: %d - Base: %d - Altezza: %d estr_SX <%d,%d>\n",vet[i].area,vet[i].base,vet[i].altezza,vet[i].estr_sx_x,vet[i].estr_sx_y);

        if(vet[i].area > maxA){
            indexA = i;
            maxA = vet[i].area;
        }

        if(vet[i].altezza > maxH){
            indexH = i;
            maxH = vet[i].altezza;
        }
        
        if(vet[i].base > maxB){
            indexB = i;
            maxB = vet[i].base;
        }
    }
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",vet[indexB].estr_sx_x,vet[indexB].estr_sx_y,vet[indexB].base,vet[indexB].altezza,vet[indexB].area);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",vet[indexA].estr_sx_x,vet[indexA].estr_sx_y,vet[indexA].base,vet[indexA].altezza,vet[indexA].area);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",vet[indexH].estr_sx_x,vet[indexH].estr_sx_y,vet[indexH].base,vet[indexH].altezza,vet[indexH].area);

    fclose(fin);
    return 0;
}

void leggiFile(FILE *fin, int nc, int matrix[][nc]){
    int i = 0,j = 0;

    while(fscanf(fin,"%d ",&matrix[i][j++]) == 1){
        if(j == nc){
            i++;
            j=0;
        }
    }
}

int trovaRegioni(int nr, int nc, int matrix[][nc], rect vet[nc*nr/2]){
    int visited[nr][nc]; // Matrice per tracciare le celle visitate
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            visited[i][j] = 0;
        }
    }
    int n = 0; // Inizializza il contatore dei rettangoli trovati

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if (matrix[i][j] == black && !visited[i][j]) {
                // Nuova regione trovata
                int altezza = 0, larghezza = 0;

                // Calcola la larghezza
                while (j + larghezza < nc && matrix[i][j + larghezza] == black) {
                    larghezza++;
                }

                // Calcola l'altezza
                while (i + altezza < nr && matrix[i + altezza][j] == black) {
                    altezza++;
                }

                // Segna tutte le celle del rettangolo come visitate
                for (int x = i; x < i + altezza; x++) {
                    for (int y = j; y < j + larghezza; y++) {
                        visited[x][y] = 1;
                    }
                }

                // Salva le informazioni del rettangolo
                vet[n].base = larghezza;
                vet[n].altezza = altezza;
                vet[n].area = larghezza * altezza;
                vet[n].estr_sx_x = i;
                vet[n].estr_sx_y = j;
                n++;
            }
        }
    }

    return n;
}