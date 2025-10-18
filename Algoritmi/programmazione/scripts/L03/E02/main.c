#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXC 51 //50 + 1
#define MAXL 34 // massimo del comando, stabilito in base a cosa scrivo
#define STANDARD_SIZE 16
#define MAX_codice 6
#define n_date 2 //

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

char *path_writer();
int check_id(char *id);
int check_data(date data);
FILE *nuovo_file();
comando_e leggiComando(void);
int check_anzianita(date *a, date *b);
int insert_ord(link *head, link p);
int keyboard_insert(link *head);
void leggiFile(FILE *fin, int *n, link *head);
link search_id(link *head, char id[MAX_codice]);
link remove_element(link *head, link element);
void print_element(link element);
int compare_date(date data1, date data2);
int remove_data(link p, date data1, date data2);
void print_file(FILE *fout, link *head);
void free_list(link *head);

int main(void){
    FILE *fin;
    int size = STANDARD_SIZE, n = 0, end = 0, count = 0, res;

    link head = NULL, result;

    comando_e act;
    char str[MAXC], id[MAX_codice], ch;
    int count_id_char = 0;

    while (!end) {

        printf("Inserisci la tua scelta:\n");
        act = leggiComando();
        // Consuma e scarta tutti i caratteri rimanenti nel buffer di input fino al carattere di nuova linea ('\n') o alla fine del file (EOF).
        while ((ch = getchar()) != '\n' && ch != EOF);

        switch (act) {
            case r_insert_key:

                while(keyboard_insert(&head)) n++;
                printf("\n%d elementi nel vettore\n\n",n);
                while ((ch = getchar()) != '\n' && ch != EOF); // Pulisce il buffer

                break;
            case r_insert_file:
                if ((fin = nuovo_file()) != NULL) {
 
                    leggiFile(fin, &n, &head); // Si suppone che gli elementi non siano gia presenti
                    printf("\n%d elementi nel vettore\n",n);

                }else printf("Errore in apertura del file\n");
                printf("\n");

                break;  
            case r_search_id:
                count_id_char = 0;

                printf("Inserisci il codice da trovare:\n");
                while(count_id_char < MAX_codice-1 && (ch = getchar()) != '\n' && ch != EOF){
                    id[count_id_char++] = ch;
                }

                printf("\n");
                result = search_id(&head, id);
                if(result){
                    printf("Elemento trovato:\n");
                    print_element(result);
                }else printf("Nessun elemento trovato\n");
                printf("\n");

                while ((ch = getchar()) != '\n' && ch != EOF); // Pulisce il buffer

                break;
            case r_remove_id:
                count_id_char = 0;

                printf("Inserisci il codice da trovare:\n");
                while(count_id_char < MAX_codice-1 && (ch = getchar()) != '\n' && ch != EOF){
                    id[count_id_char++] = ch;
                }

                printf("\n");
                result = search_id(&head, id);
                if(result){
                    printf("Elemento trovato:\n");
                    print_element(result);
                    remove_element(&head, result);
                    n--; //Aggiorno la n totale
                    free(result);
                }else printf("Nessun elemento corrispondente trovato\n");
                printf("\n");

                while ((ch = getchar()) != '\n' && ch != EOF); // Pulisce il buffer

                break;
            case r_remove_date:
                if(head != NULL){
                    date *dates = malloc(n_date*sizeof(date));
                    if(dates != NULL){
                        link p;
                        int count_found = 0;

                        for(p = head; p != NULL; p = p->next)
                            print_element(p);

                        //Prendo gli input delle date
                        for (int i = 0; i < n_date; i++) {
                            printf("Inserisci la %d data: (dd/mm/yyyy)\n", i + 1);
                            scanf("%2d/%2d/%4d", &dates[i].day, &dates[i].month, &dates[i].year);
                            while ((ch = getchar()) != '\n' && ch != EOF);

                            while(!check_data(dates[i])) {
                                printf("Reinserisci la %d data: (dd/mm/yyyy)\n", i + 1);
                                scanf("%2d/%2d/%4d", &dates[i].day, &dates[i].month, &dates[i].year);
                                while ((ch = getchar()) != '\n' && ch != EOF);
                            }
                        }
                        printf("\n");

                        //Ordino le date
                        if (compare_date(dates[0], dates[1])) { // controllo data1 > data2
                            date temp = dates[0];
                            dates[0] = dates[1];
                            dates[1] = temp;
                        }

                        link next;
                        for(p = head; p != NULL; p = next){
                            next = p->next;

                            if (compare_date(p->data, dates[0]) && compare_date(dates[1], p->data)){
                                result = remove_element(&head, p);
                                print_element(result);
                                count_found++;

                                //Avanzo e cancello
                                free(result);
                            }
                        }
                        if(!count_found) printf("Nessun elemento trovato\n");
                        n -= count_found; // Aggiorno la n totale
                        free(dates);
                    } else printf("Errore di allocazione\n");
                    
                }else printf("Nessun elemento inserito\n");
                printf("\n");
                
                break;
            case r_stampa:
 
                if (head != NULL) {
                    char *path;
                    FILE *fout;
                    printf("Inserire il path assoluto del file dove si vuole stampare o 'video' per stampare a video:\n");
                    path = path_writer();

                    if(path != NULL){
                        if((fout = fopen(path,"w")) != NULL){

                            print_file(fout, &head);
                            fclose(fout);
                            printf("\nStampa effettuata!\n");

                        }else printf("Errore, in apertura del file\n");

                    }else printf("Path inserito non valido\n");

                }else printf("Errore, Non è ancora presente nessun elemento\n");
                printf("\n");
                
                break;
            case r_fine:
                end = 1;
                break;
            default:
                printf("Errore, comando non valido.\n");
        }
    }

    free_list(&head); // libera tutti i nodi prima di uscire
    return 0;
}

char *path_writer(){
    int len_str = 0, size_str = STANDARD_SIZE*2;
    char c, *path = (char *)malloc(size_str * sizeof(char));
    if(!path){
        printf("Errore di malloc per il path\n");
        return NULL;
    }

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

    return path;
}

int check_id(char *id) {
    return id[0] == 'A' && isdigit(id[1]) && isdigit(id[2]) &&
           isdigit(id[3]) && isdigit(id[4]) && id[5] == '\0';
}

int check_data(date data){
    if (data.year < 0 || data.month < 1 || data.month > 12 || data.day < 1) return 0;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if((data.year % 4 == 0 && data.year % 100 != 0) || (data.year % 400 == 0))
        days_in_month[1] = 29; // Febbraio nell'anno bisestile
    
    return data.day <= days_in_month[data.month - 1];
}

FILE *nuovo_file(){
    char *path;     
    FILE *fin;

    printf("Inserire il path del file da analizzare\n");
    if((path = path_writer()) == NULL) return NULL;
    
    fin = fopen(path, "r"),
    free(path);
    return fin;
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

int check_anzianita(date *a, date *b){
    //Controllo prima l'anno
    if(a->year != b->year)
        return a->year > b->year;

    //Controllo il mese
    if(a->month != b->month)
        return a->month > b->month;

    if(a->day != b->day)
        return a->day > b->day;

    return 0; // Nessuno scambio per date uguali cosi mantengo la stabilità
}

int insert_ord(link *head, link p){

    //Lista vuota, inserisco il primo elemento
    if((*head) == NULL){
        (*head) = p;
        p->next = p->prev = NULL;
        return 1;
    }

    link p1;
    link tail = NULL;
    for(p1=*head; p1!=NULL;tail = p1, p1 = p1->next)
        if(check_anzianita(&p1->data,&p->data)){
            // Controlla che il nodo precedente non abbia lo stesso codice
            if (p1->prev != NULL && strcmp(p1->prev->codice, p->codice) == 0) {
                printf("Errore: Nodo con codice '%s' già presente.\n", p->codice);
                free(p);
                return 0;
            }

            // Inserisci il nodo prima di p1
            if (p1->prev != NULL) {
                p->prev = p1->prev;
                p->prev->next = p;
            } else {
                // Aggiorna la testa
                *head = p;
                p->prev = NULL;
            }
            p->next = p1;
            p1->prev = p;
            return 1;
        }
    
    // Se p1 è NULL, significa che il nodo deve essere inserito in coda
    if (tail != NULL && strcmp(tail->codice, p->codice) == 0) {
        // Nodo duplicato
        // printf("Errore: Nodo con codice '%s' già presente.\n", p->codice);
        free(p);
        return 0;
    }

    // Aggiungi il nodo in coda
    tail->next = p;
    p->prev = tail;
    p->next = NULL;

    return 1;
}

int keyboard_insert(link *head) {
    link p = malloc(sizeof(Item));
    if (!p) { printf("malloc fallita\n"); return 0; }

    printf("Inserisci: <codice> <nome> <cognome> gg/mm/aaaa <via> <citta> <cap>\n");
    int scanned = scanf("%50s %50s %50s %d/%d/%d %50s %50s %d",
        p->codice, p->nome, p->cognome,
        &p->data.day, &p->data.month, &p->data.year,
        p->via, p->citta, &p->cap);

    if (scanned != 9 || !check_id(p->codice) || !check_data(p->data)) {
        printf("Errore: input non valido.\n");
        free(p);
        return 0;
    }

    return insert_ord(head, p); // Elemento gia presente
}

void leggiFile(FILE *fin, int *n, link *head){
    int i = *n, err_n = 0;
    link p;

    while((p = malloc(sizeof(Item))) != NULL && fscanf(fin, "%50s %50s %50s %d/%d/%d %50s %50s %d", p->codice, p->nome, p->cognome, 
        &p->data.day, &p->data.month, &p->data.year,p->via, p->citta, &p->cap) == 9){
        if(check_id(p->codice) && check_data(p->data)) i+=insert_ord(head, p); //Aumento se l'elemento non era già presente
        else free(p); //Altrimenti lo elimino (dati non validi)
        err_n++;
    }
    err_n = err_n - i;

    // Controlla se malloc ha fallito
    if (p == NULL) {
        printf("Errore: malloc fallita durante la lettura del file.\n");
    } else {
        // Libera la memoria se fscanf non ha letto correttamente
        free(p);
    }
    
    printf("\nIncontrate %d linee con errori (dati non validi) - Non considerate\n", err_n);
    *n = i;
    fclose(fin);
}

link search_id(link *head, char id[MAX_codice]){
    int found = 0;
    link p = *head;

    while(!found && p != NULL){
        // printf("%s - %s\n",p->codice+1,id+1);
        if(strcmp(p->codice+1,id+1) == 0) found = 1; // Se trovo l'id
        else p = p->next;
    }

    return p;
}

link remove_element(link *head, link element){
    if(element->prev != NULL) 
        element->prev->next = element->next; // Quello dietro va avanti di 1
    else *head = element->next; //Se non puo diventa la testa
    
    if(element->next != NULL)
        element->next->prev = element->prev; // Quello avanti va indietro di 1

    return element;
}

void print_element(link element){
    printf("Id: %s, Nome: %s, Cognome: %s, Data: %02d/%02d/%04d, Via: %s, Città: %s, CAP: %d\n",
           element->codice, element->nome, element->cognome,
           element->data.day, element->data.month, element->data.year,
           element->via, element->citta, element->cap);
}

// Controlla l'anno, controllo se l'anno è uguale e il mese, in caso di anno e mese uguale controllo il giorno
int compare_date(date data1, date data2) {
    return data2.year < data1.year || 
           (data2.year == data1.year && data2.month < data1.month) ||
           (data2.year == data1.year && data2.month == data1.month && data2.day < data1.day);
}

int remove_data(link p, date data1, date data2) {
    if (compare_date(data1, p->data) && compare_date(p->data, data2)) {
        return 1; // Indica che il nodo è compreso tra le due date
    }
    return 0;
}

void print_file(FILE *fout, link *head){
    link p;
    for(p=*head; p!=NULL; p = p->next)
        fprintf(fout,"%s %s %s %02d/%02d/%04d %s %s %d\n",p->codice, p->nome, p->cognome,
           p->data.day, p->data.month, p->data.year,p->via, p->citta, p->cap);
    
}

void free_list(link *head){
    link p = *head, tmp;

    while(p != NULL){
        tmp = p->next;
        free(p);
        p = tmp;
    }

    // *head = NULL; Utile se ho intenzione di riutilizzare la head
}