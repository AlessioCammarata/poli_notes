Estende l’algebra degli insiemi per il modello relazionale.
Definisce un insieme di operatori che operano su relazioni e producono come risultato una relazione.
Gode della proprietà di chiusura 
- il risultato di qualunque operazione algebrica su relazioni è a sua volta una relazione.
---
**Operatori unari** 
- selezione (s) 
- proiezione (p) 
**Operatori binari** 
- prodotto cartesiano (´) 
- join ( ) 
- unione (È) 
- intersezione (Ç) 
- differenza (-) 
- divisione (/)
**Operatori insiemistici** 
- unione (È) 
- intersezione (Ç) 
- differenza (-) 
- prodotto cartesiano (´) 
**Operatori relazionali** 
- selezione (s) 
- proiezione (p) 
- join ( ) 
- divisione (/)
---
### Selezione e Proiezione
##### Selezione
La selezione estrae un **sottoinsieme “orizzontale”** della relazione 
- opera una decomposizione orizzontale della relazione
$$
	R = \sigma_pA
$$
L’operatore selezione **$\sigma_p$** genera una **relazione R** 
- avente lo **stesso schema di A** 
- contenente tutte le tuple della relazione A per cui è vero il **predicato p** 
Il predicato **p** è un’espressione booleana (operatori $\cap,\cup$,¬) di espressioni di confronto tra attributi o tra attributi e costanti. 
Esempi: 
- p: Città=‘Torino’ and Età > 18 
- p: DataRestituzione > DataConsegna + 10

>Viene eseguita come prima operazione sempre, in modo da avere risultati temporanei che sono piccoli e processabili piu velocemente
##### Proiezione
La proiezione estrae un sottoinsieme “verticale” della relazione • opera una decomposizione verticale della relazione
$$
R = \pi_LA
$$
L’operatore proiezione $\pi_L$ genera una **relazione R** 
- avente come **schema la lista di attributi L** (sottoinsieme dello schema di A) 
- contenente **tutte le tuple presenti in A** 
Sono **eliminati gli eventuali duplicati** dovuti all’esclusione degli attributi non in L 
- se L include una chiave candidata, non vi sono duplicati

>Si svolge prima la selezione e poi la proiezione, perché se facessi la proiezione prima perdo dei dati, in quanto la proiezione toglie i duplicati nella sua colonna scelta.
### Prodotto cartesiano e join
##### Prodotto cartesiano
Il prodotto cartesiano di due relazioni A e B genera tutte le coppie formate da una tupla di A e una tupla di B.
$$
R = A \times B
$$
Il prodotto cartesiano di due relazioni A e B genera una relazione R 
- avente come **schema l’unione degli schemi di A e di B** 
- contenente **tutte le coppie formate da una tupla di A e una tupla di B** 
Il prodotto cartesiano è 
- commutativo 
	- $A \times B = B \times A$ 
- associativo 
	- $(A \times B) \times C = A \times (B \times C)$
##### Join
Il join di due relazioni A e B genera tutte le coppie formate da una tupla di A e una tupla di B **“semanticamente legate”**.
Il join è un operatore derivato 
- può essere espresso utilizzando gli operatori $\times, \sigma_p, \pi_L$ 
Il join è definito separatamente perché esprime sinteticamente molte operazioni ricorrenti nelle interrogazioni 
Esistono diversi tipi di join 
- natural join 
- theta-join (e il suo sottocaso equi-join) 
- semi-join
### Natural join, theta-join, semi-join
##### Natural join
$$ 
R = A \bowtie B
$$
Il natural join di due relazioni A e B genera una relazione R 
- avente come schema 
	- gli attributi presenti nello schema di A e non presenti nello schema di B 
	- gli attributi presenti nello schema di B e non presenti nello schema di A 
	- una **sola copia degli attributi comuni** (con lo stesso nome nello schema di A e di B)
-  contenente tutte le coppie costituite da una tupla di A e una tupla di B per cui il valore degli attributi comuni è uguale 
**Il natural join è commutativo e associativo.**
##### Theta-join
$$ 
R = A \bowtie_p B
$$
Il theta-join di due relazioni A e B genera tutte le coppie formate da una tupla di A e una tupla di B che soddisfano una generica **“condizione di legame”** 
Il theta-join di due relazioni A e B genera una relazione R 
- avente come schema **l’unione degli schemi di A e di B** 
- contenente tutte le coppie costituite da una tupla di A e una tupla di B per cui è vero il **predicato p** 
Il **predicato p** è nella forma X q Y 
- X è un attributo di A, Y è un attributo di B 
- q è un operatore di confronto compatibile con i domini di X e di Y 
**Il theta-join è commutativo e associativo**.
>Equi-join è un caso particolare del theta-join in cui q è l’operatore di uguaglianza (=).
>Il predicato è esplicito perché indica una condizione di legame che non è per forza la PK con FK ma può essere un qualsiasi altro attributo.
##### Semi-join
$$
R = A \ltimes_p B
$$
Il semi-join di due relazioni A e B seleziona tutte le tuple di A **“semanticamente legate”** ad almeno una tupla di B 
- le informazioni di B non compaiono nel risultato 
Il semi-join di due relazioni A e B genera una relazione R 
- avente lo **stesso schema di A**
- contenente tutte le tuple di A per cui è vero il predicato specificato da p 
Il predicato **p** è espresso nella stessa forma del theta-join (confronto tra attributi di A e di B).

>Il risultato è un sottoinsieme delle relazioni di partenza.
>Tutte le tuple di A che sono semanticamente legate ad una tupla di B, ma le tuple di B non compaiono nel risultato.

Il semi-join può essere espresso in funzione del theta-join 
$$
A \ltimes_p B = \pi_{schema(A)}(A \bowtie_p B) 
$$
**Il semi-join non gode della proprietà commutativa**.
### Outer-join
Variante del join che permette di conservare l’informazione relativa alle tuple non semanticamente legate dal predicato di join 
- **completa con valori nulli le tuple prive di controparte**.

Esistono tre tipi di outer-join 
- **left**: sono completate solo le tuple del primo operando 
- **right**: sono completate solo le tuple del secondo operando 
- **full**: sono completate le tuple di entrambi gli operandi
##### Left outer-join
Il left outer-join di due relazioni A e B genera le coppie formate da 
- una tupla di A e una di B **“semanticamente legate”** 
$$+$$
- una tupla di A **“non semanticamente legata”** a tuple di B completata con **valori nulli** per tutti gli attributi di B

$$
R = A ⟕_p B
$$
Il left outer-join di due relazioni A e B genera una relazione R 
- avente come schema l’unione degli schemi di A e di B 
- contenente le coppie formate da 
	- una tupla di A e una tupla di B per cui è vero il predicato p 
	- una tupla di A che non è correlata mediante il predicato p a tuple di B completata con valori nulli per tutti gli attributi di B 
**Il left outer-join non è commutativo**.
##### Right outer-join
$$
R = A ⟖_p B
$$
Il right outer-join di due relazioni A e B genera una relazione R 
- avente come schema l’unione degli schemi di A e di B 
- contenente le coppie formate da 
	- una tupla di A e una tupla di B per cui è vero il predicato p 
	- una tupla di B che non è correlata mediante il predicato p a tuple di A completata con valori nulli per tutti gli attributi di A 
**Il right outer-join non è commutativo**.
##### Full outer-join
$$
R = A ⟗_p B
$$
Il full outer-join di due relazioni A e B genera una relazione R 
- avente come schema l’unione degli schemi di A e di B 
contenente le coppie formate da 
- una tupla di A e una tupla di B per cui è vero il predicato p 
- una tupla di A che non è correlata mediante il predicato p a tuple di B completata con valori nulli per tutti gli attributi di B 
- una tupla di B che non è correlata mediante il predicato p a tuple di A completata con valori nulli per tutti gli attributi di A 
**Il full outer-join è commutativo**.
### Unione e Intersezione
##### Unione
L’unione di due relazioni A e B seleziona tutte le tuple presenti in almeno una delle due relazioni.
$$
R = A \cup B
$$
L’unione di due relazioni A e B genera una relazione R 
- avente lo stesso schema di A e B 
- contenente tutte le tuple appartenenti ad A e tutte le tuple appartenenti a B (o a entrambi) 
>***Compatibilità*** 
- **le relazioni A e B devono avere lo stesso schema** (numero e tipo degli attributi) 

**Le tuple duplicate sono eliminate**.
**L’unione è commutativa e associativa.**
##### Intersezione
L’intersezione di due relazioni A e B seleziona tutte le tuple presenti in entrambe le relazioni.
$$
R = A \cap B
$$
L’ intersezione di due relazioni A e B genera una relazione R 
- avente lo stesso schema di A e B 
- contenente tutte le tuple appartenenti sia ad A sia a B 
>***Compatibilità*** 
- **le relazioni A e B devono avere lo stesso schema** (numero e tipo degli attributi
**L’intersezione è commutativa e associativa**.

>L'intersezione si puo replicare con la join, ed è piu efficiente farlo tramite join nei database.
### Differenza e anti-join
##### Differenza
La differenza di due relazioni A e B seleziona tutte le tuple presenti **esclusivamente** in A.
$$
R = A - B
$$
La differenza di due relazioni A e B genera una relazione R 
- avente lo stesso schema di A e di B 
- contenente tutte le tuple appartenenti ad A che non appartengono a B 
***Compatibilità*** 
- le relazioni A e B **devono avere lo stesso schema** (numero e tipo degli attributi) 
La differenza **non gode** né della **proprietà commutativa,** né della **proprietà associativa**.
##### Anti-join
$$
R = A \overline{\ltimes} B
$$
L’anti-join tra due relazioni A e B seleziona tutte le tuple di A **“semanticamente non legate”** a tuple di B 
- le informazioni di B non compaiono nel risultato 
L’anti-join di due relazioni A e B genera una relazione R 
- avente lo stesso schema di A 
- contenente tutte le tuple di A per cui non esiste nessuna tupla in B per cui è vero il predicato **p** 
Il predicato **p** è espresso nella stessa forma del theta-join e del semi-join.
L’anti-join **non gode** né della **proprietà commutativa**, né della **proprietà associativa**.
### Divisione
$$
R = A / B
$$
La divisione della relazione A per la relazione B genera una relazione R 
- avente come schema ***schema(A) - schema(B)***.
- contenente tutte le tuple di A tali che per ogni tupla (Y:y) presente in B esiste una tupla (X:x, Y:y) in A
La divisione **non gode** né della proprietà commutativa, né della proprietà associativa.

>**In pratica ti trova tutti i dati che hanno i requisiti in B.**

