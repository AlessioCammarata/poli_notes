#include <stdio.h>

int bisestile(int anno){
    return (anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0);
}

int max_mese(int mese, int anno){
    int max;

    if (mese != 2) {  // Se non è febbraio
        if (mese == 4 || mese == 6 || mese == 9 || mese == 11) {
            max = 30;  // Settembre, Aprile, Giugno e Novembre hanno 30 giorni
        } else {
            max = 31;  // Gli altri mesi hanno 31 giorni
        }
    } else {  // Se è febbraio
        if (bisestile(anno)) {
            max = 29;  // Anno bisestile
        } else {
            max = 28;  // Anno non bisestile
        }
    }

    return max;
}

int* calcola_data(int d1[3], int g){
    static int d2[3];  // Array statico per restituirlo

    // Copia la data iniziale in d2
    d2[0] = d1[0];
    d2[1] = d1[1];
    d2[2] = d1[2];

    while( g > max_mese(d2[1],d2[2])){
        g = g - max_mese(d2[1],d2[2]);
        if (d2[1] == 12){
            d2[1] = 0;
            d2[2]++;
        }
        d2[1]++;
        
    }
    d2[0] = g;

    return d2;
}

int main(void){
    int d1[3];
    int g;
    printf("Inserire giorno mese e anno in ordine (gg mm aaaa)\n");
    scanf("%d %d %d",&d1[0],&d1[1], &d1[2]);

    printf("Inserire quanti giorni sono passati:\n");
    scanf("%d",&g);

    int *d2 = calcola_data(d1,g);

    printf("Il giorno sara il %d/%d/%d",d2[0],d2[1],d2[2]);

    return 0;
}