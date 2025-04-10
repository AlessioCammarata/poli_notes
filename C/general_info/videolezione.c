// avvio il programma con m2m -l a.txt a_minuscolo.txt - argomenti al main
/*
    -l -> |'-'|'l'|'\0'| -> 3 caratteri,  argv[1][0],argv[1][1],argv[1][2] |-> poichè sono contenuti all'interno del vettore argv.

int main(int argc, char *argv[]){
    
    Bla bla bla
    
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 7

typedef struct {
    int eta;
    char *nome;
} persona;

typedef enum {
    a_cerca,a_stampa,a_chiudi,a_err
} azione;

azione leggiComando (void) {
    azione c;
    char cmd[MAXL];
    char tabella[a_err][7] = {
        "cerca","stampa","chiudi"
    };
    printf("comando (cerca");
    printf("/stampa/chiudi): ");
    scanf("%s",cmd); 
    c=a_cerca;
    while(c<a_err && strcmp(cmd,tabella[c])!=0)
        c++;
    return (c);
}

int main(void){
    
    persona persona;
    azione act;

    printf("Inserire nome di una persona\n");
    scanf("%s",persona.nome);

    printf("Inserire l'eta\n");
    scanf("%d",&persona.eta);

    act = leggiComando();
    switch (act)
    {
    case a_cerca:
        printf("Funzione disabilitata");
        break;
    case a_stampa:
        printf("La persona è %s di %d anni",persona.nome,persona.eta);
        break;
    case a_chiudi:
        printf("Ok chiuso\n");
        break;
    
    case a_err:
    default:
        printf("ERRORE\n");
        break;
    }

    return 0;
}
