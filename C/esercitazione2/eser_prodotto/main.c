#include <stdio.h>
// #include <string.h>

// int main(void){
//     int n1,n2,p,even = 0,odd = 0;
//     char prod[20];

//     printf("Inserire due numeri interi:\n");
//     scanf("%d %d",&n1,&n2);

//     p = n1*n2;
//     printf("Prodotto: %d\n",p);

//     sprintf(prod, "%d", p);

//     for(int i=0;i<strlen(prod);i++){
//         if(prod[i]%2 == 0)
//             even++;
//         else odd++;
//     }

//     printf("Il prodotto necessita di %d cifre decimali, di cui %d pari e %d dispari.\n",strlen(prod),even,odd);

//     return 0;
// }

int main() {
    int X, Y, P, even = 0, odd = 0, digit_count = 0;
    
    // Input dei due numeri
    printf("Inserire due numeri interi:\n");
    scanf("%d %d", &X, &Y);

    // Calcolo del prodotto
    P = X * Y;
    printf("Prodotto: %d\n", P);

    // Contare cifre pari, dispari e il numero totale di cifre
    int temp = (P < 0) ? -P : P;  // Consideriamo solo il valore assoluto

    if (temp == 0) {
        digit_count = 1;
        even = 1;  // 0 è considerato pari
    } else {
        while (temp > 0) {
            int digit = temp % 10;  // Estrai l'ultima cifra
            if (digit % 2 == 0)
                even++;
            else
                odd++;
            digit_count++;
            temp /= 10;  // Rimuovi l'ultima cifra
        }
    }

    // Stampiamo i risultati
    printf("Numero di cifre: %d\n", digit_count);
    printf("Cifre pari: %d\n", even);
    printf("Cifre dispari: %d\n", odd);

    return 0;
}
