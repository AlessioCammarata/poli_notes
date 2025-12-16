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

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L08/E03/F1.txt"
#define NMAX 21 //20 + 1

int leggiFile(FILE *fin, TitleCollection_t TC);

int main(void){
    FILE *fin;
    int end = 0, choose;

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
    if(leggiFile(fin,TC)){
        perror("malloc");
        //Free collection
        freeTC(TC);
        fclose(fin);
        return 1;
    }
    fclose(fin);

    while(!end){
        printf("Cosa vuoi fare?\n");
        printf("0. Esci\n");
        printf("1. Stampa in ordine\n");
        printf("2. Verifica adiacenza a coppie\n");
        printf("3. Genera le liste di adiacenza\n");
        scanf("%d",&choose);
        
    }

    freeTC(TC);
    return 0;
}

int leggiFile(FILE *fin, TitleCollection_t TC){
    int n, m, quantity;
    float value;
    char title[NMAX];
    if(fscanf(fin,"%d",&n) != 1) return 0;

    for(int i = 0; i<n; i++){
        if(fscanf(fin,"%s %d",title,&m) != 1){ 
            //Free   
            return 0;
        }
        Title_t t = addTitle(TC, title);
        DailyQuoteCollection_t BST = getCollection(t);
        for(int j = 0; j<m; j++){
            DateTime_t day = malloc(sizeof *day);
            if(!day){

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