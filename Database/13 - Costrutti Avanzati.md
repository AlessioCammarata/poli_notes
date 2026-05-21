#### Transazioni
Necessaria quando più utenti possono accedere contemporaneamente ai dati.
Offre meccanismi efficienti per 
- **gestire l’accesso concorrente** ai dati 
- effettuare il **recovery a seguito di un malfunzionamento** 

E' un’**unità logica di lavoro**, non ulteriormente scomponibile 
- una sequenza di operazioni (istruzioni SQL) di modifica dei dati, che porta la base di dati da uno stato consistente a un altro stato consistente 
- non è necessario conservare la consistenza negli stati intermedi 

Un sistema che mette a disposizione un meccanismo per la definizione e l’esecuzione di transazioni viene detto **sistema transazionale**.
I DBMS contengono blocchi architetturali che offrono servizi di gestione delle transazioni
##### Inizio di una transazione
Per definire l’inizio di una transazione, il linguaggio SQL prevede l’istruzione 
- **START TRANSACTION** 
Di solito l’istruzione di inizio della transazione è omessa 
- l’inizio è implicito 
	- prima istruzione SQL del programma che accede alla base di dati 
	- prima istruzione SQL successiva all’istruzione di termine della transazione precedente
##### Fine di una transazione
Il linguaggio SQL prevede istruzioni per definire la fine di una transazione 
- Transazione terminata con successo 
	- **COMMIT [WORK]** 
	- l’azione associata all’istruzione si chiama ***commit*** 
- Transazione terminata con insuccesso 
	- **ROLLBACK [WORK]** 
	- l’azione associata all’istruzione si chiama ***abort***
###### Commit
Azione eseguita quando una transazione termina con successo. 
La base di dati è in un nuovo stato (finale) corretto.
Le modifiche dei dati effettuate dalla transazione divengono 
- **permanenti** 
- visibili agli altri utenti
###### Rollback
Azione eseguita quando una transazione termina a causa di un errore 
- per esempio, di un errore applicativo 
Tutte le operazioni di modifica dei dati eseguite durante la transazione sono “annullate”. 
La base di dati **ritorna nello stato precedente l’inizio della transazione** 
- i dati sono nuovamente visibili agli altri utenti


Esempio:
	Trasferire la somma 100 
	- dal conto corrente bancario IT92X0108201004300000322229 
	- al conto corrente bancario IT32L0201601002410000278976
```sql
START TRANSACTION; 

UPDATE Conto-Corrente 
	SET Saldo = Saldo - 100 
	WHERE IBAN='IT92X0108201004300000322229'; 
	
UPDATE Conto-Corrente 
	SET Saldo = Saldo + 100 
	WHERE IBAN= 'IT32L0201601002410000278976'; 
	
COMMIT;
```
##### Proprietà delle transazioni (Non servono)
Le proprietà principali delle transazioni sono 
- Atomicity – atomicità 
- Consistency – consistenza 
- Isolation – isolamento 
- Durability – persistenza (o durabilità) 
>Sono riassunte dall’acronimo (inglese) **ACID**.
###### Atomicità
Una transazione è un’unità indivisibile (atomo) di lavoro 
- devono essere eseguite tutte le operazioni contenute nella transazione 
- oppure nessuna delle operazioni contenute nella transazione deve essere eseguita

La base di dati non può rimanere in uno stato intermedio assunto durante l’esecuzione di una transazione
###### Consistenza
L’esecuzione di una transazione deve portare la base di dati 
- da uno stato iniziale consistente (corretto) 
- a uno stato finale consistente 

La correttezza è verificata dai vincoli di integrità definiti sulla base di dati.
Quando si verifica la violazione di un vincolo di integrità il sistema interviene 
- per annullare la transazione 
- oppure, per modificare lo stato della base di dati eliminando la violazione del vincolo
###### Isolamento
L’esecuzione di una transazione è indipendente dalla contemporanea esecuzione di altre transazioni.
Gli effetti di una transazione non sono visibili dalle altre transazioni fino a quando la transazione non è terminata 
- si evita la visibilità di stati intermedi non stabili 
	- uno stato intermedio può essere annullato da un rollback successivo 
	- in caso di rollback, è necessario effettuare rollback delle altre transazioni che hanno osservato lo stato intermedio (effetto domino)
###### Persistenza
L’effetto di una transazione che ha effettuato il commit è memorizzato in modo permanente 
- le modifiche dei dati eseguite da una transazione terminata con successo sono permanenti dopo il commit 

Garantisce l’affidabilità delle operazioni di modifica dei dati 
- i DBMS offrono meccanismi di ripristino dello stato corretto della base di dati dopo che si è verificato un guasto
---
### Controllo dell'acceso ai Dati

Protezione dei dati da 
- **letture non autorizzate** 
- **alterazione o distruzione** 
Il DBMS fornisce strumenti per realizzare le protezioni, che sono definite dall’amministratore della base dati (DBA).
Il controllo della sicurezza verifica che gli utenti siano autorizzati a eseguire le operazioni che richiedono di eseguire.
La sicurezza è garantita attraverso un insieme di vincoli 
- specificati dal DBA in un opportuno linguaggio 
- memorizzati nel dizionario dei dati del sistema

#### Privilegi d'accesso

Qualsiasi componente dello schema di una base di dati è una risorsa (tabelle, viste , ecc..)
>Le risorse sono protette mediante la definizione di **privilegi di accesso**.

Questi descrivono i diritti di accesso alle risorse del sistema 
- SQL offre meccanismi di controllo dell’accesso molto flessibili mediante i quali è possibile specificare 
	- le risorse a cui possono **accedere gli utenti** 
	- le risorse che devono **essere mantenute private**

Ogni privilegio è caratterizzato dalle seguenti informazioni 
- la **risorsa** a cui si riferisce 
- il **tipo** di privilegio: descrive l’azione permessa sulla risorsa 
- l’utente che **concede** il privilegio 
- l’utente che **riceve** il privilegio 
- la facoltà di **trasmettere** il privilegio ad altri utenti
##### Tipi di privilegi
**INSERT**
- Permette di inserire un nuovo oggetto nella risorsa
- tabelle e viste

**SELECT**
- permette di utilizzare la risorsa all’interno di un’interrogazione 
- vale per le tabelle e le viste

**UPDATE**
- permette di aggiornare il valore di un oggetto 
- vale per le tabelle, le viste e gli attributi

**DELETE**
- permette di rimuovere oggetti dalla risorsa 
- vale per le tabelle e le viste

**REFERENCES**
- permette di far riferimento a una risorsa nella definizione dello schema di una tabella 
- può essere associato solo a tabelle e attributi

**USAGE**
- permette di utilizzare la risorsa (per esempio, un nuovo tipo di dato) nella definizione di nuovi schemi

>Il creatore della risorsa possiede tutti i privilegi, e puo anche eliminare la risorsa DROP o modificarla ALTER, l'amministratore di sistema ha tutti i privilegi

#### Gestione dei privilegi in SQL
I privilegi sono concessi o revocati mediante le istruzioni SQL 
**GRANT** 
- concede privilegi su una risorsa a uno o più utenti 
**REVOKE** 
- toglie a uno o più utenti i privilegi che erano stati loro concessi

##### GRANT
```sql
GRANT ElencoPrivilegi ON NomeRisorsa 
TO ElencoUtenti 
[WITH GRANT OPTION] 
```

 ElencoPrivilegi: specifica l’elenco dei privilegi 
 **ALL PRIVILEGES**: parola chiave per identificare tutti i privilegi 
 
NomeRisorsa: specifica la risorsa sulla quale si vuole concedere il privilegio 
ElencoUtenti: specifica gli utenti a cui viene concesso il privilegio 
**WITH GRANT OPTION**: facoltà di trasferire il privilegio ad altri utenti

##### REVOKE
```sql
REVOKE ElencoPrivilegi ON NomeRisorsa 
FROM ElencoUtenti 
[RESTRICT|CASCADE] 
```
Può togliere 
- tutti i privilegi che erano stati concessi 
- un sottoinsieme dei privilegi concessi NomeRisorsa 
**RESTRICT** 
- il comando non deve essere eseguito qualora la revoca dei privilegi all’utente comporti qualche altra revoca di privilegi 
	- Esempio: l’utente ha ricevuto i privilegi con GRANT OPTION e ha propagato i privilegi ad altri utenti 
- valore di default 
**CASCADE** 
- revoca anche tutti i privilegi che erano stati propagati 
	- genera una reazione a catena 
- per ogni privilegio revocato sono 
	- revocati in cascata tutti i privilegi concessi 
	- rimossi tutti gli elementi della base di dati che erano stati creati sfruttando questi privilegi

>RESTRICT default
#### Concetto di Ruolo
Il ruolo è un **profilo di accesso** definito dall’insieme di privilegi che lo caratterizzano.
Ogni utente ricopre un ruolo predefinito e gode dei privilegi associati al ruolo 
Vantaggi 
- controllo dell’accesso più flessibile 
	- possibilità che un utente ricopra ruoli diversi in momenti diversi 
- semplificazione dell’attività di amministrazione 
	- possibilità di definire un profilo di accesso in un momento diverso dalla sua attivazione 
	- facilità nella definizione del profilo di nuovi utenti
```sql
CREATE ROLE NomeRuolo

SET ROLE NomeRuolo
```

 >Definizione dei privilegi di un ruolo e del ruolo di un utente -> istruzione GRANT 
 >Un utente in momenti diversi può ricoprire ruoli diversi, associazione dinamica di un ruolo a un utente. 

 ---
### VISTE
La vista è una **tabella “virtuale”** 
- il contenuto (tuple) è definito mediante un’interrogazione SQL sulla base di dati 
	- il contenuto della vista dipende dal contenuto delle altre tabelle presenti nella base di dati
- il contenuto **non** è memorizzato fisicamente nella basi di dati 
	- è ricalcolato tutte le volte che si usa la vista eseguendo l’interrogazione che la definisce 

La vista è un **oggetto della base di dati**, è utilizzabile nelle interrogazioni come se fosse una tabella.
Se l’interrogazione fa riferimento a una vista, deve essere riscritta dal DBMS prima dell’esecuzione.
La riscrittura è svolta automaticamente, si sostituiscono i riferimenti alla vista con la sua definizione.

>Vantaggio la creo una volta e la posso richiamare, pero essendo un oggetto va gestito e manipolato dal DBMS.

Esempio:
```sql
--Creazione vista PICCOLI_FORNITORI
CREATE VIEW PICCOLI_FORNITORI AS 
SELECT CodF, NomeF, NSoci, Sede 
FROM F 
WHERE Nsoci<3;

--Esempi di interrogazioni (equivalenti una con view una senza)
SELECT * 
FROM F 
WHERE NSoci<3 AND Sede=‘Torino’; --Senza view

SELECT * 
FROM PICCOLI_FORNITORI 
WHERE Sede=‘Torino’; --Utilizzando la view
```

Si creano con CREATE VIEW e si eliminano con DROP VIEW:
```sql
CREATE VIEW NomeVista [(ElencoAttributi) ] 
AS InterrogazioneSQL;

DROP VIEW NomeVista;
```

>Si utilizzano le view per semplificare la scrittura di alcune query, per la gestione anche dei meccanismi di protezione e della privatezza di ogni utente o gruppo.
#### Aggiornabilità delle viste
È possibile eseguire operazioni di aggiornamento dei dati presenti in una vista **solo** per alcune tipologie di viste .

**Sono aggiornabili** le viste in cui una sola riga di ciascuna tabella di base corrisponde a una sola riga della vista
- corrispondenza univoca tra le tuple della vista e le tuple della tabella su cui è definita 
- è possibile propagare senza ambiguità le modifiche apportate sulla vista verso ogni tabella su cui è definita 

**Non è aggiornabile** una vista che, nel blocco più esterno dell’interrogazione che la definisce 
- non contiene la chiave primaria della tabella su cui è definita 
- contiene join che rappresentano corrispondenze uno a molti o molti a molti
- contiene funzioni aggregate
- contiene DISTINCT 

>Alcune viste non aggiornabili possono diventare aggiornabili modificando l’espressione SQL associata alla vista, può essere necessario ridurre il contenuto informativo della vista

Esempio:
```sql
--Vista aggiornabile
CREATE VIEW FORNITORE_SEDE AS
SELECT CodF, Sede
FROM F;

--Se inserisco (‘F10’, ‘Roma’), sto inserendo (‘F10’, NULL, NULL, ‘Roma’)
--gli attributi NomeF, NSoci devono ammettere il valore NULL

--Vista non aggiornabile
CREATE VIEW NUMSOCI_SEDE AS 
SELECT DISTINCT NSoci, Sede --Aggiunta la DISTINCT, non abbiamo la PK
FROM F;

--Inserimento di (40, ‘Napoli’) -> (NULL, NULL, 40, ‘Napoli’). PK non puo essere nulla

--Vista non aggiornabile 2
CREATE VIEW FORNITORI_TORINO AS 
SELECT * --Bisogna scrivere il valore degli attributi
FROM F
WHERE Sede=‘Torino’;

--Vista non aggiornabile 3
CREATE VIEW FORNITORI_IMPORTANTI (CodF, NomeF) AS 
SELECT DISTINCT CodF, NomeF --è presente la DISTINCT
FROM F, FP 
WHERE F.CodF=FP.CodF --è presente un join
	AND Qta>100;

--Vista aggiornabile 2 (legata alla 3)
CREATE VIEW FORNITORI_IMPORTANTI (CodF, NomeF) AS 
SELECT CodF, NomeF 
FROM F 
WHERE CodF IN (SELECT CodF --il join è stato realizzato mediante IN
				FROM FP 
				WHERE Qta>100);
				
--In questo caso la parola chiave DISTINCT non è più necessaria
```
---
