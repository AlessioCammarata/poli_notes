#include <stdio.h>
#include <stdlib.h>

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L04/E03/easy_test_set.txt"
#define Nstones 4

void free_vet(int **vet, int n);
int leggiFile(FILE *fin, int **all_stones, int n);
int necklace_maker(int *stones, int pos);

int main(void){
    FILE *fin;
    int len = 0, n, **all_stones;

    if((fin = fopen(nfin,"r")) == NULL){
        printf("Errore in apertura del file\n");
        return 1;
    }

    if(fscanf(fin,"%d",&n) != 1){
        printf("Manca il numero di collane");
        fclose(fin);
        return 1;
    }

    all_stones = malloc(n*sizeof(int *));
    if (all_stones == NULL) {
        perror("malloc");
        fclose(fin);
        return 1; //Fermo la lettura e do errore.
    }

    if (!leggiFile(fin, all_stones, n)) { // Leggo i dati e li metto in playlist
        free(all_stones);
        fclose(fin);
        return 1;
    }
    fclose(fin);

    len = necklace_maker(all_stones[0], 0);
    printf("%d\n",len);
    
    // for(int i = 0, j; i<n; i++){
    //     for(j = 0; j<Nstones;j++) printf("%d ",stones[i][j]);
    //     printf(" -> %d pietre",stones[i][j]);
    //     printf("\n");
    // }

    free_vet(all_stones, n);
    free(all_stones);
    return 0;
}

void free_vet(int **vet, int n){
    for (int i = 0; i < n; i++) { 
        free(vet[i]); 
    }
}

int leggiFile(FILE *fin, int **all_stones, int n){
    int i, j, sum;
    for(i = 0; i < n; i++){

        all_stones[i] = malloc((Nstones+1)*sizeof(int));
        if (all_stones[i] == NULL) {
            perror("malloc");
            free_vet(all_stones, i);
            return 0; //Fermo la lettura e do errore.
        }

        // leggo le pietre
        sum = 0;
        for (j = 0; j < Nstones; j++) {
            if (fscanf(fin,"%d",&all_stones[i][j]) != 1) {
                printf("Errore in lettura delle pietre alla voce %d\n",i);
                // cleanup completo (incl. corrente i)
                free_vet(all_stones, i + 1);
                return 0;
            }
            sum += all_stones[i][j];
        }
        all_stones[i][j] = sum; // Metto la somma alla fine dei valori
        
    }

    return 1;
}

// Ordine: z, r, t, s
// Disposizioni ripetute con criterio
int necklace_maker(int *stones, int pos){
    int len = 0, next;
    if(pos == -1){
        stones[pos]--;
        for(int j = 0; j<Nstones;j++) printf("%d ",stones[j]);
        return 1;
    }

    if(pos == 0) next = stones[pos] == 0 ? 1 : 0; //Finisco gli zaffiri e passo ai rubini
    else if(pos == 1) next = stones[3] == 0 ? 2 : 3; // Finisco gli smeraldi poi passo ai topzai
    else if(pos == 2) next = stones[0] == 0 ? 1 : 0;
    else if(pos == 3) next = stones[pos] == 0 ? 2 : 3; //Finisco gli smeraldi e passo a topazi

    len += necklace_maker(stones, next);

    return len;

}