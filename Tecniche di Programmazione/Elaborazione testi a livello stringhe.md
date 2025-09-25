
A volte conviene lavorare con le stringhe e con la libreria **string.h**.

#### Formattazione di testo

Letto un file lo copi in un altro dopo aver:
- ridotto le sequenze di piu spazi ad uno solo
- sostituito o eliminato caratteri a capo in modo che ogni riga sia giusta rispetto ad un margine
- centrato un testo rispetto alla lunghezza massima

```C
#include <string.h> 
const int STRLEN=21; 
const int LMAX=255; 

...

void format(char nin[],char nout[],int lmax){ 
	FILE *fin=fopen(nin,”r”); 
	FILE *fout=fopen(nout,”w”); 
	char parola[STRLEN], riga[LMAX]; 
	int i,l=-1; // -1 per assorbire il primo 1+strlen 
	riga[0] = '\0'; // oppure strcpy(riga,"");
	 
	while (fscanf(fin,”%s”,parola)==1) { 
		if (l+1+strlen(parola) <= lmax) { 
			if (l>0) { 
				strcat(riga,” “); 
			} 
			// Appende una stringa ad una gia esistente 
			strcat(riga,parola); //sovrascrive il vecchio \0 e lo aggiunge in fondo
			l += 1+strlen(parola);
		} else { 
			for (i=0; i<(lmax-l)/2; i++) 
				fprintf(fout,” “); 
			fprintf(fout,”%s\n”,riga); 
			strcpy(riga,parola); 
			l=strlen(parola); // parti poi con una riga che ha gia la parola dentro
		} 
	} 
}

```
