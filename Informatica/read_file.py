file_name = "story.txt"
new_file  = "somma_media.txt"
vet_num   = []

with open(file_name,"r",encoding="utf-8") as file:
	for row in file:
		vet_num.append(float(row))
    
with open(new_file,"w",encoding="utf-8") as file:
	for item in vet_num:
		print(f"{item:>6.2f}",file=file)
		
	if len(vet_num) > 0:
		print("----------",file=file)
		print(f"Somma = {sum(vet_num):>6.2f}",file=file)
		print("Media = %.2f" % (sum(vet_num)/len(vet_num)),file=file)
	else:
	    print("Non ci sono numeri",file=file)