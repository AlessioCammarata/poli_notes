Un'interrogazione nidificata è un'istruzione **SELECT** contenuta all'interno di un'altra interrogazione, la nidificazione di interrogazioni permette di **suddividere un problema complesso in sottoproblemi più semplici**.
È possibile introdurre istruzioni SELECT 
- in un predicato nella clausola WHERE 
- in un predicato nella clausola HAVING 
- nella clausola FROM

Esempio:
	Trovare il codice dei fornitori che hanno sede nella stessa città di F1

```sql
SELECT CodF 
FROM F 
WHERE Sede = (SELECT Sede 
			FROM F 
			WHERE CodF='F1');
```
>È possibile utilizzare '=' esclusivamente se è noto a priori che il risultato della SELECT nidificata è sempre un solo valore.
>È possibile definire una formulazione equivalente con il join.

La formulazione equivalente con il join è caratterizzata da 
- Clausola FROM contenente le tabelle referenziate nelle FROM di tutte le SELECT 
- Opportune condizioni di join nella clausola WHERE 
- Eventuali predicati di selezione aggiunti nella clausola WHERE
```sql
SELECT CodF 
FROM F AS FX, F AS FY
WHERE FX.Sede=FY.Sede AND FX.CodF = 'F1';
```
Esempio2
	Trovare il codice dei fornitori il cui numero di soci è minore del numero massimo di soci
```sql
SELECT CodF 
FROM F 
WHERE NSoci < (SELECT MAX(NSoci) 
				FROM F);
```
>Non è possibile definire una formulazione equivalente con il join.
---
#### Operatore IN
Esprime il concetto di appartenenza ad un insieme di valori 
     NomeAttributo **IN** (InterrogazioneNidificata) 

Permette di scrivere l'interrogazione 
- scomponendo il problema in sottoproblemi 
- seguendo un procedimento “bottom-up” 
L'interrogazione nidificata può essere sostituita con una lista di valori.
La formulazione equivalente con il join è caratterizzata da 
- clausola **FROM** contenente le tabelle referenziate nelle **FROM** di tutte le **SELECT** 
- opportune condizioni di join nella clausola **WHERE** 
- eventuali predicati di selezione aggiunti nella clausola **WHERE**

Esempio1:
	Trovare il nome dei fornitori che forniscono il prodotto P2
```sql
SELECT NomeF 
FROM F 
WHERE CodF IN (SELECT CodF 
				FROM FP 
				WHERE CodP='P2');
```

Esempio2:
	Trovare il nome dei fornitori che forniscono almeno un prodotto rosso
```sql
SELECT NomeF 
FROM F 
WHERE CodF IN (SELECT CodF 
				FROM FP 
				WHERE CodP IN (SELECT CodP 
								FROM P 
								WHERE Colore='Rosso'));
```
Con la join sarebbe:
```sql
SELECT NomeF 
FROM F, FP, P 
WHERE FP.CodF=F.CodF AND FP.CodP=P.CodP AND Colore='Rosso';
```
>Evitare troppi livelli di nidificazione, è facile perdersi e inoltre il DBMS non riesce ad ottimizzare la query al meglio.
---
#### Operatore NOT IN
Esprime il concetto di esclusione da un insieme di valori 
		NomeAttributo **NOT IN** (InterrogazioneNidificata) 

Richiede di individuare in modo appropriato l’insieme da ***escludere*** definito da 
- interrogazione nidificata 
- lista di valori 
>Non esiste una formulazione equivalente con il join

Esempio
	Trovare il nome dei fornitori che non forniscono il prodotto P2
```sql
SELECT NomeF 
FROM F 
WHERE CodF NOT IN (SELECT CodF 
					FROM FP 
					WHERE CodP='P2');
```
Esempio
	Trovare il nome dei fornitori che forniscono solo il prodotto P2
```sql
SELECT NomeF 
FROM F, FP 
WHERE F.CodF NOT IN (SELECT F.CodF 
					FROM FP 
					WHERE CodP<>'P2') AND F.CodF=FP.CodF;
```

>Gli attributi agli estremi della IN **devono essere dello stesso tipo** per poter applicare le ugualianze internamente
#### COSTRUTTORE DI TUPLA
Permette di definire la struttura temporanea di una tupla, si elencano gli attributi che ne fanno parte tra ().
>Permette di estendere il poter espressivo degli operatori IN e NOT IN.

VIAGGIO (CodV, LuogoPartenza, LuogoArrivo, OraPartenza, OraArrivo)
Esempio
	Trovare le coppie luogo di partenza e luogo di arrivo per cui nessun viaggio dura più di 2 ore
```sql
SELECT LuogoPartenza, LuogoArrivo 
FROM VIAGGIO 
WHERE (LuogoPartenza, LuogoArrivo) NOT IN (SELECT LuogoPartenza, LuogoArrivo 
											FROM VIAGGIO 
											WHERE OraArrivo-OraPartenza>2);
```
#### Operatore EXISTS
L’operatore **EXISTS** ammette come **parametro una interrogazione nidificata e restituisce**:
- il valore **vero** solo se l’interrogazione nidificata fornisce **un insieme non vuoto** (ossia restituisce almeno una tupla) 
- il valore **falso** se l'interrogazione interna restituisce **l'insieme vuoto** (ossia non restituisce nessuna tupla) 

Nell’interrogazione interna a EXISTS, la clausola SELECT è obbligatoria, ma irrilevante, perchè gli attributi non sono visualizzati.
La **condizione di correlazione** lega l'esecuzione dell'interrogazione interna al valore di attributi della tupla corrente nell'interrogazione esterna.

Esempio
	Trovare il nome dei fornitori del prodotto P2
```sql
SELECT NomeF 
FROM F 
WHERE EXISTS (SELECT * 
				FROM FP 
				WHERE CodP='P2' AND FP.CodF=F.CodF );
```
>La condizione di correlazione **lega la computazione dell’interrogazione nidificata** al valore di uno o più attributi dell’interrogazione più esterna.

>L'importante nella EXISTS è che esista una tupla, non il tipo dei valori, percio non ci sono vincoli e si mette sempre \* per la selezione.
##### Visibilità degli attributi
Un'interrogazione nidificata **può far riferimento ad attributi definiti in interrogazioni più esterne**.
Un'interrogazione non può far riferimento ad attributi referenziati 
- in un'interrogazione nidificata al suo interno 
- in un'interrogazione allo stesso livello
---
#### Operatore NOT EXISTS
L’operatore **NOT EXISTS** ammette come **parametro una interrogazione nidificata e restituisce**: 
- il valore vero se l'interrogazione interna restituisce l'insieme vuoto (ossia non restituisce nessuna tupla) 
- il valore falso se l’interrogazione nidificata fornisce un insieme non vuoto (ossia restituisce almeno una tupla) 

Nell’interrogazione interna a NOT EXISTS, la clausola SELECT è obbligatoria, ma irrilevante, perchè gli attributi non sono visualizzati.
La **condizione di correlazione** lega l'esecuzione dell'interrogazione interna al valore di attributi della tupla corrente nell'interrogazione esterna.

Esempio
	Trovare il nome dei fornitori che non forniscono il prodotto P2
	Si puo leggere come "Trovare il nome dei fornitori per cui non esiste una fornitura del prodotto P2".
```sql
SELECT NomeF 
FROM F 
WHERE NOT EXISTS (SELECT * 
					FROM FP 
					WHERE CodP='P2' AND FP.CodF=F.CodF);
```
>La condizione di correlazione **lega la computazione dell’interrogazione nidificata** al valore di uno o più attributi dell’interrogazione più esterna.
---
#### Correlazione tra interrogazioni
Può essere necessario **legare la computazione di un'interrogazione nidificata** al valore di uno o più attributi in un'interrogazione più esterna, il legame è espresso da **una o più condizioni di correlazione**.
Una condizione di correlazione:
- è indicata nella **clausola WHERE** dell'interrogazione nidificata che la richiede 
- è un predicato che lega attributi di tabelle nella **FROM dell'interrogazione nidificata** con attributi di tabelle nella **FROM di interrogazioni più esterne** 
Non si possono esprimere condizioni di correlazione:
- in interrogazioni allo stesso livello di nidificazione 
- contenenti riferimenti ad attributi di una tabella nella FROM di un'interrogazione nidificata

Esempio:
	Per ogni prodotto, trovare il codice del fornitore che ne fornisce la quantità massima
```sql
SELECT CodP, CodF 
FROM FP AS FPX 
WHERE Qta = (SELECT MAX(Qta) 
			FROM FP AS FPY 
			WHERE FPY.CodP=FPX.CodP);
```
Esempio 2:
VIAGGIO (CodV, LuogoPartenza, LuogoArrivo, OraPartenza, OraArrivo)
	Trovare il codice dei viaggi che hanno una durata inferiore alla durata media dei viaggi sullo stesso percorso (caratterizzato dallo stesso luogo di partenza e di arrivo)
```sql
SELECT V1.CodV 
FROM VIAGGIO AS V1 
WHERE V1.OraArrivo-V1.OraPartenza < (SELECT AVG(V2.OraArrivo-V2.OraPartenza) 
								FROM VIAGGIO AS V2
								WHERE V2.LuogoPartenza = V1.LuogoPartenza 
									AND V2.LuogoArrivo = V1.LuogoArrivo);
```
#### Operazione di divisione
Nel linguaggio SQL, l’operazione di divisione può essere realizzata mediante l'operatore **COUNT**, per verificare che gli elementi di interesse appartengano tutti all'insieme di riferimento.

Esempio:
	Trovare il codice dei fornitori che forniscono tutti i prodotti
```sql
SELECT CodF
FROM FP
GROUP BY CodF
HAVING COUNT(*) = (SELECT COUNT(*) 
		FROM P);
```
Esempio 2:
	Trovare il codice dei fornitori che forniscono almeno tutti i prodotti forniti dal fornitore F2
```sql
SELECT CodF
FROM FP
WHERE CodP IN (SELECT CodP
			FROM FP
			WHERE CodF = 'F2')
GROUP BY CodF
HAVING COUNT(*) = (SELECT COUNT(*) 
					FROM FP
					WHERE CodF = 'F2');
```
>In pratica prima seleziono i prodotti che sono forniti da F2, e poi raggruppando per CodF conto per ogni CodF quanti prodotti fornisce che sono forniti anche da F2.