//Devo utilizzare le Disposizioni ripetute, in particolare 5 elevato al numero di amici
#include <stdio.h>
#include <stdlib.h>

// #define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L04/E02/brani.txt"
#define nfin "./brani.txt"
#define NMAX 5 //Numero di proposte massimo
#define TITLE_LEN 256

typedef struct{
    int n;
    char (*title)[TITLE_LEN];
} prop;

int leggiFile(FILE *fin, prop *vet, int n);

int main(void){
    FILE *fin;
    int *val, *sol,n;
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

    if(leggiFile(fin,playlists, n)){

        for(int i = 0; i<n; i++) free(playlists[i].title);
    }
    free(playlists);
    fclose(fin);

    // for(int i = 0; i<n; i++){
    //     for(int j = 0; j<playlists[i].n; j++){
    //         printf("%s\n",playlists[i].title[j]);
    //     }
    // }
    // val = malloc(n * sizeof(int));
    // sol = malloc(k * sizeof(int));

    return 0;
}

int leggiFile(FILE *fin, prop *vet, int n){
    int i,j;
    for(i = 0; i < n; i++){
        if (fscanf(fin, "%d", &vet[i].n) != 1 ) {
            vet[i].n = 0;
            vet[i].title = NULL;
            return 0; //Scarto questa opzione perche scritta male
        }

        if (vet[i].n <= 0) { // nessun titolo per questa playlist
            vet[i].title = NULL;
            continue;
        }

        vet[i].title = malloc(vet[i].n*TITLE_LEN*sizeof(char));
        if (vet[i].title == NULL) {
            perror("malloc");
            for(int k = 0; k<i; k++) { 
                free(vet[k].title); 
                vet[k].title = NULL; 
                vet[k].n = 0; 
            }
            return 0; //Fermo la lettura e do errore.
        }

        // leggeo i titoli
        for (j = 0; j < vet[i].n; j++) {
            if (fscanf(fin, "%255s", vet[i].title[j]) != 1) {
                fprintf(stderr, "Titolo mancante alla playlist %d voce %d\n", i, j);
                // cleanup completo (incl. corrente i)
                for (int k = 0; k <= i; k++) { 
                    free(vet[k].title); 
                    vet[k].title = NULL; 
                    vet[k].n = 0; 
                }
                return 0;
            }
        }
    }
    return 1;
}

int disp_rip(int pos,int *val,int *sol,int n,int k,int cnt){
	int i; 
	if (pos >= k) { //Condizione di terminazione
		for (i=0; i<k; i++) printf("%d ", sol[i]); 
		printf("\n"); 
		return cnt+1; 
	} 
	for (i = 0; i < n; i++) { //Iterazione sulle n scelte
		sol[pos] = val[i]; //scelta
		cnt = disp_rip(pos+1, val, sol, n, k, cnt); //Ricorsione
	} 
	return cnt; 
}