I vettori sono insiemi di dati omogenei e può essere utilizzato come contenitore di dati.
- Senza alcun criterio di ordine
- Con un criterio di ordine
- Sfruttando la corrispondenza dato-indice

La corrispondenza da indice a dato è teta(1), molto veloce con complessità costante.
Invece il processo inverso ha una complessità diversa, poiche bisogna cercare nei valori e non negli indici, la complessita sarà al massimo N.

Utilizzo:
- Problemi in cui esistono corrispondenze tra numeri interi e dati
- L'intero è associato all'indice di una casella
-  È possibile che occorra un dato vuoto (nullo) per le caselle non utilizzate
---
### Problemi numerici

I vettori possono essere utilizzati nei problemi aritmetici: 
- per collezionare e manipolare (insiemi di) numeri 
- per rappresentare dati con struttura lineare (vettori) o tabellare (matrici) 
- per gestire corrispondenze tra numeri (indice e dato).

Problemi su insiemi di numeri:
- Problemi nei quali si gestiscono insiemi (gruppi) di dati numerici, con operazioni di I/O, unione, intersezione, … NON CONTA L'ORDINE 
- La soluzione spesso si basa su costrutti iterativi (eventualmente annidati) tali da: opercorrere gli elementi di un insieme opercorrere, per ogni elemento di un insieme, tutti gli elementi di un altro insieme.
---
### Intersezione tra 2 vettori

Bisogna controllare se ogni elemento di un vettore appartiene ad un altro.

