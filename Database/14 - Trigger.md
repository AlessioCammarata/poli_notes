Il funzionamento tradizionale del DBMS è **passivo** 
- le interrogazioni e gli aggiornamenti sono richiesti esplicitamente dagli utenti 
- la conoscenza dei processi che operano sui dati è tipicamente incorporata nelle applicazioni 
**Basi di dati attive** 
- la reattività è un servizio fornito da un normale DBMS 
- vengono **monitorati** eventi specifici del database e **attivate** azioni in risposta

>La reattività è assicurata dall'esecuzione automatica di **regole attive o ECA** poichè espresso nella forma 
>- **Evento**: operazione di modifica della base di dati 
>- **Condizione**: predicato sullo stato della base di dati, se la condizione è vera, l'azione viene eseguita 
>- **Azione**: sequenza di istruzioni SQL o procedura applicativa

Il Rule engine è il componente del DBMS, incaricato di 
- tracciare gli eventi 
- eseguire le regole quando è appropriato, in base alla strategia di esecuzione del DBMS
L'esecuzione delle regole è alternata all'esecuzione delle transazioni tradizionali.
---
#### Applicazioni delle regole attive
**Applicazioni interne**
- mantenimento di vincoli di integrità complessi 
- gestione delle repliche 
- manutenzione delle viste materializzate 

**Business Rules** 
- incorporano nel DBMS la conoscenza delle applicazioni 
	- ad esempio, regola di riordino dei prodotti 

**Alert** 
- utilizzati per le notifiche
#### Trigger
Nei DBMS tipicamente le regole attive sono implementate mediante ***trigger***.
Il linguaggio SQL fornisce istruzioni per la definizione dei trigger
- i trigger vengono definiti con l'istruzione DDL **CREATE TRIGGER** 

La sintassi e la semantica dei trigger sono definite nello standard SQL3 
- alcuni DBMS implementano caratteristiche diverse rispetto allo standard
##### Struttura del Trigger (ECA)
- **Evento** 
	- inserimento, cancellazione, aggiornamento di una tabella 
	- ogni trigger può monitorare solo gli eventi di una **singola** tabella 
- **Condizione** 
	- predicato SQL (è opzionale) 
- **Azione** 
	- sequenza di istruzioni SQL (Non si possono creare oggetti ma agire su tabelle esistenti)
	- blocchi di linguaggio di programmazione (proprietario),ad esempio, Oracle PL/SQL 
	- codice Java
##### Processo di esecuzione
**Quando** gli eventi si verificano [attivazione] 
**Se** la condizione è vera [valutazione] 
**Allora** l'azione viene eseguita [esecuzione]

Per definire un trigger bisogna definire inoltre:
• Modalità di esecuzione 
• Granularità dell'esecuzione
###### Modalità di esecuzione
**Immediato** (Eseguito insieme all'evento innescante)
- Il trigger viene eseguito **immediatamente prima (BEFORE) o dopo (AFTER)** l'istruzione di attivazione
	- **BEFORE** - Prima il trigger e poi l'evento che scatena il trigger
	- **AFTER** - Prima si fa l'evento che scatena il trigger e poi si esegue il trigger

**Differito** (Eseguito alla fine della transazione)
- Il trigger viene eseguito immediatamente **prima** del **commit**.

>Se non viene eseguito il COMMIT ma il ROLLBACK allora vengono cancellate anche le operazioni svolte dai trigger.
###### Granularità dell'esecuzione
**Tupla** (o livello di riga) 
- Un'esecuzione separata del trigger **per ogni tupla** interessata dall'istruzione di attivazione 
**Istruzione** 
- Una singola esecuzione del trigger **per tutte le tuple** interessate dall'istruzione attivazione
#### Trigger in Oracle
```sql
CREATE TRIGGER TriggerName 
Mode Event {OR Event } 
ON TargetTable 
[[ REFERENCING ReferenceName] 
FOR EACH ROW 
[WHEN Predicate]] 
PL/SQL Block
```
Mode è **BEFORE** o **AFTER** 

Event **ON TargetTable** è:
- INSERT
- DELETE
- UPDATE (OF ColumnName) --> Puoi indicare le colonne di interessse
**FOR EACH ROW** specifica la semantica di esecuzione **a livello di tupla** 
- se **omesso**, la semantica di esecuzione è **a livello di istruzione**
**REFERENCING OLD AS** OldVariableName 
- analogamente per NEW
**Solo** per la semantica di esecuzione a livello di tupla (ossia, **FOR EACH ROW**) 
- è possibile specificare facoltativamente una condizione 
- è possibile accedere alle variabili di stato vecchie e nuove

L'azione è 
- una sequenza di istruzioni SQL 
- un blocco PL/SQL
>Nessuna istruzione transazionale e DDL.

>Nel corpo del trigger puoi vedere i dati delle tuple, quindi puoi mettere delle condizioni nel trigger che le riguardano, si ha visibilità dello stato prima **OLD** dell'evento e dopo **NEW**.
>So quali modifiche l'evento ha apportato alla tabella.

>Se la istruzione è a livello di istruzione posso eseguire delle Query sull'intera tabella, mentre a livello di tupla no, per esempio delle SELECT.
>Non so quali modifiche l'evento ha apportato alla tabella.

---
#### Algoritmo di esecuzione
È possibile che ad una tabella siano associati piu trigger di stesso tipo o diverso, che avvengono quaindi in contemporanea.
Per questo motivo c'è un ordine in cui vengono eseguiti:
1. Vengono eseguiti i trigger di tipo **before** a **livello di istruzione**
2. Per ogni tupla nella tabella target (TargetTable) interessata dall'istruzione di trigger 
	a) Vengono eseguiti i trigger di tipo **before a livello di tupla** 
	b) Viene eseguita **l'istruzione di attivazione** + i **vincoli di integrità definiti a livello di tupla** (CHECK o PRIMARY KEY, ecc)
	c) Vengono eseguiti i trigger di tipo **after a livello di tupla**
3. Vengono controllati i **vincoli di integrità** sulle **tabelle** (CHECK o PRIMARY KEY, ecc)
4. Vengono eseguiti i trigger di tipo **after a livello di istruzione**

>Vengono eseguiti prima i before e poi gli after.
>Il trigger before di istruzione è il primo, prima dell'evento, quando poi finisce comincia l'esecuzione dell'evento (Che puo modificare piu tuple).
>Per ogni tupla avviene il before della tupla, poi viene modificate e poi l'after di tupla.
>Dopo tutti i trigger di tupla, si controllano i vincoli d'integrità e poi si eseguono i trigger after di istruzione.
###### Piu trigger dello stesso tipo
L'ordine di esecuzione di trigger con lo stesso evento, la stessa modalità e la stessa granularità non viene specificato 
- è una fonte di non determinismo
>A volte il primo a volte il secondo, non è detto.

Quando si verifica un errore 
- **rollback** di tutte le operazioni eseguite dai trigger 
- **rollback** dell'istruzione di attivazione nella transazione di attivazione
###### Non terminazione
L'esecuzione di un trigger può attivare altri trigger, l'attivazione di trigger in cascata può portare alla non terminazione dell'esecuzione del trigger.
È possibile impostare una lunghezza massima per l'esecuzione di trigger in cascata 
- default = 32 trigger 
Se il limite massimo viene superato, viene restituito un errore di esecuzione
##### Tabelle mutanti
Una **tabella mutante** è la tabella target modificata dall'istruzione (cioè dall'evento) che attiva il trigger.
La tabella mutante 
- **non** è accessibile nei trigger a livello di riga 
- può essere accessibile solo nei trigger di istruzione 
L'accesso limitato alle tabelle mutanti caratterizza solo le applicazioni Oracle, l'accesso alle tabelle mutanti è **sempre permesso in SQL3**.
### Progettazione dei trigger
La progettazione di un singolo trigger è solitamente semplice. 
Bisogna identificare 
- semantica di esecuzione 
- evento 
- condizione (opzionale) 
- azione
###### Bisogna garantire la terminazione
La terminazione è garantita in fase di esecuzione, interrompendo l'esecuzione del trigger dopo un determinato numero di attivazione di trigger in cascata.
La terminazione può essere verificata in fase di progettazione mediante il grafo di attivazione dei trigger 
- un nodo per ogni trigger 
- un arco diretto $T_i \ T_j$ se il trigger $T_i$ sta eseguendo un'azione che innesca il trigger $T_j$ 

>Un **ciclo** nel grafo mostra esecuzioni che potrebbero causare una condizione di non terminazione.

