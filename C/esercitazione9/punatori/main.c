/*
Si realizzi una funzione che permetta di visualizzare la codifica interna (binaria) di un numero reale,
realizzato, in C da un float o double
Premessa: i tipi C float e double (se ne veda, ad esempio, la definizione su
https://en.wikipedia.org/wiki/C_data_types) realizzano le specifiche IEEE-754
(https://it.wikipedia.org/wiki/IEEE_754) per i tipi di dato reali in precisione singola e doppia.
Il programma C:
• usa 2 variabili per numeri reali (af, ad, rispettivamente di tipo float e double)
• determina (utilizzando un numero intero, a scelta del programmatore) se il calcolatore utilizza la
codifica little endian o big endian e assegna di conseguenza il valore vero o falso (come intero)
a una variabile bigEndian
• visualizza (mediante l'operatore C sizeof) la dimensione (espressa in byte e in bit) delle due
variabili af, ad
• acquisisce da tastiera un numero decimale (con virgola ed eventuale esponente in base 10),
assegnandolo alle due variabili af, ad
• mediante la funzione stampaCodifica visualizza la rappresentazione interna del numero
nelle due variabili af, ad.
La funzione stampaCodifica, avente prototipo:
void stampaCodifica (void *p, int size, int bigEndian);
va chiamata due volte, ricevendo come parametri, rispettivamente il puntatore a una della due variabili (convertito a void *) e la dimensione della variabile:
stampaCodifica((void *)&af,sizeof(af),bigEndian);
stampaCodifica((void *)&ad,sizeof(ad),bigEndian);
La funzione stampaCodifica, utilizzando l'aritmetica dei puntatori, la conoscenza del tipo di
codifica e la dimensione ricevuta come parametro, deve stampare il bit di segno, i bit di esponente e
i bit di mantissa del numero.
*/

#include <stdio.h>

int isBigEndian();
void stampaCodifica(void *p, int size, int bigEndian);

int main(void){
    float af; //Numero reale in precisione singola -> 32-1|8|23
    double ad; //Numero reale in precisione doppia -> 64-1|11|52
    int bigEndian = isBigEndian();
    printf(bigEndian ? "Big endian" : "Little endian");

    printf("\nInserire un valore reale:\n");
    scanf("%lf", &ad); // per double
    af = (float)ad;    // cast implicito per il float

    stampaCodifica((void *)&af,sizeof(af),bigEndian);
    stampaCodifica((void *)&ad,sizeof(ad),bigEndian);

    return 0;
}

//Controllo, per vedere se il MSB sta all'inizio o alla fine
int isBigEndian() {
    unsigned int x = 1; // 0x00000001
    return *((char *)&x) == 0; // Prendo l’indirizzo di x e lo casto a char*, cioè a puntatore a singolo byte. - con * esterno accedo al primo byte
}

void stampaCodifica(void *p, int size, int bigEndian){
    unsigned char *vet = (unsigned char *)p;

    // Ordine dei byte
    if (!bigEndian) {
        // Little endian → stampa byte dal più "alto" al più "basso"
        for (int i = size - 1; i >= 0; i--) {
            for (int bit = 7; bit >= 0; bit--) {
                printf("%d", (vet[i] >> bit) & 1);
            }
        }
    } else {
        // Big endian → stampa da byte 0 a byte N-1
        for (int i = 0; i < size; i++) {
            for (int bit = 7; bit >= 0; bit--) {
                printf("%d", (vet[i] >> bit) & 1);
            }
        }
    }

    printf("\n");
}