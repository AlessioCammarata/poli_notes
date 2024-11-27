Per gestire le eccezioni bisogna:
- prima di tutto **rilevare un errore**.
- **Gestire** gli errori
#### Rilevare gli errori
Per rilevare gli errori ( #raise ), la funzione deve controllare se sono verificate le condizioni per il regolare svolgimento del codice.
Il debugger o il processo che si occupa di gestire queste eccezioni, raise implicita.
Ci sono diversi tipi di eccezioni:
- ValueError
- Ecc..

All'eccezione, può essere assegnato un messaggio descrittivo del problema.
Colui che alza la raise può essere in qualsiasi livello di annidazione, se la except è nel main, l'errore verrà gestito lì.

#### Creare un'eccezione
Per creare una nostra eccezione si può fare così:
```python
try:
	amount = int(input("Inserisci il costo:\n"))
	balance = 50
    if amount> balance:
		raise ValueError("Non ci sono abbastanza soldi")

except FileNotFoundError as e:
    print("I'm sorry "+str(e))

except ValueError as e:
    print("I'm sorry "+str(e))
```

>_NOTA_: In questo caso diamo alla ValueError un messaggio specifico.

---
#### Gestire gli errori
Gli errori vengono gestiti dalla try except.


Tipi di eccezione:
- ZeroDivisionError
- ValueError
- NameError
- IndexError
- KeyError
- FileNotFoundError

Questi errori, appaiono al fondo dell'esecuzione e stampati a video, seguiti da una breve spiegazione testuale.

>Tutte le eccezioni devono essere gestite da qualche parte.

Try except sono compund statement.
Ogni blocco try può avere gestite una o più eccezioni.

#Esempio 

```python
try:

    file_name = input("Inserisci il nome del file:\n")
    with open(file_name,"r",encoding="utf-8") as file:
        for row in file:
            print(int(row))

except FileNotFoundError as e:
    print("I'm sorry "+str(e))

except ValueError as e:
    print("I'm sorry "+str(e))
```

Nell'eccezione si può reinserire il codice di sopra:
```python
try:

    file_name = input("Inserisci il nome del file:\n")
    with open(file_name,"r",encoding="utf-8") as file:
        for row in file:
            print(int(row))

except FileNotFoundError as e:
    print("I'm sorry "+str(e))
    file_name = input("Inserisci il nome del file:\n") # Da qui non torna indietro

except ValueError as e:
    print("I'm sorry "+str(e))
```

**Exception** gestisce qualsiasi cosa:
```python
try:

    file_name = input("Inserisci il nome del file:\n")
    with open(file_name,"r",encoding="utf-8") as file:
        for row in file:
            print(int(row))

except Exception as e:
    print("I'm sorry "+str(e))

```

---
#### Finally
La clausola #finally si usa quando occorre compiere alcune azioni conclusive, prima che si chiudi il programma.
Nella #finally si inserisce la chiusura di tutti i file.

```python
try:

    file_name = input("Inserisci il nome del file:\n")
    file = open(file_name,"r",encoding="utf-8")
	for row in file:
		print(int(row))

except Exception as e:
    print("I'm sorry "+str(e))
finally:
	file.close()
```

#### Struttura classica del codice
La struttura classica contiene 2 #try #except annidati.
Quello più esterno è quello che tenta di aprire il file, mentre quello più interno è quello che si occupa di gestire le eccezioni del codice interno.

```python
def leggi_dati(inFile):
	pass
	

try:
	
    file_name = input("Inserisci il nome del file:\n")
    file = open(file_name,"r",encoding="utf-8")
    try:
		leggi_dati(file)
			
	except Exception as e:
		print("I'm sorry "+str(e))
		
	finally:
		file.close()
		
except FileNotFoundError as e:
    print("I'm sorry "+str(e))
```

In questo modo, se avvengono degli errori all'interno delle funzioni dopo l'apertura del file, tutto verrà raised fino alla #except e verrà eseguita la #finally.

>Con la with non serve usare la #finally.

---
#### Gestire errori di acquisizione

```python
def read_file(filename):
	pass

done = False
while not done:
	try:
		data = read_file(filename)
		done = True
	except OSError:
		print("File not found\n")
	except ValueError:
		print("File contents invalid\n")

```

