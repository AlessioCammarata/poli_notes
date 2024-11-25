Un file serve a mantenere informazioni. Il file system si occupa dei file.
I file con una estensione si dividono in:
- File binari
- File di testo

>Nei **file di testo** viene salvata la codifica dei caratteri
>**I file binari** contengono i valori che corrispondono alla relativa codifica

_Esempio_:

	Devo scrivere -10,
	
	Nel file di testo scriverò:
	- codice ASCII(o UNICODE) del casattere meno
	- codice ASCII(o UNICODE) del carattere 1
	- codice ASCII(o UNICODE) delcarattere 0
	occupando 3 byte.
	
	
	Nel file binario invece scriverò:
	- complemento a 2 del numero -10.
	
	parto da +10, 00001010
	scambio 0 ed 1 e sommo 1.
	-10 = 01110110
	Questo è l'unico byte che scrivo nel file binario.

I file binari occupano meno spazio.
La codifica di testo è visibile a tutti coloro che hanno un editor di testo.

---
### File di testo

Si dividono in testo libero e testo strutturato.
#### Testo libero

Parole libere.
#### Testo strutturato

Organizzato per record, dove i record possono essere su una singola riga o sparpagliati su piu righe, la struttura è nota.
##### Record per riga

##### Markdown, HTML

Utilizza i tag per scrivere. che descrivono come viene presentato il testo, l'informazione.

---
### leggere e scrivere file

Non puoi leggere o scrivere un file se prima non lo hai aperto, nel caso in cui non sia possibile aprirlo bisogna gestire l'errore.

###### Leggere un file

In python è possibile interagire con i file di testo:

```Python
infile = open("input.txt", "r")
```

Se ci riesce, la open() restituisce un oggetto file che va memorizzato in una variabile, in questo modo sarà possibile interagire con il file.
>È un contenitore di righe.

###### Scrivere un file

Nel caso in cui si voglia scrivere si utilizza il metodo open con il parametro "w".

```Python
infile = open("input.txt", "w")
```

Se in questo caso il file non esiste, ne viene creato uno nuovo.
Se il file esiste già il suo contenuto viene cancellato.
>Viene restituito anche in questo caso un oggetto file

>_NOTA:_
>Dopo che un file è stato utilizzato, esso va chiuso.

```Python
infile.close()
outfile.close()
```

I file si chiudono al termine del codice, ma se nel caso mancasse corrente e tengo i file aperti, le informazioni vengono perse.
Perciò bisogna chiuderli appena si ha la possibilità.

##### Descrittori

Permettono di fare cose con i file all'internod ella open():

	"r" -> Apre il file in lettura
	"w" -> Apre il file in scrittura, ne crea uno nuovo se non esiste.
	"x" -> Apre il file per creazione esclusiva, semil file esiste già da errore
	"a" -> 
	"q" -> 
	"w" -> 
	"t"
	"h"
	"+"
---
### Esempio

```Python
FILENAME = "story.txt"

file = open(FILENAME,"r")
```
---
### Attenzione a windows
Windows prova ad aprire il file con una codifica proprietaria, tutte le lettere accentate o comunque non presenti nella codifica di windows non verranno riconosciute.

perciò bisogna costringere a utilizzare la utf-8 (UNICODE):

```Python
file = aopen("file.txt","r",encoding="utf-8")
```
---
### Leggere da un file su python

La open restituisce un file handle, un oggetto file handle.
Questo oggetto, supporta una serie di metodi per i file aperti in lettura:

- Read() - Se non specifico il numero di caratteri legge tutto
- Readline() - Leggo una linea alla volta
- Readlines() - Legge tutto creando una mega stringa, compresi gli \n.

Si puo leggere un file una riga per volta oppure tutto in una volta.
Nel secondo caso, se io non ho spazio a sufficienza mi crusha la macchina non il programma.

```Python
FILENAME = "story.txt"
file = open(FILENAME,"r")


carattere = file.read(1)
print(carattere)

carattere = file.read(1)
print(carattere)

carattere = file.read(1)
print(carattere)

###
#M
#a
#r
```

Mi accorgo di essere alla fine del file se la read mi restituisce la stringa vuota "".

Leggere un file carattere per carattere:

```python
FILENAME = "story.txt"

file = open(FILENAME,"r")

carattere = file.read(1)
print(carattere, end="")

while carattere != "":
    carattere = file.read(1)
    print(carattere, end="")
    
file.close()
```

Leggere un file carattere n caratteri consecutivamente:

```python
FILENAME = "story.txt"

file = open(FILENAME,"r")

carattere = file.read(10)
while carattere != "":
    print(carattere, end="")
    carattere = file.read(10)
```

Leggere per righe:

- Ci sono 2 possibilità, readline:

```python
FILENAME = "story.txt"

file = open(FILENAME,"r")
  
riga = file.readline()

while riga != "":
    print(riga, end="")
    riga = file.readline
```
ATTENZIONE - Questo codice non funziona.

- Utilizzare il ciclo for
```python
FILENAME = "story.txt"

file = open(FILENAME,"r")  

for row in file:
    print(row,end="")
```

Esercizio:
- Quante parole per ogni riga:

```python
FILENAME = "story.txt"
file = open(FILENAME,"r")

for i,row in enumerate(file):
    parole = row.split()
    print(i+1, len(parole))
```

- Quante vocali per ogni riga

```python
FILENAME = "story.txt"
vocali = "aeiouAEIOU"
file = open(FILENAME,"r")

for i,row in enumerate(file):
    parole = row.split()
    counter = 0

    for parola in parole:
        for vocale in vocali:
            counter += parola.count(vocale)
  
    print(i+1, counter)
```

#### Cosa da non fare

Brutta poichè legge e crea una stringa che contiene tutto il testo, bisogna avere abbastanza memoria per fare una cosa del genere.

```python
file.readlines()
```

#### Esercizio:

Leggi i voti da un file e fai la media.

```python
FILENAME = "voti.txt"
file = open(FILENAME,"r")
  
voti = [float(row) for row in file ]

if len(voti) != 0:
    print("La media è ", sum(voti)/len(voti))
file.close()
```

> _NOTA_ : 
>   Una riga vuota in realtà contiene sempre \n.
    Quando arrivo alla fine ottengo una stringa vuota, che significa che non c'è più niente da leggere.

#### Convertire i valori

I valori ottenuti in lettura sono stringhe quindi vanno convertiti.

---
### Scrivere da un file su python

Python utilizza il metodo write per scrivere un file.

```Python
file.write("MAMA\n")

#OPPURE

print("MAMA", file= "file.txt")
```

>I parametri che passo alla funzione potrebbero avere dei parametri associati di default, la print ha come default lo "standard output" vale a dire il video.

- Esempio:
Leggere un file che ha dei numeri float scritti uno per riga, in output bisogna scrivere gli stessi numeri, una linea di trattini e calcolare la somma e il valore medio:

```python
file_name = "file.txt"
new_file  = "somma_media.txt"
vet_num   = []

with open(file_name,"r",encoding="utf-8") as file:
    for row in file:
        vet_num.append(float(row))

with open(new_file,"w",encoding="utf-8") as file:
    for item in vet_num:
        print(f"{item:>6.2f}",file=file)

    if len(vet_num) > 0:
        print("----------",file=file)
        print(f"Somma = {sum(vet_num):>6.2f}",file=file)
        print("Media = %.2f" % (sum(vet_num)/len(vet_num)),file=file)

    else:
        print("Non ci sono numeri",file=file)
```

>**_Nota_**: Se apro il file in modalità append "a", quello che scrivo, lo aggiungo sotto. 
>Ciò che stava dentro non viene cancellato.

##### Errore frequente

A volte i file non vengono messi nella stessa cartella di progetto, per gestirli bisogna specificare tutto il percorso per raggiungerli.

```python
path = "home\\desktop\\file.txt"
```

### Processare testo libero e strutturato (record)

Per processare ogni parola singolarmente si utilizza la read e poi la split,
Quando usi la split però prendi anche le , o i . che noi non vogliamo processare.

Per questo motivo si utilizza il metodo strip().

```python
line = "James"
line = line.rstrip()
```

Se non specifico nulla, viene eliminato qualsiasi carattere di spaziatura.
Posso anche specificare un carattere da eliminare o un insieme di caratteri da eliminare.

```python
line = line.rstrip("\n")
```
In questo caso tolgo sono \n, il risultato è "James "

- Esempio
Stampa delle parole del file una per riga, senza punti, virgole ecc..

```python
file_name = "story.txt"

with open(file_name,"r") as file:
    for row in file:
        words = row.split()
        
        for word in words:
            print(word.rstrip(".,;:?!()[]{}"))
```

Il metodo split() può avere dei parametri:
- Separatore: sep=b
- Num di tagli: maxsplit=2

La lsplit comincia a tagliare da sinistra, la rsplit da destra.

- Esempio
Stampa i titoli dei film prodotti dopo il 1992 compreso:
```python
file = "film.txt" 

with open(file,"r",encoding="utf-8") as file:
    for row in file:
        row = row.split(",")

        if int(row[1]) >= 1992:
            print(row[0])
```

>La **with** sostituisce la open, chiude in automatico l'apertura.

## File CSV

Command Separator Value, sono file di testo e hanno dei separatori che possono essere virgoele, punti o altri segni.

Nei CSV completi, tutti i caratteri sono divisi da "", in questo modo se la , è parte del testo rimane dopo che effettua la split(",").

### Come leggere i file csv in python

