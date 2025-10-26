//Devo utilizzare le Disposizioni ripetute, in particolare 5 elevato al numero di amici
#include <stdio.h>
#include <stdlib.h>

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L04/E02/brani.txt"
// #define nfin "./brani.txt"
#define NMAX 5 //Numero di proposte massimo
#define TITLE_LEN 256

typedef struct{
    int n;
    char (*title)[TITLE_LEN];
} prop;

int leggiFile(FILE *fin, prop *vet, int n);
int disp_rip(int pos, int nfriend, prop *val, int *choice);
void free_vet(prop *vet, int n);

int main(void){
    FILE *fin;
    int *choice, n;
    prop *playlists;

    if ((fin = fopen(nfin,"r")) == NULL){
        printf("Errore in apertura del file\n");
        return 1;
    }
    
    if(fscanf(fin,"%d",&n) != 1){
        printf("Manca la n");
        fclose(fin);
        return 1;
    }

    playlists = malloc(n * sizeof(prop));
    if (playlists == NULL) {
        perror("malloc"); //Stampa -> malloc: "Cannot allocate memory"
        fclose(fin);
        return 1;
    }

    if (!leggiFile(fin, playlists, n)) { // Leggo i dati e li metto in playlist
        free(playlists);
        fclose(fin);
        return 1;
    }

    choice = malloc(n * sizeof(int)); // Vettore di interi, che serve a controllare le scelte
    if (choice == NULL) {
        perror("malloc");
        free_vet(playlists, n);
        free(playlists);
        fclose(fin);
        return 1;
    }

    int total = disp_rip(0, n, playlists, choice);
    printf(total != 0 ? "Totale combinazioni: %d\n" : "Nessuna playlist possibile (almeno un amico ha %d proposte)\n", total);
    
    free(choice);
    free_vet(playlists, n);
    free(playlists);
    fclose(fin);

    return 0;
}

int leggiFile(FILE *fin, prop *vet, int n){
    int i,j;
    for(i = 0; i < n; i++){
        if (fscanf(fin, "%d", &vet[i].n) != 1) {
            free_vet(vet, i);
            return 0; // formato sbagliato
        }

        //Si possono proporre da 0 a NMAX brani
        if (vet[i].n < 0 || vet[i].n > NMAX) {
            printf("Numero di brani non valido per playlist %d: %d\n", i, vet[i].n);
            free_vet(vet, i);
            return 0;
        }

        if (vet[i].n == 0) {
            vet[i].title = NULL; //No titoli
            continue;
        }

        vet[i].title = malloc(vet[i].n * sizeof *vet[i].title); /* vet[i].n righe da TITLE_LEN */
        if (vet[i].title == NULL) {
            perror("malloc");
            free_vet(vet, i);
            return 0; //Fermo la lettura e do errore.
        }

        // leggeo i titoli
        for (j = 0; j < vet[i].n; j++) {
            if (fscanf(fin, "%255s", vet[i].title[j]) != 1) {
                printf("Titolo mancante alla playlist %d voce %d\n", i, j);
                // cleanup completo (incl. corrente i)
                free_vet(vet, i + 1);
                return 0;
            }
        }
    }
    return 1;
}

int disp_rip(int pos, int nfriend, prop *val, int *choice){
    int i;
    if (pos >= nfriend) {
        //Stampo la soluzione
        for (i = 0; i < nfriend; i++) {
            if (val[i].title == NULL) {
                printf("(n/a)");
            } else {
                int idx = choice[i];
                if (idx < 0 || idx >= val[i].n) {
                    printf("(idx?)");
                } else {
                    printf("%s", val[i].title[idx]);
                }
            }
            if (i + 1 < nfriend) printf(" ");
        }
        printf("\n");
        return 1; //1 combinazione trovata
    }

    int count = 0;
    //Cerco tutte le possibili soluzioni per l'amico
    for (i = 0; i < val[pos].n; i++) {
        choice[pos] = i; // (0,0,0,0,0) - (1,0,0,0,0) - (2,0,0,0,0) - (3,0,0,0,0) - (4,0,0,0,0), x ogni di questa sviluppo
        count += disp_rip(pos + 1, nfriend, val, choice);
    }
    return count;
}

void free_vet(prop *vet, int n){
    for (int i = 0; i < n; i++) { 
        free(vet[i].title); 
    }
}