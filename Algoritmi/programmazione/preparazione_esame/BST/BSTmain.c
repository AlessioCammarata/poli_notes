#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/BST.h"
#include "lib/OSBST.h"

// Enumerazione per le strategie di visita
enum treeVisit {
    PRE = 0,
    IN = 1,
    POST = 2
};

// Funzione helper per creare un Item
Item NEW_item(int id, char *val) {
    Item x = malloc(sizeof(struct item_s));
    if(x == NULL) return NULL;
    x->id = id;
    x->val = malloc(strlen(val) + 1);
    if(x->val == NULL) {
        free(x);
        return NULL;
    }
    strcpy(x->val, val);
    return x;
}

// Funzione helper per liberare un Item
void FREE_item(Item item) {
    if(item != NULL) {
        free(item->val);
        free(item);
    }
}

int main(){
    printf("============ TEST BST ============\n\n");

    // Inizializzazione
    bst_t bst = BSTinit();
    printf("1. BST inizializzato\n");
    printf("   Conta: %d (dovrebbe essere 0)\n", BSTcount(bst));
    printf("   Vuoto: %s\n\n", BSTempty(bst) ? "SI" : "NO");

    // Test inserimento in foglia
    printf("2. Inserimento in foglia: 50, 30, 70, 20, 40, 60, 80\n");
    Item i1 = NEW_item(50, "cinquanta");
    Item i2 = NEW_item(30, "trenta");
    Item i3 = NEW_item(70, "settanta");
    Item i4 = NEW_item(20, "venti");
    Item i5 = NEW_item(40, "quaranta");
    Item i6 = NEW_item(60, "sessanta");
    Item i7 = NEW_item(80, "ottanta");

    BSTinsert_leafR(bst, i1);
    BSTinsert_leafR(bst, i2);
    BSTinsert_leafR(bst, i3);
    BSTinsert_leafR(bst, i4);
    BSTinsert_leafR(bst, i5);
    BSTinsert_leafR(bst, i6);
    BSTinsert_leafR(bst, i7);
    printf("   Conta: %d (dovrebbe essere 7)\n\n", BSTcount(bst));

    // Test visita
    printf("3. Visita INORDER:\n   ");
    BSTvisit(bst, IN);
    printf("\n\n");

    printf("4. Visita PREORDER:\n   ");
    BSTvisit(bst, PRE);
    printf("\n\n");

    printf("5. Visita POSTORDER:\n   ");
    BSTvisit(bst, POST);
    printf("\n\n");

    // Test min e max
    printf("6. Min e Max:\n");
    Item min_item = BSTmin(bst);
    Item max_item = BSTmax(bst);
    if(min_item != NULL)
        printf("   Min: %d - %s\n", min_item->id, min_item->val);
    if(max_item != NULL)
        printf("   Max: %d - %s\n\n", max_item->id, max_item->val);

    // Test ricerca
    printf("7. Ricerca:\n");
    Item found = BSTsearch(bst, 40);
    if(found != NULL)
        printf("   Trovato 40: id=%d, val=%s\n", found->id, found->val);
    found = BSTsearch(bst, 100);
    printf("   Trovato 100: %s\n\n", found == NULL ? "NO (corretto)" : "SI (errore)");

    // Test inserimento in radice
    printf("8. Inserimento in radice: 45\n");
    Item i8 = NEW_item(45, "quarantacinque");
    BSTinsert_root(bst, i8);
    printf("   Conta: %d (dovrebbe essere 8)\n", BSTcount(bst));
    printf("   Visita INORDER dopo inserimento in radice:\n   ");
    BSTvisit(bst, IN);
    printf("\n\n");

    // Liberazione memoria
    printf("9. Test OSBST (Order-Statistic BST)\n");
    osbst_t osbst = OSBSTinit();
    Item o1 = NEW_item(50, "cinquanta");
    Item o2 = NEW_item(30, "trenta");
    Item o3 = NEW_item(70, "settanta");
    Item o4 = NEW_item(20, "venti");
    Item o5 = NEW_item(40, "quaranta");
    Item o6 = NEW_item(60, "sessanta");
    Item o7 = NEW_item(80, "ottanta");

    OSBSTinsert_leafR(osbst, o1);
    OSBSTinsert_leafR(osbst, o2);
    OSBSTinsert_leafR(osbst, o3);
    OSBSTinsert_leafR(osbst, o4);
    OSBSTinsert_leafR(osbst, o5);
    OSBSTinsert_leafR(osbst, o6);
    OSBSTinsert_leafR(osbst, o7);

    Item sel0 = BSTselect(osbst, 0);
    Item sel3 = BSTselect(osbst, 3);
    Item sel6 = BSTselect(osbst, 6);
    if(sel0 != NULL) printf("   Select(0): %d - %s\n", sel0->id, sel0->val);
    if(sel3 != NULL) printf("   Select(3): %d - %s\n", sel3->id, sel3->val);
    if(sel6 != NULL) printf("   Select(6): %d - %s\n", sel6->id, sel6->val);

    Item succ = BSTsucc(osbst, 40);
    Item pred = BSTpred(osbst, 40);
    if(succ != NULL) printf("   Succ(40): %d - %s\n", succ->id, succ->val);
    if(pred != NULL) printf("   Pred(40): %d - %s\n", pred->id, pred->val);

    printf("   Delete(50) e Balance\n");
    BSTdelete(osbst, 50);
    BSTbalance(osbst);

    printf("\n10. Liberazione memoria...\n");
    BSTfree(bst);
    
    // Libera gli item (nota: in BSTfree liberavamo solo i nodi, non gli item originali)
    FREE_item(i1);
    FREE_item(i2);
    FREE_item(i3);
    FREE_item(i4);
    FREE_item(i5);
    FREE_item(i6);
    FREE_item(i7);
    FREE_item(i8);
    FREE_item(o1);
    FREE_item(o2);
    FREE_item(o3);
    FREE_item(o4);
    FREE_item(o5);
    FREE_item(o6);
    FREE_item(o7);

    printf("   BST liberato correttamente.\n");

    return 0;
}
