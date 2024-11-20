lista_nomi = []

nome = input("Introduci nome o Q per uscire: ")
while nome.upper() != "Q":
	lista_nomi.append((nome,len(nome)))
	nome = input("Introduci nome o Q per uscire: ")
      
lista_nomi.sort()
print(lista_nomi)

from operator import itemgetter

lista_nomi.sort(key = itemgetter(1))

print(lista_nomi)