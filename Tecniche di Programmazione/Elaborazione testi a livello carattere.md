Solitamente si lavora sui caratteri se non esiste una funzione gia scritta per le stringhe che possa risolvere il problema.


### Manipolare stringhe

#### Verificare palindromia

Verificare se ottenuta una sequenza di caratteri, c'è palindromia, senza far differenza tra maiuscole e minuscole.
- Si può girare un vettore al contrario convertendo le lettere tutte in maiuscolo
si può risolvere più semplicemente?

- Basta controllare che la 1 sia uguale all'ultima
	- non deve modificare la stringa, senza conversioni
	- lavora direttamente sulla parola originale
	

```C
int palindroma(char parola[]){
	int i, n, pal=1;


	n = strlen(parola);
	for (i=0; i<n/2 && pal; i++){
		if (toupper(parola[i]) != toupper(parola[n-i-1]))
			pal = 0;
	}
	
	return pal
}
```


### Visualizzazione di parabola

Data la parabola:
- y = ax^2 + bx + c

si scriva un programma che possa acquisire i dati e visualizzare la parabola, dove avremmo le x sull'asse y e le y sull'asse x:

```C
const int NR = 20, NC = 80;
int main(void){
	float a,b,c,x,y, passoX, passoY, xmin, xmamx, ymin, ymax;
	int i,j;
	char pagina[NR][NC];
	FILE *fpout = fopen("out.txt","w");

	/*

	Input vari per ottenere i valori
	
	*/

	/* Inizializza matrice */
	for (i=0; i<NR; i++){
		for(j=0;j<NC;j++){
			pagina[i][j] = ' ';
		}
	}

	passoX = (xmax-xmin)/(NC-1);
	passoY = (ymax-ymin)/(NR-1);

	for (j=0; i<NR; i++){

		x = xmin +j*passoX;
		y = a*x*x + b*x c;
		 
		if (y>=ymin && y<=ymax){
			i = (y-ymin)/passoY; 
			pagina[i][j] = '*';
		}
	}

	for(i = NR-1; i>=0 ; i--){
		for (j=0; j<NC; j++)
			fprintf(fpout,"%c",pagina[i][j]);
		fprintf(fpout,"\n");
	}
	fclose(fpout);
}
```


