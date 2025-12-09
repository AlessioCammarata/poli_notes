1. Conta vocali in una stringa
```python
frase = input("Scrivi una frase: ")

count = 0
for c in frase.lower():
    if c in "aeiou":
        count += 1

print("Le vocali sono:", count)

```

2. Maiuscole/minuscole 
```python
parola = input("Scrivi una parola: ")

print("Maiuscolo:", parola.upper())
print("Minuscolo:", parola.lower())
print("Primo carattere:", parola[0])
print("Ultimo carattere:", parola[-1])
```

3. Somma lista 
```python
numeri = [2, 5, 7, 1, 3]
somma = 0

for n in numeri:
    somma += n

print("Somma totale:", somma)
```

4. Trova il numero maggiore senza usare max()
```python
lista = [2, 8, 4, 10, 3]

maggiore = lista[0]
for n in lista:
    if n > maggiore:
        maggiore = n

print("Il numero maggiore è:", maggiore)

```

5. Indovina il numero (random 1–10)
```python
import random

segreto = random.randint(1, 10)
tentativo = int(input("Indovina il numero (1-10): "))

while tentativo != segreto:
    tentativo = int(input("Sbagliato! Riprova: "))

print("Bravo! Hai indovinato!")

```

6. Estrazione casuale da una lista
```python
import random

nomi = ["Anna", "Luca", "Marco", "Sara"]
estratto = random.choice(nomi)

print("Il nome estratto è:", estratto)
```

7. Quiz casuale: domanda e verifica risposta
```python
import random

domande = [
    "Quanto fa 2+2?",
    "Di che colore è il cielo?",
    "Quanti giorni ci sono in una settimana?"
]

risposte = [
    "4",
    "blu",
    "7"
]

indice = random.randint(0, len(domande) - 1)

print(domande[indice])
risposta_utente = input("Risposta: ").lower()

if risposta_utente == risposte[indice]:
    print("Corretto!")
else:
    print("Sbagliato!")

```

8. Chiedi un numero finché non è positivo
```python
n = int(input("Inserisci un numero positivo: "))

while n <= 0:
    n = int(input("Valore non valido, inserisci un numero positivo: "))

print("Hai inserito:", n)
 
```

9. Richiedi password finché non è corretta
```python
password = input("Inserisci la password: ")

while password != "1234":
    password = input("Password errata. Riprova: ")

print("Accesso consentito.") 
```

10. Conta 1–10 con while
```python
i = 1
while i <= 10:
    print(i)
    i += 1

```

11. Chiedi numeri finché l’utente non scrive “stop”
```python
numeri = []
x = input("Inserisci un numero (oppure 'stop' per terminare): ")

while x != "stop":
    numeri.append(int(x))
    x = input("Inserisci un altro numero (oppure 'stop'): ")

print("Hai inserito:", numeri)

```

12. Conta parole in una frase
```python
frase = input("Scrivi una frase: ")
parole = frase.split()
print("Numero di parole:", len(parole))
```

13. Verifica se una parola è contenuta in una frase
```python
frase = input("Scrivi una frase: ")
parola = input("Scrivi una parola da cercare: ")

if parola in frase:
    print("La parola è presente.")
else:
    print("La parola NON è presente.")

```

14. Filtra numeri pari da una lista
```python
lista = [2, 7, 8, 10, 3, 5]
pari = []

for n in lista:
    if n % 2 == 0:
        pari.append(n)

print("Numeri pari:", pari)

```

15. Somma solo i numeri maggiori di 10
```python
lista = [4, 15, 2, 30, 12]
somma = 0

for n in lista:
    if n > 10:
        somma += n

print("Somma dei numeri > 10:", somma)

```

16. Rimuovi un elemento da una lista se esiste
```python
lista = [3, 7, 8, 10]
x = int(input("Quale numero vuoi rimuovere? "))

if x in lista:
    lista.remove(x)
    print("Numero rimosso.")
else:
    print("Numero non presente nella lista.")

print("Lista finale:", lista)

```

17. Lista misteriosa (5 numeri casuali 1–9)
```python
import random

lista = [random.randint(1, 9) for _ in range(5)]
num = int(input("Indovina un numero presente nella lista (1-9): "))

if num in lista:
    print("Bravo, il numero è nella lista!")
else:
    print("Peccato, non c'è!")

print("La lista era:", lista)   # opzionale per verifica

```

18. Generatore di password semplice
```python
import random

caratteri = ['a', 'b', 'c', '1', '2', '3', '!', '?']
password = ""

for _ in range(6):
    password += random.choice(caratteri)

print("La tua password è:", password)

```

19. Analisi di una frase (vocali, consonanti, spazi) 
```python
frase = input("Scrivi una frase: ")

vocali = "aeiou"
num_vocali = 0
num_consonanti = 0
num_spazi = 0

for c in frase.lower():
    if c in vocali:
        num_vocali += 1
    elif c == " ":
        num_spazi += 1
    else:
        num_consonanti += 1

print("Vocali:", num_vocali)
print("Consonanti:", num_consonanti)
print("Spazi:", num_spazi)

```

20. Mini-menu con while + if/elif/else
```python
scelta = ""

while scelta != "3":
    print("MENU")
    print("1 - Saluta")
    print("2 - Somma due numeri")
    print("3 - Esci")

    scelta = input("Scegli un'opzione: ")

    if scelta == "1":
        print("Ciao!")
    elif scelta == "2":
        a = int(input("Numero 1: "))
        b = int(input("Numero 2: "))
        print("Somma:", a + b)
    elif scelta == "3":
        print("Uscita dal programma...")
    else:
        print("Scelta non valida.")

```