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
- di usare solo gli ultimi n bit di k se M = 2^n 
- di usare solo le ultime n cifre decimali di k se M = 10n .
OPPURE
chiavi: stringhe alfanumeriche corte come interi derivati dalla valutazione di polinomi in una data base 
- M numero primo 
- h(k) = k % M