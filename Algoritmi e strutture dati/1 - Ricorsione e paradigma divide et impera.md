
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
   $a = 1,\space k_i = 1$

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
>$$\sum_{i=0}^{k} x^i = \frac{x^{k+1}-1}{x-1}$$

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
#### Ricerca Binaria

Un esempio di ricerca binaria, o dicotomica, è la ricerca di una chiave all'interno di un vettore.
È un divide and conquer con a = 1, b = 2; ogni passo confronto k con elemento centrale:
- =: terminazione con successo
- <: la ricerca prosegue nel sottovettore di sinistra
- >: la ricerca prosegue nel sottovettore di destra
Il processo termina quando l'indice di sinistra scavalca quello di destra.
```C
int BinSearch(int v[], int l, int r, int k) { 
	int m;
	if (l > r) 
		return -1; 
	m = (l + r)/2; 
	if (k == v[m]) 
		return (m); 
	if (k < v[m]) 
		return BinSearch(v, l, m-1, k); 
	return BinSearch(v, m+1, r, k); 
}
```

###### Analisi di complessità

>$D(n) = Teta(1), C(n) = Teta(1)$
   $a = 1$, b = 2

Equazione alla ricorrenze: 
$$
\begin{align}
	& T(n) = Teta(1) + T(\frac n 2) \qquad n > 1 \\
	& T(1) = Teta(1) 
\end{align}
$$
Risoluzione per sviluppo (unfolding):
$$
\begin{align}
& T(n) = 1 + T(\frac n 2)\\
& T(\frac n 2) = 1 + T(\frac n 4)\\
& T(\frac n 4) = 1 + T(\frac n 8)
\end{align}
$$
Perciò
$$T(n) = \sum_{i=0}^{log_2(n)} 1 =  1 + log_2(n)$$ 
Quindi:
$$T(n) = O(log(n))$$
---
#### Le torri di Hanoi

Problema decrease and conquer, a = 2 k = 1.
Configurazione iniziale: 
- Vi sono 3 pioli, 3 dischi di diametro decrescente sul primo piolo 
Configurazione finale: 
- 3 dischi sul terzo piolo 
Regole: 
- accesso solo al disco in cima 
- sopra ogni disco solo dischi più piccoli  
- Generalizzabile a n dischi e k pioli.

>Esempio di soluzione (3,3):
![[torri di hanoi.png]]

>Codice:
```c
void Hanoi(int n, int src, int dest) { 
	int aux; 
	aux = 3 - (src + dest); 
	if (n == 1) { //terminazione
		printf("src %d -> dest %d \n", src,dest); 
		return; 
	} 
	Hanoi(n-1, src, aux); //divisione
	printf("src %d -> dest %d \n", src, dest); // dest è la soluzione elementare
	Hanoi(n-1, aux, dest); 
}
```
###### Analisi di complessità

- Dividi: **considera n-1 dischi**                                                                               $D(n)=teta(1)$
- Risolvi: **risolve 2 sottoproblemi di dimensione n-1 ciascuno**                           $2T(n-1)$
- Terminazione: **spostamento di 1 disco**                                                              $teta(1)$
- Combina: **nessuna azione**                                                                                 $C(n) =teta(1)$

Equazione alla ricorrenze: 
$$
\begin{align}
	& T(n) = 2T(n-1) + 1 \qquad n > 1 \\
	& T(1) = 1 
\end{align}
$$
Risoluzione per sviluppo (unfolding):
$$
\begin{align}
& T(n) = 2T(n-1) + 1\\
& T(n-1) = 2T(n-2) + 1\\
& T(n-2) = 2T(n-3) + 1
\end{align}
$$
Perciò
$$T(n) = \sum_{i=0}^{n-1} 2^i =  2^n - 1$$ 
Quindi:
$$T(n) = O(2^n)$$
---
#### Funzioni ricorsive

>Meccanismi computazionali per eseguire funzioni ricorsive:

Chiamata a funzione: quando si chiama una funzione: 
- si crea una nuova istanza della funzione chiamata 
- si alloca memoria per i parametri e per le variabili locali s
- si passano i parametri 
- il controllo passa dal chiamante alla funzione chiamata 
- si esegue la funzione chiamata 
- al suo termine, il controllo ritorna al programma chiamante, che esegue l’istruzione immediatamente successiva alla chiamata a funzione. 
È possibile che una funzione ne chiami un’altra. Serve un meccanismo per gestire le chiamate annidate e i relativi ritorni: lo **stack**.

##### Stack
Lo stack è un tipo di dato astratto (ADT) che supporta operazioni di:
- **PUSH**: inserimento dell'oggetto in cima allo stack
- **POP**: prelievo (e cancellazione) dalla cima dell'oggetto inserito più recente
La strategia di gestione dei dati è detta **LIFO** ( Last-In First-Out).

Si chiama **stack frame** (o record di attivazione) la struttura dati che contiene almeno: 
- i parametri formali
- le variabili locali 
- l’indirizzo a cui si ritornerà una volta terminata l’esecuzione della funzione 
- il puntatore al codice della funzione. 
Lo stack frame viene creato alla chiamata della funzione e distrutto al suo termine.

Gli stack frame sono memorizzati nello stack di sistema. Quest'ultimo ha a disposizione una quantità prefissata di memoria. Quando oltrepassa lo spazio allocatogli, c’è **stack overflow**. 
Lo stack cresce da indirizzi maggiori a indirizzi minori (quindi verso l’alto). 
Lo **stack pointer SP** è un registro che contiene l’indirizzo del primo stack frame disponibile.

>Esempio
```c
int f1(int x); 
int f2(int x); 

main() { 
	int x, a = 10; 
	x = f1(a); 
	printf("x is %d \n", x); 
} 

int f1(int x) { 
	return f2(x); 
} 
int f2(int x) { 
	return x+1; 
}
```

>Raffigurazione:
![[stack frame representation.png]]
---
###### Funzioni tail recursive e non

- Una funzione ricorsiva **non è tail-recursive** se la chiamata ricorsiva non è l’ultima operazione da eseguire:
```c
unsigned long fact(int n) { 
	if(n == 0) return 1; 
	return n*fact(n-1); 
}
```

>la moltiplicazione può essere eseguita solo dopo il ritorno della chiamata ricorsiva, i calcoli vengono eseguiti in risalita.
---
- Una funzione ricorsiva è **tail-recursive** se la chiamata ricorsiva è l’ultima operazione da eseguire, eccezion fatta per #return:
```c
unsigned long tr_fact(int n, unsigned long f) { 
	if(n == 0) return f; 
	return tr_fact(n-1, n*f); 
}
```

> È tail-recursive perché la moltiplicazione viene eseguita prima della chiamata ricorsiva, i calcoli si fanno in discesa.

Se una funzione è tail-recursive la funzione chiamante (caller) deve solo ritornare il valore calcolato dalla funzione chiamata (callee);
L’operazione di pop dello stack frame della funzione chiamante avviene prima dell’operazione di push nello stack frame della funzione chiamata;
Lo stack frame della funzione chiamata rimpiazza semplicemente quello della funzione chiamante; L’occupazione di memoria non è più O(n) dove n sono i livelli di ricorsione, bensì O(1);
Non ci può più essere stack overflow.

>Svantaggi:
- più difficili da scrivere 
- non tutti i compilatori (tra cui quello del C) riescono a sfruttare le funzioni tail-recursive per ottimizzare il codice.
##### Dualità ricorsione - iterazione

Possibili soluzioni: 
- iterativa “nativa” 
- ricorsiva: 
	- se tail-recursive trasformabile direttamente in iterativa senza uso di stack 
	- se non tail-recursive trasformabile in iterativa con uso di stack. 
	 In generale soluzione meno efficienti di quelle iterative “native”.

Esempio con il fattoriale:

>Forma iterativa:
```c
unsigned long fact(int n) { 
	unsigned long tot = 1; 
	int i; 
	for (i=2; i<=n; i++) 
		tot = tot * i; 
	return tot; 
}
```

>Forma ricorsiva tail-recursive:
```c
unsigned long tr_fact(int n, unsigned long f) { 
	if(n == 0) //Condizione di terminazione
		return f; 
	return tr_fact(n-1, n*f); // Calcoli effettuati in discesa
}
```
Questa funzione è facilmente trasformabile in forma iterativa:
```c
unsigned long tr2iterfact(int n, unsigned long f){
	while (n > 0) { //Condizione di terminazione
		f = n * f; // secondo argomento della funzione ricorsiva
		n--; // n-1 di sopra
	} 
	return f; 
}
```

>Forma ricorsiva non tail-recursive:
```c
unsigned long fact(int n) { 
	if(n == 0) // Condizione di terminazione
		return 1; 
	return n*fact(n-1); // I calcoli vengono effettuati in salita
}
```
---