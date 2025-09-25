/*
Un file (sorgente.txt) contiene un testo composto da un numero indefinito di righe, di lunghezza
massima 200 caratteri ognuna. Un secondo file (dizionario.txt) contiene un elenco di coppie di
stringhe. Il file dizionario.txt è organizzato come segue:
• sulla prima riga è presente un numero intero e positivo S (≤ 30), che indica il numero di possibili
ricodifiche (sostituzioni) presenti nel dizionario
• seguono S coppie <ricodifica><originale> a rappresentare le sostituzioni possibili. Ogni
sostituzione <compresso> è nella forma $<intero>$
Lo scopo del programma è di ricodificare il primo file di testo andando a sostituire sequenze di caratteri
sulla base dei contenuti del secondo file. In caso di più sostituzioni possibili per una certa sottostringa,
il programma scelga la prima sostituzione trovata. Il risultato della ricodifica sia salvato su un terzo file
(ricodificato.txt).
*/

#include <stdio.h>
#include <string.h>
#define nfin "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione6/ricodifica_dizionario/sorgente.txt"
#define nfin2 "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione6/ricodifica_dizionario/dizionario.txt"
#define nfout "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione6/ricodifica_dizionario/ricodificato.txt"
#define Rmax 200
#define Smax 30
// #define nfin "./sorgente.txt"
// #define nfin2 "./dizionario.txt"

typedef struct 
{
    char nome1[50], nome2[50];
}compare;

void leggiFile(FILE *fin, int row, compare vet[row]);
void sostituisci(FILE *fin, FILE *fout, int row, compare vet[row]);

int main(void) {
    int row;
    FILE *fin, *fin2, *fout;

    if ((fin = fopen(nfin, "r")) == NULL ||
        (fin2 = fopen(nfin2, "r")) == NULL ||
        (fout = fopen(nfout, "w")) == NULL) {
        printf("Errore nell'apertura di uno dei file\n");
        return 1;
    }

    fscanf(fin2, "%d", &row);
    compare vet[row];
    leggiFile(fin2, row, vet);
    sostituisci(fin, fout, row, vet);

    fclose(fin);
    fclose(fin2);
    fclose(fout);
    return 0;
}

void leggiFile(FILE *fin, int row, compare vet[row]) {
    for (int i = 0; i < row; i++) {
        fscanf(fin, "%s %s", vet[i].nome1, vet[i].nome2);
    }
}

void sostituisci(FILE *fin, FILE *fout, int row, compare vet[row]) {
    char riga[Rmax];

    while (fgets(riga, Rmax, fin) != NULL) {
        int i = 0;
        char *p = riga;

        while (*p != '\0' && *p != '\n'){
            int trovato = 0;
            
            for(int j=0;j<row;j++){
                char *pos = strstr(p, vet[j].nome2);
                if (pos == p) {
                    // Se la parola trovata è in testa alla stringa corrente
                    fprintf(fout, "%s", vet[j].nome1); // stampa la codifica
                    p += strlen(vet[j].nome2); // salta oltre la parola trovata
                    trovato = 1;
                    break;
                }
            }

            if (!trovato) {
                fputc(*p, fout);
                p++;
            }
        }

        fprintf(fout, "\n");
    }
}