/*
Si riveda l’esercizio 1 del Lab08 apportandovi le seguenti modifiche:
• supponendo di avere dichiarato una matrice di interi M e di aver definito MAXR come 50, si acquisisca la matrice mediante una funzione (leggiMatrice) che ne ritorna il numero di righe e di
colonne effettivamente usati, come parametri “by reference” (o meglio, “by pointer”, cioè con puntatori by value). La funzione deve poter essere chiamata con un’istruzione del tipo:
leggiMatrice(M,MAXR,&nr,&nc);
• per effettuare il riconoscimento delle regioni si utilizzi una funzione riconosciRegione che,
data una casella della matrice, determini se si tratti o meno di estremo superiore sinistro di una regione, ritornandone “by reference” (come per la precedente) le dimensioni del rettangolo, e avente
come valore di ritorno un intero booleano (vero: rettangolo trovato, falso: rettangolo non trovato).
La funzione deve poter essere chiamata come segue:
if (riconosciRegione(M,nr,nc,r,c,&b,&h)) {
 // stampa messaggio per rettangolo con
 // estremo in (r,c), base b e altezza h
 .
*/

#include <stdio.h>

#define MAXR 50
#define MAXdim 50

typedef enum{
    white,black
} color;

void leggiMatrice(int M[][MAXdim], int n, int *nr, int *nc);
int riconosciRegione(int M[][MAXdim], int nr, int nc, int r, int c, int *b, int *h);

int main(void){
    int nr, nc, r, c, b, h;
    int M[MAXR][MAXdim];

    leggiMatrice(M,MAXR,&nr,&nc);
    do{
    printf("Inserisci una casella in coordinate (righe:colonne). Per finire metti (-1:-1)\n");
    scanf("%d:%d",&r,&c);

    if (riconosciRegione(M,nr,nc,r,c,&b,&h)) {
        printf("Trovato rettangolo con vertice sinistro in (%d:%d): \nBase %d, Altezza %d\n",r,c,b,h);
    }else{
        printf("Non ho trovato niente in (%d:%d) %d\n",r,c,black);
    }

    printf("\n");
    }while(r != -1 && c != -1);
    
    return 0;
}

// Funzione che legge la matrice e restituisce righe e colonne effettive via puntatori
void leggiMatrice(int M[][MAXdim], int maxr, int *nr, int *nc) {
    printf("Quante righe (max %d)? ", maxr);
    scanf("%d", nr);

    printf("Quante colonne (max %d)? ", MAXdim);
    scanf("%d", nc);

    for (int i = 0; i < *nr; i++) {
        for (int j = 0; j < *nc; j++) {
            printf("M[%d][%d] = ", i, j);
            scanf("%d", &M[i][j]);
            while(M[i][j] != 0 && M[i][j] != 1){
                printf("Il valore può essere solo 0 o 1.\nM[%d][%d] = ", i, j);
                scanf("%d", &M[i][j]);
            }
        }
    }

}

int riconosciRegione(int M[][MAXdim], int nr, int nc, int r, int c, int *b, int *h){

    int found = 0; // Inizializza il flag
    int okr,okc;

    if (r >= nr || c >= nc || M[r][c] != black)
        return 0;

    // Verifica che sia l'estremo superiore sinistro
    okr = (r == 0 || M[r - 1][c] != black);
    okc = (c == 0 || M[r][c - 1] != black);

    if (okc && okr) {
        // Nuova regione trovata
        int altezza = 0, larghezza = 0;

        // Calcola la larghezza
        while (c + larghezza < nc && M[r][c + larghezza] == black) {
            larghezza++;
        }

        // Calcola l'altezza
        while (r + altezza < nr && M[r + altezza][c] == black) {
            altezza++;
        }
        
        *b = larghezza;
        *h = altezza;
        found = 1;
    }

    return found;
}