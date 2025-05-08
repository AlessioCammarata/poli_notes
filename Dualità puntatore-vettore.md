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
 
Per accedere all'i-esimo elemento di un vettore vett[N], una funzione necessita unicamente dell'indirizzo del primo elemento: 
						vett[i] equivale a *(vett+i) 

Per accedere all elemento [i,j] di una matrice mat[NR][NC], a una funzione serve l'indirizzo del primo elemento E il numero di colonne NC della matrice: 
					mat[i][j] equivale a *(mat + NC*i + j)