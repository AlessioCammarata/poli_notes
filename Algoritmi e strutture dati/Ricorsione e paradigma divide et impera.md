
>**DEF**: Una funzione ricorsiva è una funzione che chiama se stessa una o piu volte a seconda della **condizione di terminazione** stabilita.

La condizione di terminazione serve per definizione in quanto un algoritmo è una serie **finita** di passi.
### Paradigma Divide et impera
***DIVIDE***
- da problema di dimensione n, in a≥1 problemi indipendenti e di ugual natura di dimensione n' < n, detti sottoproblemi.
***IMPERA***
- risoluzione di problema elementare
***COMBINA***
- ricostruzione di soluzione complessiva combinando le soluzioni ai sottoproblemi.

Se a = 1 allora la ricorsione è **lineare** altrimenti si dice **multi-via**.
Ad ogni passo la dimensione del problema si riduce di:
- Una ==valore k(i)==, non sempre uguale per tutti i sottoproblemi
- Un ==fattore costante b==, in generale lo stesso per tutti i sottoproblemi
- Una quantità variabile difficile da stimare

Terminologia:
>**Decrease and Conquer**  -> n-k  | valore di riduzione costante
>**Divide and Conquer**      -> n/b  | fattore di riduzione costante

---
#### Analisi di Complessità

Il costo T(n) è la somma di 3 membri:

- D(n) **costo della divisione**
- **Tempo di esecuzione** per input piccoli (Ricorsione)
- C(n) **costo della ricombinazione**

Ogni problema è indipendente, anche se ho già risolto un problema in precedenza lo risolverò di nuovo, affronto ogni problema come se non lo avessi mai visto.

>Esempio **equazione alle ricorrenze** nel caso ==divide and conquer==:
$$
	T(n) = D(n) + a\cdot T(\frac{n}{b}) + C(n) \;\:\;\: n>c
$$
$$
	T(n) = Teta(1) \;\:\;\: n≤c
$$

>Esempio **equazione alle ricorrenze** nel caso ==decrease and conquer==:
$$
	T(n) = D(n) + \sum_{i=0}^{a-1} T(n-k_i) + C(n) \;\:\;\: n>c
$$
$$
	T(n) = Teta(1) \;\:\;\: n≤c
$$
---
#### Problemi ricorsivi semplici

##### Fattoriale
Il fattoriale per definizione:
$$
\begin{flalign*}
& n! = n \cdot (n-1)! \qquad n ≥ 1 \newline
& 0! = 1! = 1
\end{flalign*}
$$

```C
unsigned long fact(int n) { 
	if ((n == 0) || (n == 1)) 
		return 1; 
	return n*fact(n-1); 
}
```
###### Analisi di complessità

>$D(n) = Teta(1), C(n) = Teta(1)$
   $a = 1,\space ki = 1$

Equazione alla ricorrenze: 
$$
\begin{align}
	& T(n) = Teta(1) + T(n-1) \qquad n > 1 \\
	& T(1) = Teta(1) 
\end{align}
$$
Risoluzione per sviluppo (unfolding):
$$
\begin{align}
& T(n) = 1 + T(n-1)\\
& T(n-1) = 1 + T(n-2)\\
& T(n-2) = 1 + T(n-3)
\end{align}
$$
Perciò
$$T(n) = \sum_{i=0}^{n-1} 1 =  n$$ 
Quindi:
$$T(n) = O(n)$$

---
##### Numeri di Fibonacci

I numeri di Fibonacci sono quei numeri che si ottengono:

$$x(n) = x(n-1) + x(n-2)$$
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
###### Analisi di complessità

>$D(n) = Teta(1),\; C(n) = Teta(1)$
   $a = 2,\; k_i = 1,\; k_{i-1} = 2$

Equazione alla ricorrenze:  (Risolvibile con unfolding)
	$T(n) = 1 + T(n-1) + T(n-2)$ con n > 1 
	$T(0) = 1 \space\space\space T(1) = 1$ 

Approssimazione conservativa: essendo 
	$T(n-2) ≤ T(n-1)$ 
	
Lo sostituisco con T(n-1) e l’equazione diventa 
	$$
\begin{align}
	& T(n) = Teta(1) + 2T(n-1) \qquad n > 1 \\
	& T(1) = T(0) = Teta(1) 
\end{align}
$$

Risoluzione per sviluppo:
$$
\begin{align}
& T(n) = 1 + 2T(n-1) \\
& T(n-1) = 1 + 2T(n-2) \\
& T(n-2) = 1 + 2T(n-3) \\
\end{align}
$$

Perciò:
$$T(n) = \sum_{i=0}^{n-1} 2^i =  2^n - 1$$

>Poiché per la **progressione geometrica**:
>$$\sum_{i=0}^{n} x^i = \frac{x^{k+1}-1}{x-1}$$

Quindi:
$$T(n) = O(2^n)$$
---
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

>Ottimizzazione: (Djikstra - Lamé)
Utilizzo il resto della divisione intera

Se x>y:
	gcd(x, y) = gcd(y, x%y)
altrimenti scambio x ed y.

Codice:
```C
int gcd(int x, int y) { 
	if(y == 0) 
		return x; 
	return gcd(y, x % y); 
}
```
###### Analisi di complessità

>$D(x,y) = Teta(1), C(x,y) = Teta(1)$
   $a = 1$

Caso peggiore x e y sono due numeri **coprimi** tra loro. (Numeri Fibonacci consecutivi)

$$x = FIB_{n+1} \qquad y = FIB_n$$
Equazione alla ricorrenze:  
$$
\begin{align}
&T(x,y) = T(FIB_{n+1}, FIB_n) = 1 + T(FIB_n,FIB_{n+1}\%FIB_n) \\
&T(x,0) = 1
\end{align}
$$

>Ma: $FIB_{n+1}\%FIB_n = FIB_{n-1}$

Perciò:
$$T(x,y) = T(FIB_{n+1}, FIB_n) = 1 + T(FIB_n,FIB_{n+1}= \sum_{i=0}^{n} i = n$$
La complessità è dunque:
$$T(x, y) = O(n)$$
$y = FIB(n) = \frac{(φ^n - φ' ^n)} {\sqrt5} = Teta(φ^n)$, allora n è una funzione di log(y) in base φ.
E quindi:
$$T(x, y) = O(log(y))$$
---
### Ricerca Binaria