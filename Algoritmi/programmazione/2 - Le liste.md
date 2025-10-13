#### Sequenza lineare 
Detta anche enumerazione o **lista** è un insieme finito di elementi di tipo generico disposti consecutivamente, in cui a ogni elemento è associato univocamente un indice: 
$$a0 , a1 , … , ai , …, an-1$$
Sulle coppie di elementi è definita una relazione predecessore/successore: 
$$ai+1 = succ(ai ) ai = pred(ai+1)$$
La sequenza è **ordinata con criterio posizionale** (primo dato, secondo, i-esimo), **in base a una chiave** (parte di dato), la sequenza può essere ordinata o non ordinata.
L’accesso avviene o in base ad una chiave (ricerca) o in base alla posizione nella sequenza e può essere **diretto**, costo O(1) oppure **sequenziale**, costo O(n).
>Esempio: 
>	[-3,4,21,43] (ordinata)
>	[21,4,-2,43] (non ordinata)
>	cerca il 4 (Ricerca in base ad una chiave)
>	cerca il terzo (ricerca in base alla posizione)
---
#### Linked list (Liste concatenate)
**I dati non sono contigui in memoria**, l'accesso è **sequenziale**, dato l’indice i, si accede all’elemento $a_i$ scorrendo la sequenza lineare a partire da uno dei suoi 2 estremi, solitamente quello di sinistra.
Il costo dell’accesso dipende dalla posizione dell’elemento nella sequenza lineare, quindi è $O(n)$ nel caso peggiore.

##### Operazioni sulle sequenze lineari (liste)
- **ricerca** di un elemento con campo chiave di ricerca uguale a chiave data.
- **inserzione** di un elemento: 
	- in **testa** alla lista non ordinata 
	- in **coda** alla lista non ordinata 
	- nella posizione tale da garantire **l’invarianza della proprietà di ordinamento** **per una lista ordinata** (si intende ordinamento in base a una chiave)
- **cancellazione** di un elemento: 
	- che si trova in **testa** alla lista non ordinata 
	- che si trova in una **posizione arbitraria** della lista non ordinata.
	- che ha un campo con contenuto uguale a quello di una **chiave di cancellazione** (richiede solitamente una ricerca preventiva dell’elemento da cancellare) 
	- con o senza **restituzione dell’elemento** cancellato (estrazione). 
---
#### Liste realizzate mediante vettori
Le liste possono essere realizzate mediante vettori (allocazione contigua) se **è noto o stimabile il numero massimo di elementi**, oppure sfruttando la **ri-allocazione** o sfruttando la **contiguità fisica degli elementi** (elemento all’indice i successore di quello all’indice i-1 e predecessore di quello all’indice i+1) o infine **disaccoppiando contiguità fisica e relazione predecessore/successore** mediante indici (lista concatenate mediante indici).
#### Liste realizzate mediante concatenazione
Le liste possono essere realizzate mediante **strutture ricorsive allocate individualmente** se **non** è noto o stimabile il **numero massimo di elementi**, se la relazione è da predecessore a successore si hanno **liste concatenate semplici**, se invece è in entrambi i versi si hanno **liste concatenate doppie**.

---
### Linked list mediante struct ricorsive
Strutture dati dinamiche come sequenze di nodi. In C ogni nodo è una struct con: 
- un numero **arbitrario** (fisso, una volta definite la struct) **di dati**, generalmente racchiusi in un campo val di tipo Item (si tratta di una covenzione, non di una regola).
- **uno o due riferimenti** (“link”) che puntano al nodo successivo e/o precedente.
![[linked list.png]]
##### Diversi modi per definire i nodi
1. **Senza typedef**, definendo il puntatore next mentre si definisce il tipo struct node:
```c
struct node { 
	Item val; 
	struct node *next; 
};
```
2. con typedef, definendo sia un alias node_t per struct node, sia un alias link per il puntatore a oggetto di tipo struct node:
```c
typedef struct node { 
	Item val; 
	struct node *next; 
} node_t, *link;
```
3. con separazione tra typedef e dichiarazione della struct node, dichiarando un alias link per il puntatore a oggetto di tipo struct node.                                                                                Nella dichiarazione di tipo struct node si usa il tipo link appena definito:
```c
typedef struct node *link; 
struct node { 
	Item val; 
	link next; 
};
```
4. con separazione tra typedef e dichiarazione della struct node, dichiarando un alias node_t per struct node.                                                                                                                             Nella dichiarazione di struct node si dichiara next come puntatore a oggetto di tipo node_t:
```c
typedef struct node node_t; 
struct node { 
	Item val; 
	node_t *next; 
};
```
5. con separazione tra typedef e dichiarazione della struct node, dichiarando un alias link per un puntatore a struct node e un alias node_t per struct node. Nella dichiarazione di struct node si usa link:
```c
typedef struct node *link, node_t; 
struct node { 
	Item val; 
	link next; 
};
```
---
#### Operazioni Atomiche
si dichiara un puntatore x a un nodo come:
```c
link x; 
```
si alloca il nodo come:
```c
x = malloc(sizeof *x); 
//OPPURE
x = malloc(sizeof(node_t));
```
**Creazione** mediante generazione del **puntatore alla testa**: 
```c
link head = NULL; 
//Test se la lista è vuota 
if (head == NULL)
```
**Inserimento** del nodo puntato da t dopo il nodo puntato da x in lista esistente:
```c
t->next = x->next; 
x->next = t;
```
**Cancellazione** del nodo puntato da t, successore del nodo puntato da x:
```c
x->next = x->next->next;
//OPPURE
x->next = t->next;
```
**Attraversamento** con elaborazioni **semplici** (non si modifica la lista: es. ricerca, visualizzazione, conteggio, …) basta il puntatore al nodo corrente x:
```c
link x, head; 
... 
for (x=head; x!=NULL; x=x->next) {...}
```
**Attraversamento** con elaborazioni **complesse** (si modifica la lista: es. inserzione, cancellazione ecc...) serve il puntatore al nodo corrente x e al suo predecessore p:
```c
link x, p, head; 
... 
p = NULL; 
for (x=head; x!=NULL; p = x, x=x->next) {...}
```
Il puntatore al nodo corrente x è **inutile** se: 
- si tratta il nodo in testa **fuori dall’iterazione** 
- si comincia l’iterazione dal **secondo elemento,** inizializzando p con head 
- per terminare si **testa** che la **lista non sia vuota** e che il prossimo elemento **non sia l’ultimo** 
- si scorre la lista **aggiornando p** (puntatore al predecessore)
```c
link p, head; 
... /* gestione separata nodo in testa */ 
for (p=head;p!=NULL && p->next!=NULL;p=p->next){...}
```
**Attraversamento** con puntatore a puntatore a nodo xp per accedere al campo puntatore a successore della struct:
```c
link *xp, head; 
... 
for (xp=&head; *xp!=NULL; xp=&((*xp)->next)) { ... }
```
**Attraversamento ricorsivo**, è immediato anche l’attraversamento all’indietro senza bisogno di puntatore al predecessore:
```c
void listTravR(link h) { 
	if (h == NULL) return; 
	ITEMdisplay(h->val); 
	listTravR(h->next); 
}

//Reverse
void listRevTravR(link h) { 
	if (h == NULL) return; 
	listRevTravR(h->next); 
	ITEMdisplay(h->val); 
}
```
---
#### Operazioni su liste
**Creazione nodo**, nelle Liste non ordinate: 
- inserimento in testa 
- inserimento in coda 
- ricerca di chiave 
- cancellazione dalla testa 
- estrazione dalla testa 
- cancellazione di nodo con chiave data.
Nelle Liste ordinate: 
- Inserimento 
- ricerca di chiave 
- cancellazione di nodo con chiave data.

##### Creazione nodo
```c
link newNode(Item val, link next) { 
	link x = malloc(sizeof *x); 
	if (x==NULL) return NULL; 
	else { 
		x->val = val; 
		x->next = next; 
	} 
	return x; 
}
```
##### Liste non ordinate

###### Inserzione in testa
1. parametri di ingresso: val e puntatore alla testa h.                                                               Valore di ritorno: **nuovo puntatore alla testa**, che il main assegnerà a head:
```c
link listInsHead (link h, Item val) { 
	h = newNode(val,h); 
	return h; // Nuovo puntatore alla testa della lista
} 
/* main */ 
.. 
link head = NULL; 
Item d; 
... 
head = listInsHead(head, d);
```

2. parametri di ingresso: val e puntatore al puntatore alla testa hp.                                               La funzione modifica direttamente il puntatore alla testa \*hp. 
>In chiamata si passa l’indirizzo del puntatore alla testa &head
```c
void listInsHeadP(link *hp, Item val) {
	*hp = newNode(val, *hp); // SI modifica il tramite il puntatore
}
/* main */ 
... 
link head = NULL; 
Item d; 
... 
listInsHead(&head, d);
```
---
###### Inserzione in coda
Serve il puntatore all’ultimo nodo che si può con un attraversamento di costo O(n) oppure è
mantenuto con costo O(1) (MEGLIO!!!).
1. O(N):
lista vuota: inserzione in testa con modifica di head 
lista non vuota: ciclo di attraversamento per raggiungere l’ultimo nodo, creazione di un nuovo nodo e aggancio come successore dell’ultimo nodo, head rimane invariato.
```c
link listInsTail(link h, Item val) { 
	link x; 
	if (h==NULL) 
		return newNode(val, NULL); 
	for (x=h; x->next!=NULL; x=x->next); //cerca ultimo nodo
	
	x->next = newNode(val, NULL); //crea nuovo nodo e aggancialo all'ultimo
	return h; 
} 
/* main */ 
... 
link head=NULL; 
Item d; 
... 
head = listInsTail(head, d);
```
2. O(N)
parametri di ingresso: val e puntatore al puntatore alla testa hp 
x = \*hp identfica la **testa della lista** 
lista vuota: inserzione in testa con modifica di \*hp 
lista non vuota: ciclo di attraversamento per raggiungere l’ultimo nodo, creazione di un nuovo nodo e aggancio come successore dell’ultimo nodo, \*hp rimane invariato.
```c
void listInsTailP(link *hp, Item val) { 
	link x=*hp; 
	if (x==NULL) *hp = newNode(val, NULL); 
	else { 
		for (; x->next!=NULL; x=x->next); //cerca ultimo nodo
		x->next = newNode(val, NULL); //crea nuovo nodo e aggancialo all'ultimo
	} 
} 
/* main */ 
... 
link head=NULL; 
Item d; 
... 
listInsTailP(&head, d);
```
>In questo caso non restituisco ma si fa tutto by reference.

3. O(N)
attraversamento con **variabile xp** di tipo puntatore a puntatore a nodo che punta al campo puntatore a successore della struct, si ha l'unificazione dei casi di inserimento in lista vuota e non vuota.
```c
void listInsTailP(link *hp, Item val) { 
	link *xp = hp; 
	while (*xp != NULL) xp = &((*xp)->next); 
	*xp = newNode(val, NULL); 
} 
/* main */ 
... 
link head=NULL; 
Item d; 
... 
listInsTailP(&head, d);
```
4. **O(1)**
Uso di 2 variabili di tipo puntatore a puntatore a nodo **hp e tp** per accedere a primo e ultimo nodo. \*hp identifica la testa della lista, \*tp la coda.
lista vuota: inserzione in testa con modifica di \*hp e di \*tp 
lista non vuota: creazione di un nuovo nodo e aggancio come successore dell’ultimo nodo, \*hp rimane invariato, \*tp viene aggiornato.
```c
void listInsTFast(link *hp,link *tp,Item val) { 
	if (*hp==NULL) 
		*hp = *tp = newNode(val, NULL); 
	else { 
		(*tp)->next = newNode(val, NULL); 
		*tp = (*tp)->next; 
	} 
} 
/* main */ 
... 
link head=NULL, tail=NULL; 
Item d; 
... 
listInsTailFast(&head, &tail, d); //Passo i puntatori sia a head che a tail
```
>Passando i due puntatori ho tolto la ricerca della testa.
>---
###### Ricerca di una chiave
Non essendo modificata la lista, basta un solo puntatore per l’attraversamento. 
Se la chiave c’è, si ritorna il dato che la contiene.
Se la chiave non c’è, si ritorna il dato nullo tramite chiamata alla funzione #ITEMsetvoid.
```c
Item listSearch(link h, Key k) { 
	link x; 
	for (x=h; x!=NULL; x=x->next) 
		if (KEYeq(KEYget(x->val), k)) //Funzione per eguagliare le chiavi
			return x->val; 
	return ITEMsetvoid(); // Funzione che mette NULL in tutti i campi della struct
} 
/* main */ 
... 
link head=NULL; 
Item d; 
Key k; 
... 
d = listSearch(head,k);
```
---
###### Cancellazione dalla testa
Se la **lista non è vuota**, aggiorna la testa della lista con il puntatore al secondo dato che diventa il primo. Ricorda il primo dato per poi liberarlo con free, il main assegna a head il nuovo puntatore alla testa.
```c
link listDelHead(link h) { 
	link t = h; // Creo una copia di h,serve per rimuovere h, dopo che la sposto
	if (h == NULL ) return NULL; 
	h = h ->next; // Sposto la testa 
	free(t); // Libero lo spazio occupato da h
	return h; 
} 
/* main */ 
... 
link head = NULL; 
... 
head = listDelHead(head);
```
---
###### Estrazione dalla testa
Per aggiornare la testa della lista si deve usare il puntatore al puntatore alla testa hp poiché il valore di ritorno della funzione è il dato.
Se la lista è vuota, si ritorna il dato nullo tramite chiamata alla funzione ITEMsetvoid, altrimenti si memorizza il primo dato per poi ritornarlo. **Si ricorda il primo dato per poi liberarlo con free.**
```c
Item listExtrHeadP(link *hp) { 
	link t = *hp ; 
	Item tmp ; 
	if (t == NULL ) 
		return ITEMsetvoid(); 

	tmp = t ->val; 
	*hp = t - >next; 
	free(t); 
	
	return tmp; 
} 
/* main */ 
... 
link head = NULL; 
Item d; 
... 
d = listExtrHeadP(&head);
```
---
###### Cancellazione di nodo con chiave data
A seguito della cancellazione, il puntatore alla testa della lista può essere: 
- NULL perché la lista era vuota 
- il puntatore al secondo dato, se la chiave si trovava nel primo 
- invariato se la lista non è vuota, la chiave non è il primo dato o non c’è in lista. Un ciclo di attraversamento con 2 puntatori identifica il nodo da cancellare.

```c
link listDelKey(link h, Key k) { 
	link x, p; 
	if (h == NULL) 
		return NULL; 
	for (x=h, p=NULL; x!=NULL; p=x, x=x->next) { 
		if (KEYeq(KEYget(x->val),k)) { 
			if (x==h) // Controllo solo se era la testa
				h = x->next; // ritorno cio che punta h
			else 
				p->next = x->next; //Punto p a quello dopo
			free(x); 
			break; 
		}
	} 
	return h; 
}
```

**Versione ricorsiva:** 
- terminazione: si punta al nodo vuoto, 
- se il nodo corrente non contiene la chiave, si ricorre sulla lista che ha come testa il nodo successore, 
- se il nodo corrente contiene la chiave, si salva il puntatore al suo successore, si cancella il nodo corrente e si ritorna il puntatore al successore che nell’istanza ricorsiva chiamante viene assegnato come successore del nodo corrente realizzando il bypass.
```c
link listDelKeyR(link x, Key k) { 
	link t; 
	if (x == NULL) return NULL; 
	if (KEYeq(KEYget(x->val), k)) { 
		t = x->next; 
		free(x); //Cancello x, ma tengo t che è x->next
		return t; //Ferma perche ha trovato
	} 
	x->next = listDelKeyR(x->next, k); //Vai avanti di 1 elemento, ritorna il valore di x, che sarebbe x->next
	return x; 
}
```
>La funzione non tocca x->next se non trova l'elemento con chiave uguale, in quel caso ritorna t.
###### Estrazione di nodo con chiave data
L’estrazione può alterare il puntatore alla testa nel caso la chiave di ricerca sia nel primo dato. 
La funzione deve: 
- ritornare: 
	- il dato nullo tramite chiamata alla funzione #ITEMsetvoid se la lista è vuota o la chiave non è presente 
	- il dato se la chiave è presente 
- aggiornare il puntatore alla testa della lista se si estrae il primo dato. 
Si propone la tecnica del puntatore a puntatore xp, inizializzato al puntatore al puntatore alla testa della lista hp (non è l’unica possibile). 
Nel ciclo di attraversamento si verifica se si trova la chiave, in caso affermativo se ne salva il puntatore e il dato, si avanza nella lista ed infine si libera il nodo estratto.
```c
Item listExtrKeyP(link *hp, Key k) { 
	link *xp, t; 
	Item i = ITEMsetvoid(); 
	for (xp=hp;(*xp)!=NULL;xp=&((*xp)->next)) { 
		if (KEYeq(KEYget((*xp)->val),k)){ 
			t = *xp; // Copio per cancellare
			*xp = (*xp)->next; // Sposto all'elemento successivo
			i = t->val; // Prendo il valore di t (cioe *xp)
			free(t); 
			break; 
		}
	} 
	return i; //Ritorno il valore che è NULL se non sono entrato nel ciclo o se non ho trovato la chiave.
}
```
---
##### Liste ordinate
Trattiamo dati di tipo Item ordinati in base a chiave, **l'inserimento (O(N)) con ricerca** della posizione e **cancellazione** **(O(N)) con ricerca**, *può decidere “non trovato” senza percorrere tutta la lista.*
###### Inserzione
Richiede l'aggiornamento del puntatore alla testa per inserzione in lista vuota o inserzione di dato con chiave minima (massima), e la ricerca della posizione in cui inserire, cioè identificazione nodo predecessore con tecnica del doppio puntatore.
```c
link SortListIns(link h, Item val) { 
	link x, p; 
	Key k = KEYget(val); 
	if (h==NULL || KEYgreater(KEYget(h->val),k)) 
		return newNode(val, h); //inserimento in testa
		
	for (x=h->next, p=h; // attraversamento per ricerca posizione
		x!=NULL && KEYgreater(k,KEYget(x->val)); // piu grande della chiave -> esco
		p=x, x=x->next); 
	
	p->next = newNode(val, x);
	return h; 
}
```
---
###### Ricerca
Essendo l’accesso ai dati della lista lineare, anche se sono ordinati, non si usa la ricerca dicotomica. La ricerca è identica a quella in lista non ordinata con eventuale interruzione anticipata.
```c
Item SortListSearch(link h, Key k) { 
	link x; 
	for (x=h; x!=NULL && KEYgeq(k, KEYget(x->val)); x=x->next) // Uscita anticipata
		if (KEYeq(KEYget(x->val), k)) 
			return x->val; 
	return ITEMsetvoid(); 
}
```
---
###### Cancellazione di nodo con chiave data 
Si aggiunge una condizione di interruzione anticipata al ciclo di attraversamento.
```c
link SortListDel(link h, Key k) { 
	link x, p; 
	if (h == NULL) return NULL; 
	for (x=h, p=NULL; x!=NULL && KEYgeq(k,KEYget(x->val)); p=x, x=x->next) { 
		if (KEYeq(KEYget(x->val),k)){ 
			if (x==h) 
				h = x->next; 
			else 
				p->next = x->next;
				
			free(x); 
			break; 
		} 
	} 
	return h; 
}
```
---
##### Liste concatenate particolari (Linked List)
Uso di **nodi fittizi** per semplificare i test di lista vuota.
**Adiacenza logica di nodo in testa e in coda** per ottenere una **lista circolare**, è possibile **l'attraversamento in entrambe le direzioni** con operazioni tipo cancellazione semplificate: liste concatenate doppie.
###### Liste con nodi fittizi (sentinelle) 
Nodo con dato fittizio (in testa e/o coda), usato per rimuovere casi speciali: 
- lista vuota 
- inserimento/cancellazione del primo o ultimo nodo

>Lista con nodo fittizio in testa
```c
//inizializza 
h = malloc(sizeof *h); 
h->next = NULL; 

//inserisci t dopo x 
t->next = x->next; 
x->next = t; 

//cancella dopo x 
t = x->next; 
x->next = t->next; 

//ciclo di attraversamento 
for (t = h->next; t != NULL; t = t->next ) 

//testa se lista vuota 
if (h->next == NULL)
```

>Lista con nodi fittizi in testa e in coda
```c
//inizializza 
h = malloc(sizeof *h); 
z = malloc(sizeof *z); 
h->next = z; 
z->next = z; 

//inserisci t dopo x 
t->next = x->next; 
x->next = t; 

//cancella dopo x 
x->next = x->next->next; 

//ciclo di attraversamento 
for (t = h->next; t != z; t = t->next ) 

//testa se lista vuota 
if (h->next == z)
```
---
###### Lista circolare
L’ultimo nodo punta al primo, viene utilizzata per gestire casi di servizi a “rotazione” 
```c
// prima inserzione 
h->next = h; 

//inserisci t dopo x 
t->next = x->next; 
x->next = t; 

//cancella dopo x 
x->next = x->next->next; 

//ciclo di attraversamento 
t = h; 
do {
	... 
	t = t->next; 
} while (t != h) 

//testa singolo elemento 
if (h->next == h)
```
---
###### Lista concatenata doppia
Un puntatore in più (al nodo precedente), questo tipo di liste facilita cancellazione (senza ricerca) dato il puntatore al nodo da cancellare:
```c
typedef struct node *link, node_t; 
struct node { 
	Item val; 
	link next; 
	link prev; 
};
```
### Problemi semplici su liste
- Inversione di lista 
- Insertion sort su lista (Lo trovi sulle slide)
- Elenchi di canzoni (Lo trovi sulle slide)
###### Inversione di lista 
Data una lista, invertirla Versione con funzioni su liste:
due liste, vecchia e nuova
- si estrae in testa dalla lista vecchia, 
- si inserisce in testa nella lista nuova 

Algoritmo: finché esiste una porzione non vuota di lista y da invertire (iterazione): 
- estrai nodo da testa della lista y 
- inserisci nodo in testa alla lista r invertita

>Finché esiste una porzione non vuota di lista y da invertire (iterazione): estrai nodo da testa della lista y e inserisci nodo in testa alla lista r invertita.
```c
link listReverseF(link x) { 
	link y = x, r = NULL; 
	Item tmp; 
	while (y != NULL) { 
		tmp = listExtrHeadP(&y); 
		r = listInsHead(r, tmp); 
	} 
	return r; 
}
```
>ATTENZIONE: si distrugge una lista, se ne crea un’altra. NON SI RICICLANO I NODI! Si estrae un Item, si inserisce un Item.

VERSIONE 2:
Versione con operazioni direttamente sulla lista: si «girano» i puntatori (ma concettualmente resta «estrai in testa, inserisci in testa») 
- x: puntatore alla testa della lista 
- r: puntatore alla testa della lista già invertita (ultimo nodo già sistemato). Inizialmente r=NULL
- y: puntatore alla porzione di lista da invertire (primo nodo ancora da sistemare). Inizialmente y=x 
- t: puntatore al nodo successivo al primo nodo ancora da sistemare (puntato da y)

>Finché esiste una porzione non vuota di lista y da invertire (iterazione): inserire il nodo puntato da y in testa alla lista puntata da r, aggiornare la testa della lista invertita r con y e aggiornare y con il suo successore
```c
link listReverseF(link x) { 
	link t, y = x, r = NULL; 
	while (y != NULL) { 
		t = y->next; 
		y->next = r; 
		r = y; 
		y = t; 
	} 
	return r; 
}
```
---