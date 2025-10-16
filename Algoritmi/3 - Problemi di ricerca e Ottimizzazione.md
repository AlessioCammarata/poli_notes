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