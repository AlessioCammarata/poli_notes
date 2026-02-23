Vogliamo rappresentare un insieme di oggetti omogenei.
Le tabelle vengono chiamate relazioni
##### Definizioni generali
**Attributo**: nome di una colonna della tabella.
**Dominio**: insieme di valori che possono essere assunti da un attributo.
**N-upla** (record): riga della tabella
**Cardinalità**: Numero di n-uple della relazione
**Grado**: Numero di attributi della relazione
##### Proprietà
- Le n-uple (righe) **non sono ordinate**
- Le n-uple sono **distinte** tra loro (non esistono righe duplicate)
- Gli attributi non sono ordinati (non è possibile individuare un attributo mediante la sua posizione)
#### Riferimenti tra le relazioni
Il modello relazionale è ***basato sui valori***
- i riferimenti tra dati in relazioni diverse sono rappresentati per mezzo di valori dei domini 
Vantaggi 
- indipendenza dalle strutture fisiche 
- rappresentazione solo dell’informazione rilevante 
- maggiore portabilità dei dati tra sistemi diversi

>Si usa un puntatore logico e non uno fisico poiche è bidirezionale e si ha indipendenza fisica dei dati, posso spostare la posizione fisica dei dati e mi rimane il riferimento logico nella istanza.
#### Assenza di valore
È possibile che alcune informazioni non siano disponibili per tutte le n-uple della relazione 

Esempio: 
	Studente (Matricola, Cognome, DataNascita, Telefono, AnnoLaurea) 
	- telefono può essere (temporaneamente?) ignoto 
	- per studente ancora non laureato, anno laurea non definito 
	- per studente appena laureato, anno laurea non ancora definito o ignoto

Definizione di un valore speciale denominato valore nullo (**NULL**) 
- non fa parte di alcun dominio
- rappresenta sia valore ignoto, sia valore non definito 
- deve essere utilizzato con cautela (esempio: Matricola=NULL?) 
>**Notazione**: 
>- gli attributi che possono assumere il valore nullo (NULL) sono spesso evidenziati con apice * nello schema della relazione
---
#### Primary key (Superchiave minimale)
Esempi:
	Non esistono due studenti con lo stesso valore per il numero di matricola 
	- il numero di matricola identifica gli studenti 
	Non esistono due studenti con lo stesso valore per i dati anagrafici 
	- nome, cognome e data di nascita identificano gli studenti

Una ***chiave*** è un **insieme di attributi** che identifica in modo **univoco** le n-uple di una relazione 
- è una proprietà dello schema di una relazione 
**Definizione formale:** un insieme K di attributi è chiave di una relazione r se 
- la relazione r non contiene due n-uple distinte con gli stessi valori per K (univocità) 
- K è minimale (cioè non esistono sottoinsiemi propri di K ancora univoci)
###### Superchiave
Un insieme K di attributi è chiave di una relazione r se 
- la relazione r non contiene **due n-uple** distinte con gli stessi valori per K (univocità) 
- K è minimale (cioè non esistono sottoinsiemi propri di K ancora univoci)
Se è verificata solo la prima proprietà, K è una **superchiave di r**.
Esempi:
	L’insieme di attributi 
		{Matricola,Nome} 
	è univoco, ma non minimale (l’attributo Matricola è univoco anche da solo), quindi è una **superchiave**, ma **non è una chiave** 
	L’insieme di attributi 
		{DataNascita, AnnoImmatricolazione} 
	è univoco e minimale: è una proprietà generale?

>Se una chiave può assumere il valore NULL si perde la proprietà di univocità della chiave, è necessario limitare la presenza di valori nulli nelle chiavi 

Soluzione 
- si definisce una chiave di riferimento, che non ammette valori nulli, detta **chiave primaria** 
- le altre chiavi (**chiavi candidate**) possono ammettere valori nulli 
- **i riferimenti tra dati in relazioni diverse sono eseguiti mediante la chiave primaria**
Notazione: 
- gli attributi che costituiscono la chiave primaria sono spesso evidenziati attraverso la **sottolineatura** nello schema della relazione.
- ---
##### Vincoli d'integrità
proprietà che deve essere soddisfatta da tutte le istanze corrette della base di dati 
Tipi di vincolo 
- ***vincoli intra-relazionali*** 
	- definiti sugli attributi di una sola relazione (esempi: vincoli di unicità, vincoli di dominio e di tupla) 
- ***vincoli inter-relazionali*** 
	- definiti su più relazioni contemporaneamente (esempio: vincoli d’integrità referenziale)
##### Vincoli di Dominio
Esprime condizioni sul valore assunto da un singolo attributo di una tupla 
- può essere un’espressione booleana (and, or, not) di predicati semplici 
esempio: Voto > 0 and Voto <= 30
##### Vincoli di tupla
Esprime condizioni sul valore assunto da singole tuple, in modo indipendente dalle altre tuple della relazione 
- può correlare attributi diversi 
- può essere un’espressione booleana (and, or, not) di predicati semplici (confronto tra attributi, tra attributi e costanti, ...) 
Esempi: 
- Prezzo = Costo + PercIVA\*Costo 
- Lode=True se Voto=30
##### Vincoli d'integrità referenziale
Informazioni in relazioni diverse sono correlate attraverso **valori comuni di uno o più attributi**:
- l’attributo MatrDocente nella relazione Corsi (**relazione referenziante**) fa **riferimento** all’attributo Matricola nella relazione Docenti (**relazione referenziata**) 
- i valori assunti dall’attributo MatrDocente nella relazione Corsi possono essere **esclusivamente** valori assunti dall’attributo Matricola, chiave primaria della relazione Docente 
- l’attributo MatrDocente nella relazione Corsi costituisce la **chiave esterna (foreign key)** di Corsi

>**Vincolo d’integrità referenziale** 

- date due relazioni R e S tali che 
	- R è la relazione referenziata 
	- S è la relazione referenziante, che fa riferimento ad R mediante l’insieme di attributi X 
- i valori assunti dall’insieme X di S possono essere **esclusivamente** valori assunti effettivamente dalla chiave primaria di R 
L’insieme di attributi X di S costituisce una **chiave esterna (o foreign key)** di S.
I vincoli d’integrità referenziale sono fondamentali per garantire la correttezza dei riferimenti (riferimento basato sui valori)
