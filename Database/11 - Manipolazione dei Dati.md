Le operazioni di aggiornamento modificano lo stato della base di dati, è necessario verificare che siano rispettati i vincoli di integrità.
Ogni istruzione può aggiornare il contenuto di una sola tabella.

**INSERT**
- **inserimento** di nuove tuple in una tabella 
DELETE 
- **cancellazione** di tuple da una tabella 
**UPDATE** 
- **modifica** del contenuto di tuple in una tabella

>Sono considerate operazioni atomiche, quindi hanno solo 2 stati, eseguita o non eseguita.
#### INSERT
Inserimento di una sola tupla 
- assegnazione di un valore costante ad ogni attributo 
```sql
		INSERT INTO NomeTabella 
		[(ElencoColonne)] 
		VALUES (ElencoCostanti); 
```
Inserimento di più tuple 
- lette da altre tabelle mediante un’istruzione SELECT 
- la query non può contenere la clausola ORDER BY 
```sql
		INSERT INTO NomeTabella 
		[(ElencoColonne)] 
		Interrogazione;
```
###### Esempi
Esempio1:
	Inserire il prodotto P7 con nome: maglia, colore: viola, taglia: 40, città: Venezia
```sql
INSERT INTO P (CodP, NomeP, Colore, Taglia, Città) 
VALUES ('P7', 'Maglia', 'Viola',40,'Venezia');
```

>è inserita nella Tabella P una nuova tupla con i valori specificati.
>Omettere la lista dei campi equivale a specificare tuti i campi secondo l'ordne di creazione delle colonne nella tabella
>	Se la tabella cambia schema, l'istruzione non è piu applicabile.

Esempio 2:
	Inserire il prodotto P8 con città: Genova, taglia: 42
```sql
INSERT INTO P (CodP, Città, Taglia) 
VALUES ('P8', 'Genova', 42); --NomeP e Colore sono DEFAULT o NULL
```

>Per tutti gli attributi il cui valore non è specificato, il dominio dell'attributo deve consentire il valore NULL. (Se il sistema non è in grado di completare la tupla da errore)

Esempio 3:
	Inserire una nuova fornitura relativa al fornitore F20, prodotto P20 e quantità 1000
```sql
INSERT INTO FP (CodF, CodP, Qta) 
VALUES ('F20', 'P20', 1000);
```
>La query va a buon fine se P20 e F20 sono gia presenti all'interno delle tabelle P e F
>Se il vincolo non è soddisfatto, l'inserimento non viene eseguito.

Esempio 4:
	FORNITURE-TOTALI (**CodP**, TotQta)
	Per ogni prodotto, inserire nella tabella FORNITURE-TOTALI la quantità totale fornita, dati aggregati estratti dalla tabella FP.
```sql
INSERT INTO FORNITURE-TOTALI (CodP, TotQta) (
		SELECT CodP, SUM(Qta) 
		FROM FP 
		GROUP BY CodP
	);
```
---
#### DELETE
```sql
DELETE FROM NomeTabella 
[WHERE predicato];
```
Cancellazione dalla tabella NomeTabella di tutte le tuple che soddisfano il predicato .
>Occorre sempre verificare che la cancellazione non causi la violazione di vincoli di integrità referenziale.

Esempio 1:
	Cancellare tutte le forniture
```sql
DELETE FROM FP;
```
>Senza clausola WHERE tutte le tuple soddisfano il predicato di selezione 
>- elimina il contenuto della tabella FP 
>- la tabella non è eliminata

Esempio 2:
	Cancellare la tupla corrispondente al fornitore con codice F1
```sql
DELETE FROM F
WHERE CodF='F1';
```
>Se in FP esistono forniture che fanno riferimento ai fornitori cancellati, la base di dati perde la propria integrità 
>- avviene una violazione del vincolo di integrità referenziale tra FP e F 
>- occorre propagare la cancellazione

Percio per mantenere la coerenza devo cancellare anche da FP prima che da F:
```sql
DELETE FROM FP --Cancello anche in FP
WHERE CodF='F1';

DELETE FROM F
WHERE CodF='F1';
```

Esempio 3:
	Cancellare i fornitori di Milano
	Se in FP esistono forniture che fanno riferimento ai fornitori cancellati, è violato il vincolo di integrità referenziale tra FP e F, occorre cancellare anche tali forniture in FP
```sql
DELETE FROM FP 
WHERE CodF IN (
		SELECT CodF 
		FROM F 
		WHERE Sede='Milano'); 
		
DELETE FROM F 
WHERE Sede='Milano';
```
---
#### UPDATE
```sql
UPDATE NomeTabella 
SET colonna = espressione 
	{, colonna=espressione} 
[ WHERE predicato];
```
Tutti i record della tabella NomeTabella che soddisfano il predicato nella clausola WHERE sono modificati in base alle assegnazioni **colonna=espressione** nella clausola SET.

Esempio 1:
	Aggiornare le caratteristiche del prodotto P1: assegnare giallo al colore, incrementare la taglia di 2 e assegnare NULL a città
```sql
UPDATE P 
SET Colore = 'Giallo', 
	Taglia=Taglia+2, 
	Città = NULL 
WHERE CodP='P1';
```
>È aggiornata la tupla individuata dal codice P1

Esempio 2:
	Aggiornare il numero dei soci al doppio del valore per tutti i fornitori di Milano
```sql
UPDATE F 
SET NSoci=2*NSoci
WHERE Città='Milano';
```
>Sono aggiornate tutte le tuple individuate dal predicato nella clausola WHERE.

Esempio 3:
	Aggiornare a 10 la quantità fornita per tutti i fornitori di Milano
```sql
UPDATE FP 
SET Qta = 10 
WHERE CodF IN (
		SELECT CodF 
		FROM F 
		WHERE Sede='Milano');
```

Esempio 4:
	Modificare con il valore F9 il codice del fornitore F2
```sql
UPDATE F 
SET CodF='F9' 
WHERE CodF='F2';
```
>Se in FP esistono dei valori con F2, bisogna cambiarli prima qui e poi li.
>Per mantenere la coerenza.

Perciò bisognerebbe scrivere:
```sql
UPDATE F 
SET CodF='F9' 
WHERE CodF='F2';

UPDATE FP 
SET CodF='F9' 
WHERE CodF='F2';
```
---
