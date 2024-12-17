from sys import exit

def file_handle(file):
    dictionary = {}
    next(file)

    for row in file:  
        row = row.rstrip().split(";")
        regione = row[10].strip()
        comune = row[6].strip()

        if regione not in dictionary:
            dictionary[regione] = [comune]
        else:
            dictionary[regione].append(comune)

    return dictionary

def find_shorter(regione):
    return min(sorted(regione),key=len)

def find_longer(regione):
    return max(sorted(regione),key=len)

def main():
    try:
        file_name = "elenco-comuni-italiani.csv"
        with open(file_name,'r',encoding="utf-8") as file:
            try:
                dictionary = file_handle(file)
                # print(dict_list.keys())
                end = False
                while not end:
                    scelta= input("Inserisci il nome della regione di cui si vogliono le informazioni\n")
                    while scelta != "***" and scelta not in dictionary:
                        scelta= input("Renserisci il nome della regione di cui si vogliono le informazioni. Il nome non è presente nel database\n")
                    
                    if scelta != "***":
                        print(f"Della regione {scelta}")
                        print(f"Il comune con il nome più corto è: {find_shorter(dictionary[scelta])}")
                        print(f"Il comune con il nome più lungo è: {find_longer(dictionary[scelta])}\n\n")

                    else:
                        end = True
                        print("Grazie e arrivederci\n")

            except Exception as e:
                exit(f"Errore nell'esecuzione, {e}")
    except FileNotFoundError as e:
        exit(f"Errore nell'apertura del file, {e}")

if __name__ == "__main__":
    main()