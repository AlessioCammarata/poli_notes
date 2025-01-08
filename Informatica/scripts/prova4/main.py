from sys import exit

def encode(file,dictionary):
    morse_text = ""

    text = file.readline().rstrip()
    for letter in text:
        if letter.upper() in dictionary:
            morse_text += dictionary[letter.upper()] + " "
        # morse_text += dictionary.get(letter.upper(),"") + " "

    return morse_text

def decode(file,dictionary):
    new_text = ""

    text = file.readline().rstrip().split()
    for letter in text:
        # if letter in dictionary:
        new_text += dictionary.get(letter,"")

    return new_text

def main():
    try:
        file_name1 = "morse.txt"
        file_name2 = "codice.txt"
        file_name3 = "testo.txt"

        with open(file_name1,'r',encoding='utf-8') as file1:
            try:
                encode_dictionary = {}
                decode_dictionary = {}
                for row in file1:
                    row = row.rstrip().split()
                    encode_dictionary[row[0]] = row[1]
                    decode_dictionary[row[1]] = row[0]

            except Exception as e:
                exit(f"Errore nella lettura del dizionario morse, {e}")


        scelta = input("Inserisci la scelta (c/d):\n")
        while scelta.lower() not in "cd":
            scelta = input("Reinserisci la scelta (c/d)")
        
        if scelta.lower() == "d":
            with open(file_name2,'r',encoding='utf-8') as file2:
                try:
                    morse_text = decode(file2,decode_dictionary)
                    print(morse_text)
                    
                except Exception as e:
                    exit(f"Errore nella decodifica, {e}")

        else:
            with open(file_name3,'r',encoding='utf-8') as file3:
                try:
                    text = encode(file3,encode_dictionary)
                    print(text)
                except Exception as e:
                    exit(f"Errore nella codifica, {e}")

    except FileNotFoundError as e:
        exit(f"Errore nell'apertura dei file, {e}")


if __name__ == "__main__":
    main()