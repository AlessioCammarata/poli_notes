#include <stdio.h>
#include <string.h>

#define MAXP 200 //massimo di 200 prodotti diversi

typedef struct {
    char serialID[13]; //stringa alfanumerica di 12 caratteri senza spazi 
    int n_items;       //numero di articoli disponibili per lo stesso prodotto
} product;

int readProducts(product listp[], int np, char *file_name);
void sortProducts(product *refp[], int np);

int main (int argc, char *argv[]) {
    product listProducts[200], *refProducts[200];
    int i, nprod = readProducts(listProducts, 200, argv[1]);
    printf("%d\n",nprod);
    for (i=0;i<nprod;i++)
        refProducts[i]=&listProducts[i];

    sortProducts(refProducts,nprod);
    
    for(int i = 0; i < nprod; i++) printf("%s %d\n",refProducts[i]->serialID, refProducts[i]->n_items);


    return 0;
}

int readProducts(product listp[], int np, char *file_name){
    FILE *fin;
    int i;

    if((fin = fopen(file_name,"r")) == NULL){
        printf("Errore nell'apertura del file\n");
        return -1;
    }

    for(i = 0; fscanf(fin,"%s %d",listp[i].serialID,&listp[i].n_items) == 2; i++);
    
    fclose(fin);
    return i;
}

void sortProducts(product *refp[], int np){
    product *temp = 0;

    for(int i = 0; i < np-1; i++){
        int min_index = i;

        for(int j = i+1;  j < np; j++){
            if(strcmp(refp[j]->serialID,refp[min_index]->serialID) < 0) min_index = j;
        }
        
        if(min_index != i){
            temp = refp[i];
            refp[i] = refp[min_index];
            refp[min_index] = temp;
        }
    }

}