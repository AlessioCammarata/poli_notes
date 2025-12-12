Dato G=(V,E) grafo non orientato, pesato con pesi reali w: E->R e connesso, estrarre da G un **albero ricoprente minimo** (Minimumweight Spanning Tree – MST) , definito come: 
- grafo G'=(V, A) dove A incluso E 
- aciclico 
- minimizza w(A)=(u,v)T w(u,v). 

Aciciclità && copertura di tutti i vertici percio **G’ è un albero.** 
L’albero MST è unico se e solo se tutti i pesi sono distinti.

>Usiamo tutti i vertici, albero perchè è aciclico, e minimo perchè il peso trovato è minimo.
###### Rappresentazione
ADT grafo non orientato e pesato: estensione dell’ADT grafo non orientato: 
- lista delle adiacenze 
- matrice delle adiacenze 
Valore-sentinella per indicare l’assenza di un arco (peso inesistente): 
- maxWT (idealmente +$\inf$), soluzione scelta nell’algoritmo di Prim
- 0 se non sono ammessi archi a peso 0 
- -1 se non sono ammessi archi a peso negativo. 
Per semplicità si considerano pesi interi e non reali.
#### Approccio completo
- Dati V vertici, l’alberi ricoprente avrà esattamente V-1 archi 
- si esplorano tutte le maniere di raggruppare V-1 archi scelti dagli Earchi del grafo 
	- l’ordine non conta (combinazioni)
	- condizione di accettazione: verifica di copertura e di aciclicità
	- problema di ottimizzazione: si considerano tutte le soluzioni e sisceglie la migliore 
- costo: esponenziale.

>Creo le combinazione di ogni archi e poi considero se sto toccando tutti i vertici e anche che non ci siano archi Back (condizione aciclicità).
#### Approccio greedy
In generale: 
- ad ogni passo, si sceglie la soluzione localmente ottima 
- non garantisce necessariamente una soluzione globalmente ottima.
Per gli MST: 
- si parte da un algoritmo **incrementale**, **generico** e **greedy** dove la scelta è ottima localmente 
- si può dimostrare che la soluzione è globalmente ottima.

>Riduciamo i costi arrivando sempre all'albero corretto.
##### Approccio incrementale, generico e greedy
Algoritmo generico:
- La soluzione A corrente è un sottoinsieme degli archi di un albero ricoprente minimo. 
- inizialmente A è l’insieme vuoto 
- ad ogni passo si aggiunge ad A un arco “**sicuro**” 
- fino a quando A non diventa un albero ricoprente minimo. 

**Invarianza**: l’arco (u,v) è ***sicuro*** se e solo se aggiunto ad un sottoinsieme di un albero ricoprente minimo produce ancora un sottoinsieme di un albero ricoprente minimo.

>Un teorema e un corollario permettono di identificare gli archi sicuri.

###### Tagli e Archi
Dato G=(V,E) grafo non orientato, pesato, connesso, si definisce **taglio** una partizione di V in S e V-S 
					V = S  V-S && S  V-S = $\empty$ 
tale che se (u,v) $\in$ E attraversa il taglio allora 
					u$\in$S && v$\in$V-S (o viceversa) 

Un taglio rispetta un insieme A di archi se nessun arco di A attraversa il taglio. 
Un arco si dice leggero se ha **peso minimo** tra gli archi che attraversano il taglio.

>Divido l'insieme dei nodi perciò in due insiemi diversi segnati dal taglio, perciò esistono degli archi che attraversano il taglio.

###### Archi sicuri (Teorema)
Dati: 
- G=(V,E) grafo non orientato, pesato, connesso 
- A sottoinsieme degli archi 
se: 
- A $\incluso$ E è contenuto in un qualche albero ricoprente minimo di G. Inizialmente A è vuoto 
- (S,V-S) è un taglio qualunque **che rispetta A** (Significa che gli archi in A non attraversano il taglio) 
- (u,v) è un **arco leggero** che attraversa (S,V-S) 

allora 
							**(u,v) è sicuro per A.**
###### Archi sicuri (Corollario)
Dati: 
- G=(V,E) grafo non orientato, pesato, connesso 
- A sottoinsieme degli archi 
se: 
- A $\incluso$ E è contenuto in un qualche albero ricoprente minimo di G. Inizialmente A è vuoto 
- C è un albero nella foresta GA = (V,A) 
- (u,v) è un arco leggero che connette C ad un altro albero in $G_A$
allora 
							**(u,v) è sicuro per A.**

##### Algoritmo di Kruskal (1956)
-  basato su algoritmo generico 
- uso del corollario per determinare l’arco sicuro: 
	- si considera una foresta di alberi, inizialmente formati dai singoli vertici 
	- si ordinano degli archi per pesi crescenti 
	- si itera la selezione di un arco sicuro: arco di peso minimo che connette 2 alberi generando ancora un albero 
	- terminazione: considerati tutti i vertici.
La rappresentazione degli alberi è fatta con ADT Union-Find (vedi Tecniche di Programmazione, lezione sull’Analisi della Complessità, problema dell’On-line connectivity).
##### ADT union find
- Struttura dati per memorizzare una collezione di insiemi disgiunti, ad esempio la partizione di un insieme in più sottoinsiemi (disgiunti per definizione di partizione) 
- anche nota come struttura dati **disjoint-set data** o **merge–find set**
- Operazioni: 
	- **UFunion**: fusione di 2 sottoinsiemi 
	- **UFfind**: verifica se 2 elementi appartengono o meno allo stesso sottoinsieme
###### Strutture dati
Dato un insieme di N elementi denominati da 0 a N-1: 
- il vettore id contiene per ogni elemento l’indice dell’elementoche lo rappresenta 
- inizialmente ogni elemento rappresenta se stesso 
- l’elemento che rappresenta il sottoinsieme è quello che rappresenta se stesso (indice coincide con contenuto a quell’indice) 
- il vettore sz contiene la cardinalità del sottoinsieme cui appartiene ogni elemento

>Comoda perchè con Kruskal vediamo i dati dentro un solo vettore.

###### ADT di I classe UF 
Versione con weighted quick-union 
- quick-union: un elemento punta a chi lo rappresenta, quindicomplessità O(1) 
- find: percorrimento di una “catena” dall’elemento fino al rappresentante “ultimo” del sottoinsieme. Grazie al mantenimento dell’informazione sulla cardinalità dell’insieme che permette di fondere l’insieme a cardinalità minore in quello a cardinalità maggiore, generando un cammino di lunghezza logaritmica, la complessità è O(logN).
```c
//UF.h
void UFinit(int N); 
int UFfind(int p, int q); 
void UFunion(int p, int q); 

//UF.c
#include 
#include "UF.h" 
static int *id, *sz; 
void UFinit(int N) { 
	int i; 
	id = malloc(N*sizeof(int)); 
	sz = malloc(N*sizeof(int)); 
	for(i=0; i<N; i++) { 
		id[i] = i; //Ogni elemento è rappresentante di se stesso 
		sz[i] = 1; //Cardinalità inziale uguale a 1
	} 
}

static int find(int x) { 
	int i = x; 
	while (i!= id[i]) 
		i = id[i]; //Scorri i rappresentanti e guarda se sono uguali
	return i; 
} 

int UFfind(int p, int q) { 
	return(find(p) == find(q)); // Ripeti finche non arrivi in testa. (id = indice)
}

void UFunion(int p, int q) { 
	int i = find(p), j = find(q); //Rappresentanti degli alberi che voglio unire
	if (i == j) return; //Stesso padre <-> stesso insieme
	// Il rappresentante dell'unione diventa il padre dell'insieme piu grande
	if (sz[i] < sz[j]) { 
		id[i] = j; //Cambio il rappresentante di i con j
		sz[j] += sz[i]; 
	} else { 
		id[j] = i; 
		sz[i] += sz[j]; 
	} 
}

//Cruscal

void GRAPHmstK(Graph G) { //Wrapper
	int i, k, weight = 0;
	//Alloco
	Edge *mst = malloc((G->V-1) * sizeof(Edge)); //Soluzione di Cruscal
	Edge *a = malloc(G->E * sizeof(Edge)); //Vettore su cui fare la ricorsione
	
	k = mstE(G, mst, a); //Chiamo Cruscal
	
	printf("\nEdges in the MST: \n");
	//Stampo la soluzione
	for (i=0; i < k; i++) { 
		printf("(%s - %s) \n", STsearchByIndex(G->tab, mst[i].v), STsearchByIndex(G->tab, mst[i].w));
		weight += mst[i].wt; 
	} 
	printf("minimum weight: %d\n", weight); 
}

//Funzione iterativa
int mstE(Graph G, Edge *mst, Edge *a) { 
	int i, k; 
	GRAPHedges(G, a); // a sono gli edges del grafo
	sort(a, 0, G->E-1);//Ordino in base al peso primo arco sarà con il peso minimo 
	UFinit(G->V); //Creo la Union Find
	for (i=0, k=0; i < G->E && k < G->V-1; i++ )
	//Controllo se i due elementi non sono nello stesso insieme
		if (!UFfind(a[i].v, a[i].w)) { 
			UFunion(a[i].v, a[i].w); //Faccio la Union tra i 2 insiemi 
			mst[k++]=a[i]; //Prendo l'arco e lo metto nella soluzione
		} 
	return k; 
}
```
**Complessità:**
Con l’ADT UF: 
$$
T(n) = O(|E| lg |E|) = O(|E| lg |V|)
$$
in quanto, ricordando che $|E| = O(|V|^2 )$ (grafo completo), 
$log|E| = O(log|V|^2 ) = O(2log|V|) = O(log|V|).$
##### Algoritmo di Prim (1956)
- basato su algoritmo generico 
- soluzione brute-force 
- uso del teorema per determinare l’arco sicuro: 
	- inizialmente S = $\empty$, poi S = {vertice di partenza} 
	- iterazione: V-1 passi in cui si aggiunge 1 arco alla soluzione
		- iterazione sugli archi per selezionarne 1: 
			- selezionare quello di peso minimo tra gli archi che attraversano il taglio e aggiungerlo alla soluzione
			- in base al vertice in cui arriva l’arco, aggiornare S 
		- terminazione: considerati tutti i vertici, quindi soluzione che contiene V-1 archi 
		- versione semplice, ma non efficiente a causa del ciclo annidato sugli archi.

-  L’approccio incrementale consiste nell’aggiungere ad ogni passo un vertice v a S 
- ciò che interessa è la distanza minima da ogni vertice ancora in V-S ai vertici già in S 
- quando si aggiunge il vertice v a S, ogni vertice w in V-S può avvicinarsi ai vertici già in S 
- non serve memorizzare la distanza tra w e tutti i vertici in S, basta quella minima e verificare se l’aggiunta di v a S la diminuisce, nel qual caso la si aggiorna.
###### Struttura dati
- Grafo rappresentato come matrice delle adiacenze dove l’assenza di un arco si indica con maxWT anziché 0 
- vettore st di G->V elementi per registrare per ogni vertice che appartiene ad S il padre 
- vettore fringe (frangia) fr di G->V elementi per registrare per ogni vertice di V-S quale è il vertice di S più vicino. È dichiarato static in Graph.c
- vettore wt di G->V+1 elementi per registrare: 
	- per vertici di S il peso dell’arco al padre 
	- per vertici di V-S il peso dell’arco verso il vertice di S più vicino 
	- si considera un elemento fittizio con arco di peso maxWT
	- il vettore è inizializzato con maxWT 
- variabile min per il vertice in V-S più vicino a vertici di S.

Azioni: 
- ciclo esterno sui vertici prendendo di volta in volta quello a minima distanza (identificato da min) e aggiungendolo a S. Inizialmente min è il vertice 0 
for (min=0; min!=G->V; ) { 
	v=min; //Prendi il valore minimo
	st[min]=fr[min]; //Metti il padre nella frangia
Notare che nel ciclo for non si incrementa min, min viene assegnato opportunamente nel corpo del ciclo.
- ciclo interno sui vertici w non ancora in S (st[w]\==-1): (Non ancora presi)
	- se l’arco (v,w) migliora la stima (if (G->madj[v][w]madj[v][w]) 
		- la si aggiorna (wt[w] = G->madj[v][w])
		- e si indica che il vertice in S più vicino a w è v (fr[w] = v)
	- se w è diventato il vertice più vicino a S (if (wt[w]<wt[min])), si aggiorna min (min=w).
```c
void GRAPHmstP(Graph G) { //Wrapper
	int v, *st, *wt, weight = 0; 
	st = malloc(G->V*sizeof(int)); //Elementi padre
	wt = malloc((G->V+1)*sizeof(int)); // Elementi peso + peso fittizio
	 
	mstV(G, st, wt); //Chiamata a Prim 
	
	printf("\nEdges in the MST: \n");
	//Stampa
	for (v=0; v < G->V; v++) { 
		if (st[v] != v) { 
			printf("(%s-%s)\n",STsearchByIndex(G->tab,st[v]),STsearchByIndex(G->tab,v));
			weight += wt[v]; 
		} 
	} 
	printf("\nminimum weight: %d\n", weight); 
}

void mstV(Graph G, int *st, int *wt) { 
	int v, w, min, *fr = malloc(G->V*sizeof(int));
	for (v=0; v < G->V; v++) { //Inizializziamo la fr
		st[v] = -1; 
		fr[v] = v; 
		wt[v] = maxWT; //Peso iniziale massimo, qualsiasi arco è migliorativo
	} 
	//Parti da un nodo (in questo caso 0)
	st[0] = 0; 
	wt[0] = 0; 
	wt[G->V] = maxWT; //Inizializzo il nodo fittizio
	for (min = 0; min != G->V; ) { 
		v = min; //Vertice di partenza
		st[min] = fr[min]; 
		for (w = 0, min = G->V; w < G->V; w++)
	//Verifica nella matrice di adiacenza i collegamenti con v e gli altri vertici 
			if (st[w] == -1) { 
				if (G->madj[v][w] < wt[w]) { //Se il peso è minore 
					wt[w] = G->madj[v][w]; // lo prendo
					fr[w] = v; // metto v in fr[w], cosi in futuro passo da v
				} 
				if (wt[w] < wt[min]) //se il peso è piu piccolo di min aggiorna min
					min = w; 
			} 
	} 
}
```
**Complessità:**
Per grafi densi: 
$$
T(n) = O(|V|^2)
$$
Possibili miglioramenti per grafi sparsi: usare una coda a priorità per gestire la fringe. Con coda a priorità implementata con heap $T(n) = O(|E|log|V|)$ .