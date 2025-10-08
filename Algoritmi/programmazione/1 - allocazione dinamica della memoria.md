Allocare una variabile significa associarvi una porzione di memoria (in cui collocare i dati).
>L’allocazione è:
- implicita, automatica e statica se gestita dal sistema 
- esplicita se sotto controllo del programmatore 
- dinamica:
	- avviene in fase di esecuzione 
	- permette di cambiare la dimensione della struttura dati 
	- permette di realizzare “contenitori” cui si aggiungono o tolgono elementi.

##### Variabili globali:
- definite al di fuori da funzioni (main incluso) 
- permanenti 
- visibili dovunque nel file a partire dalla loro definizione 
- definite in generale nell’intestazione del file.

>Vantaggi: 
- accessibili a tutte le funzioni
- non necessario passarle come parametri 
- utilizzo semplice ed efficiente 
>Svantaggi: 
- minore modularità, leggibilità, affidabilità

##### Variabili locali: 
- variabili definite all’interno delle funzioni (main incluso) 
- parametri alle funzioni 
- temporanee (iniziano ad esistere quando è chiamata la funzione e cessano quando se ne esce)
- visibili solo nella funzione in cui sono dichiarate.

##### Compilatore
>Programma che esegue un’analisi (lessicale, sintattica, semantica) del codice sorgente e genera un codice oggetto (in linguaggio macchina).

Il codice oggetto contiene riferimenti a funzioni di libreria. 
**Linker**: 
- programma che risolve: 
	- i riferimenti a funzioni di libreria 
	- I riferimenti reciproci tra più file oggetto. ▪ 
- e genera un codice eseguibile.
**Loader**: 
- modulo del sistema operativo che carica in memoria centrale: 
	- Il codice eseguibile (istruzioni) 
	- I dati su cui opera

#### Regole di allocazione dinamica
dimensioni: 
- variabili **globali** e locali **hanno** dimensione nota 
- **vettori e matrici** devono avere dimensione calcolabile 
- i vettori come parametri formali sono **puntatori** 

Le **variabili globali** vengono allocate all’avvio del programma e restano in vita per tutto il programma, possono ricordare i valori assegnati da funzioni e l’attributo **static** limita la loro visibilità al file in cui compaiono.

Le **variabili locali** sono raggruppate con i parametri formali in uno stack frame vengono allocate nello stack ad ogni chiamata della funzione e deallocate automaticamente all’uscita dalla funzione inoltre **non ricordano i valori precedenti.**

Le **variabili locali con attributo static** hanno visibilità limitata alla funzione vengono allocate assieme alle variabili globali e ricordano i valori (della chiamata precedente).

>Osservazione: 
	In questo momento manca un modo per poter decidere, durante l’esecuzione di un programma: 
	- la creazione/distruzione un dato 
	- il dimensionamento di un vettore o matrice 

Sono state introdotte perciò **istruzioni per allocare e de-allocare dati** (memoria) in modo esplicito in funzione di dati forniti da chi esegue il programma.
Allocazioni e de-allocazioni sono (ovviamente) previste e gestite dall’autore del programma.
La componente del sistema operativo che si occupa di allocazione/deallocazione è **l’allocatore di memoria dinamica** 
Questa memoria dinamica si trova in un’area detta **heap** e vi si accede solo mediante **puntatore**.

>Fasi di una struttura dati dinamica: 
>- creazione (allocazione) esplicita 
>- utilizzo con possibilità di: 
>	- riallocazione 
>	- Inserimenti 
>	- cancellazioni 
>- distruzione (de-allocazione) esplicita
---
#### La funzione malloc

La memoria in C viene allocata dinamicamente tramite la funzione malloc: 
```c
#include <stdlib.h> // è la libreria per usare malloc

void* malloc (size_t size); // size_t è un intero senza segno (si può usare come parametro attuale un int)
```
 
 **Size** è il numero (intero) di byte da allocare, il valore di ritorno è un puntatore che contiene **l’indirizzo iniziale della memoria allocata** (NULL se non c’è memoria disponibile); è tipo void *, in modo da poter essere assegnato a qualunque tipo di puntatore.

>Forma generale di chiamata **malloc**:
```c
int c;
//cast implicito 
p = malloc(sizeof (int)); 
p = malloc(sizeof c); 
//cast esplicito (non obbligatorio, ma permette controllo di errore se p non è del tipo corretto): 
p = (int *) malloc(sizeof (int)); 
p = (int *) malloc(sizeof c);
```
Esempio:
```c
#define MAX 20 
struct stud {
	char cognome[MAX];
	int matr; 
}; 
struct stud *s;

//cast implicito
s = malloc(sizeof(struct stud));
#oppure
s = malloc(sizeof(*s));

//cast esplicito
s = (struct stud *)malloc(sizeof(struct stud)); 
#oppure
s = (struct stud *)malloc(sizeof(*s));
```
>Conseguenze di errori comuni:

- Gli errori individuati dal compilatore occorre correggerli (il programma non compila correttamente).
- Gli errori NON individuati dal compilatore avvengono spesso, perché la malloc riceve solo un NUMERO e ritorna in INDIRIZZO, quindi non conosce le «intenzioni» del programmatore, ci sono due possibilità o La dimensione allocata è **SUPERIORE** a quella necessaria. In questo caso Non succede NULLA, se non lo SPRECO di memoria (allocata e non usata) oppure La dimensione allocata è inferiore al necessario, NON capita di solito NULLA nell’allocazione però DOPO, mentre si accede ai dati, SI RISCHIA DI USARE (mediante puntatore) MEMORIA NON ALLOCATA oppure ALLOCATA per un altro DATO.

Cosa succede DOPO, se si accede a memoria non allocata oppure allocata ad altri dati?
Crash del programma per accesso a indirizzo non ammesso (esito auspicabile) oppure accesso ad indirizzo legale, ma al di fuori della struttura dati allocata (errore subdolo) e perciò si SPORCA un altro dato.

>Memoria dinamica insufficiente:

Succede poco, indica che non c’è più memoria allocabile nell’heap, per la dimensione richiesta (provare ad allocare n*sizeof(int), con n molto grande): la malloc ritorna NULL è opportuno perciò testare, segnalando o uscendo con exit o return:
```c
int *p; 
... 
p = malloc(sizeof(int)); 
if (p == NULL) 
	printf("Errore di allocazione\n"); 
...
```
---
#### La funzione calloc
Equivale alla malloc(n*size); con memoria ritornata azzerata.
```c
void* calloc (size_t n, size_t size); 
```
>La calloc ha costo (in tempo) O(n), a causa dell’azzeramento, mentre malloc è O(1). 
>Tuttavia, molto sovente, l’azzeramento è opportune Io necessario (andrebbe fatto comunque).
---
#### La funzione free
Tutta la memoria allocata dinamicamente con malloc/calloc viene restituita tramite la funzione free():
```c
void free (void* p);
```
p punta alla memoria (precedentemente allocata) da liberare.
La free viene di solito chiamata quando è terminato il lavoro sulla struttura dinamica, affinchè la memoria possa essere riutilizzata. 

>ATTENZIONE: 
>l’allocatore mantiene internamente una tabella di ciò che ha allocato: 
>Si può solo chiamare free per un indirizzo precedentemente ritornato da malloc/calloc (o realloc) 
> NON si può liberare un PEZZO della memoria ottenuta (allocata) con malloc/calloc (o realloc)

L'uso di free è consigliato ma non obbligatorio, al termine dell’esecuzione di un programma la memoria viene comunque liberata (in molti casi questo è sufficiente).
Ma è possible che SIA OPPORTUNO LIBERARE per poter OTTENERE nuova memoria DURANTE l’esecuzione: **es**. programma che ripete iterativamente un lavoro che richiede allocazione. 
>Attenzione ai **memory leak** (mancata de-allocazione di una porzione di memoria): 
>	Non si può riutilizzare la memoria per un nuovo dato da allocare. Effetto: aumenta la probabilità (con programmi che allocano molto) di malloc/calloc che ritornano NULL.

Esempio:
```c
int *vett = malloc(10 * sizeof(int)); 
... 
// uso di vett, SENZA liberazione 
vett = malloc(25 * sizeof(int));
```
>ora la porzione di memoria allocata dalla prima malloc non è più indirizzabile né utilizzabile per ulteriori allocazioni (è ancora allocata, ma non puntata e non usata).

---
#### La funzione realloc
In c la dimensione della memoria allocata può essere modificata aggiungendo o togliendo una porzione in fondo tramite realloc:
```c
void* realloc (void* p, size_t size);
```
- **p** punta alla memoria precedentemente allocata
- **size** è la nuova dimensione richiesta (maggiore o minore)
- Il valore di ritorno è un puntatore
>Esempio di uso tipico:
```c
p = malloc (oldSize); 
... 
p = realloc (p, newSize); 
// si lavora sulla struttura dati espansa o ristretta 
...
```

>_Osservazione_: 
>La riduzione della memoria è sempre possibile.
>L'aumtento della dimensione può:
>	-essere impossibile e si ritorna NULL ( Non c'è abbastanza spazio)
>	-essere possibile (esiste memoria disponibile contigua)
>		Ritorna p (invariato)se è disponibile alla fine del blocco vecchio
>		Ritorna newp aggiornato se l'opzione di prima non è fattibile

Quando si chiama la realloc , **si alloca un nuovo spazio che possa contenere i dati effettivi,** viene effettuata **l'operazione di ricopiatura dei dati dal blocco vecchio a quello nuovo,** questa operazione nasconde una costo lineare di dimensione O(n) e si **ritorna il puntatore alla nuova allocazione di memoria.**

>**La realloc quindi nasconde un costo lineare**
---
#### Strutture dati dinamiche
La dimensione delle strutture dinamiche è **nota solo in fase di esecuzione** e **può variare nel tempo**.

##### Vettori dinamici
La dimensione è nota solo in fase di esecuzione del programma, può variare per riallocazione.
Si evita il sovradimensionamento del vettore (nonché i suoi limiti):
- è necessario conoscere la dimensione massima che è una costante, data questa e una parte iniziale del vettore effettivamente utilizzata il resto è spreco.
Per questo motivo si utilizzano i puntatori oppure l'allocazione mediante malloc/calloc.

>Esempio
```c
#include <stdio.h>
#include <stdlib.h>
int main() { 
	float *v; int N, i; 
	printf("N? "); scanf("%d",&N); 
	//allocazione vettore dinamico
	v = (float *) malloc (N*(sizeof (float)));
	//Controllo allocazione riuscita 
	if (v==NULL) exit(1); 
	printf("Inserisci %d elementi\n", N); 
	for (i=0; i<N; i++) { 
		printf("El. %d: ", i); 
		scanf("%f",&v[i]); 
	}
	printf("Dati in ordine inverso\n"); 
	for (i=N-1; i>=0; i--) 
		printf("El. %d: %f\n", i, v[i]); 
	free(v); // de-allocazione
	return 0; 
};
```

>**ATTENZIONE**: bisogna conoscere il numero di dati per creare ed usare il vettore dinamico!

Se il numero di dati (ignoto) fosse segnalato da un terminatore si puo:
- effettuare **due letture da file**, una per calcolare la quantità di dati e l'altra per eseguire il codice
- utilizzare la **realloc**, tenendo presente che potrebbe avere un costo lineare

Ovviamente se usiamo la realloc non aumentiamo di 1 per risparmiare il massimo dello spazio, ma di un tot costante o che aumenta in modo che bisogna farne meno possibili, in ogni caso lo spreco di spazio è minore di quello che si ha con strutture di dati statiche.
>L'ottimizzazione che utilizzeremo noi è di **raddoppiare ogni volta lo spazio quando questo è esaurito _O(NlogN) invece che O(N^2)_.**

>Esempio (modificato)
```c
#include <stdio.h>
#include <stdlib.h>
int main() { 
	float *v; int N, MAXN=1, i=0; 
	v = malloc (MAXN*(sizeof (float))); 
	printf("Inserisci elementi\n"); 
	printf("Elemento 0: "); 
	while (scanf("%f", &d)>0) { 
		if (i==MAXN) { 
			// numero logaritmico di attivazioni 
			MAXN = MAXN*2; 
			v = realloc(v,MAXN*sizeof(float)); 
			// controllo di errore omesso
		} 
		v[i++] = d; 
		printf("Elemento %d: ", i) ; 
	}
	N = i; // compreso tra MAXN/2 e MAXN 
	printf("Dati in ordine inverso\n"); 
	for (i=N-1; i>=0; i--) 
		printf("El. %d: %f\n", i, v[i]); 
	free(v); 
	return 0; 
}
```
---
##### Matrici dinamici
Ci sono due possibilità:
- Usare un vettore MONODIMENSIONALE dinamico di $nr \cdot nc$ elementi, in questo caso si ha un organizzazione **manuale** di righe e colonne su vettore: l'elemento (i,j) si trova in posizione $nc \cdot i + j$.
- Usare un vettore BIDIMENSIONALE dinamico di **nr puntatori** **a righe**      in questo caso si itera sulle nr righe per allocare un vettore di tipo desiderato di $nr \cdot nc$ elementi. Il resto è identico alla matrice sovradimensionata in modo statico.

>Esempio ( vettore monodimensionale)
```c
...
float *v; 
int nr,nc,i,j; 

printf("nr nc: "); scanf("%d%d", &nr, &nc); 
v = (float *) malloc(nr*nc*(sizeof (float))); //allocazione
if (v==NULL) exit(1); 
for (i=0; i<nr; i++) { 
	printf("Inserisci riga %d\n", i); 
	for (j=0; j<nc; j++) 
		scanf("%f", &v[nc*i+j]); //Gestione manuale: [nc*i+j]
}

printf("Matrice trasposta\n"); 
for (j=0; j<nc; j++) { 
	for (i=0; i<nr; i++) 
		printf("%6.2f", v[nc*i+j]);//Gestione manuale: [nc*i+j]
	printf("\n"); 
} 
free(v); 
...
```

>Esempio ( matrice dinamica bidimensionale)
```c
... 
//float **: vettore di puntatori
float **m; int nr,nc,i,j; 

printf("nr nc: "); scanf("%d%d", &nr, &nc);
//allocazione di vettore di nr puntatori a riga
m = (float **) malloc(nr*(sizeof (float *))); 
if (m==NULL) exit(1); 
for (i=0; i<nr; i++) { 
	printf("Inserisci riga %d\n", i);
	//vettore di float: uno per riga
	m[i] = (float *) malloc(nc*sizeof (float)); 
	if (m[i]==NULL) exit(1);
	for (j=0; j<nc; j++) 
		scanf("%f", &m[i][j]); 
} 

printf("Matrice trasposta\n");
for (j=0; j<nc; j++) { 
	for (i=0; i<nr; i++) 
		printf("%6.2f", m[i][j]); 
	printf("\n"); 
} 

//liberazione memoria dinamica (niente di automatico)
for (i=0; i<nr; i++) 
	free(m[i]); //Prima le singole righe (una alla volta)
free(m); //Poi il vettore dei puntatori alle righe
...
```
---
#### Vettori e matrici creati da funzioni
Un vettore o matrice dinamici sono accessibili da un puntatore. Il puntatore è un dato, che può quindi essere passato e/o ritornato da funzioni come pure copiato tra variabili.
Le varaibili puntatore esistono finche è in essere la funzione dove sono dichiarate e sono visibili in essa. Di solito le matrici e vettori creati in una funzione vengono utilizzati solamente li oppure può essere necessario che siano accessibili da altre funzioni.
Per fare in modo che un'altra funzione usi il vettore puntatore è sufficiente **passare il puntatore per valore:**
>Esempio (Puntatore come valore di ritorno della funzione)
```c
typedef ... Item; 
Item **malloc2dR(int nr, int nc); //funzione di tipo puntatore a vettore di Item
void free2d(Item **m, int nr); 
... 
void h (/* parametri formali */) { 
	Item **matr; //matrice di Item
	int nr, nc; 
	... 
	matr = malloc2dR(nr, nc); 
	... /* lavoro su matr */ 
	free2d(matr,nr); 
}

Item **malloc2dR(int nr, int nc) { //funzione di tipo puntatore a vettore di Item
	Item **m; //m variabile locale (doppio puntatore): puntatore a vettore di puntatori (righe)
	int i; 
	m = malloc (nr*sizeof (Item *)); 
	for (i=0; i<nr; i++) { 
		m[i] = malloc (nc*sizeof (Item)); 
	} 
	return m; //m ritornato come risultato
} 

/*
Free più facile: 
	• riceve puntatore /by value) 
	• non restituisce risultato
*/
void free2d(Item **m, int nr) { 
	int i; 
	for (i=0; i<nr; i++) { 
		free(m[i]); // Prima libera le singole righe, poi il vettore di puntatori
	} 
	free(m); 
}
```

>Esempio (Puntatore come parametro by pointer/reference)
```c
typedef ... Item; 
//funzione di tipo void, con parametro puntatore a a matrice di Item
void malloc2dP(Item ***mp, int nr, int nc); 
void free2d(Item **m, int nr); 
... 
void h (/* parametri formali */) { 
	Item **matr; //matrice di Item
	int nr, nc; 
	... 
	malloc2dP(&matr, nr, nc); 
	... /* lavoro su matr */ 
	free2d(matr,nr); 
}

void malloc2dP(Item ***mp, int nr, int nc) { 
	Item **m; //m variabile locale (doppio puntatore): non obbligatoria ma comoda «dentro» alla funzione
	int i; 
	m = (Item **)malloc (nr*sizeof(Item *)); 
	for (i=0; i<nr; i++) 
		m[i] = (Item *)malloc (nc*sizeof(Item)); 
	*mp = m; //m copiata in *mp (risultato) al termine della funzione (equivale a matr = m)
} 

void free2d(Item **m, int nr) { 
	int i; 
	for (i=0; i<nr; i++) { 
		free(m[i]); 
	} 
	free(m); 
}
```

>mp: puntatore a matrice di Item **puntatore (triplo):** puntatore a un puntatore a un vettore (puntatore a Item) di righe, **punta a variabile del programma chiamante (puntatore doppio) in cui occorre trasferire il risultato**.
---
#### Vettori a dimensione variabile
Se serve solo dimensionare vettori e matrici in fase di esecuzione esistono anche i varaible length arrays.
Si dichiara un vettore/matrice come variabile locale usando come dimensioni variabili o espressioni al posto delle costanti, allocazione e deallocazione sono automatiche e implicite.
L'uso di questo tipo di vettori è scoraggiato in quanto:
- Sono un sottoinsieme dell'allocazione dinamica
- **Presentano svantaggi:**
	- Non si può controllare se l’allocazione è andata a buon fine : l’effetto è un crash, quando lo stack è troppo piccolo.
	- Il vettore è cancellato all’uscita dalla funzione, ma il programmatore può pensare che esista ancora e continua a farvi riferimento
---
