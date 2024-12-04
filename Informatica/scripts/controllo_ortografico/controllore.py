file_names = ["story.txt","dictionary.txt"]
sets = []

# Se la storia è corretta, l'insieme delle parole della storia, dovrà essere un sottoinsieme del dizionario
# In caso contrario la sottrazione ci darà l'insieme degli errori.

def calcola_set(file):
    try:
        parole = set()
        for row in file:
            row = row.split()

            for word in row:
                parole.add(word.strip("()?!,;:'.-_").lower())

        # print("il numero di parole uniche è",len(parole))
    except Exception as e:
            print("I'm sorry, ",e)

    return parole

def main():
     
    try:
        for file_name in file_names:
            with open(file_name,"r",encoding="utf-8") as file:
                sets.append(calcola_set(file))

        if sets[0].issubset(sets[1]):
            print("Non ci sono errori ortografici\n")
        else:
            set = sets[0].difference(sets[1])
            print((f"È presente {len(set)} errore" if len(set) == 1 else f"Sono presenti {len(set)} errori") + " nella storia\n")

            for i,errori in enumerate(set):
                print(f"{i+1}.\t{errori}")
            
    except FileNotFoundError as m:
        print("I'm sorry, ",m)

if __name__ == "__main__":
     main()