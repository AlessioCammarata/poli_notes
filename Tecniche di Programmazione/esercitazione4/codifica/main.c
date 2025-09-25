#include <stdio.h>
// #define nfin "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/codifica/message.txt"
// #define nfout "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/codifica/risposta.txt"
// #define ndefin "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/codifica/risposta.txt"
// #define ndefout "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/codifica/messageT.txt"
#define nfin "./message.txt"
#define nfout "./risposta.txt"
#define ndefin "./risposta.txt"
#define ndefout "./messageT.txt"

int codifica(FILE *fin, FILE *fout);
int decodifica(FILE *fin, FILE *fout);

int main(void){
    FILE *fin,*fout,*defin,*defout;
    char *n_fin,*n_fout;

    // printf("Inserisci il nome del file di input:\n");
    // scanf("%s",nfin);

    // printf("Inserisci il nome del file di output:\n");
    // scanf("%s",nfout);

    if((fin = fopen(nfin,"r")) == NULL){
        printf("Errore in apertura del file");
    }

    if((fout = fopen(nfout,"w")) == NULL){
        printf("Errore in apertura del file");
    }

    int cod = codifica(fin,fout);

    if(cod == 0){
        printf("Errore nella codifica\n");
    }

    fclose(fin);
    fclose(fout);

    if((defin = fopen(ndefin,"r")) == NULL){
        printf("Errore in apertura del file");
    }

    if((defout = fopen(ndefout,"w")) == NULL){
        printf("Errore in apertura del file");
    }

    int decod = decodifica(fin,fout);

    if(decod == 0){
        printf("Errore nella codifica\n");
    }

    fclose(defin);
    fclose(defout);

    return 0;
}

int codifica(FILE *fin, FILE *fout){
    char car1,car = ' ';
    int k = 0,pos,h,char_counter = 0;

    while(fscanf(fin,"%c",&car1) == 1){
        if (car1 >= '0' && car1 <= '9') {

            pos = car1 - '0' + k;
            fprintf(fout,"%d",pos%10);
            k++;
            char_counter++;

        }else if((car1 >= 'A' && car1 <= 'Z') || (car1 >= 'a' && car1 <= 'z')){
            
            if (char_counter > 0 && ((car >= 'A' && car <= 'Z') || (car >= 'a' && car <= 'z'))) {
                if ((car >= 'A' && car <= 'Z') ) {
                    h = car - 'A';

                }else if((car >= 'a' && car <= 'z')){
                    h = car - 'a';

                }
                if ((car1 >= 'A' && car1 <= 'Z') ) {
                    car1 = ((car1 - 'A' + h) % 26) + 'A';
    
                }else if((car1 >= 'a' && car1 <= 'z')){
                    car1 = ((car1 - 'a' + h) % 26) + 'a';
    
                }
            }

            fprintf(fout, "%c", car1);
            char_counter++;
        }else{
            fprintf(fout,"%c",car1);
            char_counter++;
        }

        car = car1;
       
    }
    return char_counter;
}

int decodifica(FILE *fin, FILE *fout){
    char car1,ncar = ' ',car = ' ';
    int k = 0,pos,h,char_counter = 0;

    while(fscanf(fin,"%c",&car1) == 1){
        if (car1 >= '0' && car1 <= '9') {

            pos = car1 - '0' - k;
            
            fprintf(fout,"%d",(pos%10+10)%10); //mi assicuro che sia positivo
            k++;
            char_counter++;

        }else if((car1 >= 'A' && car1 <= 'Z') || (car1 >= 'a' && car1 <= 'z')){
            
            if (char_counter > 0 && ((car >= 'A' && car <= 'Z') || (car >= 'a' && car <= 'z'))) {
                // car precedente è maiuscolo
                if ((car >= 'A' && car <= 'Z') ) {
                    h = car - 'A';

                }else if((car >= 'a' && car <= 'z')){
                    h = car - 'a';

                }
                // car è maiuscolo
                if ((car1 >= 'A' && car1 <= 'Z') ) {
                    ncar = ((car1 - 'A' - h +26)%26) + 'A';
    
                }else if((car1 >= 'a' && car1 <= 'z')){
                    ncar = ((car1 - 'a' - h + 26) %26) + 'a';
                    
                }
            }
            if(ncar == ' ') ncar = car1;
            fprintf(fout, "%c", ncar);
            
            char_counter++;
        }else{
            fprintf(fout,"%c",car1);
            char_counter++;
        }

        car = car1;
        ncar = ' ';
    }
    return char_counter;

}