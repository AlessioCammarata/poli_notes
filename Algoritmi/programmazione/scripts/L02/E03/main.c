// #include <stdio.h>
#include "my_lib.h" // Ensure the file is in the same directory as main.c
#include <string.h>
// #include <stdlib.h>

#define MAXR 1000
#define buffer 31
#define MAXL 20
#define max_data 11
#define STANDARD_SIZE 32

typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_stampa, r_ordina_data, r_ordina_id, r_ordina_partenza, r_ordina_arrivo, r_cerca_tratta_c, r_cerca_tratta_sp, r_nuovo_file, r_fine
} comando_e;

typedef enum{
    ord_id, ord_data, ord_partenza, ord_arrivo
} ord;
// typedef struct {
//     char id[buffer], part[buffer], dest[buffer], data[buffer], ora_p[buffer], ora_a[buffer];
//     int ret;
// } pullman;

FILE *nuovo_file();
void leggiFile(FILE *fin, int n, pullman vet[n], pullman *vetp_orig[n], pullman *vetp_id[n], pullman *vetp_data[n], pullman *vetp_part[n], pullman *vetp_arr[n]);
comando_e leggiComando(void);
void stampaVoce(const pullman *v);
int stampaDati(char *path, int n, pullman **vetp);
int date(char* data1, char* data2, int n, pullman *vetp[]);
void ordina_date(char* data1, char* data2, char* dmin, char* dmax);
void ordina(ord param, int n, pullman *vetp[]);
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

    if ((fin = nuovo_file()) == NULL) {
        printf("Errore in apertura del file\n");
        return 1;
    }
    
    fscanf(fin, "%d", &n);
    if (n > MAXR) {
        printf("Errore, ci sono piu campi di quanti ce ne dvorebbero\n.");
        return 1;
    }

    pullman vet[n] ,**vetp , *vetp_orig[n], *vetp_id[n], *vetp_data[n], *vetp_part[n], *vetp_arr[n]; // puntatori ordinati (id/data/partenza/arrivo)
    leggiFile(fin, n, vet, vetp_orig, vetp_id, vetp_data, vetp_part, vetp_arr);
    vetp = vetp_orig;

    comando_e act;
    char str[buffer], ans, ch;

    while (!end) {

        char data1[max_data], data2[max_data];

        printf("Inserisci la tua scelta:\n");
        act = leggiComando();
        while ((ch = getchar()) != '\n' && ch != EOF);

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
                int ch, len_str = 0, start = 0, size_str = STANDARD_SIZE;
                char *path = malloc(size_str*sizeof(char));

                printf("Inserire il path assoluto del file dove si vuole stampare o 'video' per stampare a video:\n");
                while((ch = getchar()) != '\n' && ch != EOF){
                    if (len_str >= size_str -1){
                        size_str *= 2;
                        path = (char *)realloc(path, size_str*sizeof(char));
                        if(!path){
                            printf("Errore di realloc per il path\n");
                            free(path);
                            return 1;
                        }
                    }
                    path[len_str++] = (char)ch;
                }
                path[len_str] = '\0';

                while (path[start] == ' ' || path[start] == '\t') start++;
                // Rimuovi spazi/tab finali
                while (len_str > 0 && (path[len_str - 1] == ' ' || path[len_str - 1] == '\t'))
                    path[--len_str] = '\0';

                if (strcmp(path + start, "video") == 0) {
                    printf("%d\n", n);
                    for (int i = 0; i < n; i++) printf("%s %s %s %s %s %s %d\n", vetp[i]->id, vetp[i]->part, vetp[i]->dest, vetp[i]->data, vetp[i]->ora_p, vetp[i]->ora_a, vetp[i]->ret);
                } else if (stampaDati(path + start, n, vetp) == 1) return 1;

                free(path);
                printf("\nStampa effettuata!\n\n");
                break;
            case r_ordina_data:
                vetp = vetp_data;
                break;
            case r_ordina_id:
                vetp = vetp_id;
                break;
            case r_ordina_partenza:
                vetp = vetp_part;
                break;
            case r_ordina_arrivo:
                vetp = vetp_arr;
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
            case r_nuovo_file:
                if ((fin = nuovo_file()) == NULL) {
                    printf("Errore in apertura del file\n");
                    return 1;
                }
                
                fscanf(fin, "%d", &n);
                if (n > MAXR) {
                    printf("Errore, ci sono piu campi di quanti ce ne dvorebbero\n.");
                    return 1;
                }
                printf("%d\n",n);
                leggiFile(fin, n, vet, vetp_orig, vetp_id, vetp_data, vetp_part, vetp_arr);
                vetp = vetp_orig;

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

FILE *nuovo_file(){
    int len_str = 0, size_str = STANDARD_SIZE;        
    FILE *fin;
    char c, *path = (char *)malloc(size_str * sizeof(char));

    if(!path){
        printf("Errore di malloc per il path\n");
        return NULL;
    }

    printf("Inserire il path del nuovo file da analizzare\n");
    while((c = getchar()) != '\n' && c != EOF){
        if (len_str >= size_str -1){
            size_str *= 2;
            path = (char *)realloc(path, size_str*sizeof(char));
            if(!path){
                printf("Errore di realloc per il path\n");
                free(path);
                return NULL;
            }
        }
        path[len_str++] = (char)c;
    }
    path[len_str] = '\0'; 

    fin = fopen(path, "r");
    free(path);
    return fin;
}

void leggiFile(FILE *fin, int n, pullman vet[n], pullman *vetp_orig[n], pullman *vetp_id[n], pullman *vetp_data[n], pullman *vetp_part[n], pullman *vetp_arr[n]){
    int i = 0;

    // fscanf(fin, "%d", &n);
    // if (n > MAXR) {
    //     printf("Errore, ci sono piu campi di quanti ce ne dvorebbero\n.");
    //     return 1;
    // }

    while(fscanf(fin, "%s %s %s %s %s %s %d", vet[i].id, vet[i].part, vet[i].dest, vet[i].data, vet[i].ora_p, vet[i].ora_a, &vet[i].ret) == 7 && i < n){
        vetp_orig[i] = &vet[i];
        vetp_data[i] = &vet[i];
        vetp_id[i] = &vet[i];
        vetp_part[i] = &vet[i];
        vetp_arr[i] = &vet[i];
        i++;
    }
    ordina(ord_id,n,vetp_id);
    ordina(ord_data,n,vetp_data);
    ordina(ord_partenza,n,vetp_part);
    ordina(ord_arrivo,n,vetp_arr);
}

comando_e leggiComando (void) {
    comando_e c;
    char cmd[MAXL];
    char tabella[r_fine + 1][MAXL] = {
        "date","partenza","destinazione","ritardo","ritardo_tot","stampa","ordina_data", "ordina_id", "ordina_partenza", "ordina_arrivo","cerca_tratta_c","cerca_tratta_sp","nuovo_file", "fine"
    };

    printf("comando (date");
    printf("/partenza/destinazione/ritardo/ritardo_tot/stampa/ordina_data/ordina_id/ordina_partenza/ordina_arrivo/cerca_tratta_c/cerca_tratta_sp/nuovo_file/fine): ");
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

void ordina(ord param, int n, pullman *vetp[]) {
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