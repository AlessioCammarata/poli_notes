### Algoritmi di Visita
Visita di un grafo G=(V, E): 
- a partire da un vertice dato, seguendo gli archi con una certastrategia, elencare i vertici incontrati, eventualmenteaggiungendo altre informazioni. 
Algoritmi: 
- in **profondità** (depth-first search, DFS) 
- in **ampiezza** (breadth-first search, BFS).

##### Visita in profondità
Dato un grafo (connesso o non connesso), a partire da un vertice s, visita **tutti** i vertici del grafo (raggiungibili da s e non). 

Principio base della visita in profondità: espandere l’ultimo vertice scoperto che ha ancora vertici non ancora scoperti adiacenti. 

Scoperta di un vertice: prima volta che si incontra nella visita(discesa ricorsiva, visita in pre-order). Il vettore pre gioca il ruolo del vettore mark nel Calcolo Combinatorio, ma contiene i tempi crescenti di scoperta.

**GRAPHsimpleDfs**: funzione che, a partire da un vertice dato, visita tutti i vertici di un grafo, richiamando la procedura ricorsiva SimpleDfsR. Termina quando tutti i vertici sono stati visitati.  **SimpleDfsR**: funzione che visita in profondità a partire da un vertice id identificato con un arco fittizio EDGEcreate(id,id) utile in fase di visualizzazione. Termina quando ha visitato in profondità tutti i nodi raggiungibili da id.
###### Strutture dati
- grafo non pesato come lista delle adiacenze 
- vettore pre[i]dove per ciascun vertice si registra il tempo di scoperta (numerazione in preordine dei vertici) 
- contatore cnt per tempi di scoperta
cnt e \*pre sono locali alla funzione GRAPHsimpleDfse passati by reference alla funzione ricorsiva SimpleDfsR.
###### Codice
```c
void GRAPHsimpleDfs(Graph G, int id) { 
	int v, cnt=0, *pre; 
	pre = malloc(G->V * sizeof(int)); 
	if ((pre == NULL)) 
		return; 
	for (v=0;v<G->V;v++) 
		pre[v]=-1; 
	simpleDfsR(G, EDGEcreate(id,id), &cnt, pre); //Visita a partire da id.
	 
	for (v=0; v < G->V; v++) //Visita dei nodi non ancora visitati
		if (pre[v]== -1) 
			simpleDfsR(G, EDGEcreate(v,v), &cnt, pre); 
	printf("discovery time labels \n"); 
	for (v=0; v < G->V; v++) 
		printf("vertex %s : %d \n", STsearchByIndex(G->tab, v), pre[v]);
}

static void simpleDfsR(Graph G, Edge e, int *cnt, int*pre) {
	link t; 
	int w = e.w; 
	pre[w] = (*cnt)++; 
	// terminazione implicitdella ricorsione
	for (t = G->ladj[w]; t != G->z; t = t->next) 
		if (pre[t->v] == -1) 
			simpleDfsR(G, EDGEcreate(w, t->v), cnt, pre); 
}
```

**Versione estesa**
	- nodi etichettati con etichetta tempo di scoperta / tempo dicompletamento 
	- foresta di alberi della visita in profondità, memorizzata in un vettore.
Scoperta di un vertice: prima volta che si incontra nella visita (discesa ricorsiva, visita in pre-order), vettore ***pre[i].*** 

Completamento: fine dell’elaborazione del vertice (uscita dalla ricorsione, visita in post-order) vettore ***post[i]***. 
Scoperta/Completamento: tempo discreto che avanza mediante contatore ***time***. Avanzamento quando si scopre o si completa. 
Identificazione del padre nella visita in profondità: vettore st[i].

- **GRAPHextendedDfs**: funzione che, a partire da un vertice dato, visita tutti i vertici di un grafo, richiamando la procedura ricorsiva ExtendedDfsR. Termina quando tutti i vertici sono stati visitati. 
- **ExtendedDfsR**: funzione che visita in profondità a partire da un vertice id identificato con un arco fittizio EDGEcreate(id,id)utile in fase di visualizzazione. Termina quando ha visitato in profondità tutti i nodi raggiungibili da id.
###### Strutture dati
- grafo non pesato come lista delle adiacenze 
- vettori dove per ciascun vertice: 
	- si registra il tempo di scoperta (numerazione in preordine dei vertici) pre[i] 
	- si registra il tempo di completamento (numerazione in postordine dei vertici) post[i] 
	- si registra il padre per la costruzione della foresta degli alberi della visita in profondità: st[i] 
- contatore time per tempi di scoperta/completamento time, \*pre,\*post e \*st sono locali alla funzione **GRAPHextendedDfs** e passati by reference alla funzione ricorsiva **ExtendedDfsR**.

```c
void GRAPHextendedDfs(Graph G, int id) { 
	int v, time=0, *pre, *post, *st; 
	pre/post/st = malloc(G->V * sizeof(int)); 
	for (v=0;v<G->V;v++) { 
		pre[v]=-1; 
		post[v]=-1; 
		st[v]=-1;
	} 
	extendedDfsR(G, EDGEcreate(id,id), &time, pre, post, st);
	for (v=0; v < G->V; v++) 
		if (pre[v]==-1) 
			extendedDfsR(G,EDGEcreate(v,v),&time,pre,post,st);
	printf("discovery/endprocessing time labels \n"); 
	for (v=0; v < G->V; v++) 
		printf("%s:%d/%d\n",STsearchByIndex(G->tab,v),pre[v],post[v]);
	printf("resulting DFS tree \n"); 
	for (v=0; v < G->V; v++) 
		printf("%s’s parent: %s \n",STsearchByIndex (G->tab, v),STsearchByIndex (G->tab, st[v])); 
}

static void ExtendedDfsR(Graph G, Edge e, int *time, int*pre, , int *post, int *st) { 
	link t; 
	int w = e.w; 
	st[e.w] = e.v; 
	pre[w] = (*time)++; 
	for (t = G->ladj[w]; t != G->z; t = t->next) //Terminazione implicita
		if (pre[t->v] == -1) 
			ExtendedDfsR(G, EDGEcreate(w, t->v), time, pre, post, st);
	post[w] = (*time)++; 
}
```
##### Versione completa
Si etichetta ogni arco: 
- grafi orientati: T(tree), B(backward), F(forward), C(cross) 
- grafi non orientati: T(tree), B(backward)
###### Classificazione degli archi
==Grafo orientato: ==
- **T**: archi dell'albero della visita in profondità 
- **B**: connettono un vertice w ad un suo antenato v nell’albero: tempo di fine elaborazione di v sarà > tempo di fine elaborazione di w. Equivale a testare se, quando scopro l’arco (w, v), post[v] == -1
- **F**: connettono un vertice w ad un suo discendente vnell’albero: tempo di scoperta di v è > tempo di scoperta di w quandoscopro l’arco (w, v) pre[v] > pre[w]
- **C**: archi rimanenti, per cui tempo di scoperta di w è > tempo di scoperta di v quando scoprol’arco (w, v) pre[w] > pre[v].

>**Grafo non orientato: solo archi T e B.**

- **GRAPHdfs**: funzione che, a partire da un vertice dato, visita tutti ivertici di un grafo, richiamando la procedura ricorsiva dfsR.Termina quando tutti i vertici sono stati visitati. 
- **dfsR**: funzione che visita in profondità a partire da un verticeididentificato con un arco fittizio EDGEcreate(id,id)utile in fasedi visualizzazione. Termina quando ha visitato in profondità tutti inodi raggiungibili da id.

```c
void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st){ 
	link t; 
	int v, w = e.w; 
	Edge x; 
	if (e.v != e.w) //Escludi arco fittizio
		printf("(%s, %s): T \n",STsearchByIndex(G->tab, e.v), 
								STsearchByIndex(G->tab, e.w));
	st[e.w] = e.v; 
	pre[w] = (*time)++; 
	for (t = G->ladj[w]; t != G->z; t = t->next) 
		if (pre[t->v] == -1) 
			dfsR(G, EDGEcreate(w, t->v), time, pre, post, st);
		else { 
			v = t->v; 
			x = EDGEcreate(w, v);
			//test per non considerare gli archi 2 volte grafi non orientati
			//grafi non orientati -> LE IF SOTTO NON CI SAREBBERO
			if (pre[w] < pre[v]) 
				printf("(%s, %s): B\n", STsearchByIndex(G->tab, x.v),
										STsearchByIndex(G->tab,x.w)); 
			// grafi orientati -> LA PARTE SOPRA NON CI SAREBBE
			if (post[v] == -1) 
				printf("(%s, %s): B\n", STsearchByIndex(G->tab, x.v),
										STsearchByIndex(G->tab, x.w)); 
			else if (pre[v] > pre[w]) 
				printf("(%s,%s):F\n",STsearchByIndex(G->tab, x.v),
									STsearchByIndex(G->tab, x.w)); 
			else 
				printf("(%s,%s):C\n",STsearchByIndex(G->tab, x.v),
									STsearchByIndex(G->tab, x.w)); 
		} 
	post[w] = (*time)++; 
}
```
##### Visita in ampiezza
A partire da un vertice s: 
- determina tutti i vertici raggiungibili da s, quindi non visita necessariamente tutti i vertici a differenza della DFS 
- calcola la distanza minima da s di tutti i vertici da esso raggiungibili. 
- genera un albero della visita in ampiezza. 
>Ampiezza: espande tutta la **frontiera** tra vertici già scoperti/non ancora scoperti.

Scoperta di un vertice: prima volta che si incontra nella visita raggiungendolo percorrendo un arco. 
Il vettore pre[v] registra il tempo di scoperta di v. 
Dato un vertice v, il vettore st[v] registra il padre di v nell’albero della visita in ampiezza. 
Non appena il vertice viene scoperto, si registra il **tempo di scoperta e il padre nell’albero**, concludendo così l’elaborazione del vertice stesso.
###### Strutture dati
- Grafo non pesato come matrice delle adiacenze 
- **coda Q di archi e=(v,w)** 
- vettore st dei padri nell’albero di visita in ampiezza 
- vettore pre dei tempi di scoperta dei vertici 
- contatore time del tempo 
>time, \*pre e \*st sono locali alla funzione GRAPHbfse passati by reference alla funzione bfs.
###### Algoritmo
- metti l’arco fittizio di partenza e=(id,id) nella coda 
- ripeti fintanto che la coda non si svuota 
	- estrai dalla coda un arco e=(v,w) 
	- se e.w è un vertice non ancora scoperto (pre[e.w]\==-1) 
		- indica che e.v è padre di e.w nella BFS (st[e.w]= e.v) 
		- marca e.w come scoperto al tempo time (pre[e.w]= time++) e incrementa il tempo 
		- trova i vertici non ancora scoperti x adiacenti a e.we metti in coda tutti gli archi che connettono e.w ad essi. 
>bfs: funzione che visita in ampiezza a partire da un vertice di partenza id.

>***Si visita in ampiezza solo in aree connesse***.

```c
void GRAPHbfs(Graph G, int id) { 
	int v, time=0, *pre, *st, *dist; 
	/* allocazione di pre, st e dist */ 
	for (v=0; v < G->V; v++) { 
		pre[v] = -1; 
		st[v] = -1; 
		dist[v] = INT_MAX; 
	} 
	bfs(G, EDGEcreate(id,id), &time, pre, st, dist); 
	printf("\n Resulting BFS tree \n"); 
	for (v=0; v < G->V; v++) 
		if (st[v] != -1) 
			printf("%s’s parent is:%s\n",STsearchByIndex(G->tab, v), 
										STsearchByIndex(G->tab, st[v])); 
	printf("\n Levelizing \n"); 
	for (v=0; v < G->V; v++) 
		if (st[v] != -1) 
			printf("%s: %d \n",STsearchByIndex(G->tab,v),dist[v]);
}

void bfs(Graph G, Edge e, int *time, int *pre, int*st,int *dist) { 
	int x; 
	Q q = Qinit(); 
	Qput(q, e); 
	dist[e.v]=-1; 
	while (!Qempty(q)) 
		if (pre[(e = Qget(q)).w] == -1) { 
			pre[e.w] = (*time)++; 
			st[e.w] = e.v; 
			dist[e.w] = dist[e.v]+1; // Si incrementa la distanza, (d padre + 1)
			for (x = 0; x < G->V; x++) 
				if (G->madj[e.w][x] == 1) // matrice delle adiacenze
					if (pre[x] == -1) 
						Qput(q, EDGEcreate(e.w, x)); 
		} 
}
```
##### Complessità
- Operazioni sulla coda 
- Scansione della matrice delle adiacenze==T(n) = (|V|2 ).== 
- Con la lista delle adiacenze: ==T(n) = O(|V|+|E|).==
##### Proprietà
***Cammini minimi:*** la visita in ampiezza determina la minima distanza tra s e ogni vertice raggiungibile da esso.