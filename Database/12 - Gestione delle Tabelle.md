Creazione tabella e definizione di vincoli.
#### CREATE
```sql
CREATE TABLE NomeTabella 
(NomeAttributo Dominio [ValoreDiDefault ] [Vincoli] 
{ , NomeAttributo Dominio [ValoreDiDefault ] [Vincoli ]} 
AltriVincoli 
);
```
Permette di 
- definire tutti gli **attributi** (le colonne) della tabella 
- definire **vincoli di integrità** sui dati della tabella 
Dominio 
- definisce il **tipo di dato dell’attributo** 
- domini predefiniti del linguaggio SQL (domini elementari) 
- domini definiti dall’utente a partire dai domini predefiniti 
Vincoli 
- permette di specificare **vincoli di integrità sull’attributo** 
AltriVincoli 
- permette di specificare **vincoli di integrità di tipo generale** sulla tabella
##### Domini elementari
Si intende il tipo di dato, Binario boolean ecc..

>Per le stringhe esiste TEXT, **VARCHAR** (lunghezza), **CHAR** (lunghezza)
- **CHAR** occupa sempre 10 caratteri se il valore è piu lungo viene tagliato, se è piu corto occupa sempre 10 caratteri in memoria
- **VARCHAR** occupa invece la memoria esatta, dimensione variabile
---
#### Definizione database fornitore-prodotti
```sql
--Creazione della tabella fornitori
CREATE TABLE F ( 
CodF CHAR(5), 
NomeF CHAR(20), 
NSoci SMALLINT, 
Sede CHAR(15));


--Creazione della tabella Prodotti
CREATE TABLE P ( 
CodP CHAR(6), 
NomeP CHAR(20), 
Colore CHAR(6), 
Taglia SMALLINT,
Magazzino CHAR(15));

--Creazione della tabella forniture
CREATE TABLE FP ( 
CodF CHAR(5), 
CodP CHAR(6), 
Qta INTEGER);
```
---
#### ALTER TABLE
Sono possibili le seguenti “alterazioni” 
- aggiunta di una nuova colonna 
- definizione di nuovo valore di default per una colonna (attributo) esistente  
- eliminazione di una colonna (attributo) esistente 
- definizione di un nuovo vincolo di integrità 
- eliminazione di un vincolo di integrità esistente

```sql
ALTER TABLE NomeTabella 
< ADD COLUMN | 
ALTER COLUMN NomeAttributo 
	< SET | DROP DEFAULT>| DROP COLUMN NomeAttributo 
	< CASCADE | RESTRICT > | 
	ADD CONSTRAINT [NomeVincolo] 
		< definizione-vincolo-unique > |
		< definizione-vincolo-integrità-referenziale > | 
		< definizione-vincolo-check > | 
	DROP CONSTRAINT [NomeVincolo] 
	< CASCADE | RESTRICT >
```

• **RESTRICT** (opzione di **default**) 
- l’elemento (colonna o vincolo) non è rimosso se è presente in qualche definizione di un altro elemento 
• **CASCADE** 
-  tutti gli elementi che dipendono da un elemento rimosso vengono rimossi, fino a quando non esistono più dipendenze non risolte

Esempi:
	Aggiungere la colonna numero dipendenti alla tabella dei fornitori
```sql
ALTER TABLE F 
ADD COLUMN NDipendenti SMALLINT;
```

.
	Aggiungere il valore di default 0 alla colonna quantità della tabella delle furniture
```sql
ALTER TABLE FP 
ALTER COLUMN Qta SET DEFAULT 0;
```

.
	Eliminare la colonna NSoci dalla tabella dei fornitori
```sql
ALTER TABLE F 
DROP COLUMN NSoci RESTRICT;
```
---
#### DROP TABLE
```sql
DROP TABLE NomeTabella 
[ RESTRICT | CASCADE];
```
Tutte le righe della tabella sono eliminate insieme alla tabella 
**• RESTRICT** 
- la tabella non è rimossa se è presente in qualche definizione di tabella, vincolo o vista • opzione di **default** 
**• CASCADE** 
- se la tabella compare in qualche definizione di vista anche questa è rimossa
- ---
#### Dizionario dei dati
I metadati sono informazioni (dati) sui dati, possono essere memorizzati in tabelle della base di dati.
Il **dizionario dei dati** contiene i metadati di una base di dati relazionale, contiene informazioni sugli oggetti della base di dati, è gestito direttamente dal DBMS relazionale e può essere interrogato con istruzioni SQL.
Contiene diverse informazioni 
- descrizione di tutte le strutture (tabelle, indici, viste) della base di dati 
- stored procedure SQL 
- privilegi degli utenti 
- statistiche 
	- sulle tabelle della base di dati 
	- sugli indici della base di dati 
	- sulle viste della base di dati 
	- sulla crescita della base di dati

###### Informazioni sulle Tabelle
Il dizionario dei dati contiene per ogni tabella della base di dati 
- nome della tabella e struttura fisica del file in cui è memorizzata 
- nome e tipo di dato per ogni attributo 
- nome di tutti gli indici creati sulla tabella 
- vincoli di integrità
###### Tabelle del dizionario dati (non importante)
Le informazioni del dizionario dati sono memorizzate in alcune tabelle 
- ogni DBMS utilizza nomi diversi per tabelle diverse 
È possibile interrogare il dizionario dati mediante istruzioni SQL.

Esempio:
	Visualizzare il nome delle tabelle definite dall’utente e il numero di tuple memorizzate in ciascuna di esse
```sql
SELECT Table_Name, Num_Rows 
FROM USER_TABLES; --Contiene metadati relativi alle tabelle dell’utente
```
---
#### Integrità dei dati
##### Vincoli di integrità
I dati all’interno di una base di dati sono corretti se soddisfano un insieme di regole di correttezza
- le regole sono dette vincoli di integrità 
- esempio: Qta >=0 
Le operazioni di modifica dei dati definiscono un nuovo stato della base dati, non necessariamente corretto.
La verifica della correttezza dello stato di una base di dati può essere effettuata 
- dalle **procedure applicative**, che effettuano tutte le verifiche necessarie 
- mediante la definizione di **vincoli di integrità** sulle tabelle 
- mediante la definizione di **trigger**
###### Procedure applicative
All’interno di ogni applicazione sono previste tutte le verifiche di correttezza necessarie.

>L'approccio è **flessibile**, pero: 
>- Si possono aggirare le verifiche interagendo con il DBMS
>- Un errore di codifica può avere un effetto significativo sulla base di dati
>- La conoscenza delle regole di correttezza è tipicamente “nascosta” nelle applicazioni
###### Vincoli di integrità sulle tabelle
I vincoli di integrità sono 
- definiti nelle istruzioni CREATE o ALTER TABLE 
- memorizzati nel dizionario dati di sistema 
Durante l’esecuzione di qualunque operazione di modifica dei dati il DBMS verifica automaticamente che i vincoli siano osservati

**Vantaggi**:
- definizione **dichiarativa** dei vincoli, la cui verifica è affidata al sistema, il dizionario dei dati descrive tutti i vincoli presenti nel sistema.
- unico punto centralizzato di verifica, (impossibilità di aggirare la verifica dei vincoli)
**Svantaggi**:
- possono **rallentare** l’esecuzione delle applicazioni
- non è possibile definire **tipologie arbitrarie di vincoli** 
	- esempio: vincoli su dati aggregati
###### Trigger
I trigger sono **procedure eseguite in modo automatico quando si verificano opportune modifiche dei dati** 
- definiti nell’istruzione **CREATE TRIGGER** 
- memorizzati nel dizionario dati del sistema 
Quando si verifica un **evento di modifica** dei dati sotto il controllo del **trigger**, la procedura viene eseguita automaticamente.

**Vantaggi**:
- permettono di definire vincoli d’integrità di tipo complesso, normalmente usati insieme alla definizione di vincoli sulle tabelle
- unico punto centralizzato di verifica, (impossibilità di aggirare la verifica dei vincoli)
**Svantaggi**:
- possono **rallentare** l’esecuzione delle applicazioni
- applicativamente complessi
#### Riparazione delle violazioni
Se un’applicazione tenta di eseguire un’operazione che violerebbe un vincolo, il sistema può 
- impedire l’operazione, causando un errore di esecuzione dell’applicazione 
- eseguire un’azione compensativa tale da raggiungere un nuovo stato corretto 
	- esempio: quando si cancella un fornitore, cancellare anche tutte le sue forniture
#### Vincoli d'integrità SQL
Possibilità di specificare i vincoli di integrità in modo dichiarativo.
Si affida al sistema la verifica della loro consistenza.
Tipologie di vincoli: 
- vincoli di tabella 
	- restrizioni sui dati permessi nelle colonne di una tabella 
- vincoli d'integrità referenziale 
	- gestione dei riferimenti tra tabelle diverse • basati sul concetto di chiave esterna
##### Vincoli di Tabella
Sono definiti su una o più colonne di una tabella.
Sono definiti nelle istruzioni di creazione di 
- tabelle 
- domini 
Tipologie 
- chiave primaria 
- ammissibilità del valore nullo 
- unicità 
- vincoli generali di tupla 
Sono verificati dopo ogni istruzione SQL che opera sulla tabella soggetta al vincolo 
- inserimento di nuovi dati 
- modifica del valore di colonne soggette al vincolo 
>Se il vincolo è violato, l’istruzione SQL che ha causato la violazione genera un errore di esecuzione.
###### Primary Key
```sql
NomeAttributo Dominio PRIMARY KEY
--OPPURE se composto da piu attributi

PRIMARY KEY (ElencoAttributi)
```
Esempi:
	un solo attributo
```sql
CREATE TABLE F (
	CodF CHAR(5) PRIMARY KEY, 
	NomeFCHAR(20), 
	NSoci SMALLINT, 
	Sede CHAR(15)
);
```
	uno op più attributi
```sql
CREATE TABLE FP (
	CodF CHAR(5), 
	CodP CHAR(6), 
	Qta INTEGER PRIMARY KEY (CodF, CodP)
);
```
###### Ammissibilità del valore
Il valore NULL indica l’assenza di informazioni .
Quando è obbligatorio specificare sempre un valore per l’attributo.
```sql
NomeAttributo Dominio NOT NULL
```
Esempio:
```sql
CREATE TABLE F (
	CodF CHAR(5), 
	NomeFCHAR(20) NOT NULL, 
	NSoci SMALLINT, 
	Sede CHAR(15)
);
```
###### Unique
Un attributo o un insieme di attributi non può assumere lo stesso valore in righe diverse della tabella
- per un solo attributo
```sql
NomeAttributo Dominio UNIQUE
```
- per uno o piu attributi
```sql
UNIQUE (ElencoAttributi)
```
- È ammessa la ripetizione del valore NULL (considerato sempre diverso)
Esempio:
```sql
CREATE TABLE P (
	CodP CHAR(6), 
	NomeP CHAR(20) NOT NULL UNIQUE, 
	Colore CHAR(6), 
	Taglia SMALLINT, 
	Magazzino CHAR(15)
);
```
###### Vincoli generali di tupla
Permettono di esprimere condizioni di tipo generale su ogni tupla 
- vincoli di tupla o di dominio 
```sql
NomeAttributo Dominio CHECK (Condizione)
``` 
- possono essere indicati come condizione i predicati specificabili nella clausola WHERE 
- La base di dati è corretta se la condizione è vera
Esempio:
```sql
CREATE TABLE F (
	CodF CHAR(5) PRIMARY KEY, 
	NomeF CHAR(20) NOT NULL, 
	NSoci SMALLINT CHECK (NSoci>0), 
	Sede CHAR(15)
);
```

>Le operazioni viste finora sono impedite in caso di fallimento.
##### Vincoli d'integrità referenziale
Permettono di gestire il legame tra tabelle mediante il valore di attributi .
La chiave esterna è definita nell’istruzione CREATE TABLE della tabella referenziante 
```sql
FOREIGN KEY (ElencoAttributiReferenzianti ) 
REFERENCES NomeTabella [(ElencoAttributiReferenziati )] 
```
Se gli attributi referenziati hanno lo stesso nome di quelli referenzianti, non è obbligatorio specificarli.

Esempio:
```sql
CREATE TABLE FP (
	CodF CHAR(5), 
	CodP CHAR(6), 
	Qta INTEGER, PRIMARY KEY (CodF, CodP), 
	FOREIGN KEY (CodF) REFERENCES F(CodF), --Referenzio la Key esterna a CodF
	FOREIGN KEY (CodP) REFERENCES P(CodP)  --Referenzio la Key esterna a CodP
);
```
#### Politiche di gestione dei vincoli
- I vincoli d'integrità sono verificati dopo ogni istruzione SQL che potrebbe causarne la violazione 
- Non sono ammesse operazioni di inserimento e modifica della tabella referenziante che violino il vincolo 
- Nell'istruzione CREATE TABLE della tabella referenziante 
```sql
FOREIGN KEY (ElencoAttributiReferenzianti ) 
REFERENCES 
NomeTabella [(ElencoAttributiReferenziati)] 
[ON UPDATE 
<CASCADE | SET DEFAULT | SET NULL | NO ACTION>] 
[ON DELETE 
<CASCADE | SET DEFAULT | SET NULL | NO ACTION>] 
```
Operazioni di modifica o cancellazione dalla tabella referenziata causano sulla tabella referenziante: 
- **CASCADE**: propagazione dell'operazione di aggiornamento o cancellazione 
- **SET NULL/DEFAULT**: null o valore di default in tutte le colonne delle tuple che hanno valori non più presenti nella tabella referenziata 
- **NO ACTION**: non si esegue l'azione invalidante

Esempio:

```sql
CREATE TABLE P (
	CodP CHAR(6) PRIMARY KEY, 
	NomeP CHAR(20) NOT NULL UNIQUE, 
	Colore CHAR(6), 
	Taglia SMALLINT CHECK (Taglia > 0), 
	Magazzino CHAR(15)
);

CREATE TABLE F (
	CodF CHAR(5) PRIMARY KEY, 
	NomeF CHAR(20) NOT NULL, 
	NSoci SMALLINT CHECK (NSoci>0), 
	Sede CHAR(15)
);

CREATE TABLE FP (
	CodF CHAR(5), 
	CodP CHAR(6), 
	Qta INTEGER CHECK (Qta IS NOT NULL and Qta>0), 
	PRIMARY KEY (CodF, CodP), 
	FOREIGN KEY (CodF) 
		REFERENCES F(CodF) 
		ON DELETE NO ACTION 
		ON UPDATE CASCADE, 
	FOREIGN KEY (CodP) 
		REFERENCES P(CodP) 
		ON DELETE NO ACTION 
		ON UPDATE CASCADE
);
```

>Vengono messe nella tabella SLAVE, quella referenziante.
>Questo poiche l'effetto di ON UPDATE e ON DELETE, hanno effetto sulla tabella FP dopo che succede qualcosa in F o in P.

ON DELETE NO ACTION, significa che la tabella master per concludere la sua operazione ha bisogno del consenso della referenziante. (Lo slave deve dare il consenso al Master)

