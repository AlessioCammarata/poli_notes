#include <stdio.h>
#include <string.h>

#define MAXP 50
#define MAXC 30

typedef struct
{
    char nome[MAXC];
    int contatore;
} prestazione;

void leggiPrestazioni(char *filename, prestazione visite[], int n){
    int id;
    char nome[MAXC];
    FILE *fp = fopen(filename,"r");
    for(int i = 0; i<MAXP; i++) strcpy(visite[i].nome,"");
    while (fscanf(fp,"%s %d",nome, &id) == 2){
        strcpy(visite[id].nome,nome);
        visite[id].contatore = 0;
    }

    fclose(fp);
}

void leggiPazienti(char *filename, prestazione visite[], int n){
    int id;
    char str[MAXC];
    FILE *fp = fopen(filename,"r");

    while (fscanf(fp,"%s",str) == 1){
        while (fscanf(fp,"%d",&id) == 1){
            visite[id].contatore ++;
        }
    }

    fclose(fp);
}

void prestazionePiuRichiesta(prestazione visite[], int n){
    
    int max = 0, index = 0;

    for(int i = 0; i< n; i++){
        if (visite[i].nome[0] != '\0'){
            if(visite[i].contatore > max){ 
                max = visite[i].contatore;
                index = i;
            }else if (visite[i].contatore == max)
                max = strcmp(visite[i].nome,visite[index].nome) < 0 ? i : index;
        }
        
    }
    printf("Prestazione piu' richiesta e' la %d:\n %s\n\n",index,visite[index].nome);
}

void stampaStatistiche(prestazione visite[], int n){
    for(int i = 0; i<MAXC; i++){
        if (visite[i].nome[0] != '\0')
            printf("%s %d\n",visite[i].nome,visite[i].contatore);
    }
}

int main(int argc, char *argv[]){
    prestazione visite[MAXP];
    leggiPrestazioni(argv[1],visite, MAXP);
    leggiPazienti(argv[2], visite, MAXP);
    prestazionePiuRichiesta(visite, MAXP);
    stampaStatistiche(visite, MAXP);

    return 0;
}