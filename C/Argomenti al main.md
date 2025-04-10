Un modo alternativo per passare parametri (informazioni ad un programma) senza chiedere input.

I comandi vengono lanciati da Finestre terminali, linea di comando.
###### Esempio

Oltre a scrivere il nome del programma si può scrivere qualche informazione affianco.

```bash
C:\> myprog <arg1> .... <argN>
```

Gli args sono detti **argomenti sulla linea di comando**.

>È necessario perciò avviare un terminale
---
#### Senza usare terminale

Al posto di usare un terminale si può andare nel menu "run -> edit configurations" e
impostare i **program arguments.**

---
#### Come viene scritto il main?

- Esempio
```c
int main(int argc, char *argv[]){ // Ricevi gli argomenti

}
```

Cosa significa che riceve gli argomenti?

>**Nota**: argv è un vettore adimensionato di argomenti, argc è il numero di argomenti.
> argv[0] è sempre presente e contiene il nome del programma.
> Il main riceve solo stringhe - se non lo sono bisogna fare il cast

- Esempio

```bash
C:\> quadrato 5 k
```
l'argomento 0 è quadrato
l'argomento 1 è 5
l'argomento 2 è k
e perciò argc sarà 3

>**Nota**: di solito si utilizzano proprio i nomi argv e argc.
#### Come si usano argv e argc?

spesso si utilizzano tramite un ciclo for.

```c
for (i=0; i<argc;i++){
	/* elabora argv[i] */
}
```

#### Conversione degli argomenti

atoi e atof permettono di convertire una stringa in un valore numerico, restituiscono 0 in caso di errore.

- Esempio

```c
// Esempi applicati a stringhe costanti (servono solo per capire) 
int x = atoi("2"); // x=2 double 
z = atof("2.35e-2"); // z=0.0235 

// Esempio applicato agli argomenti al main 
// si suppone che il programma sia chiamato come ad esempio: 
// somma 5.4 -0.15e2 
int main (int argc, char *argv[]) { 
	float a, b, sum; 
	a = atof(argv[1]); 
	b = atof(argv[2]); 
	sum = a+b; 
	printf("il programma %s calcola %f +%f = %f\n", argv[0], a, b, sum); 
}
```

Generalmente cosa si passa come argomento ad una funzione main?
Di solito vengono passate delle opzioni e degli argomenti:

- Opzioni
	- Iniziano con un trattino se hanno un solo char e 2 se ne hanno di più
	- Generalmente vengono scritte prima degli argomenti
	- Indicano come configurare il tipo di lavoro da fare
- Argomenti
	- Indicano su cosa svolgere il lavoro
	- Vengono scritte dopo le opzioni

#Esempio 

```c
#include <stdio.h>
main(int argc, char *argv[]) { 
	int N, D, i; 
	if (argc != 3) { 
		printf("Numero argomenti non valido\n"); 
		return 1; 
	} 
	N = atoi(argv[1]); 
	D = atoi(argv[2]); 
	for (i=1;i<=N;i++) { 
		if (i%D == 0) { 
			printf("%d\n",i); 
		} 
	} 
}
```

#Esempiomeglio

```c
#include <stdio.h>
main(int argc, char *argv[]) { 
	int i, lowercase=0, uppercase=0;
	for	(i=1;	i<argc-2;	i++)	{ 
		switch	(argv[i][1])	{ 
			case	'l':	
			case	'L': 
				lowercase	=	1; 
				break; 
			case	'u':	
			case	'U': 
				uppercase	=	1; 
				break; 
			case	'h': 
				printf("Uso:	m2m	[-luh]	<nomefile	in>	<nomefile	out>\n");              } 
		}
	} 
	converti(argv[argc-2], argv[argc-1], lowercase, uppercase);// svolge il lavoro vero e proprio 
}
```

```bash
m2m –l a.txt a_minuscolo.txt 
m2m –L a.txt a_minuscolo.txt 
m2m –u b.txt b_maiuscolo.txt 
m2m –U b.txt b_maiuscolo.txt 
m2m c.txt uguale_a_c.txt 
m2m -h
```