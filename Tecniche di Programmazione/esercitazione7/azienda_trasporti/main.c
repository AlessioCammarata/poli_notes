#include <stdio.h>
#include <string.h>

#define nfin "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione7/azienda_trasporti/corse.txt"
// #define nfin "./corse.txt"
#define MAXR 1000
#define buffer 31
#define MAXL 15
#define max_data 11

typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine
} comando_e;

typedef struct {
    char id[buffer], part[buffer], dest[buffer], data[buffer], ora_p[buffer], ora_a[buffer];
    int ret;
} pullman;

void leggiFile(FILE *fin, int n, pullman vet[n]);
comando_e leggiComando(void);
int date(char* data1, char* data2, int n, pullman vet[n]);
void ordina_date(char* data1, char* data2, char* dmin, char* dmax);
int partenza(char *fermata, int n, pullman vet[n]);
int destinazione(char *fermata,int n,pullman vet[n]);
int ritardo(char* data1, char* data2,int n, pullman vet[n]);
int ritardo_tot(char *id, int n, pullman vet[n]);

int main(void){
    FILE *fin;
    int n,end=0,count;

    if ((fin = fopen(nfin,"r")) == NULL){
        printf("Errore in apertura del file\n");
        return 1;
    }

    fscanf(fin,"%d",&n);
    if(n>MAXR){
        printf("Errore, ci sono piu campi di quanti ce ne dvorebbero\n.");
        return 1;
    }
    
    pullman vet[n];
    leggiFile(fin,n,vet);
    comando_e act;

    while(!end){
        char data1[max_data], data2[max_data];
        char *str;
        printf("Inserisci la tua scelta:\n");

        act = leggiComando();
        switch(act){
            case r_date:
                printf("Inserisci due date nel formato (yyyy/mm/dd) :\n");
                scanf("%s %s",data1,data2);
                
                count = date(data1,data2,n,vet);
                if(count==0) printf("Nessuna corrispondenza\n\n");

                break;
            case r_partenza:
                printf("Inserisci il nome della fermata:\n");
                scanf("%s",str);
                
                count = partenza(str,n,vet);
                if(count==0) printf("Nessuna corrispondenza\n\n");

                break;
            case r_capolinea:
                printf("Inserisci il nome della fermata:\n");
                scanf("%s",str);
                
                count = destinazione(str,n,vet);
                if(count==0) printf("Nessuna corrispondenza\n\n");

                break;
            case r_ritardo:
                printf("Inserisci due date nel formato (yyyy/mm/dd) :\n");
                scanf("%s %s",data1,data2);
                
                count = ritardo(data1,data2,n,vet);
                if(count==0) printf("Nessuna corrispondenza\n\n");

                break;
            case r_ritardo_tot:
                printf("Inserisce l'id che si vuole controllare:\n");
                scanf("%s",str);

                count = ritardo_tot(str,n,vet);
                if(count==0) printf("Nessuna corrispondenza\n\n");
                else printf("Il ritardo accumulato è pari a: %d\n\n", count);

                break;
            case r_fine:
                end = 1;
                break;
            default:
                printf("Errore, comando non valido.");
        }
    }


    fclose(fin);
    return 0;
}

void leggiFile(FILE *fin, int n, pullman vet[n]){
    int i=0;

    while(fscanf(fin,"%30s %30s %30s %30s %30s %30s %d",vet[i].id,vet[i].part,vet[i].dest,vet[i].data,vet[i].ora_p,vet[i].ora_a,&vet[i].ret) == 7){
        i++;
    }
}

comando_e leggiComando (void) {
    comando_e c;
    char cmd[MAXL];
    char tabella[r_fine + 1][MAXL] = {
        "date","partenza","destinazione","ritardo","ritardo_tot","fine"
    };
    printf("comando (date");
    printf("/partenza/destinazione/ritardo/ritardo_tot/fine): ");
    scanf("%s",cmd); 
    c=r_date;
    while(c<r_fine && strcmp(cmd,tabella[c])!=0)
        c++;
    return (c);
}

void ordina_date(char* data1, char* data2, char* dmin, char* dmax) {
    if (strcmp(data1, data2) <= 0) {
        strcpy(dmin, data1);
        strcpy(dmax, data2);
    } else {
        strcpy(dmin, data2);
        strcpy(dmax, data1);
    }

}

int date(char* data1, char* data2, int n, pullman vet[n]){

    // Copie locali per non modificare i parametri originali
    char dmin[max_data], dmax[max_data];
    int c=0;

    ordina_date(data1,data2,dmin,dmax);

    printf("\nIntervallo: %s - %s\n", dmin, dmax);
    for(int i=0;i<n;i++){
        if(strcmp(vet[i].data, dmin) >= 0 && strcmp(vet[i].data, dmax) <= 0){
            printf("%s\n",vet[i].id);
            c++;
        }
    }
    printf("\n");

    return c;
}

int partenza(char *fermata, int n, pullman vet[n]){
    int c=0;

    printf("\nfermata di partenza: %s\n",fermata);
    for(int i = 0;i<n;i++){
        if(strcmp(fermata,vet[i].part) == 0){
            printf("%s\n",vet[i].id);
            c++;
        }
    }
    printf("\n");

    return c;
}

int destinazione(char *fermata,int n,pullman vet[n]){
    int c=0;

    printf("\nfermata di capolinea: %s\n",fermata);
    for(int i = 0;i<n;i++){
        if(strcmp(fermata,vet[i].dest) == 0){
            printf("%s\n",vet[i].id);
            c++;
        }
    }
    printf("\n");

    return c;
}

// elencare tutte le corse che hanno raggiunto la destinazione in ritardo, in un certo intervallo di date
int ritardo(char* data1, char* data2,int n, pullman vet[n]){
    char dmin[max_data], dmax[max_data];
    int c=0;

    ordina_date(data1,data2,dmin,dmax);

    printf("\nIntervallo: %s - %s\n", dmin, dmax);
    for(int i =0;i<n;i++){
        if(strcmp(vet[i].data, dmin) >= 0 && strcmp(vet[i].data, dmax) <= 0 && vet[i].ret != 0){
            printf("%s\n",vet[i].id);
            c++;
        }
    }
    printf("\n");

    return c;
}

//5. elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta
int ritardo_tot(char *id, int n, pullman vet[n]){
    int sum=0;

    for(int i=0;i<n;i++){
        if(strcmp(id,vet[i].id) == 0)
            sum += vet[i].ret;
    }
    printf("\n");

    return sum;
}