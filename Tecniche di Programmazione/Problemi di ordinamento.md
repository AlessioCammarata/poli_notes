Si possono fare degli ordinamenti tramite l'utilizzo dei vettori.

### Selection sort

Algoritmo di selezione che si basa sul principio:
- seleziona il piu piccolo,
- scambia il minimo con il dato in prima posizione
- parti dalla seconda posizione, cerchi il minimo e lo scambi con quello in 2 posizione
- vai avanti

```C
void selectionSort (int A[], int N) { 
	int i, j, imin, temp; 
	for (i=0; i<N-1; i++) { 
		/*cerca indice del minimo in A[i]..A[N-1]*/ 
		imin = i; 
		for (j = i+1; j < N; j++) 
			if (A[j] < A[imin]) 
				imin = j; 
		
		/*scambia minimo con A[i]*/ 		
		temp = A[i]; 
		A[i] = A[imin]; 
		A[imin] = temp; 
	} 
}
```

##### Si può applicare a vettori di struct e a vettori di stringhe

supponiamo di avere:

```C
void ordinaStudenti(struct studente el[], int n) { 
	int i, j, imin; 
	stuct studente temp; 
	for (i=0; i<n-1; i++) { 
		/*cerca indice del minimo in el[i]..el[n-1]*/ 
		imin = i; 
		for (j = i+1; j < N; j++) 
			if (STUDlt(el[j],el[imin])) 
				imin = j; 
		/*scambia minimo con el[i]*/ 
		temp = el[i]; 
		el[i] = el[imin]; 
		el[imin] = temp; 
	} 
}
```

Per quanto riguarda le stringhe:

```C
void ordinaNomi(char nomi[][MAXL], int n) { 
	int i, j, imin; 
	char temp[MAXL]; 
	for (i=0; i<n-1; i++) { 
		/*cerca indice del minimo in nomi[i]..nomi[n-1]*/ 
		imin = i; 
		for (j = i+1; j < N; j++) 
			if (strcmp(nomi[j],nomi[imin])<0) 
				imin = j; 
		/*scambia minimo con el[i]*/ 
		strcpy(temp,nomi[i]); 
		strcpy(nomi[i],nomi[imin]); 
		strcpy(nomi[imin],temp); 
	} 
}
```