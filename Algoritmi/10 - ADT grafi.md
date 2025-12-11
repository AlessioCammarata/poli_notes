
Il modello più generale è il grafo orientato e pesato. 
Per efficienza si implementano ADT specifici per le 4 tipologie.
- Orientato e pesato
- Orientato e non pesato
- Non orientato e pesato
- Non orientato e non pesato

>I grafi possono avere archi e nodi, dove ogni arco può essere orientato (frecce direzionale che collegano i nodi) e pesato (Costo legato al muoversi da un nodo all'altro)

Dopo l’inizializzazione: 
- **grafi statici**: non si aggiungono né si cancellano né vertici né archi 
- **grafi semi-statici**: ==non si aggiungono né si cancellano vertici, si possono aggiungere o cancellare archi ==
- **grafi dinamici**: si possono aggiungere e cancellare sia vertici, sia archi 
Nel Corso si considerano **solo grafi semi-statici**, in cui i vertici vengono cancellati «logicamente», aggiungendo un campo per marcare se è cancellato o meno.

###### Leggere un grafo

>All'interno di un grafo ho bisogno di identificare i nodi, necessitò perciò una chiave.
>Dododiché i vertici.

Vertici: informazioni rilevanti:
- interi per identificarli ai fini dell’algoritmo 
- stringhe per identificarli ai fini dell’utente memorizzate in tabelle di simboli: 
	- **esterne al grafo** 
	- **interne al grafo** 
	cui si accede mediante 2 chiavi (intero e stringa).

Tabella di simboli con funzioni: 
- STsearch da chiave (nome) a intero (indice) 
- STsearchByIndex da chiave (indice) a stringa (nome) 
**Queste funzioni servono per accedere ai valori dei nodi, e viceversa**

Possibili soluzioni:
- estensione della tabella di simboli se implementata con vettore con la STsearchByIndex 
- tabella standard (BST, hash table) e vettore a lato per la ricerca da indice a chiave

possibili implementazioni: 
- **tabella di simboli estesa**: vettore non ordinato di stringhe: l’indice del vettore coincide con l’indice del vertice che non è memorizzato esplicitamente. Ricerca inversa con scansione lineare 
- **BST o tabella di hash**: l’indice del vertice è memorizzato esplicitamente. STsearchByIndex con scansione lineare di un vettore di corrispondenza indice-chiave 

**Vertici**
Il numero di vertici |V| che serve per inizializzare grafo e tabella di simboli può essere: 
- noto per lettura o perché compare come intero sulla prima riga del file da cui si legge 
- ignoto, ma sovrastimabile: se il grafo è dato come elenco di archi 
	- con una prima lettura si determina il numero di archi e |V| si sovrastima come 2 volte il numero di archi, ipotizzando che ogni arco connetta vertici distinti 
	- con una seconda lettura si inseriscono i vertici su cui insistono gli archi nella tabella di simboli, ottenendo il numero di vertici distinti |V| esatto e la corrispondenza nome del vertice – indice

>con file in formato standard: 
>	- GRAPHload/GRAPHstore di libreria 
>	- altrimenti fileRead ad hoc nel main.

>Il grafo è un ADT di I classe.
>Gli archi sono definiti con typedef in Graph.h e sono quindi visibili anche al client.
>La tabella di simboli è un ADT di I classe.
>Altre eventuali collezioni di dati sono ADT di I classe (code, code a priorità, etc.)
```c
// Graph.h
typedef struct edge { 
	int v; 
	int w; 
	int wt; //grafi pesati
} Edge;
typedef struct graph *Graph; 
Graph GRAPHinit(int V); 
void GRAPHfree(Graph G); 
void GRAPHload(FILE *fin); 
void GRAPHstore(Graph G, FILE *fout); 
int GRAPHgetIndex(Graph G, char *label); //indice dato nome
void GRAPHinsertE(Graph G, int id1, int id2; int wt;);
void GRAPHremoveE(Graph G, int id1, int id2);
void GRAPHedges(Graph G, Edge *a); 
int GRAPHpath(Graph G, int id1, int id2); 
void GRAPHpathH(Graph G, int id1, int id2); // grafi non orientati
void GRAPHbfs(Graph G, int id); 
void GRAPHdfs(Graph G, int id); 
int GRAPHcc(Graph G); // grafi non orientati
int GRAPHscc(Graph G); // Grafi orientati
```

>**Graphload** slide 22
```c
Graph GRAPHload(FILE *fin) { 
	int V, i, id1, id2, wt; 
	char label1[MAXC], label2[MAXC]; 
	Graph G; 
	fscanf(fin, "%d", &V);//Inserito all'inizio 
	G = GRAPHinit(V); 
	//Leggo i nodi (vertici)
	for (i=0; itab, label1, i){
		fscanf(fin, "%s", label1); 
		STinsert(G->tab, label1, i);
	} 
	//Leggo gli archi (wt perchè nell'ipotesi è pesato)
	while(fscanf(fin,"%s %s %d", label1, label2, &wt) == 3) {
		id1 = STsearch(G->tab, label1); 
		id2 = STsearch(G->tab, label2); 
		if (id1 >= 0 && id2 >=0) 
			GRAPHinsertE(G, id1, id2, wt); // Ipotesi orientato
		//Se non fosse orientato dovrei mettere anche l'arco che va da id2 a id1
	} 
	
	return G; 
}

// N(N-1) / 2 -> Numero di archi massimi dati N nodi

void GRAPHstore(Graph G, FILE *fout) { 
	int i; 
	Edge *a; 
	a = malloc(G->E * sizeof(Edge)); 
	
	GRAPHedges(G, a); //Dipende dalla rappresentazione
	
	fprintf(fout, "%d\n", G->V); 
	for (i = 0; i < G->V; i++) 
		fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));
	for (i = 0; i < G->E; i++) 
		fprintf(fout, "%s %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
}

void GRAPHinsertE(Graph G, int id1, int id2, intwt) {
	insertE(G, EDGEcreate(id1, id2, wt)); 
} 
void GRAPHremoveE(Graph G, int id1, int id2) {
	removeE(G, EDGEcreate(id1, id2, 0)); 
}
```
##### Rappresentazione
###### Matrice di Adiacenza
Dato G = (V, E), la matrice di adiacenza è: 
- matrice adj di |V| x |V| elementi 
$$
adj[i,j] =
\begin{cases} 
1 \ se \ (i, j) \in E \\ 
0 \ se \ (i, j) \not\in \ E 
\end{cases}
$$
- **grafi non orientati: adj simmetrica** 
- **grafi pesati: adj[i,j]=peso dell’arco (i,j) se esiste, 0 non è un peso ammesso.**

```c
struct graph {
	int V; //numero di vertici
	int E; //numero di archi
	int **madj; //Matrice di adiacenza
	ST tab; // tabella di simboli
};
static int **MATRIXint(int r, int c, int val) {
	int i, j; 
	int **t = malloc(r * sizeof(int *)); 
	for (i=0; i < r; i++) 
		t[i] = malloc(c * sizeof(int));
	for (i=0; i < r; i++) 
		for (j=0; j < c; j++) 
			t[i][j] = val; 
	return t; 
} 

static Edge EDGEcreate(int v, int w, int wt) {
	Edge e; 
	e.v = v; 
	e.w = w; 
	e.wt = wt; 
	return e; 
}

Graph GRAPHinit(int V) { 
	Graph G = malloc(sizeof *G); 
	G->V = V; 
	G->E = 0; 
	G->madj = MATRIXint(V, V, 0); 
	G->tab = STinit(V); 
	return G; 
} 

void GRAPHfree(Graph G) { 
	int i; 
	for (i=0; i<V; i++) 
		free(G->madj[i]); 
	free(G->madj); 
	STfree(G->tab); 
	free(G); 
}
```
---
**Multigrafo**
Abbiamo archi multipli che connettono la stessa coppia di vertici. Si può generare se in fase di inserzione degli archi non si scartano quelli già esistenti.

>Non creabile con la matrice di adiacenza
>	- Se l'arco non c'era viene creato, se però all'interno c'è un valore diverso da 0, stiamo aggiornando il peso o modificando lo stesso arco

```c
static void insertE(Graph G, Edge e) { 
	int v = e.v, w = e.w, wt =e.wt; 
	if (G->madj[v][w] == 0) 
		G->E++; 
	G->madj[v][w] = 1; G->madj[v][w] = wt; 
	G->madj[w][v] = 1; G->madj[w][v] = wt; //Creato
} 

int GRAPHgetIndex(Graph G, char *label) { 
	int id; 
	id = STsearch(G->tab, label); 
	if (id == -1) { 
		id = STcount(G->tab); 
		STinsert(G->tab, label, id); 
	} 
	return id; 
}

static void removeE(Graph G, Edge e) { 
	int v = e.v, w = e.w; 
	if (G->madj[v][w] != 0) 
		G->E--; 
	G->madj[v][w] = 0; // I due nodi non sono piu collegati
	G->madj[w][v] = 0; // Per grafi non orientati
} 

void GRAPHedges(Graph G, Edge *a) { 
	int v, w, E = 0; 
	for (v=0; v < G->V; v++) 
		for (w=v+1; w < G->V; w++) //Grafi non oreintati
		for (w=0; w < G->V; w++) //Grafi orientati
			if (G->madj[v][w] !=0) 
				a[E++] = EDGEcreate(v, w, G->madj[v][w]);
	return; 
}
```
Vantaggi:  
- No costi aggiuntivi per i pesi di un grafo pesato 
- Accesso efficiente (O(1)) alla topologia del grafo (adiacenza di 2 vertici).
Svantaggi:
- Complessità spaziale 
	S(n) = $\theta(|V|^2)$ ->**vantaggiosa SOLO per grafi densi**
---
###### Liste di Adiacenza
Dato G = (V, E), la lista di adiacenza è: 
- un vettore A di |V| elementi. Il vettore è vantaggioso per via dell’accesso diretto 
- A[i] contiene il puntatore alla lista dei vertici adiacenti a i.
>Conoscendo il numero di vertici, si può implementare un vettore di liste, altrimenti liste di liste.

```c
//Dove c'è wt è solo per grafi pesati
typedef struct node *link; 
struct node { 
	int v; 
	int wt; 
	link next; 
}; 
struct graph{
	int V; // Numero di vertici
	int E; // Numero di archi
	link *ladj; //Vettore di linked list, di dimensione V
	ST tab; // Tabella di simboli
	link z; // Sentinella
};

//Inserimento in testa all'interno di una linked list
static link NEW(int v, int wt, link next) { 
	link x = malloc(sizeof *x); 
	x->v = v; 
	x->wt = wt; 
	x->next = next; 
	return x; 
} 

static Edge EDGEcreate(int v, int w, int wt) {
	Edge e; 
	e.v = v; 
	e.w = w; 
	e.wt = wt; 
	return e; 
}

// Qua creiamo le strutture dati interne del grafo
Graph GRAPHinit(int V) { 
	int v; 
	Graph G = malloc(sizeof *G); 
	G->V = V; 
	G->E = 0; 
	G->z = NEW(-1, -1, NULL); // -1 è il peso standard (wt)
	G->ladj = malloc(G->V*sizeof(link)); 
	for (v = 0; v < G->V; v++) 
		G->ladj[v] = G->z; 
	G->tab = STinit(V); 
	return G; 
}

void GRAPHfree(Graph G) { 
	int v; 
	link t, next; 
	for (v=0; v < G->V; v++) 
		for (t=G->ladj[v]; t != G->z; t = next) { 
			next = t->next; 
			free(t); 
		} 
	STfree(G->tab); 
	free(G->ladj); free(G->z); free(G); 
} 

//Serve per fare il dump del grafo su file, in pratica scorro tutto il grafo 
void GRAPHedges(Graph G, Edge *a) { 
	int v, E = 0; 
	link t; 
	for (v=0; v < G->V; v++) 
		for (t=G->ladj[v]; t != G->z; t = t->next) 
			if (v < t->v) // Condizione grafi non orientati
				a[E++] = EDGEcreate(v, t->v, t->wt);
}
```
>**Attenzione**: si possono generare cappi!
```c
static void insertE(Graph G, Edge e) { 
	int v = e.v, w = e.w, wt = e.wt; 
	G->ladj[v] = NEW(w, wt, G->ladj[v]); 
	G->ladj[w] = NEW(v, wt, G->ladj[w]); // Grafi non orientati
	G->E++; 
}

static void removeE(Graph G, Edge e) { 
	int v = e.v, w = e.w; link x, p; 
	//Cerco w nella lista di v 
	for (x = G->ladj[v], p = NULL; x != G->z; p = x, x = x->next) {
		if (x->v == w) { 
			if (x == G->ladj[v]) 
				G->ladj[v] = x->next; 
			else 
				p->next = x->next; 
			break; 
		} 
	} 
	/*
	//Cerco v nella lista di w dopo aver fatto l'opposto 
	for (x = G->ladj[w], p = NULL; x != G->z; p = x, x = x->next) {
		if (x->v == v) { 
			if (x == G->ladj[w]) 
				G->ladj[w] = x->next; 
			else 
				p->next = x->next; 
			break; 
		} 
	}
	*/ //Pezzo di codice per grafi non orientati (in piu)
	G->E--; //Decremento il numero di Edge dopo averlo tolto
	free(x); 
}
```

Vantaggi: 
- **Grafi non orientati:** 
	- elementi complessivi nelle liste = 2|E| 
- **Grafi orientati:** 
	- elementi complessivi nelle liste = |E| 
- Complessità spaziale 
	- S(n) = O(max(|V|, |E|)) = O(|V+E|) ->**vantaggioso per grafi sparsi**
Svantaggi: 
- verifica dell’adiacenza di 2 vertici v e w mediante scansione della lista di adiacenza di v 
- uso di memoria per i pesi dei grafi pesati.
---
###### Generazione di grafi
```c
#include <time.h>

int randV(Graph G) { 
	return G->V * (rand() / (RAND_MAX + 1.0)); 
} 

Graph GRAPHrand1(Graph G, int V, int E) { 
	while (G->E < E) 
		GRAPHinsertE(G, randV(G), randV(G)); 
	return G; 
} 

Graph GRAPHrand2(Graph G, int V, int E) { 
	int i, j; 
	double p = 2.0 * E / (V * (V-1)); // Probabilità E/(numero di archi massimo)
	for (i = 0; i < V; i++) 
		for (j = i+1; j < V; j++) //Funziona per i grafi non orientati
		//Grafi orientati avevano j = 0.
			if (rand() < p * RAND_MAX) 
				GRAPHinsertE(G, i, j); 
	return G; 
}
```
##### Cammino semplice
Dato un grafo non orientato G =(V, E) e 2 suoi vertici v e w, esiste un cammino semplice che li connette? 
**Non è richiesto trovarli tutti.** 
Se il grafo non orientato **è connesso** -> il cammino esiste per definizione, basta trovarne uno qualsiasi senza altri vincoli se non essere semplice. ==Non serve backtrack. ==
Se il grafo non orientato **non è connesso** -> il cammino esiste per definizione se i vertici sono nella stessa componente connessa, altrimenti non esiste.==Non serve backtrack.==

>Non facciamo backtracking, se notiamo che ripassiamo una seconda volta da un nodo la soluzione non è valida.

$\forall$ vertice t adiacente al vertice corrente v, determinare ricorsivamente se esiste un cammino semplice da t a w.
array visited[maxV] per marcare i nodi già visitati.
cammino visualizzato in ordine inverso.
complessità==T(n) = O(|V+E|).==
###### Cammino di Hamilton
Dato un grafo non orientato G =(V, E) e 2 suoi vertici v e w, se esiste un cammino semplice che li connette visitando ogni vertice una e una sola volta, questo si dice **cammino di Hamilton.** 
**Se v coincide con w, si parla di ciclo di Hamilton.**

Cammino di Hamilton tra v e w: 
- $\forall$ vertice t adiacente al vertice corrente v, determinare ricorsivamente se esiste un cammino semplice da t a w
- ritorno con successo se e solo se la lunghezza del cammino è |V|-1 
- set della cella dell’array visited per marcare i nodi già visitati 
- reset della cella dell’array visited quando ritorna con insuccesso (**backtrack**) 
- **complessità esponenziale!**

>Codici nelle slides 62-63-64.

