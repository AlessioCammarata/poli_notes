Finora gli algoritmi di ricerca si erano basati sul confronto. 
Eccezione: tabelle ad accesso diretto dove la chiave k funge da **indice** di un array st[0, 1, …, card(U)-1].
Limiti delle tabelle ad accesso diretto: 
- |U| grande (vettore st non allocabile) 
- |K| << |U| (spreco di memoria).

**Tabella di hash**: è un ADT con occupazione di spazio O(|K|) e tempo medio di accesso O(1). La funzione di **hash** trasforma la chiave di ricerca in un indice della tabella. 
La funzione di hash non può essere perfetta --> **collisione**. 
Usate per inserzione, ricerca, cancellazione, non per ordinamento e selezione.
>In hash non esiste il concetto di ordinamento.

```c
//ST.h
typedef struct symboltable *ST; 
ST STinit(int maxN, float r) ; 
void STinsert(ST st, Item val); 
Item STsearch(ST st, Key k) ; 
void STdelete(ST st, Key k) ; 
void STdisplay(ST st) ; 
void STfree(ST st); 
int STcount(ST st); 
int STempty(ST st);
```
#### Funzione di Hash
-  La tabella di hash ha dimensione M e contiene |K| elementi (|K|<<|U|) 
- La tabella di hash ha indirizzi nell’intervallo [0 … M-1] 
- La funzione di hash h mette in corrispondenza una chiave k con un indirizzo della tabella h(k) 
	h: U -> { 0, 1, ..., M-1 } 
-  L’elemento x viene memorizzato all’indirizzo h(k) dato dalla sua chiave k (attenzione alla gestione delle collisioni!).
##### Progetto della funzione di hash
Funzione ideale: hashing uniforme semplice: se le chiavi k sono equiprobabili, allora i valori di h(k) devono essere equiprobabili. 
In pratica, le chiavi k non sono equiprobabili, anzi chiavi diverse ki, kj sono correlate. 
Per rendere i valori di h(k) equiprobabili occorre: 
- rendere h(ki) scorrelato da h(kj) 
	- “amplificare” le differenze 
	- scorrelare h(k) da k 
- distribuire gli h(k) in modo uniforme: 
	- usare tutti i bit della chiave 
	- moltiplicare per un numero primo.
##### Tipologie di funzioni di hash
- **Metodo moltiplicativo**
chiavi: numeri in virgola mobile in un intervallo prefissato ( s <= k < t): 
	h(k) = (k -s) /(t - s) * M
```c
int hash(float k, int M, float s, float t) {
	return ((k-s)/(t-s))*M; 
}
```
Esempio: 
	M = 97, s = 0.0, t = 1.0 
	k = 0.513870656 
	h(k) = (0.513870656 -0) /(1 - 0) * 97 = 49
- **Metodo modulare**
chiavi: numeri interi; M numero primo 
	h(k) = k % M
```c
int hash(int k, int M){ 
	return (k%M); 
}
```
Esempio: 
	M = 19 
	k = 31 
	h(k) = 31 % 19 = 12
M numero primo evita: 
- **di usare solo gli ultimi n bit di k se M = 2^n** 
- **di usare solo le ultime n cifre decimali di k se M = 10n .**

- **Metodo modulare:**
chiavi: stringhe alfanumeriche corte come interi derivati dalla valutazione di polinomi in una data base 
- M numero primo 
- h(k) = k % M

Esempio:
	stringa now = ‘n’\*$128^2$ + ‘o’\*128 + ‘w’ 
			= 110\*$128^2$ + 111\*128 + 119 
			k = 1816567 
	k = 1816567 M = 19 
	h(k) = 1816567 % 19 = 15

>Ottengo sempre un numero che si ottiene da prodotti e somme.

chiavi: stringhe alfanumeriche lunghe come interi derivati dalla valutazione di polinomi in una data base con il metodo di Horner: ad esempio 
$$
P_7(x) = p_7x^7 +p_6x^6 + p_5x^5 +p_4x^4 +p_3x^3 +p_2x^2 +p_1^x+p_0 = 
((((((p_7x+p_6 )x + p_5 )x+p_4 )x+p_3 )x+p_2 )x+p_1 )x+p_0 
$$Come prima: 
M numero primo 
$$
h(k) = k % M
$$
Esempio:
	stringa averylongkey con base 128 (ASCII) k = 97*12811+118*12810+101*1289 +114*1288 +121*1287 +108*1286+111*1285 +110*1284 +103*1283 +107*1282 +101*1281 +121*1280
	Ovviamente k non è rappresentabile su un numero ragionevole di bit. Con il metodo di Horner: 
	k = ((((((((((97\*128+118)*128+101)*128 +114)*128+121)*128+108)*128+111)*128+110)*128+103)*128+107)*128+101)*128+121

Anche con il metodo di Horner k **non è rappresentabile su un numero ragionevole di bit**. 
È possibile però ad ogni passo eliminare i multipli di M, anziché farlo dopo in fase di applicazione del metodo modulare, ottenendo la seguente funzione di hash per stringhe con base 128 per l’ASCII:
```c
//Funzioni di hash per chiavi stringa con base fissa
int hash (char *v, int M){ 
	int h = 0, base = 128; // 127 essendo un numero prima è meglio
	for (; *v != '\0'; v++) 
		h = (base * h + *v) % M; 
	return h; 
}
```
>Questa funzione da un numero tra 0 ed M ed avrà un tot cifre quante saranno i valori della stringa.

In realtà anche per stringhe ASCII non si usa 128 come base, bensì: 
- un numero primo (ad esempio 127)
- numero pseudocasuale diverso per ogni cifra della chiave (hashuniversale) 
Con lo scopo di ottenere una distribuzione abbastanza uniforme (probabilità di collisione tra 2 chiavi diverse prossima a 1/M).

```c
//Funzioni di hash per chiavi stringa con base prima fissa
int hash (char *v, int M){ 
	int h = 0, base = 127;
	for (; *v != '\0'; v++) 
		h = (base * h + *v) % M; 
	return h; 
}
```

```c
// Funzione di hash per chiavi con stringa con hash universale
int hashU( char *v, int M) { 
	int h, a = 31415, b = 27183; 
	for ( h = 0; *v != '\0'; v++, a = a*b % (M-1)) //Cambio la base 
		h = (a*h + *v) % M; //Moltiplico a per h
	return h; 
}
```
---
#### Collisioni
Una collisione è:
$$
h(k_i)=h(k_j) \ \ per \ \ k_i \not= k_j
$$
Le collisioni sono inevitabili, occorre: 
- minimizzarne il numero (buona funzione di hash): 
- gestirle:
	- **linear chaining** 
	- **open addressing.**
##### Linear Chaining
Più elementi possono risiedere nella stessa locazione della tabella -> lista concatenata. 
Operazioni: 
- inserimento in testa alla lista (Cosi non la scorro)
- ricerca nella lista (Lista non ordinata, si paga complessità lineare)
- cancellazione dalla lista. (Anche qua complessità lineare)
**Determinazione della dimensione M della tabella:** 
- il più piccolo primo M >= numero di chiavi max / r così che la lunghezza media delle liste sia r
```c
//L'esempio usa questo metodo (base prima)
int hash (Key k, intM) { 
	int h = 0, base = 127;
	for (; *k != '\0'; k++)
		h = (base * h + *k) % M;
	return h;
}
```
```c
//ST.c
#include 
#include 
#include 
#include "Item.h" 
#include "ST.h" 

typedef struct STnode* link; 
struct STnode { 
	Item item; 
	link next; 
}; 
struct symbtab { 
	link *heads; // vettore di liste con nodo sentinella in coda
	int N; // numero di chiavi
	int M; // Dimensione tabella
	link z; //Nodo sentinella
}; 

static link NEW( Item item, link next) { 
	link x = malloc(sizeof *x); 
	x->item = item; 
	x->next = next; 
	return x; 
}

ST STinit(int maxN, float r) { 
	int i; 
	ST st; 
	st = malloc(sizeof(*st)); 
	st->N = 0; //Il numero iniziale è 0
	st->M = STsizeSet(maxN, r); // Alloco M ad una certa dimensione STzizeSet (M >= numero di chiavi max / r), numero di righe della hash table
	st->heads = malloc(st->M*sizeof(link)); // Alloco M teste
	st->z = NEW(ITEMsetNull(), NULL); //Creo il nodo sentinella
	for (i=0; i < st->M; i++) //Faccio puntare le teste al nodo sentinella
		st->heads[i] = st->z; 
	return st; 
}

//Supponendo: maxN <= 53
//Questa funzione ritorna il numero primo piu vicino ad maxN/r
static int STsizeSet(int maxN, float r) { 
	int primes[16]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
	int i = 0; 
	int size; 
	size = maxN /r; 
	if (size < primes[15]) { 
		for (i = 0; i<16; i++) 
			if (size <= primes[i]) 
				return primes[i]; 
	} else 
		printf("Too many entries!\n"); 
	return -1; 
}

void STfree(ST st) { 
	int i; 
	link t,u; 
	for(i=0; i<st->M; i++) 
		for (t = st->heads[i]; t != st->z; t = u){ 
			u = t->next; 
			free(t); 
		} 
	free(st->heads); 
	free(st); 
} 
int STcount(ST st) { 
	return st->N; 
} 
int STempty(ST st) { 
	if (STcount(st) == 0) 
		return 1; 
	return 0; 
}

static int hash(Key v, int M) { 
	int h = 0, base = 127; 
	for ( ; *v != '\0'; v++) 
		h = (base * h + *v) % M; 
	return h; 
} 

static int hashU(Key v, int M) { 
	int h, a = 31415, b = 27183; 
	for ( h = 0; *v != '\0'; v++, a = a*b % (M-1)) 
		h = (a*h + *v) % M; 
	return h; 
} 
//Inserimento in testa
void STinsert (ST st, Item val) { 
	int i; 
	//Prendo la chiave del valore, la passo ad hash che mi dice dove puntare nella       linked list
	i = hash(KEYget(&val), st->M); 
	st->heads[i] = NEW(val, st->heads[i]); 
}

Item STsearch(ST st, Key k) { //Wrapper funzione di ricerca 
	//Passo la chiave in cui collide la key che viene passata
	return searchR(st->heads[hash(k, st->M)], k, st->z); 
} 
Item searchR(link t, Key k, link z) { //Ricerca ricorsiva
	if (t == z) 
		return ITEMsetNull(); 
	if ((KEYcmp(KEYget(&t->item), k))==0) 
		return t->item;
	return searchR(t->next, k, z); 
} 
//Cancellazione della chiave
void STdelete(ST st, Key k) { 
	int i = hash(k, st->M); 
	st->heads[i] = deleteR(st->heads[i], k); 
} 
link deleteR(link x, Key k) { 
	//Cerca nella linked list e poi unisce il nodo precedente a quello successivo
	if ( x == NULL ) 
		return NULL; 
	if ((KEYcmp(KEYget(&x->item), k))==0) { 
		link t = x->next; 
		free(x); 
		return t; 
	} 
	x->next = deleteR(x->next, k); 
	return x; 
}

void STdisplay(ST st) { 
	int i; 
	for (i=0; i < st->M; i++) { 
		printf("st->heads[%d] = ", i); 
		visitR(st->heads[i], st->z); 
		printf("\n"); 
	} 
} 
void visitR(link h, link z) { //Visita ricorsiva delle liste linkate
	if (h == z) return; 
	ITEMstore(h->item); 
	visitR(h->next, z); 
}
```
###### Complessità
Ipotesi: 
Liste non ordinate: 
- N =|K| = numero di elementi memorizzati 
- M = dimensione della tabella di hash 
Hashing semplice uniforme: 
	h(k) ha egual probabilità di generare gli M valori di uscita. 
Definizione 
	fattore di carico $\alpha$=N/M (>, = o < 1)
>Quanti elementi ci sono in media per cella?

-  Inserimento: **T(n) = O(1)** 
- Ricerca: 
	- caso peggiore **T(n) = $\theta$(N)** - (Ricerca lineare)
	- caso medio **T(n) = O(1+ $\alpha$)** 
- Cancellazione: 
	- **T(n) = O(1)** se disponibile il puntatore ad x e la lista è doppiamente linkata 
	- Come la ricerca se disponibile il valore di x, oppure il valore della chiave k, oppure la lista è semplicemente linkata
>Solitamente la cancellazione implica la Ricerca.
##### Open Addressing
- Ogni cella della tabella può contenere un solo elemento 
- Tutti gli elementi sono memorizzati in tabella 
- Collisione: ricerca di cella non ancora occupata mediante **probing**: 
	- generazione di una permutazione delle celle = ordine di ricerca della cella libera. Concettualmente:
	h(k, t) : U x { 0,1,...,M-1 } x { 0,1,...,M-1 }
```c
//ST.c
struct symboltable { 
	Item *a; 
	int N; 
	int M;
}; 

ST STinit(int maxN, float alpha) { 
	int i; 
	ST st = malloc(sizeof(*st)); 
	st->N = 0; 
	st->M = STsizeSet(maxN, alpha); 
	if (st->M == -1) 
		st = NULL; 
	else { 
		st->a = malloc(st->M * sizeof(Item) ); //Creo il vettore
		for (i = 0; i < st->M; i++) 
			st->a[i] = ITEMsetNull(); // Inizializzo a NULL
	} 
	return st; 
}

/*
Determinazione della dimensione M della tabella: 
 il più piccolo numero primo M >= maxN/alpha.
*/
//Come prima ma è cambiato il fattore di carico
static int STsizeSet(int maxN, float alpha) { 
	int primes[16]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
	int i = 0; 
	if (maxN < primes[15]*alpha) { 
		for (i = 0; i<16; i++) 
			if (maxN <= primes[i]*alpha) 
				return primes[i]; 
	} else 
		printf("Too many entries!\n"); 
	return -1;
}
```
##### Funzioni di Probing
- Linear probing 
- Quadratic probing 
- Double hashing 

Un problema dell’open addressing è il **clustering**, cioè il raggruppamento di posizioni occupate contigue.
###### Linear Probing
>***Insert***: 
- calcola i = h(k) 
- se libero, inserisci chiave, altrimenti incrementa i di 1 modulo M
- ripeti fino a cella vuota.
```c
void STinsert(ST st, Item item) { 
	int i = hash(KEYget(&item), st->M); 
	while (full(st, i)) // Se è pieno vado in i+1, deve esserci uno spazio vuoto
		i = (i+1)%st->M; 
	//Trovata la posizione inserisco e incremento N.
	st->a[i] = item; 
	st->N++; 
} 

int full(ST st, int i) { 
	if (ITEMcheckNull(st->a[i])) 
		return 0; 
	return 1; 
}
```
>***Search***:
- calcola i = h(k) 
- se trovata chiave, termina con successo 
- incrementa i di 1 modulo M 
- ripeti fino a cella vuota (insuccesso).
```c
Item STsearch(ST st, Key k) { 
	int i = hash(k, st->M); 
	while (full(st, i)) //Se trovo la chiave la ritorno senno incremento i
		if (KEYcmp(k, KEYget(&st->a[i]))==0) 
			return st->a[i]; 
		else 
			i = (i+1)%st->M; 
	return ITEMsetNull(); //Torono NULL se non ho trovato la chiave
}
```
>***Delete***:

operazione complessa che interrompe le catene di collisione. 
L’open addressing è in pratica utilizzato solo quando non si deve mai cancellare. 
Soluzioni: 
1. sostituire la chiave cancellata con una chiave sentinella che conta come piena in ricerca e vuota in inserzione 
2. reinserire le chiavi del cluster sottostante la chiave cancellata
---
>**Soluzione 1:**

Nell’ADT si introduce un vettore status di interi: 0 se la cella è vuota, 1 se è occupata, -1 se cancellata. La funzione CheckFull controlla se la cella i è piena (status=1). La funzione CheckDeleted controlla se la cella è piena (status=1).
```c
struct symboltable { 
	Item *a; 
	int *status; 
	int N; 
	int M;
};
static int CheckFull(ST st, int i); 
static int CheckDeleted(ST st, int i);

static int CheckFull(ST st, int i) { 
	if (st->status[i] == 1) 
		return 1; 
	return 0; 
} 

static int CheckDeleted(ST st, int i){ 
	if (st->status[i] == -1) 
		return 1; 
	return 0; 
} 
void STinsert(ST st, Item item) { 
	int i = hash(KEYget(&item), st->M); 
	while (CheckFull(st, i)) 
		i = (i+1)%st->M; st->a[i] = item; 
	st->status[i] = 1; 
	st->N++; 
}

Item STsearch(ST st, Key k) { 
	int i = hash(k, st->M); 
	//Scavalco anche le cella cancellate
	while (CheckFull(st, i)==1 || CheckDeleted(st, i)==1) 
		if (KEYcmp(k, KEYget(&st->a[i]))==0) 
			return st->a[i];
		else 
			i = (i+1)%st->M; 
	return ITEMsetNull(); 
} 

void STdelete(ST st, Key k){ 
	int i = hash(k, st->M); 
	while (CheckFull(st, i)==1 || CheckDeleted(st, i)==1) 
		if (KEYcmp(k, KEYget(&st->a[i]))==0) 
			break; 
		else 
			i = (i+1) % st->M; 
	if (ITEMcheckNull(st->a[i])) 
		return; 
	//Cancello l'elemento e decremento N
	st->a[i] = ITEMsetNull(); 
	st->N--; 
	st->status[i]=-1; 
}
```
---
>**Soluzione 2:**
```c
void STdelete(ST st, Key k) { 
	int j, i = hash(k, st->M); 
	Item tmp; 
	while (full(st, i)) 
		if (KEYcmp(k, KEYget(&st->a[i]))==0) 
			break; 
		else 
			i = (i+1) % st->M; 
	if (ITEMcheckNull(st->a[i])) return; 
	st->a[i] = ITEMsetNull(); 
	st->N--; 
	//Per tutti gli elementi a partire dal successivo (i+1) di quello trovato,           shifto indietro di 1 il vettore (se non si trova nella posizione corretta)
	for (j = i+1; full(st, j); j = (j+1)%st->M, st->N--) {
		tmp = st->a[j]; 
		st->a[j] = ITEMsetNull(); 
		STinsert(st, tmp); 
	} 
}
```
**Complessità** con l’ipotesi di: 
- hashing semplice uniforme 
- probing uniforme. 
Tentativi in media di “probing” per la ricerca: 
- search hit: 1/2(1 + 1/(1–$\alpha$)) 
- search miss: 1/2(1 + 1/(1- $\alpha$)2 )
>Funziona bene finche la tabella non è piena al 50%, se supero quel limite ho degli errori nella complessità se non si trovano le chiavi.
---
###### Quadratic Probing
>***Insert***: 
- i è il contatore dei tentativi (all’inizio 0) 
- index = $(h’(k) + c_1 \cdot i + c_2 \cdot i^2 )\%M$ 
- se libero, inserisci chiave, altrimenti incrementa i e ripeti fino a cella vuota.
```c
#define c1 1 
#define c2 1 
void STinsert(ST st, Item item) { 
	int i = 0, start = hash(KEYget(&item), st->M), index=start;
	while (full(st, index)) { 
		i++; 
		index = (start + c1*i + c2*i*i)%st->M; 
	} 
	st->a[index] = item; 
	st->N++; 
}

//Search
Item STsearch(ST st, Key k) { 
	int i=0, start = hash(k, st->M), index = start; 
	while (full(st, index)) 
		if (KEYcmp(k, KEYget(&st->a[index]))==0) 
			return st->a[index]; 
		else { 
			i++; 
			index = (start + c1*i + c2*i*i)%st->M; //Polinomio di secondo grado
		} 
	return ITEMsetNull(); 
}
```

###### Double Hashing
Ti sposti di una funzione matematica (di hash), calcolo due funzioni di hash e ottengo il modulo di M della somma delle due funzioni di hash, funziona meglio del linear probing.

- calcola i = h1 (k) 
- se posizione libera, inserisci chiave, altrimenti calcola j =h2 (k) e prova in i = (i + j) % M 
- ripeti fino a cella vuota. Ricordare che, se M = 2\*max, $\alpha$< 1

ATTENZIONE
>bisogna che il nuovo valore i = (i + j) % M = (h1 (k) + h2 (k)) % M 
>sia diverso dal vecchio valore di i altrimenti si entra in un ciclo infinito. 
>Per evitarlo: 
>- h2 non deve mai ritornare 0 
>- h2%M non deve mai ritornare 0 
>
>Esempi di h1 e h2 : 
>	h1 (k) = k % M e M primo 
>	h2 (k) = 1 + k%97 
>   h2 (k) non ritorna mai 0 e h2%M non ritorna mai 0 se M > 97

```c
static int hash1(Key k, int M) { 
	int h = 0, base = 127; 
	for ( ; *k != '\0'; k++) 
		h = (base * h + *k) % M; 
	return h; 
} 
static int hash2(Key k, int M) { 
	int h = 0, base = 127; 
	for ( ; *k != '\0'; k++) 
		h = (base * h + *k); 
	h = ((h % 97) + 1); //Aggiungo 1, cosi non sara mai uguale al valore di prima
	return h; 
} 

void STinsert(ST st, Item item) { 
	int i = hash1(KEYget(&item), st->M); 
	int j = hash2(KEYget(&item), st->M); 
	while (full(st, i)) 
		i = (i+j)%st->M; 
	st->a[i] = item; 
	st->N++; 
}

```

**Complessità**
Ipotesi: 
- hashing semplice uniforme 
- probing uniforme. 
Tentativi di “probing” per la ricerca: 
- search miss: 1/(1–$\alpha$) 
- search hit: 1/$\alpha$ ln (1/(1- $\alpha$))
>Quando le tabelle sono praticamente piene, si fanno un numero di tentativi che va bene 
>(aumenta ma non di tanto).
>è piu difficile da implementare del linear probing.