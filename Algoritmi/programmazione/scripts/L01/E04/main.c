// #include <stdio.h>
#include "my_lib.h" // Ensure the file is in the same directory as main.c
#include <string.h>
// #include <stdlib.h>

#define nfin "C:/Users/aless/Desktop/Polito/poli_notes/Algoritmi/programmazione/lab1/azienda di trasporti/corse.txt"
// #define nfin "./corse.txt"
#define MAXR 1000
#define buffer 31
#define MAXL 20
#define max_data 11

typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_stampa, r_ordina_data, r_ordina_id, r_ordina_partenza, r_ordina_arrivo, r_cerca_tratta_c, r_cerca_tratta_sp, r_fine
} comando_e;

// typedef struct {
//     char id[buffer], part[buffer], dest[buffer], data[buffer], ora_p[buffer], ora_a[buffer];
//     int ret;
// } pullman;

void leggiFile(FILE *fin, int n, pullman vet[n], pullman *vetp[n], pullman *vetp_id[n], pullman *vetp_data[n], pullman *vetp_part[n], pullman *vetp_arr[n]);
comando_e leggiComando(void);
void stampaVoce(const pullman *v);
int stampaDati(char *path, int n, pullman **vetp);
int date(char* data1, char* data2, int n, pullman *vetp[]);
void ordina_date(char* data1, char* data2, char* dmin, char* dmax);
void ordina(int param, int n, pullman *vetp[]);
int cerca_dico_id(char *id, int n, pullman *vetp[]);
int cerca_linea_id(char *id, int n, pullman *vetp[]);
int cerca_dico_pre(char *fermata, int n, pullman *vetp[]);
int cerca_linea_pre(char *fermata, int n, pullman *vetp[]);
int partenza(char *fermata, int n, pullman *vetp[]);
int destinazione(char *fermata,int n,pullman *vetp[]);
int ritardo(char* data1, char* data2,int n, pullman *vetp[]);
int ritardo_tot(char *id, int n, pullman *vetp[]);

int main(void){
    FILE *fin;
    int n, end = 0, count, res;

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
    pullman *vetp_id[n];   // puntatori ordinati per codice
    pullman *vetp_data[n]; // puntatori ordinati per data
    pullman *vetp_part[n]; // puntatori ordinati per partenza
    pullman *vetp_arr[n];  // puntatori ordinati per arrivo

    leggiFile(fin, n, vet, vetp, vetp_id, vetp_data, vetp_part, vetp_arr);
    ordina(0,n,vetp_id);
    ordina(1,n,vetp_data);
    ordina(2,n,vetp_part);
    ordina(3,n,vetp_arr);
    
    comando_e act;
    char str[buffer], ans;

    while (!end) {

        char data1[max_data], data2[max_data];

        printf("Inserisci la tua scelta:\n");
        act = leggiComando();
        switch (act) {
            case r_date:

                printf("Inserisci due date nel formato (yyyy/mm/dd) :\n");
                scanf("%s %s", data1, data2);
                count = date(data1, data2, n, vetp_data);

                if (count == 0) printf("Nessuna corrispondenza\n\n");
                break;
            case r_partenza:

                printf("Inserisci il nome della fermata:\n");
                scanf("%s", str);
                count = partenza(str, n, vetp_part);

                if (count == 0) printf("Nessuna corrispondenza\n\n");
                break;
            case r_capolinea:

                printf("Inserisci il nome della fermata:\n");
                scanf("%s", str);
                count = destinazione(str, n, vetp_arr);

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

            case r_cerca_tratta_c:
                printf("Ricerca dicotomica o no? (s\\n)\n");
                scanf(" %c", &ans);

                printf("Inserire il codice:\n");
                scanf("%s", str);

                if (ans == 's'){
                    cerca_dico_id(str, n, vetp_id);

                } else{
                    cerca_linea_id(str, n, vetp);
                }

                break;
            case r_cerca_tratta_sp:
                printf("Ricerca dicotomica o no? (s\\n)\n");
                scanf(" %c", &ans);

                printf("Inserire la stazione di partenza:\n");
                scanf("%s", str);

                if (ans == 's'){
                    res = cerca_dico_pre(str, n, vetp_part);

                } else{
                    res = cerca_linea_pre(str, n, vetp);
                }

                if (!res) printf("Nessuna corrispondenza trovata\n");
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

void leggiFile(FILE *fin, int n, pullman vet[n], pullman *vetp[n], pullman *vetp_id[n], pullman *vetp_data[n], pullman *vetp_part[n], pullman *vetp_arr[n]){
    int i = 0;
    while(fscanf(fin, "%s %s %s %s %s %s %d", vet[i].id, vet[i].part, vet[i].dest, vet[i].data, vet[i].ora_p, vet[i].ora_a, &vet[i].ret) == 7 && i < n){
        vetp[i] = &vet[i];
        vetp_data[i] = &vet[i];
        vetp_id[i] = &vet[i];
        vetp_part[i] = &vet[i];
        vetp_arr[i] = &vet[i];
        i++;
    }
}

comando_e leggiComando (void) {
    comando_e c;
    char cmd[MAXL];
    char tabella[r_fine + 1][MAXL] = {
        "date","partenza","destinazione","ritardo","ritardo_tot","stampa","ordina_data", "ordina_id", "ordina_partenza", "ordina_arrivo","cerca_tratta_c","cerca_tratta_sp","fine"
    };

    printf("comando (date");
    printf("/partenza/destinazione/ritardo/ritardo_tot/stampa/ordina_data/ordina_id/ordina_partenza/ordina_arrivo/cerca_tratta_c/cerca_tratta_sp/fine): ");
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

int cerca_dico_id(char *id, int n, pullman *vetp[]) {
    int l = 0, r = n - 1, m, cmp;
    while (l <= r) {
        m = (l + r) / 2;
        cmp = strcmp(id, vetp[m]->id);
        if (cmp == 0) {
            stampaVoce(vetp[m]);
            return m; // trovato
        } else if (cmp < 0) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    printf("Nessuna corrispondenza\n");
    return -1; // non trovato
}

int cerca_linea_id(char *id, int n, pullman *vetp[]){
    int i = 0;
    while(i<n && strcmp(vetp[i]->id,id) != 0) i++;

    if (i != n){
        stampaVoce(vetp[i]);
        return i;
    }else{
        printf("Nessuna corrispondenza\n");
        return -1;
    }
}

int cerca_dico_pre(char *fermata, int n, pullman *vetp[n]){
    int l = 0, r = n - 1, m, cmp, found = 0, maxn = strlen(fermata);

    while (l <= r) {
        m = (l + r) / 2;
        cmp = strncmp(fermata, vetp[m]->part, maxn);
        if (cmp == 0) {
            // Trova il primo a sinistra
            int i = m;
            while (i > 0 && strncmp(fermata, vetp[i-1]->part, maxn) == 0) i--;
            // Stampa tutti quelli col prefisso
            while (i < n && strncmp(fermata, vetp[i]->part, maxn) == 0) {
                stampaVoce(vetp[i]);
                found = 1;
                i++;
            }
            return found;
        } else if (cmp < 0) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return 0;
}

int cerca_linea_pre(char *fermata, int n, pullman *vetp[n]){
    int i = 0,found = 0, nmax = strlen(fermata);
    while(i<n){
        if(strncmp(vetp[i]->part,fermata,nmax) == 0){ 
            stampaVoce(vetp[i]);
            found = 1;
        }
        i++;
    }

    return found;
}