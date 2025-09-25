#include <stdio.h>
#define fileout "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/formattatat/testo.txt"
#define filein "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/formattatat/input.txt"

int is_point(char c){
    return c == '.' || c == ',' || c == ';' || c == ':' || c == '!' || c == '?' || c == '\'' || c == '(' || c== ')';
}

void converti(FILE *fin, FILE *fout){
    char car,car1;
    int flag = 0,col = 0,ecol;

    while(fscanf(fin,"%c",&car) == 1){
        
        if(car >= '0' && car <= '9'){
            car = '*';
            col++;
            fprintf(fout,"%c",car);
        }else if(is_point(car)){
            if(fscanf(fin,"%c",&car1) == 1){
                //Controllo se è gia uno spazio o no
                if (car1 != ' ' ){
                    // Controllo se quella dopo e una lettera minuscola e quello prima è un punto
                    if(car1 >= 'a' && car1 <= 'z' && (car == '.' || car == '!' || car == '?')){
                        car1 = car1- 'a' + 'A';
                    }

                    if(car1 == '\n'){
                        fprintf(fout,"%c ",car);
                        car = '\n';
                        col--;
                    } else fprintf(fout,"%c %c",car,car1);

                    col=col +3;
                }else{
                    fprintf(fout,"%c%c",car,car1);
                    col=col +2;
                }

            }else{
                fprintf(fout,"%c",car);
                col++;
            }
            
        }else if(car != '\n'){
            fprintf(fout,"%c",car);
            col++;
        }
        
        if (car == '\n'){
            ecol = col;
            while (ecol<25){
                fprintf(fout," ");
                ecol++;
            }
            col++;
        }
        if (col == 25 || car == '\n'){
            fprintf(fout,"| c:%d\n",col);
            col = 0;
        }
        
    }
    ecol = col;
    while (ecol<25){
        fprintf(fout," ");
        ecol++;
    }
    col++;
    fprintf(fout,"| c:%d\n",col);

}

int main(void){
    FILE *fin,*fout;

    if((fin = fopen(filein,"r")) == NULL){
        printf("Errore in apertura del file\n");
    }

    if((fout = fopen(fileout,"w")) == NULL){
        printf("Errore in apertura del file\n");
    }

    converti(fin,fout);

    fclose(fin);
    fclose(fout);
    return 0;

}