/*
Funziona, ma dovrebbe essere piu pulito, soprattutto per l'utilizzo delle flag.
*/

#include <stdio.h>
#define filein "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/verifica_espressioni/espr.txt" 

int operando(char c){
    return c== '+' || c == '-' || c == '*' || c == '/' || c == '%';
}
int controlla_riga(char *str){
    /*
    n -> Operando valido
    op -> Operazione
    c -> contatore parentesi
    p -> controllo parentesi chiusa
    */
    int i=0,n=0,space=0,c=0,op=0,p=0;

    while(str[i] != '\0' && c>=0){

        if (str[i] == '(') {
            if(p) c= -1;
            c++;
            if (n) c = -1;  // Errore: un numero non può essere seguito da '(' senza operatore
            op = 0;  
            n = 0;
        } 
        else if (str[i] == ')') {
            c--;
            if (op || c < 0) c = -1;  // Errore: parentesi chiusa dopo un operatore o sbilanciata
            n = 1;  // Una parentesi chiusa è considerata un operando valido
            p=1;
        } 
        else if (str[i] >= '0' && str[i] <= '9'){
            if(space || p) c = -1;
            else{
                if (str[i+1] == ' ') space=1;
                else space = 0;
            }

            if(op) op = 0;
            n=1;
        }else if(operando(str[i])){
            if (op || n == 0) c = -1;  // Errore: due operatori consecutivi o operatore senza operando prima
            op = 1;
            space = 0;
            n = 0;
            p=0;
        }


        i++;
    }
    if (op) c = -1;
    return c==0;
}

int main(void){
    FILE *fin;
    int ok,n=1;
    char buffer[100];  
    
    if ((fin = fopen(filein,"r")) == NULL){
        printf("Errore nell'apertura del file\n");
        return 1;
    }

    while(fgets(buffer, sizeof(buffer), fin) != NULL){
        ok = controlla_riga(buffer);
        printf("%d\n",ok);
        if(ok == 0) printf("Errore nell'espressione %d\n",n);
        n++;
    }

    fclose(fin);
    return 0;

}