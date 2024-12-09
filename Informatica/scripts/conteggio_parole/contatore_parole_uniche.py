file_name = "lyrics.txt"

try:
    with open(file_name,"r",encoding="utf-8") as file:
        try:
            parole = {}
            for row in file:
                row = row.split() # Prima dello split, è possibile aggiungere un rstrip(), per togliere gli \n.
                
                for word in row:
                    word = word.strip("()?!,;:'.-_").lower()
                    parole[word] = parole.get(word,0) + 1
                    # if word not in parole:
                    #     parole[word] = 0
                    # parole[word] +=1

            for parola in parole:
                print(f"La parola {parola} compare: {parole[parola]} volte")

        except Exception as e:
                print("I'm sorry , ",e)

except FileNotFoundError as m:
    print("I'm sorry, ",m)
