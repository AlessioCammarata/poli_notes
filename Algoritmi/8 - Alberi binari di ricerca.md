#### Alberi Binari
Definizione ricorsiva: 
Un albero binario T è: 
- un insieme vuoto di nodi vuoto 
- una terna formata da una radice, un sottoalbero binario sinistro eun sottoalbero binario destro.
```c
typedef structnode* link;
struct node { 
	Item item; 
	link left; 
	link right; 
};
```
>All’albero si accede tramite il puntatore h alla radice.
##### Calcolo di parametri
```c
int count(link root) { //Numero di nodi
	if (root == NULL) 
		return 0; 
	return count(root->left) + count(root->right) + 1;
} 
int height(link root) { //Altezza
	int u, v; 
	if (root == NULL) 
		return -1; 
	u = height(root->left); 
	v = height(root->right);
	if (u>v) 
		return u+1; 
	return v+1; 
}
```
##### Visite
Attraversamento o visita: elenco dei nodi secondo una strategia: 
- **pre-ordine**: root, Left(root), Right(root)
- **in-ordine**: Left(root), root, Right(root) 
- **post-ordine**: Left(root), Right(root), root
###### Pre-ordine
```c
void preOrder(link root){
	if (root == NULL)
		return; 
	printf("%s ",root->name);
	preOrder(root->left);
	preOrder(root->right);
}
```
###### In-ordine
```c
void inOrder(link root){
	if (root == NULL)
		return; 
	inOrder(root->left);
	printf("%s ",root->name);
	inOrder(root->right);
}	
```
###### Post-ordine
```c
void postOrder(link root){
	if (root == NULL) 
		return; 
	postOrder(root->left);
	postOrder(root->right);
	printf("%s ",root->name);
}
```
##### Analisi di complessità
Ipotesi 1: albero completamente bilanciato (pieno):  (Divide and Conquer)
- D(n) = (1), C(n) = (1) 
- a = 2, b = 2 (sottoproblemi di dimensione n-1, approssimati conservativamente a n) Equazione alla ricorrenze: 
	T(n) = 1 + 2T(n/2) n > 1 
	T(1) = 1 
	T(n) = O(n)

Ipotesi 2: albero totalmente sbilanciato (degenerato in una lista) : (Decrease and conquer)
- D(n) = (1), C(n) = (1) 
- a = 1, ki = 1 
Equazione alla ricorrenze: 
	T(n) = 1 + T(n-1) n > 1 
	T(1) = 1 
	T(n) = O(n)
	
---
#### Alberi binari ed espressioni
	Slide 51

---