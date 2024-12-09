
Le strutture dati complesse non sono altro che la combinazione di liste, insiemi e dizionari.
## Insieme

È un contenitore mutabile non ordinato (non si può indicizzare con dei numeri) di elementi univoci.

Sono ottimizzati per mantenere valori univoci. Per tali ragioni, la ricerca di un elemento negli insiemi è molto più veloce (di ordini di grandezza), ed essi sono sempre preferibili alle liste.

>Gli insiemi non sono indicizzabili, ragione per cui se provassi a indicizzare una lista come segue:

```python
insieme = {"df", "sdf"}
print(insieme[0])
```

otterrei un'eccezione di tipo `TypeError`.

#### Creazione di un insieme

Per creare un insieme si usano le `{}` con all'interno parametri o la funzione `set()`, passandogli strutture dati come delle liste

```python
insieme = {"df", "sdf"}
insieme = set([2, 1, 2, 4])
```

>Per creare un insieme vuoto si usa necessariamente la funzione `set()` senza alcun argomento.
   Se utilizzassi le `{}`  la struttura dati creata sarebbe un dizionario.

Quando creo un insieme con elementi ripetuti, gli stessi elementi saranno inseriti una sola volta all'interno dell'insieme:

```python
insieme = {1, 1, 2}
print(insieme) # {1, 2}
```

Se stampo più volte un insieme, a ogni iterazione l'output sarà diverso per l'ordine per cui gli elementi vengono stampati. 
Ciò accade perché non si può indicizzare un insieme, non essendo ordinato. 

>**NOTA**: 
>_In un insieme possono essere contenuti solo oggetti immutabili e comparabili_.

#### Operazioni con gli insiemi

Gli insiemi supportano tutte le operazioni della controparte matematica, e hanno a disposizione alcuni dei metodi e delle funzioni applicabili alle liste

##### Lunghezza

La funzione `len()` restituisce il numero di elementi dell'insieme

```python
insieme = {1, 2}
print(len(insieme)) # 2
```

##### Minimo, massimo e somma

Le funzioni `max()`, `min()` e `sum()` restituiscono, rispettivamente, il massimo, il minimo e la somma degli elementi dell'insieme

```python
insieme = {0, 1, 2}
print(max(insieme)) # 2
print(min(insieme)) # 0
print(sum(insieme)) # 3
```

##### Presenza di elementi

Con l'operatore `in` posso determinare se un elemento è presente o meno in maniera molto più veloce di una lista grazie a efficienti meccanismi di hashing. 

```python
insieme = {1, 2}
print(1 in insieme) # True
```

##### Iterazione

Poiché gli insieme sono contenitori, sono iterabili mediante ciclo for:

```python
insieme = {1, 2}
for i in insieme:
	print(i) # 1 2
```

##### Ordinamento

Se volessi applicare un algoritmo di ordinamento in un insieme avente elementi ordinabili, posso utilizzare la funzione `sorted()`

```python
nomi = {"Marco", "Giada", "Matteo"}

print(nomi) # {'Matteo', 'Giada', 'Marco'}

print(sorted(nomi)) # ['Giada', 'Marco', 'Matteo']
```

Ma ciò produrrebbe una lista. Questo accade perché gli insieme non sono strutture dati ordinate

##### Aggiungere elementi

```python
cast = set(["Luigi", "Gumbys", "Spiny"]) #1
cast.add("Arthur") #2
cast.add("Spiny") #3
```

>Se è già nel set non viene aggiunto
##### Rimuovere elementi

Si può utilizzare discard per togliere un elemento senza sollevare eccezioni nel caso in cui l'elemento sia presente oppure,
Posso rimuovere un singolo elemento con la remove, se esiste lo toglie:
```python
cast.remove( remove("The Colonel" "The Colonel") # Raises an exception
```

Solleva un’eccezione se l’elemento non fa parte del set.

clear() serve per svuotare completamente l'insieme.

```python
nomi = {"Marco", "Giada", "Matteo"}
nomi.clear() 

print(nomi) # {}
```

##### Copia

Se uso il metodo `copy()` su un insieme viene generato un altro insieme, non un alias

```python
nomi = {"Marco", "Giada", "Matteo"}
nomi2 = nomi.copy()

print(nomi2)
```

#### Operazioni matematiche

##### Subset

Il metodo `issubset()`, restituisce vero se un insieme è un  sottoinsieme di un altro

```python
nomi = {"Marco", "Giada", "Matteo"}
nomi_piccolo = {"Marco"}

print(nomi_piccolo.issubset(nomi)) # True
```

##### Superset

Contrario di `issuperset()`
Che significa che contiene completamente l'altro insieme.

```python
nomi = {"Marco", "Giada", "Matteo"}
nomi_piccolo = {"Marco"}

print(nomi.issuperset(nomi_piccolo)) # True
```
##### Uguaglianza

Per verificare se due insieme sono uguali uso `==`

```python
nomi = {"Marco", "Giada", "Matteo"}
nomi_piccolo = {"Marco"}

print(nomi_piccolo == nomi) # False
```

##### Unione

Per unire due insiemi uso il metodo `union()`

```python
nomi = {"Marco", "Giada", "Matteo"}
nomi_altro = {"DJF", "Marco"}

print(nomi_piccolo == nomi) # False
```

##### Intersezione

Il metodo `intersection()` restituisce un insieme contenente l'intersezione dei due insiemi.

```python
canadian = { "Red", "White" } 
british = { "Red", "Blue", "White" } 
italian = { "Red", "White", "Green" }

# in_both: The set {"White", "Red"} 
in_both = british.intersection(italian)
```

##### Differenza

Per fare la differenza di insiemi (operazioni non commutativa, a differenza delle altre) uso il metodo `difference()`

```python
print("Colors that are in the Italian flag but not the British:") print(italian.difference(british)) # Prints {'Green'}
```

##### Differenza simmetrica

Restituisce un insieme contenente gli elementi non in comune tra due insieme, quindi un unione - intersezione (unione esclusiva):

```python
# ex_both: The set {"Green", "Blue"} 
ex_both = british.symmetric_difference(italian)
```
---
### Esercizio sugli insiemi

Conta le parole uniche in un testo di una canzone:
```python
file_name = "lyrics.txt"

try:
    with open(file_name,"r",encoding="utf-8") as file:
        try:
            parole = set()
            for row in file:
                row = row.split()

                for word in row:
                    # if word[0] != "(":
                    #     parole.add(word.strip("?!,.-_").lower())
                    parole.add(word.strip("()?!,;:'.-_").lower())

            print(parole)
            print("il numero di parole uniche è",len(parole))
            
        except Exception as e:
                print("I'm sorry, ",e)
                
except FileNotFoundError as m:
    print("I'm sorry, ",m)
```
---
### Dizionario

Il dizionario viene anche chiamato array associativo o mappa.
Non c'è un ordinamento per posizione, ma vengono restituite nell'ordine in cui sono state inserite.

È una struttura chiave valore, con chiave univoca.
Ogni chiave ha un valore ad esso associato, che non è per forza univoco.

I dizionari si rappresentano con '{}'.

```python
dictionary = {}
dictionary = {'luca':10,'sonia':5}
```

Le chiavi dei dizionari possono essere stringhe o numeri.
Gli elementi invece possono essere qualsiasi tipo di oggetto.

#### Copiare un dizionario

Si crea una nuova copia non un alyas:

```python
dictionary = {'luca':10,'sonia':5}
new_dict = dict(dictionary)
```

È una copia differente, si trova in un'altra parte di memoria, se voglio copiare l'alyas posso fare:

```python
dictionary = {'luca':10,'sonia':5}
new_dict = dictionary
```
#### Accedere ad elementi di un dict

Per accedere si utilizzano le [], all'interno di esse bisogna inserire il nome della chiave del dizionario:

```python
dictionary = {'luca':10,'sonia':5}

print(dictionary['luca']) # 10
```

#### Chiave già presente nel dict

Per sapere se la chiave è gia presente nel dizionario possiamo scrivere:

```python
dictionary = {'luca':10,'sonia':5}

if 'luca' in dictionary:
	print("Luca è gia presente")
```

#### Get per recuperare le informazioni

Tramite il metodo get, si può recuperare un qualsiasi valore dalla chiave, e nel caso in cui la chiave non esiste da un valore di default:

```python
dictionary = {'luca':10,'sonia':5}

number = dictionary.get('luca',"missing")  #10
number = dictionary.get('marta',"missing") #'missing
```

#### Aggiungere una nuova coppia k->v

Per aggiungere una nuova coppia chiave valore si fa cosi:

```python
dictionary = {'luca':10,'sonia':5}

dictionary['matteo'] = 16
```

se 'matteo' è gia presente, andrò semplicemente a modificare il valore già presente.

#### Cancellare elementi

metodo pop cancella sia la chiave che l'elemento:
```python
dictionary = {'luca':10,'sonia':5}

print(dictionary.pop('luca')) # {'sonia':5}
```

#### Ciclare

Ad ogni iterazione con il ciclo for, ottengo la chiave come key:
```python
dictionary = {'luca':10,'sonia':5}

for key in dictionary:
	print(dictionary[key])
```

#### Metodi e funzioni dei dizionari

Ci sono metodi simili ai vettori.
- Clear() -> Cancella sia la chiave sia il valore associato
- Copy()
- Get() -> Permette di ottenere il valore dalla chiave, se non è presente puoi inserirlo di default
- Items() -> Restituisce una tupla chiave valore
- keys() -> Restituisce un vettore che contiene le chiavi del dizionario
- values() -> Restituisce una lista dei valori associati alle chiavi

Esempio **items()**:
```python
for (chiave,valore) in parole.items()
	print(f"La parola {chiave} compare: {valore} volte")
```

Esempio **values()**:
```python
valori = dictionary.values()
print(valori)
```
---
#### Utilizzare i dizionari come array associativi

Il dizionario può avere come chiave, valori immutabili:
- **Numeri**
- **Stringhe**
- **Tuple**

Ad una chiave posso associare qualsiasi oggetto.

---
#### Utilizzare i dizionari come record di dati

In questo caso il record di dati è composto da dati differenti (eterogenei).

Esempio:
```python
dictionary = {'Nome':'luca',
			  'Cognome':'sonia'
			  'eta' : 25 
		}
```

Si possono creare anche liste di dizionari, all'interno di una lista si inseriscono dizionari in modo da poter ciclare in maniera efficace.

Esercizio:
Creare un dizionario che contiene matricola, cognome, nome ed inserirlo in una lista:
```python
import csv

file_name = "14BHDLZ_2022_shuffled.csv"  

try:
    with open(file_name,"r",encoding="utf-8") as file:
        try:
            dati_studenti = []
            reader = csv.reader(file, delimiter=",")

            # n = 3 # Ad esempio, per iniziare dalla quarta riga
            # for _ in range(n):
            #     next(reader)
            next(reader)

            for row in reader:
                dati_studenti.append({"matricola": row[0],
					                  "cognome":row[1].lower(),
						              "nome":row[2].lower()}
						            )

            print(dati_studenti[0])

        except Exception as e:
                 exit(f"I'm sorry, {e}")

except FileNotFoundError as m:
     exit(f"I'm sorry, {m}")
```

Esercizio:
Creare un dizionario che contiene matricola, cognome, nome ed inserirlo in una lista:
```python
  
from csv import DictReader

file_name = "14BHDLZ_2022_shuffled.csv" 
try:
    with open(file_name,"r",encoding="utf-8") as file:
        try:
            dati_studenti = []
            reader = DictReader(file)

            for dicta in reader:
                dati_studenti.append(dicta)
        
            print(dati_studenti[0])

        except Exception as e:
                exit(f"I'm sorry , {e}")

except FileNotFoundError as m:
    exit(f"I'm sorry, {m}")
```

---

Esercizio:
Conta le parole uniche del testo, per ogni parola mettere affianco il numero di ripetizioni:
```python
file_name = "lyrics.txt"

try:
    with open(file_name,"r",encoding="utf-8") as file:
        try:
            parole = {}
            for row in file:
                row = row.split()

                for word in row:
                    word = word.strip("()?!,;:'.-_").lower()
                    parole[word] = parole.get(word,0) + 1
                    # if word not in parole:
                    #     parole[word] = 0
                    # parole[word] +=1
            for parola in parole:
                print(f"La parola {parola} compare: {parole[parola]} volte")
            
        except Exception as e:
                 exit(f"I'm sorry, {e}")

except FileNotFoundError as m:
     exit(f"I'm sorry, {m}")
```

