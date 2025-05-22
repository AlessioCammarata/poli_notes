Vettori e puntatori sono **duali** e consentono l’accesso ai dati in 2 forme: 
- vettoriale con indici e [ ] 
- con puntatori mediante &, * e aritmetica dei puntatori 

>REGOLA: Il nome della variabile che identifica il vettore corrisponde formalmente al puntatore al primo elemento del vettore stesso: <nome_vettore>⇔ &<nome_vettore>[0]

Esempio:
```C
int dati[100];
```
- dati ⇔ &dati[0] 
- *dati ⇔ dati[0] 
- *(dati+i) ⇔ dati[i]
---
#### Esempi di utilizzo di un puntatore

Prendere un vettore di 100 interi e riempirlo:

1) Nessun puntatore
```C
int dati[100]; 
... 
for (i=0;i<100;i++) scanf("%d“,&dati[i]);
```

2) Utilizzo i puntatori, senza & nello scanf
```C
int dati[100], *p; 
...
p = &dati[0]; // Si poteva anche mettere dati, poiche equivale a &dati[0]
for ( i=0;i<100;i++) scanf ( "%d " , p+i);
```

3) Puntatore che si sposta
```C
int dati[100], *p; 
...
p = &dati[0]; 
for (i=0;i<100;i++, p++) scanf("%d", p); // Incremento nel for
```
---
#### Notazioni miste

>puntatore a intero int *v, inizializzato a dati (=&dati[0]) e usato con notazione vettoriale
```C
int *v = dati; 
for (i=0; i<100; i++) scanf("%d", &v[i]);
```

>vettore di interi dati utilizzato come puntatore
```C
int *v = dati; 
for (i=0; i<100; i++) scanf("%d", dati + i);
```

##### Limite alla dualità

>il nome del vettore corrisponde ad una **costante puntatore**, non ad una variabile, quindi **non può essere incrementato per scandire il vettore**.
---
##### Puntatori e sottovettori

Per identificare un sottovettore compreso tra indici l e r di un vettore dato: 
- si limita tra l e r l’indice i (identificazione implicita del sottovettore):

```C
for (i=l; i<=r; i++) scanf("%d", &dati[i]); 
for (i=l; i<=r; i++) printf("%d" , dati[i]);
```

---

#### Decomposizione di matrici

- Le matrici (bidimensionali e multidimensionali) si possono decomporre per righe (o sotto-matrici) 
- Le matrici sono memorizzate con la tecnica row-major o matrice bidimensionale come vettore di righe o casella di una riga adiacenti e righe in sequenza

Se ho una matrice 3 righe e 2 colonne, vengono disposte per righe.

	prima riga
	seconda riga

Esempio (Prodotto scalare * vettore)

```C
float M[NR][NC], V[NC], Prod[NR]; 
int r, c; 
... 
for (r=0; r<NR; r++) { 
	Prod[r] = 0.0; 
	for (c=0; c<NC; c++) Prod[r] = Prod[r] + M[r][c]*V[c]; 
}
```
Oppure

```C
float M[NR][NC], V[NC], Prod[NR], *riga; 
int r, c;
...
for (r=0; r<NR; r++) { 
	Prod[r] = 0.0;
	riga = M[r];
	for (c=0; c<NC; c++) Prod[r] = Prod[r] + riga[c]*V[c];
}
```

##### Vettori e matrici come parametri

Vettori e matrici passati come parametri non vengono generati all’interno della funzione: 
- Passando il nome di un vettore (coma parametro attuale) a una funzione, si passa il puntatore al primo elemento del vettore
- si passa solo il puntatore alla prima casella (non la dimensione: se la si vuole, va passata come parametro aggiuntivo e indipendente).

La dualità puntatore ⇔ vettore è: 
	- totale per vettori (monodimensionali) 
	- parziale per matrici (vettori multidimensionali)
 
Per accedere all'i-esimo elemento di un vettore **vett\[N]**, una funzione necessita unicamente dell'indirizzo del primo elemento: 
						**vett\[i**] equivale a ***(vett+i)** 

Per accedere all'elemento **\[i,j]** di una matrice **mat\[NR]\[NC]**, a una funzione serve l'indirizzo del primo elemento E il numero di colonne NC della matrice: 
					**mat\[i]\[j]** equivale a ***(mat + NC*i + j)**

---
#### Corrisponenza parametri formali-attuali

>Parametro formale vettore - attuale puntatore
- Consente di generare un vettore da un sotto-vettore, oppure da un puntatore.

Si puo passare un puntatore ad una funzione che vuole un vettore come parametro

---
#### Puntatori e stringhe

Le stringhe sono vettori di char terminati da \0.
Si possono trattare come vettori o con i puntatori e la loro aritmetica.

Esempi di funzioni che esistono gia nelle librerie:

- Strlen 
-v1
Conta i caratteri cercando l'indice '\0'.
```C
int strlen0(char s[]){ //Riceve un vettore adimensionato
	int cnt=0;
	while (s[cnt]!=’\0’) 
		cnt++; 
	return cnt;
}
```
-v2 (Utilizzo puntatore)
```C
int strlen1(char s[]){ 
	int cnt=0;
	char *p=&s[0]; //Stiamo assegnando un valore a p
	while (*p !=’\0’) { 
		cnt++; 
		p++; 
	} 
	return cnt; 
}
```
-v3
```C
int strlen2(char *s){ //Parametro formale puntatore a char
	int cnt=0; 
	while (*s++ != ’\0’) 
		cnt++; 
	return cnt; 
}
```
-v4 (Solo puntatori)
```C
int strlen3(char *s){ 
	char *p = s; 
	while (*p != ’\0’) 
		p++; 
	return p-s; 
}
```

>**Strcmp** è un'altra funzione, che ritorna un risultato ternario:
- La prima è maggiore della seconda (In ordina alfabetico) ->  +
- La seconda è maggiore della prima (In ordine alfabetico) ->  -
- Sono uguali -> 0

>Quando uno dei due è diverso tra loro ed uno da \0, esce dal ciclo;
>Ritorna la differenza tra gli ultimi caratteri.
>Se la prima finisce prima dell'altra allora il valore è negativo

Esempio strcmp:
-v1 (Solo vettori)
```C
int strcmp0(char s0[], char s1[]){ 
	int i=0; 
	while (s0[i]==s1[i] && s0[i]!=’\0’) 
		i++; 
	return (s0[i]-s1[i]); 
}
```
-v2 (Utilizzo puntatori)
```C
int strcmp1(char *s0, char *s1) { 
	while ((*s0==*s1) && (*s0!=’\0’)){ 
		s0++; 
		s1++; 
	} 
	return (*s0-*s1); 
}
```

>**Strncmp** -> Confronta solo i primi n caratteri delle stringhe.

Esempio di strncmp:
```c
int strncmp0(char s0[], char s1[], int n){ 
	int i=0; 
	while (s0[i]==s1[i] && s0[i]!=’\0’) 
		if (i<n) 
			i++; 
		else
			return 0; 
	
	return (s0[i]-s1[i]); 
}
```

>**strstr** ->Date due stringhe cerca la seconda stringa all'interno della prima ritornando un puntatore:
- NULL se non viene trovata la seconda stringa all'interno della prima
- Al primo carattere della sottostringa trovata (la prima volta)

Esempio:
-v1
```c
char *strstr0(char s[], char c[]){ 
	int i, lun_s, lun_c; 
	lun_s=strlen(s); 
	lun_c=strlen(c); 
	for (i=0; i<=lun_s-lun_c; i++) 
		if (strncmp(&s[i],c,lun_c)==0) 
			return (&s[i]); 
	return (NULL); 
}
```
---
#### Input mediante sscanf

Ibrido che prende l'input da stringa, serve quando si vuole mettere dei dati in una stringa e fare poi dell'input formattato.

> Si utilizza in combo con la fgets.

Non funziona come la fscanf che va avanti dopo che leggi, sscanf legge il valore dal puntatore percio non va trattato allo stesso modo.
Si prende un puntatore che va avanti e punta alla sottostringa.

```c
fgets(riga,MAX,stdin); 
s=riga;
while (sscanf(s, "%d%n", &x, &i)>0) { 
	s = s+i; // oppure s = &s[i]; 
	somma += x; 
	cnt++; 
} 
printf("La media e’: %f\n", somma/cnt);
```

> %d%n -> %d nella variabile che trovi scrivi l'intero e riempi la variabile x
> il %n ti dice quanti caratteri ci ha messo l'input per arrivare fino a li.

---
### Vettori di puntatori

Il puntatore è anche un dato, delle variabili possono contenere dei puntatori ma si possono anche creare dei vettori di puntatori.

>Un vettore di puntatori che puntano a vettori corrisponde ad una **Matrice**.

>**NOTA:** Le matrici fatte come vettori di puntatori sono diverse dalle matrici create coi vettori.

Una matrice è un vettore di righe e si definisce con float\[NR]\[NC].
```c
#define NR 4 
#define NC 5 
float M[NR][NC];

printf("dim. matr.: %d\n", sizeof(M)); // Sara 80 = 4*5*4
printf("dim. riga: %d\n", sizeof(M[0])); // sara 20 = 4*5
printf("dim. elem.: %d\n", sizeof(M[0][0])); // 4
```

Esempio con vettore di puntatori:
```c
#define NR 4 
#define NC 5 
float R0[NC],R1[NC],R2[NC],R3[NC]; 
float *VP[NR] = {R0,R1,R2,R3}; //Inizializzazione
```

Abbiamo fabbricato una matrice finta, che permette di scrivere -> **VP\[i]\[j] = (VP\[i])\[j]**.
Nonostante VP sia un vettore.
Se si misurano le dimensioni però:

```c
printf("dim. matr.: %d\n", sizeof(VP)); //32 = 8*4 byte perchè è un vettore di puntatori
printf("dim. riga: %d\n", sizeof(VP[0])); // 8 byte è un puntatore
printf("dim. elem.: %d\n", sizeof(VP[0][0])); // 4 byte
```

Questi vettori servono poichè, ci permettono di creare matrici che hanno righe di lunghezza diversa poichè noi teniamo il riferimento di dove inizia il vettore.

>Conviene se si hanno delle righe molto lunghe e delle righe corte.

##### Matrice di caratteri

```c
void main (void){ 
	int i,g; 
	char giorni[7][10]= {"lunedì","martedì", "mercoledì","giovedì", "venerdì","sabato","domenica"}; 
	
	printf("quale	carattere	(1-6)?	"); 
	scanf("%d",&i); 
	for	(g=0; g<7; g++) 
		if	(i<strlen(giorni[g])) 
			printf("%c", giorni[g][i-1]); 
		else 
			printf("_"); 
	printf("\n"); 
}
```
oppure (Vettore di puntatori)
```c
void main (void) { 
	int i,g; 
	char *giorni[7]={"lunedì","martedì", "mercoledì","giovedì", "venerdì","sabato","domenica"}; 
	
	printf("quale carattere (1-6)? "); 
	scanf("%d",&i); 
	for (g=0; g<7; g++) 
		if (i<strlen(giorni[g])) 
			printf("%c", giorni[g][i-1]); 
		else 
			printf("_	"); 
	printf("\n"); 
}
```
##### Notazione matriciale

In entrambi i casi:
- Matrice di caratteri
- Vettore di puntatori
Si può utilizzare la **notazione matriciale**.

Esempio: (Ordinamento di stringhe)

- Matrice di caratteri
```c

void main (void){ 
	int i,ns; 
	char m[20][51]; // 51 colonne per i \0 
	printf("scrivi stringhe:\n"); 
	for (ns=0; ns<20; ns++) { 
		gets(m[ns]); 
		if (strlen(m[ns])==0) break; 
	}
	
	ordinaMatrice(m,ns); 
	printf("stringhe ordinate:\n"); 
	for (i=0; i<ns; i++) 
	printf("%s\n", m[i]); 
}
```
- Vettore di puntatori
Vogliamo appiccicare delle parole ad un vettore unico, in modo da risparmiare spazio.

```c
void main (void) { 
	int i,ns; 
	char *v[20], buf[520]; //20 puntatori e buffer di 52*10
	printf ( "scrivi stringhe:\n "); 
	for (ns= i=0; ns<20; ns++) { 
		v[ns]=buf+i; gets(v[ns]); 
		if (strlen(v[ns])==0) break; 
		i = i+strlen(v[ns])+1; 
	} 
	
	ordinaVettore (v,ns); 
	printf ( "stringhe ordinate:\n "); 
	for	( i=0; i<ns; i++) 
	printf ( "%s\n ",v[i]); 
}
```

Sommario:

- Matrice di caratteri:
	- 20 righe: massimo numero di stringhe 
	- 51 colonne: massima lunghezza di stringa 
	- 20\*51 = 1020 caratteri: dimensione matrice 
- Vettore di puntatori a stringhe:
	- 20 puntatori: dimensione vettore di puntatori 
	- 520 caratteri: dimensione di caratteri contenente le stringhe (500 caratteri per le stringhe + 20 terminatori) | < 1020 caratteri
---
#### **Struct** puntatori e vettori

Piu informazioni eterogenee possono essere unite come parti di uno steso dato.

> I campi della struct sono eterogenei (nel vettore sono omogenei tutti dello stesso tipo)
> hanno un nome (nei vettori un indice), 

#### Puntatore a struct

Per accedervi con i puntatori si accede come si accede normalmente per gli altri tipi.
Un puntatore può :
- Puntare ad una struct intera
- Puntare ad un campo della struct
- Essere un campo di una struct

Come passo dal puntatore alle cose che punta?

```c
struct studente{ 
	char cognome[MAX], nome[MAX]; 
	int matricola; 
	float media; 
};

...
struct studente *p;
(*p).media // Per accedere al campo media della struct

float *mp;
mp = &(*p).media; //Sto ricavando il campo media da *p, e lo assegno al untatore mp
```
>Servono le parentesi tonde perché nella tabella delle precedenze il punto precede l'asterisco.

Voglio mettere una sottostruct in una struct:
Come si accede poi al valore dell'esame?
```c
struct esame { 
	int scritto, orale; 
}; 

struct studente { 
	char cognome[MAX], nome[MAX]; 
	int matricola; 
	struct esame *es; 
};

(*p).media 
(*(*p).esame).scritto // Per accedere al voto dello scritto

OPPURE (In c ci sono delle notazioni speciali): //Equivalenti

p->media 
p->esame->scritto

```

> -> equivale a dire che parti dal puntatore, vai alla struct e guarda il campo media.

---
#### Struct ricorsive (Algoritmi II anno)

Si dice ricorsiva una struct che include tra i suoi campi uno o più puntatori a strutture dello stesso tipo.
Servono per realizzare liste, alberi, grafi.

Esempio:
```c
struct studente { 
	char cognome[MAX], nome[MAX]; 
	int matricola; 
	struct studente *link; // sto puntando ad un altro studente.
};
```
Si viola una regola, per cui stiamo usando un qualcosa prima di averlo definito, la stessa struct.
Il trucco è che essendo un puntatore io la dimensione la so per principio ed è di 8 byte.

>Una struct non puo contenere una struct dello stesso tipo, ma un puntatore si.

Altro esempio:
Si può definire un sinonimo per il tipo, prima di aver creato la struct utilizzando il puntatore
```c
typedef struct studente *P_stud;

struct studente { 
	char cognome[MAX], nome[MAX]; 
	int matricola; P_stud link; 
};
```
Altro esempio:

```c
typedef struct studente T_stud; 
struct studente { 
	char cognome[MAX], nome[MAX]; 
	int matricola; T_stud *link; //Devi usare il puntatore perche non lo hai fatto prima
};
```

---
### Vettori di puntatori a struct

Un vettore di struct è diverso da un vettore di puntatori a struct.

Esempio:
```c
typedef struct studente { 
	char cognome[MAXS]; 
	char nome[MAXS]; 
	int matr; 
	float media; 
} stud_t;


stud_t *elencoRif[MAXN]; //Creare vettore di puntatori
for (i=0; i<MAXN; i++) 
	elencoRif[i] = &elenco[i];
```