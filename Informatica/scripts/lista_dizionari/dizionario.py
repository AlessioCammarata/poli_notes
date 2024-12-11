# import csv

# file_name = "14BHDLZ_2022_shuffled.csv"

# try:
#     with open(file_name,"r",encoding="utf-8") as file:
#         try:
#             dati_studenti = []
#             reader = csv.reader(file, delimiter=",")
#             # n = 1  # Ad esempio, per iniziare dalla quarta riga
#             # for _ in range(n):
#             #     next(reader)
#             next(reader)
#             for row in reader:
#                 dati_studenti.append({"matricola": row[0], "cognome":row[1].lower(), "nome":row[2].lower()})

#             print(dati_studenti[0])
#         except Exception as e:
#                 print("I'm sorry , ",e)

# except FileNotFoundError as m:
#     exit(f"I'm sorry, {m}")


####### Tests
# Ordina dizionari - Sort() non funziona
# Utilizzo di itemgetter

import csv
from operator import itemgetter

file_name = "14BHDLZ_2022_shuffled.csv"

try:
    with open(file_name,"r",encoding="utf-8") as file:
        try:
            dati_studenti = []
            reader = csv.reader(file, delimiter=",")
            # n = 1  # Ad esempio, per iniziare dalla quarta riga
            # for _ in range(n):
            #     next(reader)
            next(reader)
            for row in reader:
                dati_studenti.append({"matricola": row[0], "cognome":row[1].lower(), "nome":row[2].lower()})

            #print(dati_studenti.sort()) # Da errore: '<' not supported between instances of 'dict' and 'dict'
            dati_studenti.sort(key=itemgetter("cognome")) # Cosi funziona
            print(max(dati_studenti,key=itemgetter("cognome")))
        except Exception as e:
                print("I'm sorry , ",e)

except FileNotFoundError as m:
    exit(f"I'm sorry, {m}")