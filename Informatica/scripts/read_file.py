try:
	amount = int(input("Inserisci il costo:\n"))
	balance = 50
	if amount> balance:
		raise ValueError("Non ci sono abbastanza soldi")

except FileNotFoundError as e:
	print("I'm sorry "+str(e))

except ValueError as e:
	print("I'm sorry "+str(e))