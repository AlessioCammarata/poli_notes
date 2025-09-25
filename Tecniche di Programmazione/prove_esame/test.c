#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXC 100
#define MAXL 30


typedef struct {
    char nome[MAXL]; 
    int prezzo_medio; 
    int notti_persona;
} citta;

void stampa(citta *elP[], int n) {
 int i;
 for (i=0; i<n; i++) {
    printf("citta: %s, prezzo medio a persona/notte: %d, notti_persona: %d\n", elP[i]->nome, elP[i]->prezzo_medio, elP[i]->notti_persona);
 }
}

// Funzione di confronto da usare con qsort
// int comparaCittaPerNome(const void *a, const void *b) {
//     const citta * const *pa = (const citta **)a;
//     const citta * const *pb = (const citta **)b;
//     return strcmp((*pa)->nome, (*pb)->nome);
// }


int leggi(citta elenco[MAXC], int n, char *f_name){
    FILE *fin;
    int i,j,m = 0, nights, people, price, trovato;
    char city[MAXL];
    int costo_totale[n], tot_notti_persona[n];

    fin = fopen(f_name, "r");
    if (fin == NULL) {
        return -1;
    }

    while (fscanf(fin, "%s %d %d %d", city, &nights, &people, &price) == 4) {

        // Cerca se la città è già presente
        trovato = 0;
        for (i = 0; i < m; i++) {
            if (strcmp(elenco[i].nome, city) == 0) {
                // Aggiorna i dati esistenti
                tot_notti_persona[i] += nights * people;
                costo_totale[i] += price * nights;
                trovato = 1;
                break;
            }
        }
        if (!trovato) {
            // Nuova città
            if (m >= n) break; // controllo dimensione array
            strcpy(elenco[m].nome, city);
            tot_notti_persona[m] = nights * people;
            costo_totale[m] = price * nights;
            m++;
        }
    }
    fclose(fin);

    // Calcola prezzo medio per ogni città
    for (i = 0; i < m; i++) {
        elenco[i].notti_persona = tot_notti_persona[i];
        elenco[i].prezzo_medio = (int)round((double)costo_totale[i] / tot_notti_persona[i]);
        
    }

    return m; // numero di città lette

}

/*
Dato l’elenco totale delle città, seleziona quelle con prezzo medio di pernottamento a notte e persona maggiore o uguale al parametro th, ottenuto a partire dal secondo
argomento sulla linea di comando. 
I puntatori alle struct selezionate vanno accumulati nel vettore di puntatori elP e ordinati per nomi in ordine crescente, mentre 
il numero di città selezionate viene ritornato come risultato e assegnato alla variabile num.
*/
int selectByPriceSorted(citta elenco[MAXC], int n, citta *elP[MAXC], int th){
    int num = 0,v;
    citta *temp;

    for (int i =0; i<n ; i++){
        if(elenco[i].prezzo_medio >= th){
            elP[num++] = &elenco[i];
        }
    }

    for(int i = 0; i<num; i++){
        for(int j = i+1; j<num;j++){
            if (strcmp(elP[i]->nome,elP[j]->nome) > 0){
                temp = elP[j];
                elP[j] = elP[i];
                elP[i] = temp;
            }
        }
    }
    // qsort(elP,num,sizeof(citta *),comparaCittaPerNome);

    return num;
}

int main (int argc, char *argv[]) {
    citta elenco[MAXC], *elP[MAXC];
    int th = atoi(argv[2]);
    int n = leggi(elenco, MAXC, argv[1]);
    int num = selectByPriceSorted(elenco, n, elP, th);
    stampa(elP,num);
    return 0;
}
