#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM 20

typedef struct {
    
    char nome[30];
    char lingua[20];
    float tariffa;
    int giorni;

} interprete;

int leggiDati(interprete personale[NUM], int n, char *file_name);
interprete *massimoGiorno(interprete personale[NUM], int n);
void stampaSelezionati(interprete *val[], int n);
int selezionaLingua(interprete personale[NUM], int n, interprete *filt[NUM], char *value);

int main(){

    interprete personale[NUM];
    interprete *max;
    interprete *filtrati[NUM];

    int n = leggiDati(personale, NUM, "interpreti.txt");
    max = massimoGiorno(personale, n);
    stampaSelezionati(&max , 1);
    int count = selezionaLingua(personale, n, filtrati, "Inglese");
    stampaSelezionati(filtrati, count);

    return 0;
}

int leggiDati(interprete personale[NUM], int n, char *file_name){
    FILE *fin;
    int i;

    if ( (fin = fopen(file_name,"r")) == NULL){
        printf("Errore nel'apertura del file\n");
        exit(-1);
    }

    for(i = 0; fscanf(fin,"%s %s %f %d",personale[i].nome,personale[i].lingua,&personale[i].tariffa,&personale[i].giorni) == 4;i++);

    fclose(fin);
    return i;
}

interprete *massimoGiorno(interprete personale[NUM], int n){
    interprete *max = &personale[0];

    for(int i = 0; i<n; i++){
        if(personale[i].giorni > max->giorni){
            max = &personale[i];
        }
    }
    return max;
}

void stampaSelezionati(interprete *val[], int n){
    for(int i = 0; i<n; i++) 
        printf("%s: %s, %.2f/ora, %d giorni\n",val[i]->nome,val[i]->lingua,val[i]->tariffa,val[i]->giorni);
    printf("\n");
}

int selezionaLingua(interprete personale[NUM], int n, interprete *filt[NUM], char *value){
    int c = 0;

    for(int i = 0; i< n; i++){
        if (strcmp(personale[i].lingua,value) == 0)
            filt[c++] = &personale[i];
    }

    return c;
}