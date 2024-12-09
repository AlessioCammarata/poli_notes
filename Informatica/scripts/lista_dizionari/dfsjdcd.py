
from csv import DictReader

file_name = "14BHDLZ_2022_shuffled.csv"

try:
    with open(file_name,"r",encoding="utf-8") as file:
        try:
            dati_studenti = []
            reader = DictReader(file)

            for dict in reader:
                dati_studenti.append(dict)

            print(dati_studenti[0])
        except Exception as e:
                exit(f"I'm sorry , {e}")

except FileNotFoundError as m:
    exit(f"I'm sorry, {m}")
