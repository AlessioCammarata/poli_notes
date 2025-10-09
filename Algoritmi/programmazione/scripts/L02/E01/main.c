#include <stdio.h>

int gcd(int x, int y);

int main(){
    int x, y;

    printf("Inserire coppie di numeri per calcolare il GCD (terminare con due numeri negativi):\n");
    while(scanf("%d %d", &x, &y) == 2){
        if(x < 0 || y < 0) break;
        printf("GCD(%d,%d) = %d\n", x, y, gcd(x,y));
        printf("----\n");
        printf("Inserisci un'altra coppia di numeri (termina con due numeri negativi):\n");
    }

    return 0;
}

int gcd(int x, int y) { 
	if(x == y) 
		return x; 
	if (x>y)
        if(x%2 == 0 && y%2 == 0) // entrambi pari
            return 2*gcd(x/2, y/2);
        else if(x%2 != 0 && y%2 == 0)// è dispari x e y pari
		    return gcd(x, y/2);
        else if(x%2 == 0 && y%2 != 0) // è pari x e y dispari
            return gcd(x/2, y);
        else // entrambi dispari
            return gcd((x-y)/2, y); 
    
	return gcd(y, x); 
}