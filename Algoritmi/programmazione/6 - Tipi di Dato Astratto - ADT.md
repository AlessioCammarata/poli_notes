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
- enfasi sull’algoritmo e non sui dati ▪ prelude al polimorfirmo ▪ Tuttavia NON si tratta di un tipo generico, ma di una soluzione che concentra eventuali modifiche all’interno dell’ADT Sono accettabili soluzioni ▪ quasi ADT o con tipo visibile al client (che può tuttavia ignorare la visibilità), non necessariamente dinamico ▪ ADT di I classe o dato nascosto, ma allocazione dinamica e puntatori
---
###### Tipo 1 
Semplice scalare, chiave coincidente.
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
```c
typedef struct item { 
	char name[MAXC]; 
	int num; 
} Item; 
typedef char *Key;
```
Essendo la stringa statica, è interna alla struct e la chiave punta al (a parte del) dato.
###### Tipo 4: composto per riferimento
struct con vettore di caratteri allocato dinamicamente e intero. La stringa dinamica è proprietà dell’ADT (composizione per riferimento). La chiave è il vettore di caratteri.
```c
typedef struct item { 
	char *name; 
	int num; 
} Item; 
typedef char *Key;
```
Essendo la stringa dinamica, è esterna alla struct e la chiave punta al (a parte del) dato.
##### Scelte
quando (la chiave) è un puntatore, la chiave punta al dato o a parte del dato (non si genera un duplicato). 
- Non è l’unica scelta possibile: ci sono programmi e/o funzioni in cui la chiave è esterna al dato (un’aggiunta) 
Funzioni di interfaccia indipendenti dallo specifico Item per quanto possibile.
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
Serie di implementazioni di ***item.c***.
###### Implementazione 1
```c
//direttive #include d’ora in poi omesse
Key KEYget(Item val) { 
	return (val);
} 
int KEYcompare (Key k1, Key k2){
	return (k1-k2); 
} 
Item ITEMscan() { 
	Item val; scanf("%d", &val); 
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
```c
slide 28
```
###### Implementazione 3
```c
slide 29
```
###### Implementazione 4
```c
slide 30
```
---
