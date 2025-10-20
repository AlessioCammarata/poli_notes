I **problemi di ricerca** hanno come dati:
- Lo spazio delle soluzioni possibili - S
- Lo spazio delle soluzioni valide - V
Bisogna assicurarsi che esista una soluzione valida ed elencare gli elementi soluzione.
All'interno dello spazio delle soluzioni possibili si trovano quelle valide.

I **problemi di ottimizzazione** hanno gli stessi dai S e V.
S = V perciò tutte le soluzioni sono valide e data una funzione obiettivo f (costo o vantaggio), selezionare una o più soluzioni per cui f è minima o massima, perciò l’enumerazione è necessaria.

>Massimizzare una funzione che mida un guadagno, minimizzare quella che mi da svantaggio.
>Minimo (massimo): assoluto o in un dominio contiguo: 
- Soluzione **ottima**: min/max assoluto 
- Soluzione **ottima localmente**: min/max locale
---
##### Esplorazione dello spazio delle soluzioni
Partiamo dal problema perciò non abbiamo ancora le soluzioni.
Si parte dalla **soluzione iniziale quella vuota**, in cui non applico nessuna scelta, ovviamente non valida. **Estendiamo perciò la soluzione** mediante **l'applicazione di scelte**, avrò la **terminazione al raggiungimento della soluzione.**

Algoritmo generico che usa una struttura dati SD: 
==Ricerca():== 
- ==metti== la soluzione iniziale in SD 
- finché SD non diventa vuota: 
	- ==estrai== una soluzione parziale da SD; 
	- se è una soluzione valida, ==Return== Soluzione 
	- ==applica== le scelte lecite e ==metti== le soluzioni parziali risultanti in SD 
- Return fallimento. (Non esiste una soluzione valida)

Quando SD è: 
- una **coda** (FIFO), la **ricerca è in ampiezza** (breadth-first) 
- una **pila** (LIFO), la **ricerca è in profondità** (depth-first) - come lo stack.
- una **coda a priorità**, la **ricerca è best-first.**

>==Ricerca in profondità== significa che esploro un ramo fino in fondo fino alla foglia e poi analizzo gli altri rami
>==Ricerca in ampiezza== vuol dire che esploro tutte le possibilità per ogni livello.
>Con la ==coda a priorità== esploro in ampiezza ma prendo la soluzione che si avvicina di più all'obiettivo che sto cercando.

L'algoritmo può essere:
- **Informato**: Ha conoscenza specifica (eruristica) per il problema
- **Non Informato**: Non conosce nulla del problema.

>Se l'algortimo è in grado di esplorare tutto lo spazio delle soluzioni si dice **completo**.

Che approcci seguiremo?
- In profondità (pile o stack)
- Algo non informato
- Algo completo
- Algo ricorsivo

##### Rappresentazione
Lo spazio delle soluzioni è rappresentato come **albero di ricerca**: 
- di **altezza** n, (dove n è la dimensione della soluzione) 
- di **grado** k, (dove k è il massimo numero di scelte possibili) 
- la **radice** è la soluzione iniziale vuota, (non è valida ovviamente)
- i **nodi intermedi** sono etichettati con le soluzioni parziali,
- le **foglie** sono le soluzioni. Una funzione determina se sono soluzioni valide
>Esempio sulle slide. (pag. 16)
---
#### Calcolo combinatorio e spazio delle soluzioni
Serve per scoprire quante sono le soluzioni possibili.
Funziona se la scelta avviene con determinate regole:
- Scelte appartenente al gruppo. (per esempio scegli un numero da 1 a 10)
- Regole di associazione
	- elementi **distinti** o no (scegliere più volte lo stesso numero)
	- elementi **ordinati** o no (è importante l'ordine con cui compio le scelte)
	- elementi **ripetuti** o no 
> Tutte le soluzioni sono buone, bisogna scegliere per calcolare le possibili soluzioni.

Il calcolo combinatorio: 
- conta quanti sono i sottoinsiemi di un insieme dato che godono di una certa proprietà 
- cioè determina il numero dei modi mediante i quali possono essere associati, secondo prefissate regole, gli elementi di uno stesso gruppo.

##### Principi-base
1. ==L'addizione==, (non serve, banale).
Voglio scegliere un elemento dall'insieme S di 10 elementi, posso prenderlo in 10 modi diversi perciò, se dividessi l'insieme in sottoinsiemi disigunti, il numero di scelte possibili è dato dalla cardinalità dei sottoinsiemi in cui scelgo, quindi resta sempre 10 in questo caso.

2. ==Moltiplicazione==
Devo scegliere un oggetto da n gruppi, in totale quanti modi ho per fare la mia scelta, supponendo che ho 5 gruppi e devo fare 5 scelte (prenderne uno da ognuno) quanti modi ho di riempire quella tupla? prodotto della cardinalità di ogni gruppo.

##### Criteri di raggruppamento
Si possono raggruppare k oggetti presi da un gruppo S di nelementi tenendo presente: 
l’**unicità** degli elementi: gli elementi del gruppo S sono tutti distinti, quindi S è un insieme? O è un multi-insieme(multiset)? 
l’**ordinamento**: 2 configurazioni sono le stesse a meno di un riordinamento? 
le **ripetizioni**: uno stesso oggetto del gruppo può o meno essere riusato più volte all'interno di uno stesso raggruppamento?

##### Disposizione semplice
Una disposizione semplice $D_{n,k}$ di n oggetti distinti di classe k è un sottoinsieme ordinato composto da k degli n oggetti. (0 <= k <= n). (==L'ordinamento conta no ripetizioni==)
$$
	D_{n,k} = \frac {n!}{(n-k!)} = n \cdot (n-1) \cdot ... \cdot (n-k+1)
$$
>Vi sono tutte quelle disposizioni che dipendono da n e k.
>Due soluzioni sono diversi se hanno elementi diversi o se li ho presi in ordine differente.

Esempio:
	Quanti e quali sono i numeri di 2 cifre distinte che si possono scrivere utilizzando i numeri 4, 9, 1 e 0?
		n = 4, k = 2    ----->seguendo la formula le disposizioni sono -----> 24/2 = 12 soluzioni 
		Verificando: {49, 41, 40, 94, 91, 90, 14, 19, 10, 04, 09, 01 }

##### Disposizione con ripetizione
Una disposizione semplice $D'_{n,k}$ di n oggetti distinti di classe k è un sottoinsieme ordinato composto da k degli n oggetti ognuno può essere preso k volte. (0 <= k ). (No relazione tra k ed n)
(==L'ordinamento conta pero ci sono ripetizioni==)
$$
	D'_{n,k} = n^k
$$
>Avrò più soluzioni rispetto alle Disposizioni semplici
>Due soluzioni sono diversi se hanno elementi diversi o se li ho presi in ordine differente oppure gli stessi oggetti ma presi k volte la prima volta e k' la seconda.

Esempio:
	Quanti e quali sono i numeri binari puri su 4 bit? (Ogni bit può assumere valore 0 o 1.)
		n = 2, k = 4    ----->seguendo la formula le disposizioni sono ----->$2^4$ = 16 soluzioni 
		Verificando: {0000, 0001, 0010, 0011, 0100, 0101, 0110, 0111 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111 }
##### Permutazioni semplici
(==L'ordinamento conta non ci sono ripetizioni==)
$$
	P_n = D_{n,n} = n!
$$
>2 soluzioni sono diverse solo se cambia l'ordine in cui le prendo.

Esempio:
	Quanti sono gli anagrammi di ORA (3 lettere distinte)?
	n = 3 -> 3! = 6
	Verificando: { ORA, OAR, ROA, RAO, AOR, ARO }
##### Permutazioni con ripetizione
Dato un multi-insieme (un insieme in cui ci sono elementi ripetuti) di cui a uguali fra loro, b uguali fra loro ,.... . Il numero di permutazioni distinte con oggetti ripetuti è:
(==L'ordinamento conta ma ci sono ripetizioni==)
$$
	P^{a, b, ..}_n = \frac {n!}{(a! \cdot b! \cdot ..)}
$$
>2 soluzioni sono diverse solo se cambia l'ordine in cui le prendo.

Esempio:
	Quanti e quali sono gli anagrammi distinti di ORO (parola di 3 lettere di cui 2 identiche)?
	n = 3 a =2 ----> 3!/2! = 3
	Verificando: { OOR, ORO, ROO }
##### Combinazioni semplici
In una combinazione semplice $C_{n,k}$ sto prendendo oggetti senza ripetizioni, n oggetti distinti, e ne prendo k in cui però ==l'ordinamento non conta==. (1234 è uguale a 4321).
$$
 C_{n,k} = \binom n k = \frac {D_{n,k}} {P_k} = \frac {n!}{k!(n-k)!}
$$
>Le soluzioni sono diverse se hanno elementi diversi.

Esempio:
	Quante terne si possono fare con i 90 numeri del gioco del Lotto?
	n = 90, k =3 ----------> 90! / 3!(87)! = 117480.
	Oppure:
	In un torneo quadrangolare di calcio tra Juve, Toro, Inter e Milan di sola andata, quante e quali partite si disputano? 
	n= 4, k = 2 C4, 2 = 4!/2!(4-2)! = 6 
	Soluzione { Juve-Milan, Juve-Inter, Juve-Toro, Milan-Inter, Milan-Toro, Inter-Toro }
##### Combinazioni con ripetizione
Una combinazione con ripetizione C’n, k di n oggetti distinti di classe k (a k a k) è un sottoinsieme non ordinato composto da k degli n oggetti (0 ≤ k) ognuno dei quali può essere preso sino a k volte.
$$
 C'_{n,k} = \frac {(n+k-1)!}{k!(n-1)!}
$$
>Le soluzioni sono diverse se uno di essi contiene almeno un oggetto che non figura nell’altro oppure se gli oggetti che figurano in uno figurano anche nell’altro ma sono ripetuti un numero diverso di volte.

Esempio:
	Lanciando contemporaneamente 2 dadi, quante sono le composizioni con cui si possono presentare le facce?
	Modello: combinazioni con ripetizione:
		C’6, 2 = (6 + 2 - 1)!/2!(6-1)! = 21

---
##### Insieme delle parti
Dato un insieme S di k elementi (k=|S|), l’insieme delle parti (o powerset) phi(S) è l’insieme dei sottoinsiemi di S, incluso S stesso e l’insieme vuoto.

Esempio: 
	S = {1, 2, 3, 4 } e k = 4 
	phi(S) = {{}, {4}, {3}, {3,4}, {2}, {2,4}, {2,3}, {2,3,4}, {1}, {1,4}, {1,3}, {1,3,4}, {1,2}, {1,2,4}, {1,2,3}, {1,2,3,4} }

##### Partizione di un insieme
Dato un insieme I di n elementi, una collezione S = {$S_i$} di blocchi forma una partizione di I se e solo se valgono tutte le seguenti condizioni:
- I blocchi non sono vuoti
- I blocchi sono a coppie disgiunti
- La loro unione è I
Il numero di blocchi k varia da 1 (blocco = insieme I) a n (ogni blocco contiene un solo elemento di I).

Esempio
	I = {1, 2, 3, 4 } n = 4 
	(k = 1, 1 partizione) (k = 2 7 partizioni) (k = 3 6 partizioni)  (k = 4 1 partizione)
	1 partizione:   {1, 2, 3, 4} 
	7 partizioni:{1, 2, 3}, {4} {1, 2, 4}, {3} {1, 2}, {3, 4} {1, 3, 4}, {2} {1, 3}, {2, 4} {1, 4}, {2, 3} {1}, {2, 3, 4}
	 6 partizioni:  ({1, 2}, {3}, {4}) ({1, 3},{2},{4}) ({1},{2 ,3}, {4}) ({1, 4}, {2}, {3}) ({1},{2, 4},{3}) ({1},{2},{3,4})
	 1 partizione:  ({1}, {2}, {3}, {4})

###### Numero di partizioni
Il numero complessivo delle partizioni di un insieme I di n oggetti in k blocchi con 1 ≤ k ≤ n è dato dai **numeri di Bell** definiti dalla seguente ricorrenza:
$$ 
\begin{align}
	& B_0 = 1 \\
	& B_{N+1} = \sum_{k=0}^{n} \binom n k \cdot B_k
\end{align}
$$
I primi numeri di Bell sono: B0 = 1, B1 = 1 , B2 = 2, B3 = 5 , B4 = 15 , B5 = 52, ecc...

#### Esplorazione esaustiva dello spazio delle soluzioni
##### Scomposizione in sottoproblemi
È il passo più importante del progetto di una soluzione ricorsiva: 
- bisogna identificare il problema risolto dalla singola ricorsione 
- cioè suddividere il lavoro tra varie chiamate ricorsive. 
Si opera in maniera distribuita, senza visione unitaria della soluzione.
###### Approcci:
- ogni ricorsione sceglie un elemento della soluzione. Terminazione: la soluzione ha raggiunto la dimensione richiesta oppure non ci sono più scelte 
- la ricorsione esamina uno degli elementi dell’insieme di partenza per decidere se e dove andrà aggiunto alla soluzione.

>Si segue il primo approccio perché è più intuitivo
##### Strutture dati
Strutture dati possono essere **globali o locali**:
Locale significa che la struttura locale la vede solo la singola chiamata ricorsiva mentre le globali sono comuni a tutte le chiamate.
Globali: cioè comuni a tutte le istanze della funzione ricorsiva
Esempi: 
	dati del problema (matrice, mappa, grafo), vincoli, scelte disponibil.i, soluzione
Locali: cioè locali a ciascuna delle istanze 
Esempi: 
	indici di livello di chiamata ricorsiva, copie locali di strutture dati, indici o puntatori a parti di strutture dati globali

>Globale e locale le stiamo valutando come visibilità ma non c'entrano con l'implementazione in c di globale e locale.
>L'uso di variabili globali C per strutture dati globali è sconsigliato ma non vietato.
>La soluzione adattata è quella di passare come parametro tutti i dati, ed è possibile racchiuderli in #struct per leggibilità

###### Tipologie Strutture dati per oggetti interi
Le strutture dati possono essere:
- Oggetti non interi: Tabelle di simboli per ricondursi ad interi
- Insiemi o insiemi di oggetti di partenza: 
	- **Unico**: vettore #val
	- **molteplici**: sottovettori di tipo Livello
	- **alternativa**: liste
- Soluzioni, che non si chiede di memorizzarle tutte, ma di elencarle.
	- vettore #sol
	- variabile scalare passata by value e ritornata
- Indici:
	- #pos identifica il livello della ricorsione e serve per decidere quali caselle di scelta usare o soluzioni riempire
	- #n e #k indicano la dimensione del problema e della soluzione cercata
- Vincoli, non tutte le scelte sono lecite
	- **Statici**, dati dal problema solitamente
	- **Dinamici**, dati dal problema (se devo pescare un elemento dal vettore dopo non c'è più)
---
###### Principio di moltiplicazione
Si effettuano **n** **scelte in successione**, rappresentate mediante un albero.
I nodi hanno un numero di figli variabile livello per livello. Ognuno dei figli può essere visto come una delle **scelte possibili a quel livello**.
Il **massimo numero di figli determina il grado dell’albero**, **L’altezza dell’albero è n**. 
Le **soluzioni** sono le etichette degli archi che si incontrano in ogni cammino **radice-foglia**.

Esempio:
	Menu con scelta tra 2 antipasti (A0 , A1 ), 3 primi (P0 , P1 , P2 ) e 2 secondi (S0 ,S1 ) (n=k=3). Albero di grado 3 e altezza 3, 12 percorsi radice-foglie.
##### Principi base dell'esplorazione

>Slide 74 modulo 3.

\*val è una struttura dati globale, perche passata a tutte le istanze della funzione ricorsiva.
pos = cnt = 0 all'inizio.
pos indica il livello della ricorsione, se è >= n significa che ho già fatto tutte le scelte nei livelli precedenti. Quindi stampo le soluzioni.
cnt alla fine deve valere 12.

---
##### BackTracking
Il backtracking non è un paradigma vero e proprio, come il divide et impera, il greedy o la programmazione dinamica in quanto non vi è uno schema generale. È piuttosto una tecnica algoritmica per **esaminare ordinatamente le possibili istanze** (soluzioni ammissibili o valide) di uno spazio di ricerca. 
Un’applicazione che dimostra l’importanza del backtracking è il Puzzle di Einstein. 
(Slide 85 modulo 3 di ricerca e ottimizzazione)
###### Puzzle di Einstein
>Sulle slide c'è l'esempio completo tipo 50 pagina a partire dalla 85.
###### Backtracking nelle disposizioni semplici
Per non generare elementi ripetuti: 
- un vettore mark registra gli elementi già presi (mark\[i]\==0 -> elemento i-esimo non ancora preso, 1 altrimenti) 
- la cardinalità di mark è pari al numero di elementi di val(tutti distinti, essendo un insieme)  
- in fase di scelta l’elemento i-esimo viene preso solo se mark\[i]\==0, mark\[i] viene assegnato con 1 
- in fase di backtrack, mark[i] viene assegnato con 0 
- cnt registra il numero di soluzioni.
```C
val = malloc(n * sizeof(int));
sol = malloc(k * sizeof(int));
mark = calloc(n, sizeof(int));

int disp(int pos,int *val,int *sol,int *mark, int n, int k,int cnt){
	int i; 
	if (pos >= k){ // Condizione di terminazione
		for (i=0; i<k; i++) printf("%d ", sol[i]); 
		printf("\n"); 
		return cnt+1; 
	} 
	for (i=0; i<n; i++){ // iterazione sulle n scelte
		if (mark[i] == 0) { // Controllo ripetizione
			mark[i] = 1; //marcamento e scelta
			sol[pos] = val[i]; 
			cnt = disp(pos+1, val, sol, mark, n, k,cnt); //Ricorsione
			mark[i] = 0; //Smarcamento
		} 
	} 
	return cnt; 
}
```
---
###### Backtracking nelle disposizioni ripetute
Ogni elemento può essere ripetuto fino a k volte. Non c’è un vincolo imposto da n su k,
Per ognuna delle posizioni si enumerano esaustivamente tutte le scelte possibili, #cnt registra il numero di soluzioni.
```c
int disp_rip(int pos,int *val,int *sol,int n,int k,intcnt){
	int i; 
	if (pos >= k) { //Condizione di terminazione
		for (i=0; i<k; i++) printf("%d ", sol[i]); 
		printf("\n"); 
		return cnt+1; 
	} 
	for (i = 0; i < n; i++) { //Iterazione sulle n scelte
		sol[pos] = val[i]; //scelta
		cnt = disp_rip(pos+1, val, sol, n, k, cnt); //Ricorsione
	} 
	return cnt; 
}
```
---
###### Backtracking nelle permutazioni semplici
Per non generare elementi ripetuti: 
- un vettore mark registra gli elementi già presi (mark\[i]\==0 -> elemento i-esimo non ancora preso, 1 altrimenti) 
- la cardinalità di mark è pari al numero di elementi di val(tutti distinti, essendo un insieme) 
- in fase di scelta l’elemento i-esimo viene preso solo se mark\[i]\==0, mark\[i] viene assegnato con 1 
- in fase di backtrack, mark\[i] viene assegnato con 0 
- cnt registra il numero di soluzioni.
```c
int perm(int pos,int *val,int *sol,int *mark, int n, int cnt){
	int i; 
	if (pos >= n){ //Condizione di terminazione
		for (i=0; i<n; i++) printf("%d ", sol[i]); 
		printf("\n"); 
		return cnt+1; 
	} 
	for (i=0; i<n; i++) //Itero sulle n scelte
		if (mark[i] == 0) { //controllo ripetizione
			mark[i] = 1; 
			sol[pos] = val[i]; 
			cnt = perm(pos+1, val, sol, mark, n, cnt); //ricorsione
			mark[i] = 0; // Smarcamento
		} 
		return cnt; 
	}
```
###### Backtracking nelle permutazioni ripetute
Si procede in maniera analoga alle permutazioni semplici, con le seguenti variazioni: 
- n è la cardinalità del multiinsieme 
- si memorizzano nel vettore dist_val di n_dist celle gli elementi distinti del multiinsieme 
	- si ordina il vettore val con un algoritmo O(nlogn) 
	- si «compatta» val eliminando gli elementi duplicati e lo si memorizza in dist_val con un algoritmo O(n)
- il vettore mark di n_dist elementi registra all’inizio il numero di occorrenze degli elementi distinti del multiset 
- l’elemento dist_val[i] viene preso se mark[i]>0, mark[i] viene decrementato 
- al ritorno dalla ricorsione mark[i] viene incrementato
- cnt registra il numero di soluzioni.
```c
int perm_r(int pos, int *dist_val, int *sol,int *mark, int n, int n_dist, int cnt) { 
	int i; 
	if (pos >= n) { 
		for (i=0; i<n; i++) printf("%d ", sol[i]); 
		printf("\n"); 
		return cnt+1; 
	} 
	for (i=0; i<n_dist; i++) { 
		if (mark[i] > 0) { 
			mark[i]--; 
			sol[pos] = dist_val[i]; 
			cnt=perm_r(pos+1,dist_val,sol,mark,n, n_dist,cnt);
			mark[i]++; 
		} 
	} 
	return cnt; 
}
```