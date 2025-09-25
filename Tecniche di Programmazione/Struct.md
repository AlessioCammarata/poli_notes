
---
### Struct senza typedef
Un nuovo tipo di dato, si definisce con la parola struct, è un vero e proprio tipo.
```C
struct studente {
	char cognome[max], nome[ma];
	int matricola;
	float media;
};
```

È come una scatola che contiene solo variabili, un oggetto senza metodi e con solo il costruttore.
si chiamano **campi**.

Per definire delle variabili si deve:
```C
struct studente s, t;
```
>**NOTA**: Queste sono due variabili diverse

Schema 1 per la definizione:
(Definiamo sia la strtuct che le variabili contemporaneamente).
```C
struct studente {
	char cognome[max], nome[ma];
	int matricola;
	float media;
}s,t;
```

Facendo cosi si può anche togliere il nome:

```C
struct {
	char cognome[max], nome[ma];
	int matricola;
	float media;
}s,t;
```

Schema 2:
(Prima definisco la struct e poi le variabili)

```C
struct studente {
	char cognome[max], nome[ma];
	int matricola;
	float media;
};

struct studente s, t;
```

### Typedef

typedef viene utilizzato per dare un nome ad un tipo. 
Si da un altro nome ad una cosa che c'è gia.

```C
typedef int number;

number i,num; // Sono  interi
```

Questa cosa permette di ridefinire struct studente con un altro nome.

```C
typedef struct Studente {
	char cognome[max], nome[ma];
	int matricola;
	float media;
};

Studente s, t;
```

>**NOTA**: Si utilizza una sola parola senza utilizzare spazi in mezzo.

---
### Definizione

Sono tipi di dati aggregati come i **vettori**.

#### Differenze

Struct
- accesso per nome 
- dati eterogenei
- parametri per valore
- Accesso parametrizzato

Vettori
- accesso con indice
- dati omogenei


##### Vantaggio dei vettori

Con un ciclo for riesco ad ottenere tutti i campi.
Nelle struct l'accesso dipende da s.nome, dove nome non puo essere un parametro.

```C
/* nella funzione l'accesso è esplicito, non parametrizzato */
void stampaCampo(struct studente s, char id[]) {
	if (strcmp(id,”cognome”)==0) printf("%s",s.cognome);
	else if(strcmp(id,”nome”)==0) printf("%s",s.nome); 
	else if(strcmp(id,”matricola”)==0) printf("%d",s.matricola);
 ... }
```
#### Quale è meglio?

Le struct si utilizzano quando i nomi sono piu importanti e ci sono pochi campi.
Non ho interesse nell'avere accesso parametrizzato.
I dati sono eterogenei.

---
### Vettori di struct

Come si accede:
```C
struct studente s,t, v[10];

scanf("%s", s.nome);
scanf("%s", s.cognome);
scanf("%d", &s.matricola);

s[5].nome // Vettore, la casella del vettore è una struct, percio per accederci si fa cosi.
```

Esempio:
```C

void ordinaStudenti(struct studente el[], int n) { 
/* funzione da scrivere. MODIFICA il contenuto del vettore riordinando gli studenti per media crescente. Funzione completata alla fine del capitolo 4 (col selectionSort) */ 
}

int main(void) {
	struct studente elenco[NMAX];
	int i, n;
	printf("quanti studenti(max %d)? ",NMAX);
	scanf("%d",&n);
	for (i=0; i<n; i++) {
		elenco[i] = leggiStudente();
	}
	ordinaStudenti(elenco,n);
	printf("studenti ordinati per media\n");
	for (i=0; i<n; i++) {
		stampaStudente(elenco[i]);
	}
}
```

---
