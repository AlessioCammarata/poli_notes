### Calendario Eventi

EVENTO(**CodE**, NomeEvento, CategoriaEvento, CostoEvento, DurataEvento) 
CALENDARIO_EVENTI(**CodE**, **Data**, OraInizio, Luogo) 
SOMMARIO_CATEGORIA(**CategoriaEvento**, **Data**, NumeroTotaleEventi, CostoComplessivoEventi)
#### Consegna
Si vuole gestire la pianificazione degli eventi nella città di Torino per l’anniversario dei 150 anni dell’unità d’Italia (Italia 150). 
Gli eventi appartengono a diverse categorie (attributo CategoriaEvento), quali mostre, dibattiti, proiezioni, e sono caratterizzati da un costo di realizzazione (attributo CostoEvento). Ciascun evento può essere ripetuto più volte in date diverse. 
La tabella CALENDARIO_EVENTI riporta la pianificazione degli eventi in diversi giorni e luoghi della città. Si scrivano i trigger per gestire le seguenti attività. 

(1) Aggiornamento della tabella SOMMARIO_CATEGORIA. La tabella SOMMARIO_CATEGORIA riporta, per ogni categoria di evento e per ogni data, il numero complessivo di eventi previsti e il costo complessivo per la loro realizzazione. Si scriva il trigger per propagare le modifiche alla tabella SOMMARIO_CATEGORIA quando viene inserito un nuovo evento a calendario (inserimento nella tabella CALENDARIO_EVENTI). 


(2) Vincolo di integrità sul costo massimo dell’evento. Il costo di un evento della categoria proiezione cinematografica (attributo CategoriaEvento) non può essere superiore a 1500 euro. Se un valore di costo superiore a 1500 è inserito nella tabella EVENTO, all’attributo CostoEvento deve essere assegnato il valore 1500. Si scriva il trigger per la gestione del vincolo di integrità. 


(3) Vincolo sul numero massimo di eventi per data. In ogni data non possono essere pianificati più di 10 eventi. Ogni modifica della tabella CALANDARIO_EVENTI che causa la violazione del vincolo non deve essere eseguita.
#### Svolgimento
##### (1) Aggiornamento della tabella SOMMARIO_CATEGORIA
Bisogna aggiornare la tabella SOMMARIO_CATEGORIA, quando viene inserito un nuovo evento in CALENDARIO_EVENTI.
###### Propagazione
Per la propagazione di un evento inserito in calendario in Sommario_Categoria serve, 
- Leggere da EVENTO la categoria per l'evento inserito
- Verifico se è gia presente un record per quella categoria e data
	- SI: Incremento
	- NO: Creo il nuovo record

```plsql
--EVENTO(CodE, NomeEvento, CategoriaEvento, CostoEvento, DurataEvento) 
--CALENDARIO_EVENTI(CodE,Data, OraInizio, Luogo) 
--SC(CategoriaEvento, Data, NumeroTotaleEventi, CostoComplessivoEventi)
CREATE TRIGGER UpdateSommarioCategoria
AFTER INSERT ON CALENDARIO_EVENTI
FOR EACH ROW -- Granularità di tupla
DECLARE
	Categoria char(10);
	Costo number;
	N number; --Serve a capire se un elemento è presente o no
BEGIN 
	--Devo aggiornare SOMMARIO_CATEGORIA
	SELECT CategoriaEvento, CostoEvento into Categoria, Costo
	FROM EVENTO
	WHERE CodE = :NEW.CodE;
	
	select count(*) into N 
	from SOMMARIO_CATEGORIA
	where CategoriaEvento = Categoria AND Data = :NEW.Data;
	
	if(N<>0) then 
		-- Aggiorno valore
		update SOMMARIO_CATEGORIA
		set NumeroTotaleEventi = NumeroTotaleEventi + 1,
			CostoComplessivoEventi = CostoComplessivoEventi + Costo
		where CategoriaEvento = Categoria AND Data = :NEW.Data;
	else
		-- Inserisco nuovo valore
		insert into SOMMARIO_CATEGORIA (CategoriaEvento, Data, NumeroTotaleEventi, CostoComplessivoEventi)
		values (Categoria, :NEW.Data, 1, Costo);
		
	end if; 
END;
```
##### (2) Vincolo di integrità sul costo massimo dell’evento

```plsql
--EVENTO(CodE, NomeEvento, CategoriaEvento, CostoEvento, DurataEvento) 
--CALENDARIO_EVENTI(CodE,Data, OraInizio, Luogo) 
--SC(CategoriaEvento, Data, NumeroTotaleEventi, CostoComplessivoEventi)
CREATE TRIGGER CinematografiaConstraint
BEFORE UPDATE or INSERT ON EVENTO
FOR EACH ROW -- Granularità di tupla
WHEN (NEW.CategoriaEvento = 'cinematografia' AND NEW.CostoEvento > 1500)
BEGIN 
	--Devo aggiornare modificare l'evento prima che venga inserito
	:NEW.CostoEvento := 1500; 
END;
```
##### (3) Vincolo sul numero massimo di eventi per data

>Questa soluzione invece non va bene, perche stiamo modificando la tabella attuale quindi non puoi controllare (Mutating Table Error)
```plsql
--EVENTO(CodE, NomeEvento, CategoriaEvento, CostoEvento, DurataEvento) 
--CALENDARIO_EVENTI(CodE,Data, OraInizio, Luogo) 
--SC(CategoriaEvento, Data, NumeroTotaleEventi, CostoComplessivoEventi)
CREATE TRIGGER EventPerDateConstraint
BEFORE INSERT or UPDATE of Data ON CALENDARIO_EVENTI
FOR EACH ROW -- Granularità di tupla
DECLARE 
	N number; --Numero di date
BEGIN 
	--Devo controllare la data prima che venga inserito al calendario_eventi
	SELECT count(*) INTO N
	FROM CALENDARIO_EVENTI
	WHERE Data = :NEW.Data;
	
	if(N>9) then
		RAISE_APPLICATION_ERROR(-20001, 'Sono gia presenti 10 eventi per questa data');
	end if;
END;
```

Proposta dalla prof:
```plsql
CREATE TRIGGER EventPerDateConstraint
AFTER INSERT or UPDATE of Data ON CALENDARIO_EVENTI
DECLARE 
	N number; --Contiene il numero di date con piu di 10 eventi
BEGIN 
	--Devo controllare le date nella tabella dopo averla inserito
	SELECT COUNT(DISTINCT Data) into N
	FROM CALENDARIO_EVENTI
	WHERE Data IN(SELECT Data
				FROM CALENDARIO_EVENTI
				GROUP BY Data
				HAVING COUNT(*) > 10;
	
	if(N <> 0) then
		RAISE_APPLICATION_ERROR(-20001, 'Sono gia presenti 10 eventi per data');
	end if;
END;
```

---
### Borse di Studio
#### Consegna
STUDENTE(Matricola, NomeStudente, Annolmmatricolazione, CorsoLaurea) 
CORSO(CodCorso, NomeCorso, NumeroCrediti) 
ESAMI_SOSTENUTI(CodCorso,Matricola, Data, Voto) 
GRADUATORIA_STUDENTI(Matricola, Punteggio) 
BORSE_STUDIO_ASSEGNATE (CodBorsa, Matricola, NumeroOre) 
DOMANDA_INSERIMENTO_GRADUATORIA(Matricola, Data Domanda) 
OFFERTA_BORSA_STUDIO(CodBorsa,CodCorso, NumeroOre) 
NOTIFICA_INFORMAZIONI(CodN, CodBorsa, Matricola*, Messaggio)

-  **Inserimento di uno studente in graduatoria**
Lo studente presenta la domanda per l'assegnazione di borse di studio. 
La domanda viene accettata se lo studente non è già presente in graduatoria (tabella GRADUATORIA) ed ha acquisito almeno 120 crediti sugli esami superati. 
Se almeno uno dei requisiti non è soddisfatto, la domanda viene annullata. 
Altrimenti si deve aggiornare la graduatoria, assegnando allo studente un punteggio dato dal prodotto della media dei voti per gli esami superati (votazione maggiore o uguale a 18), per il numero di anni di iscrizione dello studente al corso di laurea (si assuma che l'anno corrente sia fornito dalla variabile SYSDATE).

-  **Assegnazione di una borsa di studio per un corso**
Quando viene offerta una borsa di studio per un corso, si seleziona dalla graduatoria lo studente a cui assegnare la borsa. 
Viene selezionato lo studente con punteggio più alto tra gli studenti che soddisfano i seguenti requisiti: lo studente ha superato l'esame per il corso per cui è offerta la borsa di studio, e lo studente complessivamente non svolge più di 150 ore sulle borse di studio assegnate. 
Si assuma che ci sia sempre al più un solo studente che soddisfi tutti i requisiti. 
Occorre notificare l'esito dell'operazione, sia che la borsa di studio sia stata assegnata, sia che non sia possibile assegnare la borsa (in questo caso, la matricola sarà NULL). 
L'attributo CodN è un contatore che viene incrementato ogni volta che viene inserita una nuova notifica. 
Se la borsa di studio è assegnata, si deve aggiornare la tabella BORSE_STUDIO_ASSEGNATE.

- **verifica di correttezza e eventuale correzione del seguente vincolo.** 
Per ciascuna borsa di studio offerta, il numero di ore previsto deve essere pari ad almeno 15 ore. Se viene offerta una borsa di studio con un numero di ore inferiore a 15, il valore deve essere assegnato a 15.
#### Svolgimento

##### Inserimento
```plsql
CREATE TRIGGER nuova_richiesta_graduatoria
AFTER INSERT ON DOMANDA_INSERIMENTO_GRADUATORIA
FOR EACH ROW --Devo calcolare il punteggio
DECLARE 
	N number; -- 0 o 1, conto il numero di valori presenti
	TotCrediti number; --Numero totale di crediti
	Media number; --Media dei voti presi
	AnniIscrizione number; --Conta da quanti anni è iscritto
BEGIN 
	--Verifico se lo studente è gia in graduatoria
	SELECT COUNT(*) into N
	FROM GRADUATORIA_STUDENTI
	WHERE Matricola = :NEW.Matricola;
	
	if(N<>0) then
		RAISE_APPLICATION_ERROR(-20001, 'Studente gia presente in graduatoria');
	end if;
	
	--Verifico i requisiti sui crediti
	SELECT SUM(NumeroCrediti), AVG(Voto) into TotCrediti,Media
	FROM ESAMI_SOSTENUTI ES, CORSO C
	WHERE ES.CodCorso = C.CodCorso AND 
		Voto >= 18 AND
		ES.Matricola = :NEW.Matricola;
		
	--Bisogna mettere NULL perche la quesry sopra puo tornare NULL
	if(TotCrediti IS NULL OR TotCrediti < 120) then
		--Studente non va bene per i crediti
		RAISE_APPLICATION_ERROR(-20001, 'Numero di crediti non adeguato');
	end if;
	
	--Calcolo anni di iscrizione
	SELECT (EXTRACT(YEAR FROM SYSDATE) - AnnoImmatricolazione) INTO AnniIscrizione
	FROM STUDENTI
	WHERE Matricola = :NEW.Matricola;
	
	IF (AnniIscrizione <= 0) THEN 
		AnniIscrizione := 1; 
	END IF;
	
	--Calcolo punteggio ed inserimento
	INSERT INTO GRADUATORIA_STUDENTI (Matricola, Punteggio) 
	VALUES (:NEW.Matricola, Media * AnniIscrizione);
END;
```
#### Assegnazione
```plsql
--STUDENTE(Matricola, NomeStudente, Annolmmatricolazione, CorsoLaurea) 
--CORSO(CodCorso, NomeCorso, NumeroCrediti) 
--ESAMI_SOSTENUTI(CodCorso,Matricola, Data, Voto) 
--GRADUATORIA_STUDENTI(Matricola, Punteggio) 
--BORSE_STUDIO_ASSEGNATE (CodBorsa, Matricola, NumeroOre) 
--DOMANDA_INSERIMENTO_GRADUATORIA(Matricola, Data Domanda) 
--OFFERTA_BORSA_STUDIO(CodBorsa,CodCorso, NumeroOre) 
--NOTIFICA_INFORMAZIONI(CodN, CodBorsa, Matricola*, Messaggio)
CREATE OR REPLACE TRIGGER offerta_borsa
AFTER INSERT ON OFFERTA_BORSA_DI_STUDIO
FOR EACH ROW --Devo calcolare il punteggio
DECLARE 
	max_punteggio NUMBER; --Punteggio massimo
	StudentID number; --Studente che vince la borsa
	MAXN number; --Per memorizzare CodN
BEGIN 
	--Calcolo il punteggio massimo tra gli studenti che hanno i requisiti
		--1. Superato l'esame per il corso oggetto della borsa
		--2. Complessivamente non svolga piu di 150 ore sulle borse assegnate
	SELECT MAX(Punteggio) INTO MaxPunteggio
	FROM GRADUATORIA_STUDENTI
	WHERE Matricola IN (
	-- Requisito 1: Ha superato l'esame specifico
				SELECT  Matricola
				FROM ESAMI_SOSTENUTI
				WHERE Voto >= 18 AND CodCorso = :NEW.CodCorso
	) AND Matricola NOT IN (
	-- Requisito 2: Non supera le 150 ore totali (considerando le già assegnate)
				SELECT Matricola
				FROM BORSE_STUDIO_ASSEGNATE
				GROUP BY Matricola
				HAVING SUM(NumeroOre) + :NEW.NumeroOre > 150
	);
	
	if (MAXN IS NULL)
		MAX := 0;
	end if
	
	if(MaxPunteggio IS NOT NULL) then
	--Se esiste un elemento eleggibile, seleziono quello con punteggio massimo
		SELECT Matricola INTO StudentID
		FROM GRADUATORIA_STUDENTI
		WHERE Matricola IN (
		-- Requisito 1: Come prima
					SELECT  Matricola
					FROM ESAMI_SOSTENUTI
					WHERE Voto >= 18 AND CodCorso = :NEW.CodCorso
		) AND Matricola NOT IN (
		-- Requisito 2: Come prima
					SELECT Matricola
					FROM BORSE_STUDIO_ASSEGNATE
					GROUP BY Matricola
					HAVING SUM(NumeroOre) + :NEW.NumeroOre > 150
		) AND Punteggio = MaxPunteggio;
	
		SELECT MAX(CodN) INTO MAXN
		FROM NOTIFICA_INFORMAZIONI;
	
	--Se esiste un elemento eleggibile
		--Assegno la borsa inserendo un record in BORSE_ASSEGNATE
		--notifico che la borsa è stata assegnata (NOTIFICA_INFORMAZIONI)
	
		insert into BORSE_STUDIO_ASSEGNATE (CodBorsa, Matricola, NumeroOre)
		VALUES (:NEW.CodBorsa, StudentID, :NEW.NumeroOre);
		
		insert into NOTIFICA_INFORMAZIONI (CodN, CodBorsa, Matricola, Messaggio)
		VALUES (MAXN + 1, :NEW.CodBorsa, StudentID, 'Borsa assegnata');
	else
	--Altrimenti notifico che la borsa non è assegnata (NOTIFICA_INFORMAZIONI)
		INSERT INTO NOTIFICA_INFORMAZIONI (CodN, CodBorsa, Matricola, Messaggio) VALUES (MAXN + 1, :NEW.CodBorsa, NULL, 'Borsa non assegnata per mancanza di requisiti');
	end if;
END;
```
#### Verifica
```plsql
--STUDENTE(Matricola, NomeStudente, Annolmmatricolazione, CorsoLaurea) 
--CORSO(CodCorso, NomeCorso, NumeroCrediti) 
--ESAMI_SOSTENUTI(CodCorso,Matricola, Data, Voto) 
--GRADUATORIA_STUDENTI(Matricola, Punteggio) 
--BORSE_STUDIO_ASSEGNATE (CodBorsa, Matricola, NumeroOre) 
--DOMANDA_INSERIMENTO_GRADUATORIA(Matricola, Data Domanda) 
--OFFERTA_BORSA_STUDIO(CodBorsa,CodCorso, NumeroOre) 
--NOTIFICA_INFORMAZIONI(CodN, CodBorsa, Matricola*, Messaggio)
CREATE TRIGGER verifica_ore_offerta_borsa
Before INSERT OR MODIFY of NumeroOre ON OFFERTA_BORSA_DI_STUDIO
FOR EACH ROW --Devo controllare la singola tupla
WHEN :NEW.NumeroOre < 15
BEGIN 
	--Assegno il valore minimo
	:NEW.NumeroOre := 15;
END;
```

per ciascun corso le borse di studio offerte per il corso non possono superare complessivamente un monte ore pari a 300.
```plsql
CREATE TRIGGER verifica_ore_offerta_borsa
After INSERT OR MODIFY of NumeroOre ON OFFERTA_BORSA_DI_STUDIO
BEGIN 
	--Assegno il valore minimo

END;
```

---
### Richiesta Ferie
#### Consegna
PERSONA (Matricola, Mansione) 
TIPO-TURNO (CodT, Oralnizio, Durata) 
TURNO (Matricola, Data, CodT) 
NOTIFICA (Matricola, Data, EsitoRichiesta) 
RICHIESTA-FERIE(CodR, Matricola, Data)

Scrivere il trigger per gestire le richieste di un giorno di ferie da parte delle persone che lavorano in un ospedale (inserimento nella tabella RICHIESTA-FERIE). 

La richiesta di ferie viene accettata se la persona che la inoltra non è di turno nel giorno di ferie richiesto (tabella TURNO). 
Altrimenti, se la persona è di turno in quel giorno, la richiesta di ferie è accettata solo se esiste un'altra persona che può sostituirla per il turno. 
In caso contrario, la richiesta di ferie viene respinta. 

Una persona può sostituire un 'altra persona per un turno in un certo giorno se ha la stessa mansione della persona che deve sostituire, e non è già di turno in quel giorno. Deve essere notificato l'esito della richiesta (accettata o respinta) mediante un inserimento nella tabella NOTIFICA-TURNO.
#### Svolgimento
```plsql
--PERSONA (Matricola, Mansione) 
--TIPO-TURNO (CodT, Oralnizio, Durata) 
--TURNO (Matricola, Data, CodT) 
--NOTIFICA (Matricola, Data, EsitoRichiesta) 
--RICHIESTA-FERIE(CodR, Matricola, Data)
CREATE TRIGGER gestisci_richieste_ferie
After INSERT OR UPDATE ON RICHIESTA-FERIE
FOR EACH ROW
DECLARE
	N number; -- Conteggio turni del richiedente
	S number; -- Flag sostituzione
BEGIN 
	--Devo controllare se la persona non è di turno
	SELECT COUNT(*) into N
	FROM TURNO
	WHERE Matricola = :NEW.Matricola and Data = :NEW.Data;
	
	if (N=0) then
		-- Caso A: La persona non è di turno, ferie accettate automaticamente
		INSERT INTO	NOTIFICA (Matricola, Data, EsitoRichiesta)
		VALUES (:NEW.Matricola, :NEW.Data, 'Richiesta Ferie Accettata');
	else
		-- Caso B: La persona è di turno, cerchiamo un sostituto
		SELECT COUNT(*) into S
		FROM PERSONA
		WHERE Matricola NOT IN (
			SELECT Matricola
			FROM TURNO
			WHERE Data = :NEW.Data
		) AND Mansione = (
			SELECT Mansione
			FROM Persona
			WHERE Matricola = :NEW.Matricola
		) AND Matricola <> :NEW.Matricola; -- Non può sostituire se stessa

		if(S<>0) then
			-- Sostituto trovato: elimino il turno del richiedente e accetto
			DELETE FROM TURNO
			WHERE Matricola = :NEW.Matricola AND Data = :NEW.Data;
			
			INSERT INTO	NOTIFICA (Matricola, Data, EsitoRichiesta)
			VALUES (:NEW.Matricola, :NEW.Data, 'Richiesta Ferie Accettata');
		else
			-- Nessun sostituto disponibile: ferie rifiutate
			INSERT INTO	NOTIFICA (Matricola, Data, EsitoRichiesta)
			VALUES (:NEW.Matricola, :NEW.Data, 'Richiesta Ferie Rifiutata');
		end if;
	end if;
END;
```