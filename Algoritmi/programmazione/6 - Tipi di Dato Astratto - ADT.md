Cerchiamo di costruire delle strutture dati che possiamo riutilizzare il piu possibile nel nostro codice.
> Scegliere una adeguata struttura dati per: 
- **codificare** le informazioni del problema proposto (in input, risultati intermedi e finali) 
- consentire la manipolazione delle informazioni (le **operazioni**)

Le informazioni in forma utilizzabile da un sistema di elaborazione si dicono **dati** e sono memorizzati in **strutture dati:** 
- ==interne== (memoria centrale) 
- ==esterne== (memoria di massa) 
- ==statiche== (dimensione decisa in stesura del programma e fissa nel tempo) 
- ==dinamiche== (dimensione decisa in fase di utilizzo e variabile nel tempo)

>Devo sapere i tipi di dati disponibili che possono essere:
- **Base**, elementari forniti dal linguaggio
- **Definiti dall'utente,** typedef o struct
- **Tipi di dati astratti**: netta separazione tra definizione e implementazione.
###### ADT
**Scopo** 
Livello di astrazione sui dati tale da mascherare completamente l’implementazione rispetto all’utilizzo 
**Definizione**:
- tipo di dato (valori + operazioni) accessibile **SOLO** attraverso un’**interfaccia**. 
- utilizzatore = **client**.
- specifica del tipo di dato = **implementazione**.
##### Creazione di ADT
>Il C non ha un meccanismo semplice ed automatico di creazione di ADT.
>L’ADT è realizzato come modulo con una coppia di file interfaccia/implementazione.
>Enfasi su come nascondere i dettagli dell’implementazione al client.
###### Quasi ADT
È un ADT con qualche eccezione.
**Interfaccia** 
- definizione del nuovo tipo con typedef 
- raramente si appoggia su tipi base, in generale è un tipo composto, aggregato o contenitore (struct wrapper) 
- Prototipi delle funzioni 
**Implementazione**: 
	Il client include il file header, quindi vede i dettagli interni del dato e/o del wrapper.

Esempio: 
	nuovo tipo Complex 
	- struct con campi per parte reale e coefficiente dell’immaginario 
	- funzione di prodotto tra 2 numeri complessi. 
	Il client che include complex.h vede i dettagli della struct (ma non li usa)
```c
//Comlex.h
typedef struct { 
	float Re; float Im; 
} Complex; 

Complex prod(Complex c1, Complex c2);

//complex.c
#include "complex.h" 
Complex prod(Complex c1, Complex c2) { //Sto lavorando by value
	Complex c; 
	c.Re = c1.Re * c2.Re - c1.Im * c2.Im; 
	c.Im = c1.Re * c2.Im + c2.Re * c1.Im; 
	return c; //Si passa la c tramite un'altra memcopy
}

//main.c
#include "complex.h" 
int main (void) { 
	Complex a, b, c; 
	... 
	c = prod(a,b); //Sto facendo una memcopy perche non sto usando puntatori
	... 
}
```
Nel client si potrebbe fare c.Re = 5, quindi variare i dati manualmente, per questo è "quasi" ADT.

---
###### ADT di I classe
Per impedire al client di vedere i dettagli della struct: 
- il tipo di dato viene dichiarato nel file .h di interfaccia come struttura incompleta, o come puntatore a struct incompleta, non viene quindi definita la struct composto, aggregato o wrapper 
- la struct viene invece completamente definita nel file .c 
- il client utilizza unicamente puntatori alla struttura incompleta 
- Il puntatore è opaco e si dice ***handle***.
Esempio:
	Interfaccia ad ADT per numeri complessi : complex.h: 
		- nuovo tipo Complex come **puntatore** a struct complex_s 
		- prototipi della funzione di prodotto tra 2 numeri complessi e delle funzioni di creazione e distruzione 
	Implementazione: complex.c: 
		- definizione completa del tipo struct complex_s 
		- della funzione di prodotto tra 2 numeri complessi e delle funzioni di creazione e distruzione 
>**Il client che include complex.h NON vede i dettagli della struct.**
```c
//complex.h
typedef struct complex_s *Complex;

Complex crea(void); 
void distruggi(Complex c); 
Complex prod(Complex c1, Complex c2);

//complex.c
#include "complex.h" 
struct complex_s { 
	float Re; float Im; 
}; 
Complex crea(void) { 
	Complex c = malloc(sizeof *c); 
	return c; 
} 

void distruggi(Complex c) { 
	free(c); 
} 

Complex prod(Complex c1, Complex c2) { 
	Complex c = crea(); 
	c->Re = c1->Re * c2->Re - c1->Im * c2->Im; 
	c->Im = c1->Re * c2->Im + c2->Re * c1->Im; 
	return c; 
}

//main.c
#include "complex.h" 
int main (void) { 
	Complex a, b, c; 
	a = crea(); 
	b = crea(); 
	... 
	c = prod(a,b); 
	... 
	distruggi(a); 
	distruggi(b); 
	distruggi(c); 
}
```
###### Quasi ADT o ADT di I classe? 
Per i casi semplici di dati composti o aggregati, che non prevedano allocazione dinamica, il quasi ADT: 
- è un ragionevole compromesso:
	- non nasconde completamente i dettagli interni 
	- **non richiede allocazione dinamica** 
- costituisce una soluzione più semplice e pratica.
##### ADT Item 
Tipo di dato generico per dato unico o record che include un campo chiave (composto o aggregato: dipende dai casi). 
Esempi: 
	- numero 
	- stringa 
	- dati su una persona 
	- numero complesso 
	- punto di piano o spazio
	-…
#### Vantaggi dell’ADT 
enfasi sull’algoritmo e non sui dati e prelude al polimorfismo. (Il dato può cambiare forma)
Tuttavia NON si tratta di un tipo generico, ma di una soluzione che concentra eventuali modifiche all’interno dell’ADT.
Sono accettabili soluzioni:
- quasi ADT ->con tipo visibile al client (che può tuttavia ignorare la visibilità), non necessariamente dinamico 
- ADT di I classe -> dato nascosto, ma allocazione dinamica e puntatori
---
##### Versione quasi ADT
Quando definisco l'item all'interno di una struttura dati, è utile avere una chiave che identifica l'item. (Per esempio primary key, la matricola definisce la struct perchè è univoca).
###### Tipo 1 
Semplice scalare, chiave coincidente.
>Associamo il tipo di chiave all'Item
```c
typedef int Item; 
typedef int Key;
```
Nessun problema di proprietà, in quanto non c’è allocazione dinamica
###### Tipo 2
Vettore dinamico di caratteri chiave coincidente 
```c
typedef char *Item; 
typedef char *Key;
```
Item e chiave sono puntatori a carattere e la chiave punta al dato.
###### Tipo 3: composto per valore
struct con vettore di caratteri sovradimensionato staticamente e intero (composizione per valore). La chiave è il vettore di caratteri. 
>Le cose che stanno all'interno devono essere finite, per esempio le stringhe devono avere il MAXC. Quando alloco la struct alloco anche ciò che sta al suo interno.
>Quando faccio il free (distruggi) della struct si distrugge tutto perché non ci sono altre malloc.
```c
typedef struct item { 
	char name[MAXC]; 
	int num; 
} Item; 
typedef char *Key; //In questo caso la chiave è il name
```
Essendo la stringa statica, è interna alla struct e la chiave punta al (a parte del) dato.
###### Tipo 4: composto per riferimento
struct con vettore di caratteri allocato dinamicamente e intero. La stringa dinamica è proprietà dell’ADT (composizione per riferimento). La chiave è il vettore di caratteri.
>Definisco le cose anche con puntatori. In questo caso quando voglio distruggere devo fare le malloc anche degli elementi interni (in questo caso del nome). 
```c
typedef struct item { 
	char *name; 
	int num; 
} Item; 
typedef char *Key; //In questo caso la chiave è il name
```
Essendo la stringa dinamica, è esterna alla struct e la chiave punta al (a parte del) dato.
##### Scelte
- quando (la chiave) è un puntatore, la chiave punta al dato o a parte del dato (non si genera un duplicato). 
	- Non è l’unica scelta possibile: ci sono programmi e/o funzioni in cui la chiave è esterna al dato (un’aggiunta) 
- Funzioni di interfaccia indipendenti dallo specifico Item per quanto possibile.
##### Funzioni di interfaccia indipendenti da Item
```c
/* definizione di Item e Key */ 
int KEYcompare(Key k1, Key k2); 
Key KEYscan();

Item ITEMscan(); 
void ITEMshow(Item val); 
int ITEMless(Item val1, Item val2); 
int ITEMgreater(Item val1, Item val2); 
int ITEMcheckvoid(Item val); 
Item ITEMsetvoid();
```
##### Funzioni di interfaccia dipendenti da Item
```c
// Caso 1 e 2
Key KEYget(Item val); //struct passata per valore

// Caso 3 e 4
Key KEYget(Item *pval);
/*
la chiave è un riferimento a un campo di Item. Se la struct fosse passata per valore, il puntatore sarebbe un riferimento alla copia locale della stringa, deallocato all’uscita della funzione
*/
```
---
##### Implementazioni
Serie di implementazioni di ***item.c***. (Rispetto a ciò che abbiamo definito prima)
###### Implementazione 1
```c
//direttive #include d’ora in poi omesse
Key KEYget(Item val) { 
	return (val);
} 
int KEYcompare (Key k1, Key k2){
	return (k1-k2); 
} 
Item ITEMscan() { //Creo il valore e faccio scanf
	Item val; 
	scanf("%d", &val); 
	return val; 
} 
void ITEMshow(Item v) { 
	printf("%d", val); 
} 
int ITEMless(Item val1, Item val2) { 
	return (KEYget(val1)<KEYget(val2));
}
```
###### Implementazione 2
Static significa che è visibile a tutte le funzioni all'interno di questo file. 
Variabile globale solo in compilazione, poi viene tolto.
```c
//vettore statico sovradimensionato per acquisire le stringhe
static char buf[MAXC]; 

Key KEYget(Item val) { 
	return (val); 
} 
int KEYcompare (Key k1, Key k2) { 
	return (strcmp(k1,k2)); 
} 
//Prendo qualsiasi cosa e la metto in buf, poi lo duplico dinamicamente.
Item ITEMscan() { 
	scanf("%s",buf); 
	return strdup(buf); //La strdup fa la malloc
} 
void ITEMshow(Item val) { 
	printf("%s", val); 
} 
int ITEMless(Item val1, Item val2) { 
	return (strcmp(KEYget(val1),KEYget(val2))<0); 
}
```
###### Implementazione 3
```c //Composizione per valore
/*
struct con 
- vettore di caratteri 
- intero 
La chiave è il vettore di caratteri
*/
Key KEYget(Item *pval) { 
	return (pval->name); 
} 
int KEYcompare (Key k1, Key k2) { 
	return (strcmp(k1,k2)); 
} 
Item ITEMscan() { //Composizione per valore (NO MALLOC)
	Item val; //Creo valore che va nello stack
	scanf("%s %d", val.name, &(val.num)); 
	return val; //Restituisco una copia di val e poi chiudo
} 
void ITEMshow(Item val) { 
	printf("%s %d", val.name, val.num); 
} 
int ITEMless(Item val1, Item val2) { 
	return (strcmp(KEYget(&val1),KEYget(&val2))<0); 
}
```
###### Implementazione 4
```c
static char buf[MAXC]; 

Key KEYget(Item *pval) { 
	return (pval->name);
} 
int KEYcompare (Key k1, Key k2) { 
	return (strcmp(k1,k2));
} 
/*
struct con 
- vettore di caratteri dinamico
- intero 
La chiave è il vettore di caratteri
*/
Item ITEMscan() { 
	Item val; 
	scanf("%s %d", buf, &(val.num)); 
	val.name = strdup(buf); //Malloc implicita *name
	return val; //Return by value, copia di val
} 
void ITEMshow(Item val) { 
	printf("%s %d", val.name, val.num); 
} 
int ITEMless(Item val1, Item val2) { 
	return (strcmp(KEYget(&val1),KEYget(&val2))<0); 
}
```
---
>Caso critico: il client legge 2 dati di tipo Item, li elabora e poi li distrugge:
```c
a = ITEMscan(); 
b = ITEMscan(); 
// elabora a e b 
ITEMfree(a); ITEMfree(b);
```
La de-allocazione ha senso se c’è stata allocazione, quindi solo nei casi 2 e 4, non nei casi 1 e 3. Due casi: il client 
- rinuncia a de-allocare (oppure chiama funzioni di de-allocazione fittizie, che non fanno nulla) 
- tratta diversamente i casi con allocazione e senza, diventando dipendente da Item.
###### Conclusione
La soluzione 1 e 3 sono accettabili, la 2 anche mentre la 4 no.
Con le quasi-ADT è meglio non usare troppo allocazione dinamica, in generale quasi-ADT meglio usare quando **non c'è allocazione dinamica.**

---
##### Versione ADT I Classe
L’ADT di prima classe ha senso per dati «complessi», quindi per le tipologie 3 e 4 di Item basati su struct.
Nelle tipologie 1 e 2 la chiave è talmente semplice che una soluzione a quasi ADT è accettabile.
```c
typedef struct item *Item; // Item è un puntatore a struct incompleta e quindi invisibile
typedef char *Key; // Il client conosce il tipo key
```
Funzioni comuni alle tipologie 3 e 4:
```c
Key KEYget(Item val) { 
	return (val->name); 
} 
int KEYcompare (Key k1, Key k2) { 
	return (strcmp(k1, k2)); 
} 
void ITEMshow(Item val) { 
	printf("%s %d", val->name, val->num); 
} 
int ITEMless(Item val1, Item val2) { 
	return (strcmp(KEYget(val1),KEYget(val2))<0); 
}
```
###### Implementazione 3
```c
// Allocazione e de-allocazione della struct
Item ITEMnew(void) { 
	Item val=(Item)malloc(sizeof(struct item)); 
	if (val==NULL) 
		return ITEMsetvoid(); 
	val->name[0] = '\0'; 
	val->num = 0; 
	return val; 
} 
void ITEMfree(Item val) { 
	free(val); 
}

// dato creato (e valori assegnati) internamente alla ITEMscan
Item ITEMscan() { 
	Item val = ITEMnew(); 
	if (val != NULL) { 
		scanf("%s %d", val->name, &val->num); 
	} 
	return val; 
}
```
###### Implementazione 4
```c
//Allocazione della struct che include la stringa vuota
Item ITEMnew(void) { 
	Item val=(Item)malloc(sizeof(struct item)); 
	if (val==NULL) 
		return ITEMsetvoid(); 
	val->name = NULL; //La stringa non contiene ancora niente
	val->num = 0; 
	return val; 
} 
//deallocazione stringa se non vuota
void ITEMfree(Item val) { 
	if (val->name!=NULL) 
		free(val->name); 
	free(val); 
}
//dato creato (e valori assegnati) internamente alla ITEMscan
Item ITEMscan() { 
	Item val = ITEMnew(); 
	if (val != NULL) { 
		scanf("%s %d", buf, &val->num); 
		val->name = strdup(buf); //malloc implicita (Gia visto sopra)
	} 
	return val; 
}
//VERSIONE 2
//Item già creato, passato per riferimento.
//Item ricevuto per riferimento e valori assegnati internamente alla ITEMscan
void ITEMscan(Item val) { 
	scanf("%s %d", buf, &val->num); 
	val->name = strdup(buf); 
}
```
###### Conclusione
Le ADT di I classe è ottimo nel caso 4 (campo stringa dinamica).
Con ITEMnew e ITEMscan garantisce al client completa responsabilità su allocazione/deallocazione

---
### ADT per collezioni
È suggerita la soluzione ADT di I classe 
Operazioni principali:
- **insert**: inserisci nuovo oggetto nella collezione 
- **delete**: cancella un oggetto della collezione 
Altre operazioni:
- inizializzare struttura dati 
- conteggio elementi (o verifica collezione vuota) 
- distruzione struttura dati 
- copia struttura dati
##### ADT di I classe lista (non ordinata)
```c
//list.h
typedef struct list *LIST; 
void listInsHead (LIST l, Item val); 
Item listSearch(LIST l, Key k); 
void listDelKey(LIST l, Key k);

//list.c
typedef struct node *link; 
struct node { 
	Item val; 
	link next; 
}; 
struct list { 
	link head; 
	int N; 
}; 
void LISTinsHead (LIST l, Item val) { 
	l->head = newNode(val,l->head); 
	l->N++; 
} 
//implementazione delle altre funzioni
```
###### Vantaggi dell’ADT di I classe 
L’ ADT di I classe: 
1. nasconde al client i dettagli 
2. permette al client di istanziare più variabili del tipo dell’ADT 
Un quasi ADT viola una delle 2 regole precedenti o entrambe. I quasi ADT visti sinora (per composti/aggregati) violavano la prima regola.
#### Non ADT
Per gli ADT collezioni di dati può bastare avere a disposizione un solo contenitore, facendone una variabile globale dell’implementazione. 
Scompare il tipo di dato per la collezione (non c’è un’istruzione typedef). Sarebbe meglio chiamarlo non ADT, ma si mantiene il nome storico di «quasi ADT».

```c
//list.h
void listInsHead (Item val); 
Item listSearch(Key k); 
void listDelKey(Key k); //manca typedef e non c’è il parametro LIST l

//list.c
typedef struct node *link; // definizione di nodo e di puntatore a nodo
struct node { 
	Item val; 
	link next; 
} ; 

static link head=NULL; //variabili globali per puntatore alla testa e cardinalità
static int N=0; 

void LISTinsHead (Item val) { 
	head = newNode(val,head); 
	N++; 
} 
//implementazione delle altre funzioni
```
##### ADT di I classe Set (insieme)
```c
//set.h
typedef struct set *SET; 
SET SETinit(int maxN); 
void SETfree(SET s); 
void SETfill(SET s, Item val); 
int SETsearch(SET s, Key k); 
SET SETunion(SET s1, SET s2); 
SET SETintersection(SET s1, SET s2); 
int SETsize(SET s); 
int SETempty(SET s); 
void SETdisplay(SET s);
```

>Può essere definito in qualsiasi modo, pero il modo in cui viene fatto poi influenza le prestazioni degli algoritmi in cui queste strutture dati vengono utilizzate.

###### Vantaggi/svantaggi 
- la dimensione della lista virtualmente può crescere all’infinito, mentre il vettore va dimensionato 
- complessità della funzione SETsearch di appartenenza: 
	- vettore ordinato ->ricerca dicotomica ->O(logN) 
	- vettore non ordinato -> ricerca lineare -> O(N) 
	- lista (ordinata/non ordinata) -> ricerca lineare -> O(N) 
- complessità delle funzioni SETunion e SETintersection: 
	- vettore/lista ordinato -> O(N) 
	- vettore/lista non ordinato -> O(N^2 )
##### Implementazione con vettore ordinato
```c
//set.c
struct set { 
	Item *v; 
	int N; //Dimensione massima
}; 
SET SETinit(int maxN) { 
	SET s = malloc(sizeof *s); // wrapper
	s->v = malloc(maxN*sizeof(Item)); 
	s->N=0; 
	return s; 
} 
void SETfree(SET s) { 
	free(s->v); 
	free(s); 
}

//Ricerca dicotomica
int SETsearch(SET s, Key k) { 
	int l = 0, m, r = s->N -1; 
	while (l <= r) { 
		m = l + (r-l)/2; 
		if (KEYeq(key(s->v[m]), k)) 
			return 1; 
		if (KEYless(key(s->v[m]), k)) 
			l = m+1; 
		else 
			r = m-1; 
	} 
	return 0; 
}

//strategia simile alla Merge del MergeSort
SET SETunion(SET s1, SET s2) { 
	int i=0, j=0, k=0, size1=SETsize(s1); 
	int size2=SETsize(s2); 
	SET s; 
	s = SETinit(size1+size2); //Size ottenuta dal caso peggiore, tutti gli elementi diversi
	for(k = 0; (i < size1) || (j < size2); k++) 
		if (i >= size1) 
			s->v[k] = s2->v[j++]; 
		else if (j >= size2) 
			s->v[k] = s1->v[i++]; 
		else if (ITEMless(s1->v[i], s2->v[j])) 
			s->v[k] = s1->v[i++]; 
		else if (ITEMless(s2->v[j], s1->v[i])) 
			s->v[k] = s2->v[j++]; 
		else { 
			s->v[k] = s1->v[i++]; 
			j++; 
		}
	} 
	s->N = k; //Imposto la nuova lunghezza
	return s; 
}

/*
int min (int x, int y) { 
	if (x <= y) 
		return x; 
	return y; 
}
*/
SET SETintersection(SET s1, SET s2) { 
	int i=0, j=0, k=0, size1=SETsize(s1); 
	int size2=SETsize(s2), minsize; 
	SET s; 
	minsize = min(size1, size2); //Definizioe di min nel commento
	s = SETinit(minsize); 
	while ((i < size1) && (j < size2)) { 
		if (ITEMeq(s1->v[i], s2->v[j])) { 
			s->v[k++] = s1->v[i++]; 
			j++; 
		} else if (ITEMless(s1->v[i], s2->v[j])) 
			i++; 
		else j++; 
	} 
	s->N = k; 
	return s; 
}
```
##### Implementazione con vettore ordinato
```c
typedef struct SETnode *link; 
struct set { link head; int N; }; 
struct setNode { Item val; link next; }; 
SET SETinit(int maxN) { 
	SET s = malloc(sizeof *s); 
	s->head = NULL; 
	s->N = 0; 
	return s; 
} 

void SETfree(SET s) { 
	link x, t; 
	for (x=s->head; x!=NULL; x=t) { 
		t = x->next; 
		free(x); 
	} 
	free(s); 
}
//Ricerca lineare
int SETsearch(SET s, Key k) { 
	link x; 
	x = s->head; 
	while (x != NULL) { 
		if (KEYeq(key(x->val), k)) 
			return 1; 
		x = x->next; 
	} 
	return 0; 
}

/*
Metto i dati della prima lista nel risultato, poi
Inserisco gli elementi della seconda lista che non sono gia presenti nella soluzione.

*/
SET SETunion(SET s1, SET s2) { 
	link x1, x2; 
	int founds2, counts2=0; 
	SET s = SETinit(s1->N + s2->N); 
	x1 = s1->head; 
	while (x1 != NULL) { 
		SETfill(s, x1->val); 
		x1 = x1->next;
	} 
	for (x2 = s2->head; x2 != NULL; x2 = x2->next) { 
		x1 = s1->head; 
		founds2 = 0; 
		while (x1 != NULL) { 
			if (ITEMeq(x1->val, x2->val)) founds2 = 1; 
			x1 = x1->next; 
		} 
		if (founds2 == 0) { 
			SETfill(s, x2->val); 
			counts2++; 
		} 
	} 
	s->N = s1->N + counts2; 
	return s; 
}

SET SETintersection(SET s1, SET s2) { 
	link x1, x2; 
	int counts=0; 
	SET s; 
	s = SETinit(s1->N + s2->N); 
	x1 = s1->head; 
	while (x1 != NULL) { 
		x2 = s2->head; 
		while (x2 != NULL) { 
			if (ITEMeq(x1->val, x2->val)) { 
				SETfill(s, x1->val); 
				counts++; 
				break;
			} 
			x2 = x2->next; 
		} 
		x1 = x1->next; 
	} 
	s->N = counts; 
	return s; 
}
```
#### Code Generalizzate
Sono collezioni di oggetti (dati) di tipo Item con operazioni principali: 
- **Insert**: inserisci un nuovo oggetto nella collezione 
- **Search**: ricerca se un oggetto è nella collezione 
- **Delete**: cancella un oggetto della collezione 
Altre operazioni: 
- inizializzare la coda generalizzata 
- conteggio oggetti (o verifica collezione vuota) 
- distruzione della coda generalizzata 
- copia della coda generalizzata

>Utilizzando il concetto di coda.
###### Coda cronologica
- estrazione dell’elemento inserito più recentemente 
	- politica **LIFO**: **Last-In First-Out** 
	- **stack o pila** 
	- inserzione (push) ed estrazione (pop) dalla testa 
- estrazione dell’elemento inserito meno recentemente 
	- politica **FIFO**: **First-In First-Out** 
	- **queue o coda** 
	- inserzione (enqueue o put) in coda (tail) ed estrazione (dequeue o get) dalla testa (head)
###### Coda a priorità
L’inserzione garantisce che, estraendo dalla testa, si ottenga il dato a priorità massima (o minima).
###### Coda casuale
Estraendo si ottiene un dato a caso
###### Tabella di Simboli
L’estrazione ritorna un contenuto secondo determinati criteri.

>Controlli pieno/vuoto per evitare di inserire in coda piena o estrarre da coda vuota. 
>Scelta tra 2 strategie: 
>	1. il client tiene conto del numero di dati nella coda oppure l’ADT fornisce funzioni di interfaccia per il controllo pieno/vuoto 
>	2. l’ADT controlla la correttezza delle operazioni, indicando il successo/fallimento. 
>Nel seguito si adotta la prima strategia (la più semplice per l’implementazione).
##### ADT pila (stack)
Definizione: ADT che supporta operazioni di 
- STACKpush: inserimento in cima 
- STACKpop: preleva (e cancella) dalla cima l’oggetto inserito più di recente 
Terminologia: la strategia di gestione dei dati è detta **LIFO** (Last In First Out)

**Versioni possibili**:
con vettore 
- quasi ADT 
- ADT di I classe 
con lista 
- quasi ADT 
- ADT di I classe
###### Vettore vs. lista: vantaggi/svantaggi
Spazio: 
- **vettore**: spazio allocato sempre pari al massimo previsto, ***vantaggioso per stack quasi pieni***
- **lista**: spazio utilizzato proporzionale al numero di elementi correnti, ***vantaggioso per stack che cambiano rapidamente dimensione***
Tempo: 
- **push e pop** T(n) = O(1)
###### Quasi ADT vs. ADT I classe
Quasi ADT 
- implementazione mediante variabili **globali** (dichiarate fuori da funzioni) e **invisibili** da altri file sorgenti (static)
ADT di I classe 
- una struct puntata (da handle), contenente, come campi, la variabili globali del quasi ADT.
###### Implementazione con vettore
Slide 69
###### Implementazione con lista
Slide 73

##### L’ADT coda (queue) 
Definizione: ADT che supporta operazioni di: 
- **enqueue/put**: inserisci un elemento (QUEUEput) 
- **dequeue/get**: preleva (e cancella) l’elemento che è stato inserito meno recentemente (QUEUEget) 
Terminologia: la strategia di gestione dei dati è detta **FIFO** (First In First Out).
###### Vettore vs. lista: vantaggi/svantaggi 
Spazio: 
- vettore: spazio allocato sempre pari al massimo previsto, vantaggioso per code quasi piene 
- lista: spazio utilizzato proporzionale al numero di elementi correnti, vantaggioso per code che cambiano rapidamente dimensione 
Tempo: put e get T(n) = O(1). 

>Con le liste, vale sempre invece per il vettore si fanno buffer circolari.
>***buffer circolare***:
- put assegna alla prima cella libera, se esiste, in posizione indicata da indice tail (O(1)) 
- get da posizione variabile (head assume valori tra 0 e N-1). Le celle del vettore occupate da elementi si spostano per via di put e get (buffer circolare). 
	- head e tail sono incrementati MODULO N (N-2, N-1, 0, 1, …)
	- Non è più garantito head<=tail: 
		- coda vuota: head raggiunge tail 
		- coda piena: tail raggiunge head
###### Quasi ADT vs. ADT I classe 
Quasi ADT 
- implementazione mediante variabili globali (dichiarate fuori da funzioni) e invisibili da altri file sorgenti (static) 
ADT di I classe 
- una struct puntata (da handle), contenente, come campi, la variabili globali del quasi ADT.


---