#include <stdio.h>
#include <stdlib.h>

#define nfin "C:/Users/aless/Desktop/Polito/poli_notes/Algoritmi/programmazione/scripts/L02/E02/mat.txt"
#define MAXR 10

int **malloc2dR(FILE *fin, int nr, int nc);
void separa(int **mat, int nr, int nc, int *vet_b, int *vet_n);

int main(){
    FILE *fin;
    int i, nc, nr, card, dim_b, dim_n, **mat, *vet_b, *vet_n;

    if((fin = fopen(nfin,"r")) == NULL){
        printf("Errore nell'apertura del file\n");
        return 1;
    }

    if (fscanf(fin, "%d %d", &nr, &nc) != 2) {
        printf("Errore, nella definizione delle dimensioni della matrice\n");
        fclose(fin);
        return 1;
    }

    if(mat = malloc2dR(fin, nr, nc)){
        //Calcolo dimensioni e allocazione
        card = nc*nr;
        dim_n = card/2;
        dim_b = dim_n + (card %2 == 0 ? 0 : 1);
        vet_b = malloc(dim_b*sizeof(int));
        vet_n = malloc(dim_n*sizeof(int));
        if(vet_b && vet_n){
            //Chiamata a separa
            separa(mat,nr,nc, vet_b, vet_n);
            
            //Stampa
            printf("Caselle bianche:\n");
            for(i = 0; i<dim_b; i++) printf("%d ",vet_b[i]);
            printf("\n");
            printf("Caselle nere:\n");
            for(i = 0; i<dim_n; i++) printf("%d ",vet_n[i]);

        }else printf("Errore: allocazione vettori fallita\n");

        //Deallocazione
        for(i = 0; i<nr; i++) free(mat[i]);
        free(mat);
        free(vet_b);
        free(vet_n);
    }else printf("Errore: allocazione matrice fallita\n");

    fclose(fin);
    return 0;
}

int **malloc2dR(FILE *fin, int nr, int nc){
    int i,j, **mat = malloc(nr*sizeof(int *));
    if(!mat) return NULL;

    for(i = 0; i<nr;i++){
        mat[i] = malloc(nc*sizeof(int));
        if(!mat[i]){
            for(j = 0; j < i; j++) free(mat[j]);
            free(mat);
            return NULL;
        }
        for(j = 0; j<nc; j++){
            if (fscanf(fin,"%d",&mat[i][j]) != 1){
                for(j = 0; j <= i; j++) free(mat[j]);
                free(mat);
                return NULL;
            }
        }
    }
    
    return mat;
}

void separa(int **mat, int nr, int nc, int *vet_b, int *vet_n){
    int i,j, n1 = 0, n2 = 0;

    for(i = 0; i<nr; i++){
        for(j = 0; j<nc; j++){
            if(n1>=n2)
                vet_b[n2++] = mat[i][j];
            else
                vet_n[n1++] = mat[i][j];
        }
    }
}