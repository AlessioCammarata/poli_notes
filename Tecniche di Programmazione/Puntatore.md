
Serve ad indicare un pezzo di memoria.

##### Intro alla memoria

**memoria centrale** -> quella volatile, piu veloce
**memoria secondaria** -> quella di massa, piu lenta

- la memoria è come un vettore di byte

**celle e parole** : 

- cella:
	- gruppo di k-bit cui si accede unitariamente
	- in generale k= 8 -> 1 byte
	- se la cella è da 1 byte si dice byte-addressable
- parola
	- raggruppamento di celle
	- in generale occupa 4 o 8 byte

##### Endian (Come ordinare l'indirizzo di memoria)

Big endian:
- Il most significant Byte occupa l'inidirizzo di memoria piu basso
- il Least significant Byte occupa l'indirizzo di memoria più alto
Little endian
- Il most significant Byte occupa l'inidirizzo di memoria piu alto
- il Least significant Byte occupa l'indirizzo di memoria più basso

Dipende dal contesto, a seconda di come è stato progettato.
Allineamento:
- parola di memoria che inizia ad un indirizzo divisibile per il numero di byte che compongono la parola stessa (la dimensione)

Questo ha effetto nelle struct, infatti in questo tipo, i dati vengono messi esattamente come li dichiariamo, con lo stesso ordine, e percio ci possono essere dei buchi o spazio inutilizzato in piu.

##### Variabili

Sono contenitori caratterizzati da:
- Nome
- Tipo

Compilatore/linker (e loader) collocano (**allocano**) le variabili a certi indirizzi di memoria su 1 o piu parole e mantengono una tabella di corrispondenza identificatore-indirizzo-tipo.

---
### Puntatore

Il puntatore è un modo alternativo per identificare variabili, alternativo al nome, e per accedere ai dati.
Perciò deve essere un **indirizzo** e il **tipo** (deve sapere a cosa punta).

Il puntatore inoltre è anche un dato ed è perciò **manipolabile**.
- Si può mettere dentro delle variabili
- Ci si può fare dell'aritmetica

>NOTA: Un **identificatore** non può essere modificato.

##### Riferimento e deferenzazione
- Operatori di **riferimento** (Puntare a qualcosa sapendo il nome)
&s è un puntatore ad s, è un riferimento ad s.

- Operatore di **dereferenziazione** (Puntatore a qualcosa senza sapere il nome)
P è il puntatore, ed è un riferimento a *P.

I simboli & e \*, sono utilizzati in **definizioni** ed **uso** dei puntatori.
- I 2 operatori sono duali e si usano come prefisso.

Esempio:
```C
int n = 41223; // lo mette nell'indirizzo 304
// Supponiamo che P sta nell'indirizzo di memoria 30C, e contiene l'indirizzo di memoria di n
```
Percio P vede n.
Questi 2 modi di accedere ad n sono equivalenti:
```C
printf("n: %d\n",n);
printf("n: %d\n",*p);
```

La scanf vuole l'indirizzo di dove mettere il dato:
```C
scanf("%d", &n); //Indico l'indirizzo con la &
scanf("%d", p); //Gli do direttamente l'indirizzo
```

#### Dichiarazione

La dichiarazione richiede il riferimento a un tipo base:
```C
int *px; // Non si sa a cosa punta, è una freccia che non indica niente
```
Ciò a cui punterà px sarà intero, e punterà solo dopo l'assegnazione \*px = qualcosa.

##### Perché si usa?

Perché è comodo.

##### Dichiarazione con inizializzazione

```C
int x = 0;
int *p = &x; // mwtto l'indirizzo di x in p.
char *s = NULL; // Null è il puntatore vuoto, l'indirizzo 0.
```
oppure

```C
int x,*p = &x; // mwtto l'indirizzo di x in p.
char *s = NULL; // Null è il puntatore vuoto, l'indirizzo 0.
```

##### Cos'è NULL ? e il puntatore anonimo?

NULL è 0, e significa che stiamo assegnando ad un puntatore qualcosa che non indica niente.

Void \*g è un puntatore che non punta a niente non ha un tipo;

##### Assegnazione
Come si assegna un valore ad un puntatore, cosa si assegna?
- Un indirizzo di memoria ad una variabile
- Un valore a una variabile puntata da un puntatore

1) Puntatore come dato:
```C
p = &x; // p è un puntatore
s = p; 
pnome = &(stud.nome);
p_i = &dati[i];
```
2) Puntatore come riferimento:
```C
*p = 3*(x+2) // modifico cio che sta dentro p
*s = *p; 
*p_i = *p_i + 1;
```

##### Operatori relazionali

Un confronto tra due puntatori ritorna vero se i due puntatori fanno riferimento alla stessa variabile (Stesso indirizzo di memoria).
- p1 == p2

Un confronto tra quello che contengono i due puntatori si fa invece con l'asterisco.
- \*p1 == \*p2

##### Aritmetica dei puntatori

```C
int a[3] = {1,9,2}, *p_a = &a[0];
char b[5] = {'a','e','i','o','u'}, *p_b = &b[0];


printf("a[0]=*p_a=%d,p_a=%p\n",a[0],p_a); 
printf("a[1]=*(p_a+1)=%d,p_a+1=%p\n",a[1],p_a+1); 
printf("b[0]=*p_b =%c,p_b=%p\n",b[0],p_b); 
printf("b[3]=*(p_b+3)=%c,p_b+3=%p\n",b[3],p_b+3);
```
L'output sarà:

	a[0]=*p_a=1,p_a=0028FEF8 
	a[1]=*(p_a+1)=9,p_a+1=0028FEFC 
	b[0]=*p_b=a,p_b=0028FEF3 
	b[3]=*(p_b+3)=o,p_b+3=0028FEF6

>Incrementare (decrementare) di 1 un puntatore equivale a calcolare il puntatore al dato successivo (precedente) in memoria (supposto contiguo) dello stesso tipo.

>Sommare (sottrarre) un valore intero i a un puntatore corrisponde a incrementare (decrementare) i volte di 1 il puntatore

##### Passaggio dei parametri

- Il linguaggio C prevede unicamente passaggio di parametri a funzioni per valore (“by value”) 
	- Il valore del parametro attuale, calcolato alla chiamata della funzione, viene copiato nel parametro formale 
	
- Non è previsto passaggio per riferimento (“by reference”), ma lo si realizza, in pratica, mediante
	- Passaggio per valore di puntatore a dato (“by pointer”) 
	- E la funzione deve usare il puntatore per accedere al dato
---