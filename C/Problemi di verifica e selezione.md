### Problemi di verifica e selezione

	- Ricerca di un valore in un vettore
	- verifiche su sequenza di dati

Esempio:

Un file contiene una sequenza, di cui si hanno il numero di dati.
Verificare che ogni dato sia ripetuto almeno una volta nella sequenza, un dato si considera ripetuto se se ne trova uno che differisce in valore assoluto inferiore al 1%:

```C
int datiRipetuti (FILE *fp) { 
	float dati[MAXDATI]; 
	int ndati, i, j, ripetuto; 
	
	fscanf(fp,“%d”,&ndati);
	
	for (i=0; i<ndati; i++) 
		fscanf(fp,“%f”,&dati[i]);
	
	for (i=0; i<ndati; i++) { 
		ripetuto = 0; 
		for (j=0; j<ndati && !ripetuto; j++) 
			if (i!=j && simili(dati[i],dati[j])) //Controllo la condizione 3
				ripetuto=1; 
		if (!ripetuto) return 0; // Abbandono se il dato non è ripetuto
	} 
	return 1; 
}

/* 
Controllo se la differenza in valore assoluto è < del 1%, Il piu grande in valore assoluto è quello che poi starà a denominatore.
*/
int simili (float a, float b) { 
	if (fabs(a)>fabs(b)) 
		return (fabs(a-b)/fabs(a) < 0.01); 
	else 
		return (fabs(a-b)/fabs(b) < 0.01); 
}

```

### Problema di selezione

Conversione numero di matricola -> Nome.
Faremo un vettore di struct:

```C
#include <string.h> 
typedef struct { 
	char matricola[MMAX+1], nome[NMAX+1]; 
} t_stud; 

... 

/*
La funzione modifica direttamente il vettore, che viene passato alla funzione.
Lo riempe con il nome tramite la strcpy.
*/
int matrNome(char m[], t_stud tabella[], int n, char n[]){ 
	int I; 
	for (i=0; i<n; i++) { 
		if (strcmp(m,tabella[i].matricola)==0) { 
			strcpy (n, tabella[i].nome); 
			return 1; 
		} 
	}
	return 0; 
}
```
