# from sys import exit

def leggi(file):
    '''
    Filehandle del file che deve essere letto.
    Inserisce nel dizionario un set contenente le pagine.
     dizio = dizionario che devo creare
     return dizionario di insiemi.
    '''
    dizio = {}
    for row in file:
        row = row.rstrip().split(":")
        if row[1] in dizio:
            dizio[row[1]].add(int(row[0]))
        else:
            dizio[row[1]] = {int(row[0])}

    return dizio

def stampa(dizio):

    for key in sorted(dizio):
        print(key + ":", end=" ")
        insieme = sorted(dizio[key])

        for item in insieme[:-1]:
            print(item,end=", ")
        print(insieme[-1])

def main():
    try:
        file_name = "index.txt"
        with open(file_name,'r',encoding="utf-8") as file:
            try:
                dizio_set = leggi(file)

                stampa(dizio_set)
                

            except Exception as e:
                exit(f"ERRORE, {e}")
    except FileNotFoundError as e:
        exit(f"ERRORE, {e}")
        

if __name__ == "__main__":
    main()