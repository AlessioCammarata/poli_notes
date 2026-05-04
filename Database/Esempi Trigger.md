##### Esempio di progettazione (3)
###### Schema di riferimento
Tabelle 
- Studente S (**SId**, SName, DCId) 
- Corso di laurea DC (**DCId**, DCName) 
Vista materializzata 
- Studenti iscritti ES (**DCId**, TotalStudents) 
	- per ogni corso di laurea, TotalStudents conta il numero totale degli studenti iscritti 
	- definito dalla query 
```sql
SELECT DCId, COUNT(*) 
FROM S 
GROUP BY DCId;
```
Propagare le modifiche sulla tabella S alla vista materializzata (tabella) ES 
- inserimento di nuove tuple in S 
- cancellazione di tuple da S 
- aggiornamento dell'attributo DCId in una o più tuple di S
###### Progettazione
Progettare tre trigger per gestire separatamente ogni modifica dei dati
- trigger di inserimento, trigger di cancellazione, trigger di aggiornamento 
- tutti i trigger condividono la stessa semantica di esecuzione 

Semantica di esecuzione 
- **dopo** che la modifica ha avuto luogo 
	- la tabella ES viene aggiornata dopo che la tabella S è stata modificata 
- **livello di tupla** 
	- esecuzione separata per ogni tupla della tabella S 
		- significativamente più semplice da implementare
###### Trigger di inserimento
Evento
- insert on S
Condizione
- Nessuna, è sempre eseguito
Azione
- se la tabella ES contiene DCId a cui è iscritto lo studente
	- Incrementare TotaleStudents
- altrimenti
	- Aggiungere una nuova tupla in ES per il corso di laurea, con TotaleStudents impostato ad 1
```plsql
CREATE TRIGGER InsertNewStudent 
AFTER INSERT ON S --Di tupla è sempre AFTER (Tranne nel caso ancora non spiegato)
FOR EACH ROW --Di tupla mi serve la tupla singola, per vedere il corso di laurea
DECLARE 
	N number; --Variabile locale al Trigger 
BEGIN 
--- verificare se la tabella ES contiene la tupla per il corso di laurea 
--- corso NEW.DCId a cui lo studente si iscrive 
select count(*) into N 
from ES 
where DCId = :NEW.DCId;

if (N <> 0) then 
	--- la tupla per il corso di laurea NEW.DCId è disponibile in ES 
	update ES 
	set TotalStudents = TotalStudents + 1 
	where DCId = :NEW.DCId; 
else 
	--- nessuna tupla per il corso di laurea NEW.DCId è disponibile in ES 
	insert into ES (DCId, TotalStudents) 
	values (:NEW.DCId, 1); 
end if; 
END;
```
###### Trigger di cancellazione
Evento
- delete from S
Condizione
- Nessuna, è sempre eseguito
Azione
- se lo studente era l'unico iscritto al corso di laurea 
	- Cancellare la tupla corrispondente da ES
- altrimenti
	- Decrementare TotaleStudents
```plsql
CREATE TRIGGER InsertNewStudent 
AFTER DELETE FROM S --Di tupla, usiamo AFTER
FOR EACH ROW --Di tupla mi serve la tupla singola, per vedere il corso di laurea
DECLARE 
	N number; --Variabile locale al Trigger 
BEGIN 
--- leggere il numero di studenti iscritti al corso di laurea OLD.DCId
select count(*) into N 
from ES 
where DCId = :OLD.DCId;

if (N > 1) then 
	--- ci sono molti studenti iscritti
	update ES 
	set TotalStudents = TotalStudents - 1 
	where DCId = :OLD.DCId; 
else 
	--- c'è un solo studente iscritto
	delete from E
	where DCId = :OLD.DCId; 
end if; 
END;
```
###### Trigger di aggiornamento
Evento
- update of DCId on S
Condizione
- Nessuna, è sempre eseguito
Azione
- Aggiornare la tabella ES per il corso di laurea a cui era iscritto lo studente
	- Decrementare quello in cui era, o cancellare se era l'unico
- Aggiornare la tabella ES per il corso di laurea a cui è iscritto  adesso lo studente
	- Incrementare TotaleStudents, o inserire nuova tupla
```plsql
CREATE TRIGGER InsertNewStudent 
AFTER UPDATE OF DCId FROM S --Di tupla, usiamo AFTER
FOR EACH ROW --Di tupla mi serve la tupla singola, per vedere il corso di laurea
DECLARE 
	N number; --Variabile locale al Trigger 
BEGIN 
--- leggere il numero di studenti iscritti al corso di laurea OLD.DCId
select count(*) into N 
from ES 
where DCId = :OLD.DCId;

if (N > 1) then 
	--- ci sono molti studenti iscritti
	update ES 
	set TotalStudents = TotalStudents - 1 
	where DCId = :OLD.DCId; 
else 
	--- c'è un solo studente iscritto
	delete from E
	where DCId = :OLD.DCId; 
end if; 
--- verificare se la tabella ES contiene la tupla per il corso di laurea 
--- corso NEW.DCId a cui lo studente si iscrive 
select count(*) into N 
from ES 
where DCId = :NEW.DCId;

if (N <> 0) then 
	--- la tupla per il corso di laurea NEW.DCId è disponibile in ES 
	update ES 
	set TotalStudents = TotalStudents + 1 
	where DCId = :NEW.DCId; 
else 
	--- nessuna tupla per il corso di laurea NEW.DCId è disponibile in ES 
	insert into ES (DCId, TotalStudents) 
	values (:NEW.DCId, 1); 
end if; 
END;
```
##### Esempio di progettazione (2)
###### Schema di riferimento
Sono riportate le seguenti tabelle 
- Supplier S (**S#**, SName, …) 
- Part P (**P#**, PName, …) 
- Supply SP (**S#**, **P#**, Qty) 
Vincolo da rispettare 
- la quantità di un prodotto fornito non può essere superiore a 1000. Se è maggiore, ridurla a 1000. 
I vincoli di controllo **non consentono azioni di compensazione**
- implementare con un trigger
###### Vincolo
Predicato di vincolo 
- Qty > 1000 
- è anche la condizione di attivazione 
Eventi 
- insert on SP 
- update of Qty on SP 
Azione 
- Qty = 1000
###### Semantica e Trigger
Semantica dell'esecuzione  
- **prima** che avvenga la modifica 
	- il suo effetto può essere modificato prima che il vincolo venga controllato 
- **livello di tupla** 
	- ogni tupla viene modificata separatamente

```plsql
CREATE TRIGGER ExcessiveQty 
BEFORE UPDATE OF Qty OR INSERT ON S -- Usiamo Before
FOR EACH ROW --Di tupla mi serve la tupla singola, per vedere il la quantita
WHEN (NEW.Qty > 1000)
BEGIN 
:NEW.Qty := 1000;
END;
```
>Utilizzo before, prima il trigger e poi l'evento, in questo modo modifico la tupla prima che venga inserita in modo da inserire gia la tupla con valore 1000.

##### Esempio di progettazione (1)
###### Schema di riferimento
Sono riportate le seguenti tabelle 
- Supplier S (**S#**, SName, …) 
- Part P (**P#**, PName, …) 
- Supply SP (**S#**, **P#**, Qty) 
Vincolo da rispettare 
- un pezzo può essere fornito al massimo da 10 fornitori diversi
###### Vincolo
Predicato di vincolo 
```sql
SELECT P#
from SP
group by P#
having count(*) > 10;
```
- insieme di parti che violano il vincolo
Eventi 
- insert on SP 
- update of P# on SP 
Azione 
- rifiutare la transazione in violazione
###### Semantica e Trigger
Semantica dell'esecuzione  
- **dopo** la modifica
- **livello di istruzione**
	- per catturare l'effetto dell'intera modifica
	- (Oracle) per consentire l'accesso alla tabella mutante

```plsql
CREATE TRIGGER TooManySuppliers
AFTER UPDATE OF P# OR INSERT ON S
DECLARE
	N number;
BEGIN 
-- La query estrae tutti i record dalla tabella `SP` che corrispondono ai prodotti incriminati. Se un prodotto ha 11 fornitori, la tua variabile `N` varrà **11** (il numero di _forniture_ in `SP`), non **1** (il numero di _prodotti_).
select count(*) into N
from SP
where P# IN (select P# from SP
			group by P#
			having count(*) > 10);

--Se ne esiste anche solo uno, allora segnalo l'errore
if(N<>0) then
	raise_application_error(xxx, 'Constraint violated');
end if;
END;
```
