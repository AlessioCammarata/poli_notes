#include <stdio.h>

int main(void){

    char op;
    float val1,val2,result=0;

    printf("Inserisci l'operazione che vuoi fare: (+) (-) (*) (/)\n");
    op = getchar();

    printf("Inserisci il primo operando:\n");
    scanf("%f",&val1);
    printf("Inserisci il secondo operando:\n");
    scanf("%f",&val2);

    switch(op){
        case '+':
            result = val1 + val2;
            break;

        case '-':
            result = val1 - val2;
            break;

        case '*':
            result = val1 * val2;
            break;

        case '/':
            if (val2 != 0)
                result = val1 / val2;
            else
                printf("Non si puo dividere per 0\n");
            break;

        default:
            printf("Operazione non valida");
            return 0;
    }

    printf("%c %.2f",op,result);

}