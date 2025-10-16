#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 51 //50 + 1
#define MAXL 34 //

typedef struct Item *link, Item; 

typedef enum {
    r_insert_key, r_insert_file, r_search_id, r_remove_id, r_remove_date, r_stampa, r_fine
} comando_e;

typedef struct{
    int year, month, day;
} date;

struct Item{
    char codice[MAXC];
    char nome[MAXC];
    char cognome[MAXC];
    date data_di_nascita;
    char via[MAXC];
    char citta[MAXC];
    int cap;
    link *prev, *next;
};

// void leggiFile(FILE *fin, int n, Item vet[n], pullman *vetp_orig[n], pullman *vetp_id[n], pullman *vetp_data[n], pullman *vetp_part[n], pullman *vetp_arr[n]);
comando_e leggiComando(void);

int main(void){
    FILE *fin;
    int n = 16, end = 0, count, res;

    Item *vet = malloc(n*sizeof(Item));

    comando_e act;
    char str[MAXC], ans;

    while (!end) {

        printf("Inserisci la tua scelta:\n");
        act = leggiComando();
        switch (act) {
            case r_insert_key:

                printf("Inserisci i dati da tastiera nell'ordine: () :\n");

                break;
            case r_insert_file:
                if ((fin = nuovo_file()) != NULL) {
                        
                    if (fscanf(fin, "%d", &n) == 1 && n <= MAXR) {
                        // Prima di leggere un nuovo file:
                        // free(vet);
                        // free(vetp_orig);
                        // free(vetp_id);
                        // free(vetp_data);
                        // free(vetp_part);
                        // free(vetp_arr);

                        // // Dopo aver letto n dal nuovo file:
                        // vet = malloc(n * sizeof(pullman));
                        // vetp_orig = malloc(n * sizeof(pullman *));
                        // vetp_id   = malloc(n * sizeof(pullman *));
                        // vetp_data = malloc(n * sizeof(pullman *));
                        // vetp_part = malloc(n * sizeof(pullman *));
                        // vetp_arr  = malloc(n * sizeof(pullman *));

                        if(vet && vetp_orig && vetp_id && vetp_data && vetp_part && vetp_arr){
                            leggiFile(fin, n, vet, vetp_orig, vetp_id, vetp_data, vetp_part, vetp_arr);
                            vetp = vetp_orig;
                            
                        }else{
                            printf("Errore di malloc per il path\n");                                                            fclose(fin);
                            fclose(fin);
                            end = 1;
                        }
                    }else{
                        printf("Errore, ci sono piu campi di quanti ce ne dvorebbero\n.");
                        fclose(fin);
                        end = 1;
                    }
                }else printf("Errore in apertura del file\n");

                break;
            case r_search_id:

                printf("Inserisci il nome della fermata:\n");
                scanf("%s", str);

                if (count == 0) printf("Nessuna corrispondenza\n\n");
                break;
            case r_remove_id:


                if (count == 0) printf("Nessuna corrispondenza\n\n");
                break;
            case r_remove_date:
    
                printf("Inserisce l'id che si vuole controllare:\n");
                scanf("%s", str);

                if (count == 0) printf("Nessuna corrispondenza\n\n");
                else printf("Il ritardo accumulato dalla tratta %s è pari a: %d minuti\n\n", str, count);

                break;
            case r_stampa:
                int ch;

                // while ((ch = getchar()) != '\n' && ch != EOF);
                // printf("Inserire il path assoluto del file dove si vuole stampare o 'video' per stampare a video:\n");
                // fgets(str, buffer, stdin);
                // str[strcspn(str, "\n")] = 0;

                // if (strcmp(str, "video") == 0) {
                //     printf("%d\n", n);
                //     for (int i = 0; i < n; i++) printf("%s %s %s %s %s %s %d\n", vetp[i]->id, vetp[i]->part, vetp[i]->dest, vetp[i]->data, vetp[i]->ora_p, vetp[i]->ora_a, vetp[i]->ret);
                // } else if (stampaDati(str, n, vetp) == 1) end = 1;

                printf("\nStampa effettuata!\n\n");
                break;
            case r_fine:
                end = 1;
                break;
            default:
                printf("Errore, comando non valido.\n");
        }
    }

    return 0;
}

// void leggiFile(FILE *fin, int n, pullman vet[n], pullman *vetp[n], pullman *vetp_id[n], pullman *vetp_data[n], pullman *vetp_part[n], pullman *vetp_arr[n]){
//     int i = 0;
//     while(fscanf(fin, "%s %s %s %s %s %s %d", vet[i].id, vet[i].part, vet[i].dest, vet[i].data, vet[i].ora_p, vet[i].ora_a, &vet[i].ret) == 7 && i < n){
//         vetp[i] = &vet[i];
//         vetp_data[i] = &vet[i];
//         vetp_id[i] = &vet[i];
//         vetp_part[i] = &vet[i];
//         vetp_arr[i] = &vet[i];
//         i++;
//     }

//     fclose(fin);
// }

comando_e leggiComando (void) {
    comando_e c;
    char cmd[MAXL];
    char tabella[r_fine + 1][MAXL] = {
        "inserimento_tastiera","inserimento_file","ricerca_id","cancella_id","ricerca_date","stampa","fine"
    };

    printf("comando (inserimento_tastiera");
    printf("/inserimento_file/ricerca_id/cancella_id/ricerca_date/stampa/fine): ");
    scanf("%s",cmd); 
    c=r_insert_key;

    while(c<r_fine+1 && strcmp(cmd,tabella[c])!=0)
        c++;

    return (c);
}