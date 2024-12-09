# Aggiungere un contatto
# Salvare un contatto
# Quittare
# Stampare
# Modificare
# Cancellare
# Cercare

def stampa(rubrica):
    for contatto in rubrica:
        print(contatto, rubrica[contatto])

def cerca(rubrica):
    nome = input("Inserire il nome che si vuole modificare:\n")
    cognome = input("Inserire il cognome che si vuole modificare:\n")
    chiave = cognome + " "+ nome
    if chiave in rubrica:
        print(chiave, rubrica[chiave])
    else:
        print("Contatto non presente")

def modifica(rubrica):
    nome = input("Inserire il nome che si vuole modificare:\n")
    cognome = input("Inserire il cognome che si vuole modificare:\n")
    chiave = cognome + " "+ nome
    if chiave in rubrica:
        numero = input("Inserire il nuovo numero:\n")
        rubrica[chiave] = numero
    else:
        print("Contatto non presente")

def cancella(rubrica):
    nome = input("Inserire il nome che si vuole cancellare:\n")
    cognome = input("Inserire il cognome che si vuole cancellare:\n")
    chiave = cognome + " "+ nome
    if chiave in rubrica:
        rubrica.pop(cognome + " "+ nome)

def aggiorna(rubrica,file_name):
    try:
        with open(file_name,"w",encoding="utf-8") as file:
            try:
                for contatto in rubrica:
                    nome_cognome = contatto.split()
                    print(f"{nome_cognome[0]},{nome_cognome[1]},{rubrica[contatto]}",file=file)

            except Exception as e:
                    exit("I'm sorry, ",e)
            
    except FileNotFoundError as m:
        exit("I'm sorry, ",m)

def aggiungi(rubrica):
    nome = input("Inserire il nome che si vuole aggiungere:\n")
    cognome = input("Inserire il cognome che si vuole aggiungere:\n")
    chiave = cognome + " "+ nome

    if chiave not in rubrica:
        numero = input("Inserire il numero che si vuole aggiungere:\n")
        rubrica[cognome + " "+ nome] = numero
    else:
        print("Persona già presente")

def carica_rubrica(file):
    try:
        with open(file,"r",encoding="utf-8") as file:
            try:
                rubrica = {}
                for row in file:
                    row = row.rstrip().split(",")

                    # La chiave è la stringa cognome nome
                    rubrica[row[0] + " "+ row[1]] = row[2]

                return rubrica
            except Exception as e:
                    exit("I'm sorry, ",e)
            
    except FileNotFoundError as e:
        exit("I'm sorry, ",e)
    

def main():
    file_name = "numeri.txt"
    rubrica = carica_rubrica(file_name)
    
    scelta = " "
    while scelta != "q":
        print()
        print("P --> Print")
        print("M --> Modify a contact")
        print("D --> Delete a contact")
        print("A --> Add a contact")
        print("S --> Search for a contact")
        print("W --> Write a contact to disk")
        print("Q --> Quit")
        print()
        scelta = input("Inserire la scelta:\n").lower()
        print(scelta)

        match scelta:
            case "p": 
                stampa(rubrica)
            case "m":
                modifica(rubrica)
                print("Numero modificato con successo!\n")
            case "d": 
                cancella(rubrica)

                print("Numero cancellato con successo!\n")
            case "a": 
                aggiungi(rubrica)
                print("Numero aggiunto con successo!\n")
            case "s": 
                cerca(rubrica)
            case "w": 
                aggiorna(rubrica,file_name)

                print("Rubrica aggiornata con successo!\n")
            case "q": 
                print("Arrivederci\n")
            case _:
                print("Opzione errata\n")


if __name__ == "__main__":
    main()