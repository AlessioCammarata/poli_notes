#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define nfin "C:/Users/aless/Desktop/Polito/poli_notes/Algoritmi e strutture dati/programmazione/lab1/azienda di trasporti/corse.txt"
// #define nfin "./corse.txt"
#define MAXR 1000
#define buffer 31
#define MAXL 15
#define max_data 11

typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_stampa, r_ordina_data, r_ordina_id, r_ordina_partenza, r_ordina_arrivo, r_fine
} comando_e;

typedef struct {
    char id[buffer], part[buffer], dest[buffer], data[buffer], ora_p[buffer], ora_a[buffer];
    int ret;
} pullman;

void leggiFile(FILE *fin, int n, pullman vet[n], pullman *vetp[n]);
comando_e leggiComando(void);
void stampaVoce(const pullman *v);
int stampaDati(char *path, int n, pullman **vetp);
int date(char* data1, char* data2, int n, pullman *vetp[]);
void ordina_date(char* data1, char* data2, char* dmin, char* dmax);
void ordina(int param, int n, pullman *vetp[]);
int partenza(char *fermata, int n, pullman *vetp[]);
int destinazione(char *fermata,int n,pullman *vetp[]);
int ritardo(char* data1, char* data2,int n, pullman *vetp[]);
int ritardo_tot(char *id, int n, pullman *vetp[]);

int main(void){
    FILE *fin;
    int n, end = 0, count;

    if ((fin = fopen(nfin, "r")) == NULL) {
        printf("Errore in apertura del file\n");
        return 1;
    }
    
    fscanf(fin, "%d", &n);
    if (n > MAXR) {
        printf("Errore, ci sono piu campi di quanti ce ne dvorebbero\n.");
        return 1;
    }

    pullman vet[n];
    pullman *vetp[n];
    leggiFile(fin, n, vet, vetp);
    comando_e act;
    char str[buffer];

    while (!end) {

        char data1[max_data], data2[max_data];

        printf("Inserisci la tua scelta:\n");
        act = leggiComando();
        switch (act) {
            case r_date:

                printf("Inserisci due date nel formato (yyyy/mm/dd) :\n");
                scanf("%s %s", data1, data2);
                count = date(data1, data2, n, vetp);

                if (count == 0) printf("Nessuna corrispondenza\n\n");
                break;
            case r_partenza:

                printf("Inserisci il nome della fermata:\n");
                scanf("%s", str);
                count = partenza(str, n, vetp);

                if (count == 0) printf("Nessuna corrispondenza\n\n");
                break;
            case r_capolinea:

                printf("Inserisci il nome della fermata:\n");
                scanf("%s", str);
                count = destinazione(str, n, vetp);

                if (count == 0) printf("Nessuna corrispondenza\n\n");
                break;
            case r_ritardo:

                printf("Inserisci due date nel formato (yyyy/mm/dd) :\n");
                scanf("%s %s", data1, data2);
                count = ritardo(data1, data2, n, vetp);

                if (count == 0) printf("Nessuna corrispondenza\n\n");
                break;
            case r_ritardo_tot:
    
                printf("Inserisce l'id che si vuole controllare:\n");
                scanf("%s", str);
                count = ritardo_tot(str, n, vetp);

                if (count == 0) printf("Nessuna corrispondenza\n\n");
                else printf("Il ritardo accumulato dalla tratta %s è pari a: %d minuti\n\n", str, count);

                break;
            case r_stampa:
                int ch;

                while ((ch = getchar()) != '\n' && ch != EOF);
                printf("Inserire il path assoluto del file dove si vuole stampare o 'video' per stampare a video:\n");
                fgets(str, MAXR, stdin);
                str[strcspn(str, "\n")] = 0;

                if (strcmp(str, "video") == 0) {
                    printf("%d\n", n);
                    for (int i = 0; i < n; i++) printf("%s %s %s %s %s %s %d\n", vetp[i]->id, vetp[i]->part, vetp[i]->dest, vetp[i]->data, vetp[i]->ora_p, vetp[i]->ora_a, vetp[i]->ret);
                } else if (stampaDati(str, n, vetp) == 1) return 1;

                printf("\nStampa effettuata!\n\n");
                break;
            case r_ordina_data:
                ordina(1, n, vetp);
                break;
            case r_ordina_id:
                ordina(0, n, vetp);
                break;
            case r_ordina_partenza:
                ordina(2, n, vetp);
                break;
            case r_ordina_arrivo:
                ordina(3, n, vetp);
                break;
            case r_fine:
                end = 1;
                break;
            default:
                printf("Errore, comando non valido.\n");
        }
    }

    fclose(fin);
    return 0;
}

void leggiFile(FILE *fin, int n, pullman vet[n], pullman *vetp[n]){
    int i=0;

    while(fscanf(fin,"%s %s %s %s %s %s %d",vet[i].id,vet[i].part,vet[i].dest,vet[i].data,vet[i].ora_p,vet[i].ora_a,&vet[i].ret) == 7){
        vetp[i] = &vet[i];
        i++;
    }
}

comando_e leggiComando (void) {
    comando_e c;
    char cmd[MAXL];
    char tabella[r_fine + 1][MAXL] = {
        "date","partenza","destinazione","ritardo","ritardo_tot","stampa","ordina_data", "ordina_id", "ordina_partenza", "ordina_arrivo","fine"
    };
    printf("comando (date");
    printf("/partenza/destinazione/ritardo/ritardo_tot/stampa/ordina_data/ordina_id/ordina_partenza/ordina_arrivo/fine): ");
    scanf("%s",cmd); 
    c=r_date;
    while(c<r_fine+1 && strcmp(cmd,tabella[c])!=0)
        c++;
    return (c);
}

int stampaDati(char *path, int n, pullman **vetp){
    FILE *fout;
    if ((fout = fopen(path,"w")) == NULL){
        printf("Errore in apertura del file\n");
        return 1;
    }
    fprintf(fout,"%d",n);
    for (int i =0; i<n; i++) fprintf(fout,"\n%s %s %s %s %s %s %d",vetp[i]->id, vetp[i]->part, vetp[i]->dest, vetp[i]->data, vetp[i]->ora_p, vetp[i]->ora_a, vetp[i]->ret);
    fclose(fout);
    return 0;
}

void stampaVoce(const pullman *v) {
    printf("Tratta [%s] da %s a %s del %s (dalle %s alle %s, con ritardo di %d minut%c)\n", v->id, v->part, v->dest, v->data, v->ora_a, v->ora_p, v->ret, ((v->ret == 1) ? 'o' : 'i'));
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

int cmp_data(const void *a, const void *b) {
    const pullman *pa = (const pullman *)a;
    const pullman *pb = (const pullman *)b;
    int cmp = strcmp(pa->data, pb->data);
    if (cmp != 0)
        return cmp;
    cmp = strcmp(pa->ora_p, pb->ora_p);
    if (cmp != 0)
        return cmp;
    // Terza chiave: id
    return strcmp(pa->id, pb->id);
}


int cmp_id(const void *a, const void *b) {
    const pullman *pa = (const pullman *)a;
    const pullman *pb = (const pullman *)b;
    return strcmp(pa->id, pb->id);
}

int cmp_partenza(const void *a, const void *b) {
    const pullman *pa = (const pullman *)a;
    const pullman *pb = (const pullman *)b;
    return strcmp(pa->part, pb->part);
}

int cmp_destinazione(const void *a, const void *b) {
    const pullman *pa = (const pullman *)a;
    const pullman *pb = (const pullman *)b;
    return strcmp(pa->dest, pb->dest);
}

void merge(pullman *vetp[], pullman *temp[], int left, int mid, int right, int (*cmp)(const void *, const void *)) {
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (cmp(vetp[i], vetp[j]) <= 0) {
            temp[k++] = vetp[i++];
        } else {
            temp[k++] = vetp[j++];
        }
    }
    while (i < mid) temp[k++] = vetp[i++];
    while (j < right) temp[k++] = vetp[j++];
    for (i = left; i < right; i++) vetp[i] = temp[i];
}

void merge_sort_rec(pullman *vetp[], pullman *temp[], int left, int right, int (*cmp)(const void *, const void *)) {
    if (right - left > 1) {
        int mid = (left + right) / 2;
        merge_sort_rec(vetp, temp, left, mid, cmp);
        merge_sort_rec(vetp, temp, mid, right, cmp);
        merge(vetp, temp, left, mid, right, cmp);
    }
}

void merge_sort(pullman *vetp[], int n, int (*cmp)(const void *, const void *)) {
    pullman **temp = malloc(n * sizeof(pullman*));
    if (!temp) {
        printf("Errore di allocazione memoria per merge sort\n");
        return;
    }
    merge_sort_rec(vetp, temp, 0, n, cmp);
    free(temp);
}

void ordina(int param, int n, pullman *vetp[]) {
    int (*cmp)(const void *, const void *);
    switch(param) {
        case 0: cmp = cmp_id; break;
        case 1: cmp = cmp_data; break;
        case 2: cmp = cmp_partenza; break;
        case 3: cmp = cmp_destinazione; break;
        default: cmp = cmp_id; break;
    }
    merge_sort(vetp, n, cmp);
}

int date(char* data1, char* data2, int n, pullman *vetp[]){
    char dmin[max_data], dmax[max_data];
    int c=0;
    ordina_date(data1,data2,dmin,dmax);
    printf("\nIntervallo: %s - %s\n", dmin, dmax);
    for(int i=0;i<n;i++){
        if(strcmp(vetp[i]->data, dmin) >= 0 && strcmp(vetp[i]->data, dmax) <= 0){
            stampaVoce(vetp[i]);
            c++;
        }
    }
    printf("\n");
    return c;
}

int partenza(char *fermata, int n, pullman *vetp[]){
    int c=0;
    printf("\nfermata di partenza: %s\n",fermata);
    for(int i = 0;i<n;i++){
        if(strcmp(fermata,vetp[i]->part) == 0){
            stampaVoce(vetp[i]);
            c++;
        }
    }
    printf("\n");
    return c;
}

int destinazione(char *fermata,int n,pullman *vetp[]){
    int c=0;
    printf("\nfermata di capolinea: %s\n",fermata);
    for(int i = 0;i<n;i++){
        if(strcmp(fermata,vetp[i]->dest) == 0){
            stampaVoce(vetp[i]);
            c++;
        }
    }
    printf("\n");
    return c;
}

int ritardo(char* data1, char* data2,int n, pullman *vetp[]){
    char dmin[max_data], dmax[max_data];
    int c=0;
    ordina_date(data1,data2,dmin,dmax);
    printf("\nIntervallo: %s - %s\n", dmin, dmax);
    for(int i =0;i<n;i++){
        if(strcmp(vetp[i]->data, dmin) >= 0 && strcmp(vetp[i]->data, dmax) <= 0 && vetp[i]->ret != 0){
            stampaVoce(vetp[i]);
            c++;
        }
    }
    printf("\n");
    return c;
}

int ritardo_tot(char *id, int n, pullman *vetp[]){
    int sum=0;
    for(int i=0;i<n;i++){
        if(strcmp(id,vetp[i]->id) == 0)
            sum += vetp[i]->ret;
    }
    printf("\n");
    return sum;
}