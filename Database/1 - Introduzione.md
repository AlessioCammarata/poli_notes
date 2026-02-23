una base di dati è una collezione di dati gestita da un DBMS (Database Management System).
#### DBMS
Un sistema per la gestione di basi di dati o DBMS (Data Base Management System) è un sistema software in grado di **gestire collezioni di dat**i che siano 
- grandi 
- condivise 
- persistenti 
assicurando la loro affidabilità e privatezza.
##### Caratteristiche
==Dimensioni== *molto maggiori* della memoria centrale disponibile 
- gestione dei dati in **memoria secondaria** 
==Condivisione== dei dati tra applicazioni ed utenti: una base di dati è una **risorsa integrata**, condivisa da più settori aziendali:
- riduzione della **ridondanza** dei dati 
- riduzione delle **inconsistenze** tra i dati 
- meccanismo di **controllo dell’accesso concorrente**
>Accesso concorrente ma controllato.
###### Persistenza dei dati
Ha un tempo di vita non limitato a quello dell’esecuzione dei programmi che li utilizzano.
###### Affidabilità dei dati in caso di malfunzionamenti hardware e software
Ha delle funzionalità di salvataggio (**backup**) e ripristino (**recovery**).
>Creare tante copie, in tempistiche frequenti, 

>Ripristino utilizzando un file di log dove si tiene traccia delle operazioni svolte dalle applicazioni. (Sta in memoria stabile)
>Vengono rieseguite le operazioni interne al file di log.
###### Privatezza dei dati
Meccanismi di autorizzazione per abilitare gli utenti.
>Si possono avere le view personalizzate a seconda dell'utente. (Admin e users)
###### Efficienza
Capacità di svolgere le operazioni utilizzando un insieme di risorse (tempo e spazio) accettabile per gli utenti sistema informatico adeguatamente dimensionato.
###### Efficacia
Capacità di rendere produttive le attività degli utenti.

>Il DBMS fornisce le stesse funzionalità del FIle System ma è molto piu specifico ed utilizza un certo modello logico con certe query, fornisce delle funzionalità legate al contesto specifico.
---
#### Modello dei dati
Un modello dei dati è un insieme di concetti utilizzati per organizzare i dati di interesse e descriverne la struttura in modo da essere comprensibile ad un elaboratore 
- tipi di dato elementari (intero, carattere, ...) 
- meccanismo di strutturazione per definire strutture più complesse (costruttore di record, array, …)
- **Modello di dati relazionale** 
	- Modello di dati più diffuso 
	- Dati organizzati in insiemi di **record omogenei** (a struttura fissa) e rappresentati come **tabelle**.
---
Tabella Docenti: (Esempio)

| Nome    | Dipartimento | Telefono | --> Schema |
| ------- | ------------ | -------- | ---------- |
| Verdi   | Informatica  | 123456   | -->Istanza |
| Bianchi | Elettronica  | 636363   | -->Istanza |
| Neri    | Informatica  | 414243   | -->Istanza |
>Lo ==schema==, che descrive la struttura dei dati 
>- praticamente **invariante nel tempo** 
>- è rappresentato dall’**intestazione** di ogni tabella (nome tabella e nomi colonne)

>L’==istanza==, costituita dal contenuto di ogni tabella, cioè dai valori effettivi dei dati 
>- **variabile nel tempo**, anche molto rapidamente 
>- è rappresentata dalle **righe** delle tabelle
---
##### Modello concettuale
Permette di rappresentare i dati in modo indipendente dal modello logico 
- descrive concetti del mondo reale 
- utilizzato nella fase di progettazione 
>Esempio: modello Entità-Relazione
##### Modello logico
Descrive la struttura dei dati nel DBMS 
- utilizzato dai programmi che accedono ai dati 
- indipendente dalle strutture fisiche 
>Esempio: modello relazionale
#### Progettazione di una base di dati
Si divide in progettazione **concettuale, logica e fisica:**
###### Progettazione Concettuale
Rappresentare i **requisiti informali** di un'applicazione in termini di schema concettuale che fa riferimento a un **modello concettuale di dati.** (Modello ER)
###### Progettazione Logica
**Traduzione** dello schema concettuale definito nella fase precedente nello schema logico del database che fa riferimento a un **modello logico di dati**. (Modello UML)
>Si ottiene un modello logico normalizzato.
###### Progettazione Fisica
Lo schema logico è completato dai dettagli dell'implementazione fisica (organizzazione dei file e indici) su un determinato DBMS. Il prodotto è chiamato schema fisico e si riferisce a un **modello fisico di dati.** (Le tabelle finali in memoria)
>Questa parte non viene affrontata in questo corso.
---
##### Astrazione degli schemi
**Schema logico** 
- descrizione della base di dati mediante il modello logico del DBMS 
**Schema interno** 
- rappresentazione dello schema logico mediante strutture fisiche di memorizzazione
**Schema esterno** 
- descrizione di parti della base di dati, denominate “viste”, che riflette il punto di vista di particolari utenti 
- è definita sul modello logico
- ---
#### Indipendenza dei dati
L’indipendenza dei dati garantisce che gli utenti e i programmi applicativi che utilizzano una base di dati possano ignorare i dettagli realizzativi utilizzati nella costruzione della base di dati.
È una conseguenza della suddivisione in livelli di astrazione.
Livelli di indipendenza dei dati: 
- Indipendenza fisica 
- Indipendenza logica
###### Indipendenza fisica
- consente di interagire con il DBMS in modo indipendente dalla struttura fisica dei dati 
- l’accesso a una relazione (livello logico o esterno) avviene sempre nello stesso modo, indipendentemente dalla modalità di memorizzazione 
- è possibile modificare il modo in cui i dati sono memorizzati fisicamente senza influire sui programmi che utilizzano i dati
###### Indipendenza logica
- consente di interagire con il livello esterno in modo indipendente dal livello logico 
- è possibile modificare il livello logico mantenendo inalterate le strutture esterne (purché le corrispondenze siano inalterate) 
- è possibile aggiungere nuove viste o modificare viste esistenti senza modificare lo schema logico
---
#### Accesso ai dati
>Utilizziamo SQL.
###### Linguaggi di accesso ai dati
Sono divisi in due categorie 
- ***linguaggi di definizione dei dati*** (**Data Definition Language o DDL**) utilizzati per definire gli schemi logici, esterni e fisici e le autorizzazioni per l’accesso 
- ***linguaggi di manipolazione dei dati*** (**Data Manipulation Language o DML**) utilizzati per l’interrogazione e l’aggiornamento delle istanze della base di dati
##### Utenti
**Database administrator**: responsabile del controllo (centralizzato) e della gestione della base di dati 
- garantisce prestazioni sufficienti 
- assicura l’affidabilità del sistema 
- gestisce le autorizzazioni di accesso ai dati 
**Progettisti e programmatori:** definiscono e realizzano 
- la struttura della base di dati 
- i programmi che accedono alla base di dati 
**Utenti**: utilizzano la base di dati per le proprie attività 
- utenti finali: utilizzano transazioni, cioè programmi che realizzano attività predefinite 
- utenti casuali: formulano interrogazioni (o aggiornamenti) non predefinite mediante i linguaggi interattivi di accesso alla base di dati.
---
#### Vantaggi e Svantaggi dei DBMS
