#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 51 //50 + 1
#define MAXL 34 //
#define STANDARD_SIZE 16

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
    date data;
    char via[MAXC];
    char citta[MAXC];
    int cap;
    link prev, next;
};

FILE *nuovo_file();
int controlla_anzianita(date *a, date *b);
void inserisci_ord(link *head, link p);
int inserisci_tastiera(link *head);
void leggiFile(FILE *fin, int *n, Item *vet);
comando_e leggiComando(void);

int main(void){
    FILE *fin;
    int size = STANDARD_SIZE, n = 0, end = 0, count = 0, res;

    // Item *vet = malloc(size*sizeof(Item));
    link head = NULL;

    comando_e act;
    char str[MAXC], ans, ch;

    while (!end) {

        printf("Inserisci la tua scelta:\n");
        act = leggiComando();
        // Consuma e scarta tutti i caratteri rimanenti nel buffer di input fino al carattere di nuova linea ('\n') o alla fine del file (EOF).
        while ((ch = getchar()) != '\n' && ch != EOF);

        switch (act) {
            case r_insert_key:

                while(inserisci_tastiera(&head)) n++;

                printf("\n%d elementi nel vettore\n",n);

                break;
            case r_insert_file:
                if ((fin = nuovo_file()) != NULL) {
 
                    leggiFile(fin, &n, head); // Si suppone che gli elementi non siano gia presenti
                        
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
                // int ch;
                link p = malloc(sizeof *p);
                for(p=head; p!=NULL; p = p->next){
                    printf("%s\n",p->codice);
                }
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

    // free_list(&head); // libera tutti i nodi prima di uscire
    return 0;
}

FILE *nuovo_file(){
    int len_str = 0, size_str = STANDARD_SIZE*2;        
    FILE *fin;
    char c, *path = (char *)malloc(size_str * sizeof(char));

    if(!path){
        printf("Errore di malloc per il path\n");
        return NULL;
    }

    printf("Inserire il path del file da analizzare\n");
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

int controlla_anzianita(date *a, date *b){

}

void inserisci_ord(link *head, link p){
    
}

int inserisci_tastiera(link *head) {
    link p = malloc(sizeof *p);
    if (!p) { fprintf(stderr, "malloc fallita\n"); return 0; }

    printf("Inserisci: <codice> <nome> <cognome> gg/mm/aaaa <via> <citta> <cap>\n");
    int scanned = scanf("%50s %50s %50s %d/%d/%d %50s %50s %d",
        p->codice, p->nome, p->cognome,
        &p->data.day, &p->data.month, &p->data.year,
        p->via, p->citta, &p->cap);

    if (scanned != 9) {
        free(p);
        return 0;
    }

    /* inizializza i puntatori della lista prima dell'inserimento */
    p->prev = p->next = NULL;

    /* inserisci ordinato (implementa insert_ordered per l'ordinamento per anzianità) */
    insert_ordered(head, p);

    return 1;
}

void leggiFile(FILE *fin, int *n, Item *vet){
    int i = *n;

    while(fscanf(fin, "%50s %50s %50s %d/%d/%d %50s %50s %d",vet[i].codice, vet[i].nome, vet[i].cognome, &vet[i].data.day, &vet[i].data.month, &vet[i].data.year, vet[i].via, vet[i].citta, &vet[i].cap) == 9){
        i++;
    }
    
    *n = i;
    fclose(fin);
}

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

