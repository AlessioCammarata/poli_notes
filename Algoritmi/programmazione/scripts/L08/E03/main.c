/*
 un quasi ADT per la data e uno per l’ora (o un unico ADT per entrambe), implementati come
struct con campi interi per anno, mese e giorno, ore e minuti
 un ADT di I classe per il titolo e uno per collezione di titoli (a scelta se in un solo modulo o in
due). Per la collezione di titoli si faccia uso di una lista ordinata (si usi il codice del titolo come
chiave di ordinamento)
 un quasi ADT per la quotazione giornaliera e un ADT di I classe per collezione di quotazioni
giornaliere (a scelta se in un solo modulo o in due). Per la collezione di quotazioni si faccia uso
di un BST (con data come chiave di ricerca e ordinamento). Per gli inserimenti di dati nel BST
sono sufficienti gli inserimenti in foglia
 un client che fornisca le seguenti funzionalità:
    1. acquisizione del contenuto di un file contenente un insieme di transazioni
    2. ricerca di un titolo azionario (ricerca in lista)
    3. ricerca, dato un titolo precedentemente selezionato, della sua quotazione in una certa data
    (ricerca in un BST)
    4. ricerca, dato un titolo precedentemente selezionato, della sua quotazione minima e
    massima in un certo intervallo di date (si noti che la ricerca, in un BST, di più chiavi
    comprese in un dato intervallo, non è una funzione standard e va quindi realizzata: si
    consiglia una variante di un algoritmo di visita in-order)
    5. ricerca, dato un titolo precedentemente selezionato, della quotazione minima e massima
    lungo tutto il periodo registrato (il problema può essere ricondotto a un caso particolare
    del punto precedente)
    6. dato un titolo precedentemente selezionato, bilanciamento dell'albero di quotazioni se il
    rapporto tra il cammino più lungo e più corto nell'albero supera una certa soglia S.
    Nota: si ricorda che è possibile bilanciare un dato BST mediante applicazione ricorsiva
    del partizionamento rispetto alla chiave mediana. 
*/
#include <stdio.h>
#include <stdlib.h>
#include "DateTime.h"
#include "Titles.h"
#include "DailyQuote.h"

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L08/E03/F3.txt"
#define NMAX 21 //20 + 1

int leggiFile(FILE *fin, TitleCollection_t TC);

int main(void){
    FILE *fin;
    int end = 0, choose;
    char name_title[NMAX];

    if((fin = fopen(nfin,"r")) == NULL){
        perror("Apertura del file");
        return 1;
    }

    TitleCollection_t TC = INITlist();
    if(!TC){
        perror("malloc");
        fclose(fin);
        return 1;
    }
    if(!leggiFile(fin,TC)){
        perror("malloc");
        //Free collection
        freeTC(TC);
        fclose(fin);
        return 1;
    }
    fclose(fin);

    // Inizializzo le variabili
    Title_t title;
    DateTime_t date = malloc(sizeof *date); 
    DateTime_t date1 = malloc(sizeof *date1);
    DateTime_t date2 = malloc(sizeof *date2);
    float min, max;
    while(!end){
        printf("Cosa vuoi fare?\n");
        printf("0. Esci\n");
        printf("1. Ricerca un titolo azionario\n");
        printf("2. Ricerca della quotazione di un titolo in una certa data\n");
        printf("3. Ricerca della quotazione minima e massima di un titolo in un certo intervallo di date\n");
        printf("4. Ricerca della quotazione minima e massima di un titolo lungo tutto il periodo registrato\n");
        printf("5. Bilanciamento dell'albero di quotazioni rispetto una certa soglia S\n");
        
        
        // min e max verranno inizializzati nei case dove servono
        if(scanf("%d",&choose) != 1) end = 1;
        switch(choose){
            case 0:
                end = 1;
                break;
            case 1:
                printf("Inserisci il titolo azionario\n");
                scanf("%20s",name_title);
                
                if(searchTitle(TC,name_title) != NULL) printf("Titolo trovato!\n");
                else printf("Titolo inesistente\n");
                break;
            case 2:
                printf("Inserisci il titolo azionario\n");
                scanf("%20s",name_title);
                
                title = searchTitle(TC,name_title);
                if(title == NULL){
                    printf("Titolo inesistente\n");
                    break;
                }

                printf("Inserire una data specifica: (dd/mm/yyyy)\n"); //Andrebbero messi altri controlli tipo m tra 1 e 12 ecc.
                while(scanf("%d/%d/%d",&date->day,&date->month,&date->year) != 3){
                    printf("Reinserire una data specifica: (dd/mm/yyyy)\n");
                }

                float val = getDQfromDate(title, date);
                if(val != -1) printf("La daily quote nella data %d/%d/%d, ha valore: %.2f\n",date->day,date->month,date->year,val);
                else printf("Nessuna DQ relativa alla data inserita\n");

                break;
            case 3:
                printf("Inserisci il titolo azionario\n");
                scanf("%20s",name_title);
                
                title = searchTitle(TC,name_title);
                if(title == NULL){
                    printf("Titolo inesistente\n");
                    break;
                }

                if (!date1) { printf("Errore malloc date1 (case 3)\n"); break; }
                printf("Inserire una data specifica: (dd/mm/yyyy)\n");
                while(scanf("%d/%d/%d",&date1->day,&date1->month,&date1->year) != 3){
                    printf("Reinserire una data specifica: (dd/mm/yyyy)\n");
                }

                if (!date2) { printf("Errore malloc date2 (case 3)\n"); free(date1); break; }
                printf("Inserire una data specifica: (dd/mm/yyyy)\n");
                while(scanf("%d/%d/%d",&date2->day,&date2->month,&date2->year) != 3){
                    printf("Reinserire una data specifica: (dd/mm/yyyy)\n");
                }
                if(cmpDate(date1,date2) > 0){
                    DateTime_t switcher = date2;
                    date2 = date1;
                    date1 = switcher;
                }
                printf("Intervallo: %d/%d/%d - %d/%d/%d\n",date1->day,date1->month,date1->year,date2->day,date2->month,date2->year);


                min = 1e9;
                max = -1e9;
                getDQfromDates(title,date1,date2,&min,&max);
                if(min != 1e9){
                    printf("Il valore minimo nell'intervallo è: %.2f\n",min);
                    printf("Il valore massimo nell'intervallo è: %.2f\n",max);

                }else printf("Non c'è nessun elemento in questo periodo\n");
                
                break;
            case 4:
                printf("Inserisci il titolo azionario\n");
                scanf("%20s",name_title);
                
                title = searchTitle(TC,name_title);
                if(title == NULL){
                    printf("Titolo inesistente\n");
                    break;
                }

                date1->day = 0;
                date1->month = 0;
                date1->year = 0;

                date2->day = 32;
                date2->month = 13;
                date2->year = 3000;

                min = 1e9;
                max = -1e9;
                getDQfromDates(title,date1,date2,&min,&max);
                printf("Il valore minimo toccato è: %.2f\n",min);
                printf("Il valore massimo toccato è: %.2f\n",max);
                break;
            case 5:
                int threshold;
                printf("Inserisci il titolo azionario\n");
                scanf("%20s",name_title);
                
                title = searchTitle(TC,name_title);
                if(title == NULL){
                    printf("Titolo inesistente\n");
                    break;
                }

                printf("Inserire la soglai del bilanciamento\n");
                scanf("%d",&threshold);

                balanceQuotes(title,threshold);
                printf("Bilanciamento effettuato!");
                break;
            default:
                printf("Scelta non valida\n"); 
        }
        printf("\n");
    }

    free(date); free(date1); free(date2);
    freeTC(TC);
    return 0;
}

int leggiFile(FILE *fin, TitleCollection_t TC){
    int n, m, quantity;
    float value;
    char *title;
    if(fscanf(fin,"%d",&n) != 1) return 0;

    for(int i = 0; i<n; i++){
        title = malloc(NMAX*sizeof *title);
        if(fscanf(fin,"%s %d",title,&m) != 2){ 
            //Free   
            return 0;
        }

        Title_t t = addTitle(TC, title);
        DailyQuoteCollection_t BST = getCollection(t);
        for(int j = 0; j<m; j++){
            DateTime_t day = malloc(sizeof *day);
            if(!day){
                return 0;
            }
            if(fscanf(fin,"%d/%d/%d %d:%d %f %d",&day->year,&day->month,
                            &day->day,&day->hour,&day->minute,
                            &value,&quantity) != 7){
                //Free
                return 0;
            }
            //Aggiungi valori al titolo
            insertQuoteInBST(BST, day, value, quantity);
        }
    }

    return 1;
}
