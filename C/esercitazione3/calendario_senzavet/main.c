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

void calcola_data(int *g1, int *m1, int *a1, int g){

    while( g > max_mese(*m1,*a1)){
        g = g - max_mese(*m1,*a1);
        if (*m1 == 12){
            *m1 = 0; // azzero il mese
            (*a1)++; // aumento l'anno
        }
        (*m1)++; // aumento il mese 
    }
    *g1 = g; //assegno i giorni rimasti

}

int main(void){
    int g1,m1,a1,g2,m2,a2;
    int g;
    printf("Inserire giorno mese e anno in ordine (gg mm aaaa)\n");
    scanf("%d %d %d",&g1,&m1, &a1);
    while(a1 > 2025 || a1 < 1){
        printf("Reinserire l'anno deve essere compreso tra 1 e 2025\n");
        scanf("%d", &a1);
    }
    printf("Data inserita: %d/%d/%d\n",g1,m1,a1);

    printf("Inserire quanti giorni sono passati:\n");
    scanf("%d",&g);

    calcola_data(&g1,&m1,&a1,g+g1);

    printf("Il giorno sara il %d/%d/%d\n",g1,m1,a1);

    return 0;
}