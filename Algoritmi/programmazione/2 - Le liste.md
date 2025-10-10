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