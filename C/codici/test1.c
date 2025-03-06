#include <stdio.h>
#include <string.h>

// float const PI = 3.14;
#define PI 3.14

int main(void)
{
    char str[20];
    float val,result = 0;
    char answer;
    printf("Di cosa si vuole calcolare l'area? Quadrato (Q) o Cerchio (C):\n");
    scanf(" %c", &answer);

    switch(answer){
        case 'C':
            printf("Vuoi calcolarlo tramite il raggio(R) o il diametro(D)?\n");
            scanf(" %c", &answer);

            printf("Inserire il valore relativo alla lunghezza scelta, %c:\n",answer);
            scanf("%f", &val);

            switch (answer){
                case 'D':
                    result = PI*val*val/4;
                    break;
                
                case 'R':
                    
                    result = PI*val*val;
                    break;

                default:
                    printf("Scelta non valida.\n");
                    return 0;
            }
            
            strcpy(str, "Area Cerchio");
            break;
        
        case 'Q':
            printf("Vuoi calcolarlo tramite il Lato (L) o la diagonale(D)?");
            scanf(" %c", &answer);

            printf("Inserire il valore relativo alla lunghezza scelta, %c:\n",answer);
            scanf("%f", &val);

            switch (answer){
                case 'L':

                    result = val*val;
                    break;
                
                case 'D':

                    result = val*val/2;
                    break;

                default:
                    printf("Scelta non valida.\n");
                    return 0;
            }
            strcpy(str, "Area Quadrato");
            break;

        default:
            printf("Scelta non valida.\n");
            return 0;

    }

    printf("%s: %.1f",str,result);


    
    return 0;
}
