Un programma si dice modulare quando il problema viene risolto per scomposizione in **sottoproblemi**, e la scomposizione è visibile.

>Un **dato modulare**, è un tipo di dato con le relative funzioni:

Esempio: 
	**acquisizione ripetuta** di segmenti tramite i loro estremi (punti sul piano cartesiano con coordinate intere)
	calcolo della loro lunghezza.
	*terminazione acquisizione:* segmenti a lunghezza 0.
>Soluzione 1: Fa tutto il main
```c
typedef struct { 
	int X, Y; 
} punto_t; 

int main(void) { 
	punto_t A, B; 
	int fine=0; 
	float l; 
	while (!fine) { 
		printf("coordinate primo estremo: "); 
		scanf("%d%d", &A.X, &A.Y); 
		
		printf("coordinate secondo estremo: "); 
		scanf("%d%d", &B.X, &B.Y);
		
		l=sqrt((B.X-A.X)*(B.X-A.X)+ (B.Y-A.Y)*(B.Y-A.Y)); 
		printf("Segmento (%d,%d)-(%d,%d) l: %f\n", A.X,A.Y,B.X,B.Y,l); 
		fine = l==0; 
	} 
	return 0; 
}
```

>Soluzione 2: modulare

esiste il tipo di dato **punto_t**, cui sono associate 3 funzioni: **puntoScan**, **puntoPrint**, **puntoDist**.
```c
typedef struct { 
	int X, Y; 
} punto_t; 

void puntoScan(FILE *fp, punto_t *pp) {  //funzione di lettura
	fscanf(fp, "%d%d", &pp->X, &pp->Y); 
} 

void puntoPrint(FILE *fp, punto_t p) { // funzione di scrittura
	fprintf(fp, "(%d,%d)", p.X, p.Y); 
} 

float puntoDist(punto_t p0, punto_t p1) { // funzione di elaborazione
	int d2 = (p1.X-p0.X)*(p1.X-p0.X) + (p1.Y-p0.Y)*(p1.Y-p0.Y); 
	return ((float) sqrt((double)d2)); 
}

int main(void) { 
	punto_t A, B; 
	int fine=0; 
	float l; 
	while (!fine) { 
		printf("primo estremo: "); puntoScan(stdin, &A); 
		printf("secondo estremo: "); puntoScan(stdin, &B); 
		l = puntoDist(A,B); 
		printf("Il segmento "); puntoPrint(stdout,A); 
		printf("-"); puntoPrint(stdout,B); 
		printf(" ha lunghezza: %f\n", l); 
		fine = lunghezza==0; 
	} 
	return 0; 
}
```
##### Modularità nell'allocazione dinamica
A e B sono puntatori a struct, le struct sono allocate dinamicamente ed esplicitamente, le funzioni ricevono e restituiscono puntatori a struct.
```c
typedef struct { 
	int X, Y; 
} punto_t; 

punto_t *puntoCrea(void) { //funzione di creazione
	punto_t *pp = (punto_t *) malloc(sizeof(punto_t)); 
	return pp; 
} 

void puntoLibera(punto_t *pp) { //funzione di distruzione
	free(pp); 
} 

void puntoScan(FILE *fp, punto_t *pp) { //funzione di lettura
	fscanf(fp, "%d%d", &pp->X, &pp->Y); 
} 

void puntoPrint(FILE *fp, punto_t *pp) {  //funzione di scrittura
	fprintf(fp, "(%d,%d)", pp->X, pp->Y); 
} 

float puntoDist(punto_t *pp0, punto_t *pp1) { //funzione di elaborazione
	int d2 = (pp1->X-pp0->X)*(pp1->X-pp0->X) + (pp1->Y-pp0->Y)*(pp1->Y-pp0->Y); 
	return ((float) sqrt((double)d2)); 
}

int main(void) { 
	punto_t *A, *B; 
	int fine=0; 
	float lunghezza; 
	A = puntoCrea(); 
	B = puntoCrea(); 
	
	while (!fine) { 
		printf("I estremo: "); puntoScan(stdin, A); 
		printf("II estremo: ");puntoScan(stdin, B); 
		lunghezza = puntoDist(A,B); 
		
		printf("Segmento "); 
		puntoPrint(stdout,A); printf("-"); puntoPrint(stdout,B); 
		printf(" ha lunghezza: %f\n", lunghezza); 
		file = lunghezza==0; 
	} 
	puntoLibera(A); 
	puntoLibera(B); 
	return 0; 
}
```
---
##### Creazione/distruzione
>Il **responsabile** di distruggere il puntatore è colui che lo ha creato, percio se viene creato all'interno del main è preferibile liberarlo all'interno del main.
>Però l'importante è cancellare tutto cio che si crea quando il programma finisce, per non creare **Memory leak**.

Il main proposto:
- crea e distrugge le variabili A e B 
- distrugge la variabile max, creata da puntoM mediante chiamata a puntoDupl, senza che il main ne renda visibile la creazione. 
La soluzione è corretta, ma debole.

Esempio:
```c
punto_t *puntoDupl(punto_t *pp) { 
	punto_t *pp2 = puntoCrea(); //Chiamata alla funzione di creazione
	*pp2 = *pp; 
	return pp2; 
} 

punto_t *puntoM(punto_t *pp0, punto_t *pp1) { 
	punto_t origine = {0,0}; 
	float d0 = puntoDist(&origine,pp0); 
	float d1 = puntoDist(&origine,pp1); 
	if (d0>d1) 
		return puntoDupl(pp0); 
	else 
		return puntoDupl(pp1); 
}

int main(void) { 
	punto_t *A, *B, *max; 
	A = puntoCrea(); B = puntoCrea(); //il main crea A e B
	/* input dei 2 punti A e B */ 
	
	max = puntoM(A,B); //puntoM crea max
	printf("Punto piu' lontano: "); puntoPrint(stdout,max); 
	
	//il main distrugge A, B e max
	puntoLibera(A); 
	puntoLibera(B); 
	puntoLibera(max); 
	return 0; 
}
```
---
#### Composizione e Aggregazione
strategie per raggruppare dati o riferimenti a dati in un unico dato composto tenendo conto delle relazioni gerarchiche di appartenenza e possesso.

- **Composizione stretta con possesso**
	- Per ==valore== *A include B*
	- Per ==riferimento== *A include un riferimento a B* (B è esterno ad A ma viene considerato di sua proprietà)
- **Aggregazione (composizione senza possesso)**
	- A include un riferimento a B (B NON è proprietà di A, fa riferimento a un dato “esterno”).
##### Composizione con possesso
Composizione implica, chi crea distrugge. (A livello teorico astratto)

>Se A **possiede** B, ha la **responsabilità** di crearlo e distruggerlo.

>Vantaggi della **modularità** per **composizione**
>	-ogni tipo di dato è un’entità a se stante, focalizzata su un compito specifico.
>	-ogni componente di un dato è autosufficiente e riutilizzabile
>	-il tipo di dato di più alto livello coordina il lavoro di quelli di livello inferiore
>	-modifiche al tipo di dato inferiore sono localizzate, riutilizzabili e invisibili al tipo di dato superiore.
###### Composizione per valore
Un dato **contiene** completamente il dato interno. Utilizziamo memoria statica.
Esempio: slide 25 creatura.
###### Composizione per riferimento
Un **dato** contiene un puntatore al dato interno di cui mantiene il completo possesso.
Esempio: stesso esercizio di prima in pratica. slide 42
###### Aggregazione (Composizione per riferimento)
Esempi: 
- elenco dei dipendenti di un’azienda 
	- I dipendenti esistono al di là dell’azienda 
- volo aereo caratterizzato da compagnia, orario, costo, aeroporti di origine e destinazione
	- Compagnia ed aeroporti esistono al di là del volo.

#### Programmi multi-file
Ragionare su file multipli, devo poter spezzare il programma in vari moduli e i moduli in più file.

I moduli su più file sono: 
- compilati e testati individualmente 
- interagiscono in maniera ben definita attraverso interfacce 
- implementano l’information hiding, nascondendo i dettagli interni. 
Soluzione adottata: 
- file di intestazione (header) .h per dichiarare l’interfaccia 
- file di implementazione .c con l’implementazione di quanto esportato e di quanto non esportato

Nel .h si mettono solo i prototipi.
>Le variabili globali vanno nel .c

Per utilizzare l'header bisogna usare #include.



