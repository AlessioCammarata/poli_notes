### Ricorsione

Una funzione ricorsiva è una funzione che chiama se stessa una o piu volte a seconda della condizione di terminazione stabilita.

Ci sono a sottoproblemi, ed ogni sottoproblema lavora su tot dati che possiamo ridurre di un valore k:

>**Decrease and Conquer** -> n-k
>**Divide and Conquer** -> n/k

##### Analisi di Complessità

Il costo è la somma di 3 membri:

- D(n) costo della divisione
- Tempo di esecuzione per input piccoli(Ricorsione)
- C(n) costo della ricombinazione

Ogni problema è indipendente, anche se ho gia risolto un problema in precedenza lo risolverò di nuovo, affronto ogni problema come se non lo avessi mai visto.

---
#### Problemi ricorsivi semplici

##### Fattoriale

```C
unsigned long fact(int n) { 
	if ((n == 0) || (n == 1)) 
		return 1; 
	return n*fact(n-1); 
}
```
---
##### Numeri di Fibonacci

I numeri di Fibonacci sono quei numeri che si ottengono:

				$x(n) = x(n-1) + x(n-2)$
Dove x(0) = 0, e x(1) = 1.

Esempi:

> 0 -> 0 da definizione
> 1 -> 1 da definizione
> 2 -> 1 + 0 = 1
> 3 ->  1 + 1 = 2
> ecc...

Codice
```C
unsigned long fib(int n){ 
	if(n == 0 || n == 1) 
		return(n); 
	return(fib(n-2) + fib(n-1)); 
}
```
###### Analisti di complessità

>$D(n) = Teta(1), C(n) = Teta(1)$
   $a = 2, ki = 1, ki-1 = 2$

Equazione alla ricorrenze:  (Risolvibile con unfolding)
	$T(n) = 1 + T(n-1) + T(n-2)$ con n > 1 
	$T(0) = 1 T(1) = 1$ 

Approssimazione conservativa: essendo 
	$T(n-2) ≤ T(n-1)$ 
	
Lo sostituisco con T(n-1) e l’equazione diventa 
	$T(n) = 1 + 2T(n-1)$ con n > 1 
	$T(0)=T(1) = 1$

Risoluzione per sviluppo:

$T(n) = 1 + 2T(n-1)$
$T(n-1) = 1 + 2T(n-2)$
$T(n-2) = 1 + 2T(n-3)$

Perciò

$T(n) = \sum_{i=0}^{n-1} i * 2^i =  2^n - 1$ 
Poiche per la progressione geometrica:
>$\sum_{i=0}^{n} x^i = \frac{x^{k+1}-1}{x-1}$ 

Quindi:
$T(n) = O(2^n)$

##### Massimo Comune Divisore

Trovare il massimo comune divisore tra due numeri.
Algoritmo di Euclide:
V1:
Se x>y
	gcd(x, y) = gcd(x-y, y)
else
	gcd(x, y) = gcd(x, y-x)

Codice
```C
int gcd(int x, int y) { 
	if(x == y) 
		return x; 
	if (x > y) 
		return gcd(x-y, y); 
	return gcd(x, y-x); 
}
```

Ottimizzazione: (Djikstra - Lamé)
Se x>y:
	gcd(x, y) = gcd(y, x%y)
	
Codice
```C
int gcd(int x, int y) { 
	if(y == 0) 
		return x; 
	return gcd(y, x % y); 
}
```
###### Analisti di complessità

>$D(x,y) = Teta(1), C(x,y) = Teta(1)$
   $a = 1$

Caso peggiore x e y sono due numeri coprimi tra loro. (Numeri Fibonacci consecutivi)

	$x = FIB(n+1) y = FIB(n)$

Equazione alla ricorrenze:  
	$T(x,y) = T(FIB(n+1), FIB(n)) = 1 + T(FIB(n),FIB(n+1)$%$FIB(n))$
	$T(x,0) = 1$ 
ma 
	$FIB(n+1)$%$FIB(n) = FIB(n-1)$ 
Percio:
	$T(x,y) = T(FIB(n+1), FIB(n)) = 1 + T(FIB(n),FIB(n+1)= \sum_{i=0}^{n} i = n$

La complessità è percio:
	$T(x, y) = O(n)$

$y = FIB(n) = \frac{(φ^n - φ' ^n)} {\sqrt5} = Teta(φ^n)$, allora
n è una funzione di log(y) in base φ.
E quindi:
	$T(x, y) = O(log(y))$
	