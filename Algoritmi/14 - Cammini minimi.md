>Un cammino è un insieme di archi.

G=(V,E) grafo orientato, pesato (w: E->R). 
Definizioni: 
**peso w(p) di un cammino p**: 
	w(p) = i=1 kw(vi-1, vi) 
**peso (s,v) di un cammino minimo da s a v**: 
	min{w(p): se  s p v } $\delta$(s,v) =  altrimenti 

Cammino minimo da s a v: 
qualsiasi cammino p con w(p) = $\delta$(s,v)
>Slide 1.

Cammini minimi: 
- da sorgente singola: 
	cammino minimo e suo peso da s a ogni altro vertice v 
	- algoritmo di Dijkstra 
	- algoritmo di Bellman-Ford 
- con destinazione singola
- tra una coppia di vertici 
- tra tutte le coppie di vertici.
###### Archi con pesi negativi
-  $\exists$ (u,v) $\in$ E per cui w(u,v) < 0 ma $\not\exists$ ciclo a peso < 0: 
	- algoritmo di Djikstra: soluzione ottima non garantita 
	- algoritmo di Bellman-Ford: soluzione ottima garantita 
- $\exists$ ciclo a peso < 0: problema privo di significato, $\not\exists$ soluzione: 
	- algoritmo di Djikstra: risultato senza significato 
	- algoritmo di Bellman-Ford: rileva ciclo <0.
---
### Cammini minimi e cicli
- I cammini minimi non possono contenere cicli a peso negativo in quanto il problema perderebbe di significato 
- I cammini minimi non possono contenere cicli a peso positivo, in quanto non sarebbero minimi (eliminando il ciclo si avrebbe peso inferiore) 
Percio:
- **I cammini minimi sono semplici** 
- **I cammini minimi constano di al più |V|-1 archi**
###### Approccio brute-force
In assenza di cicli a peso negativo: 
- enumerare i sottoinsiemi di archi di cardinalità tra 1 e |V|-1
- l’ordine conta, quindi powerset con disposizioni semplici 
- accettabilità: il sottoinsieme di archi forma un cammino 
- ottimalità: selezionare quello a peso minimo. 
>Costo esponenziale. (Non applicabile).
###### Sottostruttura ottima di un cammino minimo
>Un sotto-cammino di un cammino minimo è un cammino minimo.

Dimostrazione per assurdo: (programmazione dinamica).
##### Rappresentazione dei cammini minimi
1. **Vettore** dei predecessori st\[v]: 
$\forall v \in V$ st\[v] vale parent(v) se $\exists$,   -1 altrimenti 

2. **Sottografo** dei predecessori: 
	$G_{\pi}$ =($V_\pi ,E_2$), dove 
	- $V_\pi$ = {v $\in$V: st\[v] != -1} $\cup$ {s} 
	- $E_\pi$ = {(st\[v], v) $\in$ E : v $\in$ $V_\pi$ - {s}}

3. **Albero** dei cammini minimi.
G’ = (V’, E’) dove V’ $\subseteq$ V && E’ $\subseteq$ E 
- V’: insieme dei vertici raggiungibili da s 
- s radice dell’albero 
- $\forall v \in V’$ l’unico cammino semplice da s a v in G’ è un cammino minimo da s a v in G. 
Nei grafi non pesati: si ottiene con una visita in ampiezza.
###### Principio di rilassamento
In un dato momento accetta che la tua soluzione sia sovrastimata.
>Rilassare la stima significa avvicinarsi alla soluzione.

- d[v] è la stima (limite superiore) del peso del cammino minimo da s a v. (ipotizzo +infinito tempo).
	- **d è la stima**
	- **st è la lista dei predecessori del vertice**
	d[v]= maxWT, st[v] = -1;
	d[s] = 0; 
	st[s] = 0; //Distanza da un nodo a se stesso

- rilassare: d[v] e st[v] verificando se conviene il cammino da s a u e l'arco e = (u,v), dove w(u,v) è il peso dell'arco.
```c
 //d[u] +è la stima dal nuovo nodo.
if (d[v]>d[u]+w(u,v)) { 
	d[v] = d[u]+w(u,v); //Sto rilassando
	st[v] = u; //Aggiorno il predecessore
}
```
###### Proprietà
**(disuguaglianza triangolare)**
G=(V,E): grafo orientato, pesato w: E->R con sorgente s. $\forall$(u,v) $\in$ E 
$$
\delta(s,v) \le \delta(s,u) + w(u,v) 
$$
Un cammino minimo da s a v non può avere peso maggiore del cammino formato da un cammino minimo da s a u e da un arco (u, v).

**(proprietà del limite superiore)**:
G=(V,E): grafo orientato, pesato w: E->R con sorgente s e stime per i vertici inizializzate. 
$\forall$v $\in$ V $$d(v) \ge \delta(s,v)$$Una volta che il limite superiore d(v) assume il valore $\delta$(s,v) esso non cambia più.

**(proprietà dell’assenza di cammino):**
G=(V,E): grafo orientato, pesato w: E->R con stime per i vertici inizializzate. 

Se non esiste un cammino tra s e v, allora si ha sempre 
$$
d(v) = \delta(s,v) = \infty
$$
**(proprietà della convergenza)**:
G=(V,E): grafo orientato, pesato w: E->R con sorgente s e stime per i vertici inizializzate. 
Sia il cammino minimo da s a v composto da 
- cammino da s a u 
- arco e = (u,v) 
A seguito dell’applicazione del rilassamento su e = (u,v) 
	se prima del rilassamento d[u] = $\delta$(s,u) 
	dopo il rilassamento d[v] = $\delta$(s,v).

**(proprietà del rilassamento)**:
G=(V,E): grafo orientato, pesato w: E->R con sorgente s e stime per i vertici inizializzate
Se p=$<v_1,v_2, ... , v_k>$ è un cammino minimo da $v_1 \ a \ v_k$ 
Dopo tutti i passi di rilassamento sugli archi 
- $d(v_k) = \delta(s,v_k)$ 
- e d($v_k$) non cambia più.
---
>Dopo il rilassamento di e = (u,v) si ha che
>$$ d[v] \le d[u] + w(u,v) $$>A seguito del rilassamento d[v] non può essere aumentato, ma
> - o è rimato invariato (rilassamento senza effetto) 
> - o è diminuito per effetto del rilassamento.
---
###### Applicazione
Rilassamento: 
- applicato 1 volta ad ogni arco (Dijkstra) o più volte (Bellman-Ford)
- ordine con cui si rilassano gli archi.
#### Algoritmo di Dijkstra
- Ipotesi: $\not\exists$ archi a peso < 0 
- Strategia: **greedy** 
- S: insieme dei vertici il cui peso sul cammino minimo da s è già stato determinato 
- V-S: coda a priorità PQ dei vertici ancora da stimare. 
	Termina per PQ vuota: 
	- estrae u da V-S (d[u] minimo) 
	- inserisce u in S 
	- rilassa tutti gli archi uscenti da u.
```c
void GRAPHspD(Graph G, int id) { 
	int v; 
	link t; 
	PQ pq = PQinit(G->V); // PQ con priorità in d
	int *st, *d; 
	st = malloc(G->V*sizeof(int)); // tante celle quanti sono i nodi
	d = malloc(G->V*sizeof(int)); // tante celle quanti sono i nodi
	for (v = 0; v < G->V; v++){ 
		st[v] = -1; //Nessuno ha il predecessore
		d[v] = maxWT; //Metto infinito
		PQinsert(pq, d, v); //Inserisco il nodo nella PQ
	} 
	d[id] = 0; 
	st[id] = id; 
	PQchange(pq, d, id);
	
	//Dijkstra
	while (!PQempty(pq)) { 
		if (d[v = PQextractMin(pq, d)] != maxWT) //Estre dalla testa di PQ
			//Lista di adiacenza del nodo
			 for (t=G->ladj[v]; t!=G->z ; t=t->next) 
				 if (d[v] + t->wt < d[t->v]) { //Se miglioro la stima
					 d[t->v] = d[v] + t->wt; //Riscrvii la stima su v
					 // riposiziona il nodo successivo nella PQ
					 PQchange(pq, d, t->v); 
					 st[t->v] = v; //Assegna il predecessore a v
				} 
	} 
	// Stampa risultato
	printf("\n Shortest path tree\n"); 
	for (v = 0; v < G->V; v++) 
		printf("parent of %s is %s \n", STsearchByIndex(G->tab, v),STsearchByIndex (G->tab, st[v])); 
	printf("\n Min.dist. from %s\n", STsearchByIndex(G->tab, s));
	for (v = 0; v < G->V; v++) 
		printf("%s: %d\n", STsearchByIndex(G->tab, v), d[v]);
	Pqfree(pq); 
}
```
###### Complessità
V-S: coda a priorità pq dei vertici ancora da stimare.  (Teta(|V|))
Termina per pqvuota. Implementando la pq con uno heap: 
- estrae u da V-S (d[u] minimo)  (O(log|V|))
- inserisce u in S 
- rilassa tutti gli archi uscenti da u.  (rilassare O(log|V|) archi uscenti O(|E|))

**T(n) = O((|V|+|E|) lg |V|)** 
**T(n) = O(|E| lg |V|)** se tutti i vertici sono raggiungibili da s
###### Dijkstra e grafi con archi a peso negativo
Da fastidio perchè dopo che estraggo un nodo, non posso tornare indietro.
>Con archi a peso negativo non si raggiunge l'ottimo globale, ci si ferma prima.
>Funzione per un ottimo locale.
##### Cammini minimi su DAG pesati
L’assenza di cicli semplifica l’algoritmo: 
- ordinamento topologico del DAG 
- per tutti i vertici ordinati: 
- applica la relaxation da quel vertice.
###### Complessità
-  Applicabile a DAG anche con archi negativi 
- T(n) = O(|V|+|E|).
>Differisce da Djikstra perche non dovendo fare la PQchange non c'è log(|V|).
##### Cammini massimi su DAG pesati
Problema non trattabile su grafi pesati qualsiasi. 
L’assenza di cicli tipica dei DAG rende facile il problema: 
- ordinamento topologico del DAG 
- per tutti i vertici ordinati: 
- applica la relaxation «invertita» da quel vertice: 
```c
if (d[v]< d[u] + w(u,v)) { 
	d[v] = d[u] + w(u,v); 
	st[v] = u; 
}
```
>Stimo al ribasso, se trovo un cammino piu lungo aggiorno, come prima. (relax invertito)
#### Algoritmo di Bellman-Ford
-  Ipotesi: possono $\exists$ archi a peso < 0 
- Rileva cicli < 0 
- Strategia: **programmazione dinamica** (applicabilità già dimostrata) 
- soluzione ricorsiva: $d_w$[v] è la lunghezza del cammino minimo da s a v con al più w archi 
	- $d_0$[v] vale 0 se v coincide con s, $\infty$ altrimenti 
	- $d_w$[v]= min{$d_w$[v], $\min_{u\in \mathbb{Inc(V)} }$($d_{w-1}$[u] + w(u,v))} 
	- $\mathbb{Inc(V)}$: insieme dei vertici da cui escono archi incidenti in v
**Calcolo bottom-up:** 
- vettori d e st delle distanze minime e dei predecessori opportunamente inizializzati 
- |V|-1 passi 
- al passo i-esimo: 
	- ciclo di rilassamento sugli archi «in avanti» (lista di adiacenza e non di incidenza) 
- al |V|-esimo passo: 
	- diminuisce almeno una stima: $\exists$ ciclo <0
	- altrimenti soluzione ottima. 
Il numero di passi è al massimo **|V|-1**: se ci si accorge di aver raggiunto un punto fisso (non cambiano le stime da un passo a quello successivo), si può interrompere anticipatamente il ciclo.

```c
void GRAPHspBF(Graph G, int id){ 
	int v, i, negcycfound; 
	link t; 
	int *st, *d; 
	st = malloc(G->V*sizeof(int)); 
	d = malloc(G->V*sizeof(int)); 
	for (v = 0; v < G->V; v++) { 
		st[v]= -1; 
		d[v] = maxWT; 
	} 
	d[id] = 0; 
	st[id] = id;
	for (i=0; i<G->V-1; i++) 
		for (v=0; v<G->V; v++) //Scorro tutti i nodi
			if (d[v] < maxWT) 
				for (t=G->ladj[v]; t!=G->z ; t=t->next) //Lista di adj
					if (d[t->v] > d[v] + t->wt) { 
						d[t->v] = d[v] + t->wt; 
						st[t->v] = v; 
					}
	//V-esimo passaggio 
	negcycfound = 0; 
	for (v=0; v<G->V; v++) 
		if (d[v] < maxWT) 
			for (t=G->ladj[v]; t!=G->z ; t=t->next) 
				if (d[t->v] > d[v] + t->wt) 
					negcycfound = 1;
					
	if (negcycfound == 0) {
		 printf("\n Shortest path tree\n"); 
		 for (v = 0; v < G->V; v++) 
			 printf("Parent of %s is %s \n", 
				 STsearchByIndex(G->tab, v), 
				 STsearchByIndex (G->tab, st[v])); 
		printf("\n Min.dist. from %s\n", STsearchByIndex (G->tab, s));
		for (v = 0; v < G->V; v++) 
			printf("%s: %d\n", STsearchByIndex (G->tab, v), d[v]);
	} else 
		printf("\n Negative cycle found!\n"); 
}
```
>Al |V|-esimo passo di rilassamento non diminuisce alcuna stima: **terminazione con soluzione ottima.** 
>Ricordare: la terminazione può anche avvenire prima.

Perciò se al v-esimo passo non esco significa che c'è un ciclo negativo.
###### Complessità
- Inizializzazione (O(|V|))
- |V|-1 passi in ciascuno dei quali si rilassano tutti gli archi (O(|V||E|))
- |V|esimo passo di controllo in cui si rilassano tutti gli archi (O(|E|))
**T(n) = O(|V| |E|).**