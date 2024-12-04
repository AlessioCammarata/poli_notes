file_name = "lyrics.txt"

try:
    with open(file_name,"r",encoding="utf-8") as file:
        try:
            parole = set()
            for row in file:
                row = row.split()
                
                for word in row:
                    
                    # if word[0] != "(": 
                    #     parole.add(word.strip("?!,.-_").lower())
                    parole.add(word.strip("()?!,;:'.-_").lower())

            print(parole)
            print("il numero di parole uniche è",len(parole))
        except Exception as e:
                print("I'm sorry, ",e)

except FileNotFoundError as m:
    print("I'm sorry, ",m)


