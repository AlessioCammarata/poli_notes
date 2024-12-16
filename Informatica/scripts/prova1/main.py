from sys import exit
from operator import itemgetter

def file_handle(file):

    file.readline()
    dati = []

    # next(file)
    #Leggo tutte le righe del file dalla seconda in poi
    for row in file:

        #Prendo le parole, divise una per una da ,
        row = row.rstrip().split(",")

        # Prendo i singoli parametri che mi servono
        provincia  = row[3].strip('"')
        indicatore = row[5].strip('"')
        valore = float(row[4])

        record = {
            'provincia': provincia,
            'indicatore': indicatore,
            'valore': valore
        }

        #Inserisco il dizionario nel vettore
        dati.append(record)

    return dati

def find_dati(dict_list):
    # Trova tutti gli indicatori una sola volta, e li ordina alfabeticamente
    return sorted(set(dict_list[i]["indicatore"] for i in range(len(dict_list))))

def calcola_classifica(dict_list,indicatore):
    classifica = []

    for dizio in dict_list:
        if dizio["indicatore"] == indicatore:
            classifica.append(dizio)

    return classifica

def main():
    try:
        file_name = "20201214_QDV2020_001.csv"
        with open(file_name,'r',encoding="utf-8") as file:
            try:
                #Ottengo una lista di dizionari che contengono le informazioni necessarie
                dict_list = file_handle(file)

                #Ottengo la lista degli indicatori
                lista_indicatori = find_dati(dict_list)

                ok  = False
                while not ok:
                    
                    print("\nScegliere l'indicatore: \n\n")
                    for i in range(len(lista_indicatori)):
                        print(f"{i+1:2}. {lista_indicatori[i]}")

                    try:
                        scelta = int(input("Inserire la scelta dell'indicatore presente nella lista:\n "))
                        if 1 > scelta > 90:
                            print("Il valore inserito deve essere compreso tra 1 e 90\n")
                        else:
                            ok = True
                            # print(scelta)
                            #Calcolo una sottolista di dizionari dove il valroe indicatore è quello selezionato
                            classifica = calcola_classifica(dict_list,lista_indicatori[scelta-1])
                            classifica.sort(key=itemgetter("valore"),reverse=True)
                            print("Classifica secondo l'indicatore: ", lista_indicatori[scelta-1])
                            for item in classifica:
                                print(f"{item['provincia']:25}: {item['valore']:15}")

                    except ValueError as e:
                        print("\nDevi inserire un numero intero.\n")

            except Exception as e:
                exit(f"Errore {e}")

    except FileNotFoundError as e:
        exit(f"Errore {e}")

if __name__ == "__main__":
    main()