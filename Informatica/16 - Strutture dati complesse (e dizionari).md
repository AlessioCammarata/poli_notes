
Le strutture dati complesse non sono altro che la combinazione di liste, insiemi e dizionari, 

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
insieme = {1, 2}
print(max(insieme)) # 2
print(min(insieme)) # 1
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

Restituisce un insieme contenente gli elementi non in comune tra due insieme, quindi un unione - intersezione (unione esclusiva) 



---
### Esercizio
Conta le parole uniche in un testo di una canzone:


### Dizionario

