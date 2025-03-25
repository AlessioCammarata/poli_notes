#include <stdio.h>

int comprimi(FILE *fin, FILE *fout);
int decomprimi(FILE *fin, FILE *fout);

int main(void){
    FILE *fin, *fout, *finy, *fouty;

    if((fin = fopen("C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/zipe_cod/message.txt","r"))==NULL){
        printf("Errore in apertura del file");
    }

    if((fout = fopen("C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/zipe_cod/risposta.txt","w"))==NULL){
        printf("Errore in apertura del file");
    }
    int result = comprimi(fin,fout);
    
    fclose(fin);
    fclose(fout);

    if((fouty = fopen("C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/zipe_cod/messageT.txt","w"))==NULL){
        printf("Errore in apertura del file");
    }

    if((finy = fopen("C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/zipe_cod/risposta.txt","r"))==NULL){
        printf("Errore in apertura del file");
    }

    int dec = decomprimi(finy, fouty);

    fclose(finy);
    fclose(fouty);

    return 0;
}

int comprimi(FILE *fin, FILE *fout){
    char car1,car2,scar;
    int counter = 0,n = 0,flag = 1;

    if (fscanf(fin,"%c",&car1) == 1 ) fprintf(fout,"%c",car1);
    n++;
    while(fscanf(fin,"%c",&car2) == 1 && flag){
        if (car1 == car2 && counter<9){
            counter++;

        } else{ 
            scar = car1;
            car1 = car2;

            if (counter < 1) {
                fprintf(fout,"%c",car1);

            }else if(counter == 1){
                fprintf(fout,"%c%c",scar,car1);
            }else{
                fprintf(fout,"$%d%c",counter,car1);
            }


            counter = 0;
        }
        n++;
        if (car2 == '$'){
            flag = 0;
            n = 0;
        }
    }

    if (counter > 1){
        fprintf(fout,"$%d",counter,car1);
    }

    return n;
}

int decomprimi(FILE *fin, FILE *fout){
    char car1,car2;
    int num;

    fscanf(fin,"%c",&car1);
    while(fscanf(fin,"%c",&car2) == 1){
        if (car2 != '$'){
            fprintf(fout,"%c",car1);
            printf("%c",car1);
            car1 = car2;
        }else{
            fscanf(fin,"%1d",&num);

            for(int i = 0;i<num+1;i++){
                fprintf(fout,"%c",car1);
            }
            fscanf(fin,"%c",&car1);
        }
        
    }
}