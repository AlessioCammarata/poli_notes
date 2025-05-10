/*
Si scriva un programma in grado di localizzare, all’interno di un generico testo, le occorrenze di ogni
parola che contiene una certa sequenza di caratteri. Le “parole” (nel testo) contengono unicamente
caratteri alfanumerici (identificati dalla funzione isalnum di ctype.h), più parole sono separate
da spazi o segni di punteggiatura (identificati dalle funzioni isspace e ispunct).
Il programma riceve in input:
• il file sequenze.txt: sulla prima riga contiene il numero totale di sequenze, al più 20, sulle
righe successive, una per riga, le sequenze da ricercare. La lunghezza delle singole sequenze è
limitata a massimo 5 caratteri. Si trascuri la differenza tra maiuscole e minuscole
• il file testo.txt: contiene il testo. Il numero di righe non è noto a priori. Si assuma che la
lunghezza di ogni riga sia al più pari a 200 caratteri. Si assuma inoltre che nessuna parola del
testo sia più lunga di 25 caratteri.
Il programma deve visualizzare, per ognuna delle “sequenze”, quali parole la contengono e dove si
trovano nel file. La posizione delle parole viene data contando le parole stesse a partire dall'inizio
del testo (si usi 1 per la prima parole, 2 per la seconda e così via). Ai fini dell'esercizio ci si limiti a
identificare e visualizzare solamente le prime 10 occorrenze per ogni sequenza.
*/

//VERSIONE CHE NON CONSIDERA GLI APOSTROFI

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define nfin "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione7/occorrenze_parole/sequenze.txt"
#define nfin1 "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione7/occorrenze_parole/testo.txt"
// #define nfin "./sequenze.txt"
// #define nfin1 "./testo.txt"
#define maxRIGA 200
#define maxWORD 25
#define maxNseq 20
#define maxSEQ 5
#define outputS 1000
#define maxOCC 10

void leggiFile(FILE *fin, char seq[][maxSEQ]);
// void leggiTesto(FILE *fin, char text[][maxWORD]);

int cercaParola(FILE *fin, char word[maxSEQ], char output[outputS]);

int main(void){
    FILE *fin,*fin1;
    int n;

    if((fin = fopen(nfin,"r")) == NULL || (fin1 = fopen(nfin1,"r")) == NULL){
        printf("Errore nell'apertura di uno dei due file\n");
        return 1;
    }

    fscanf(fin,"%d",&n);
    if(n>maxNseq) n=maxNseq;
    char seq[n][maxSEQ], output[outputS] = "";
    int find = 0;

    leggiFile(fin, seq);

    for(int i=0; i<n; i++){
        printf("--------------------------------------\n");
        printf("Analizzando %s\n\n",seq[i]);
        find = cercaParola(fin1,seq[i],output);
        rewind(fin1);
        if(!find) printf("Sequenza non trovata");
        else printf("%s",output);

        printf("\n");
    }

    fclose(fin);
    fclose(fin1);
    return 0;
}

void leggiFile(FILE *fin, char seq[][maxSEQ]){
    int i=0;
    while(fscanf(fin,"%s",seq[i]) == 1){
        i++;
    }
}

int cercaParola(FILE *fin, char word[maxSEQ], char output[outputS]){

    int i=0,f=0,c,len=strlen(word);
    char act_word[maxWORD + 1];
    sprintf(output, "La sequenza %s è contenuta in: ", word);

    // Leggo il file dall'inizio alla fine
    while(fscanf(fin,"%s",act_word) == 1 && f < maxOCC){
        i++;
        // printf("%s -- %s _%d\n",word,act_word,i); //DEBUG
        int len_word = strlen(act_word),match = 0;

        for(int j = 0; j< len_word && !match;j++){
            // Controlliamo se c'è una corrispondenza
            for(c = 0; tolower(word[c]) == tolower(act_word[j+c]);c++);
            if (c == len){
                // printf("MATCH\n\n"); // DEBUG
                match++;
                f++;
                //Concateno la stringa temporanea all'output.
                char temp[maxWORD + 50];
                if (f == 1) sprintf(temp, "%s (posizione %d)", act_word, i);
                else sprintf(temp, ", %s (posizione %d)", act_word, i);
                strcat(output, temp);
            }
        }
        
    }

    return f;
}   
