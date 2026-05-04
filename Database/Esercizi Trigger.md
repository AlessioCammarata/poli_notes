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