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