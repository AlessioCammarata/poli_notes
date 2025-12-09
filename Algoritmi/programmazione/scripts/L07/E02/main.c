#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// #define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L07/E02/elementi.txt"
#define nfin "./elementi.txt"
#define MAX 100
#define N_DIAG 3     // numero di diagonali da presentare
#define N_E_DIAG 5   // massimo numero di elementi per diagonale

// name: nome senza spazi
// type: 0=transizione, 1=acro indietro, 2=acro avanti
// start_dir/end_dir: 1=fronte, 0=spalle
// prec: 0=può essere primo, 1=deve essere preceduto
// final: 1=chiude la diagonale (non può avere successivi), 0=altrimenti
// value: punteggio dell'elemento
// difficulty: difficoltà dell'elemento
typedef struct{
    char name[MAX];
    int type, start_dir, end_dir, prec, final;
    float value;
    int difficulty; 
} Elements;

// idx: indici degli elementi scelti
// len: numero di elementi nella diagonale
// diff: somma delle difficoltà della diagonale
// val: somma dei valori della diagonale
// has_two_acro_seq: vero se contiene almeno due acrobatici consecutivi
// has_forward/has_backward: vero se contiene almeno un acro avanti/indietro
// last_diff: difficoltà dell'ultimo elemento (per gestire il BONUS)
typedef struct {
    int idx[N_E_DIAG];
    int len;
    int diff;
    float val;
    int has_two_acro_seq;
    int has_forward;
    int has_backward;
    int last_diff;
} Diag;

// Vettore dinamico di diagonali generate
typedef struct {
    Diag *arr;
    int size; //Dimensione
    int cap; //Capienza
} DiagList;

// Deallocazione dell'array di elementi
void free_all(Elements **e, int n);
//Lettura del file di elementi (prima riga: N; poi N righe con i campi)
int leggiFile(FILE *fin, Elements **e, int n);
//Inizializzazione/push/free del vettore dinamico
static void diaglist_init(DiagList *dl);
static void diaglist_push(DiagList *dl, Diag d);
static void diaglist_free(DiagList *dl);
//Ricorsione per trovare diagonali valide
static void gen_diagonals_rec(Elements **e, int n, int DD,
    int pos, int prev_end,
    int seq[], int len,
    int curr_diff, float curr_val,
    int has_acro, int last_was_acro, int has_two_acro_seq,
    int has_forward, int has_backward,
    DiagList *out);
static void gen_diagonals(Elements **e, int n, int DD, DiagList *out); //Wrapper
//Funzione per scegliere il migliore tra le soluzioni valide
static void choose_best(const DiagList *dl, int DP, float *best, int best_idx[N_DIAG]);

int main(void){
    FILE *fin;
    int n, DD, DP;
    Elements **elements;

    printf("Inserisci DD e DP, in riga Es. 12 28\n");
    if(scanf("%d %d",&DD,&DP) != 2) return 1;

    // Apertura e lettura file elementi (N e poi N record)
    if((fin = fopen(nfin,"r")) == NULL){ 
        perror("Errore in apertura del file"); 
        return 1; 
    }
    if(fscanf(fin,"%d",&n) != 1){ 
        perror("Errore in lettura del file"); 
        fclose(fin); 
        return 1; 
    }

    elements = malloc(n*sizeof(Elements *));
    if (!elements) { 
        perror("malloc"); 
        fclose(fin); 
        return 1; 
    }
    if(!leggiFile(fin, elements ,n)){ 
        perror("Errore in lettura del file"); 
        fclose(fin); 
        free_all(elements,n); 
        return 1; 
    }

    // Generazione di tutte le diagonali valide con pruning locale
    DiagList dl; 
    diaglist_init(&dl);
    gen_diagonals(elements, n, DD, &dl);

    // Scelta della miglior terna sotto DP e vincoli globali
    float best; 
    int best_idx[3]; 
    choose_best(&dl, DP, &best, best_idx);

    // Stampa (come da esempio)
    if (best < 0.0f){
        printf("DD = %d DP = %d\n", DD, DP);
        printf("Nessun programma valido trovato.\n");
    } else {
        printf("DD = %d DP = %d\n", DD, DP);
        printf("TOT = %.3f\n", best);
        for(int d=0; d<3; d++){
            const Diag *dg = &dl.arr[best_idx[d]];
            float shown = dg->val;
            int bonus = 0;
            if (d==2 && dg->last_diff >= 8){ 
                shown *= 1.5f; 
                bonus=1; 
            }
            if (bonus) printf("DIAG #%d > %.3f * 1.5 (BONUS)\n", d+1, dg->val);
            else printf("DIAG #%d > %.3f\n", d+1, dg->val);
            for(int p=0;p<dg->len;p++){
                printf("%s%s", elements[dg->idx[p]]->name, (p+1<dg->len)?" ":"\n");
            }
        }
    }

    // Pulizia risorse
    diaglist_free(&dl);
    free_all(elements, n);
    fclose(fin);
    return 0;
}

// Dealloca tutti i record letti
void free_all(Elements **e, int n){
    for(int i = 0; i<n; i++) 
        free(e[i]);
    free(e);
}

// Legge N elementi dal file e popola l'array
int leggiFile(FILE *fin, Elements **e, int n){
    int i;
    for(i = 0; i<n; i++){
        e[i] = malloc(sizeof(Elements));
        if(!e[i]){ 
            free_all(e, i); 
            return 0; 
        }
        if(fscanf(fin,"%s %d %d %d %d %d %f %d",
                  e[i]->name,
                  &e[i]->type,
                  &e[i]->start_dir,
                  &e[i]->end_dir,
                  &e[i]->prec,
                  &e[i]->final,
                  &e[i]->value,
                  &e[i]->difficulty) != 8 ){
            free(e[i]); 
            free_all(e, i); 
            return 0;
        }
    }
    return i==n;
}

// Inizializzazione/push/free del vettore dinamico
static void diaglist_init(DiagList *dl){ 
    dl->arr=NULL; 
    dl->size=0; 
    dl->cap=0; 
}
static void diaglist_push(DiagList *dl, Diag d){
    if (dl->size==dl->cap){
        dl->cap = dl->cap ? dl->cap*2 : 64;
        dl->arr = (Diag*)realloc(dl->arr, dl->cap*sizeof(Diag));
    }
    dl->arr[dl->size++] = d;
}
static void diaglist_free(DiagList *dl){ 
    free(dl->arr); 
    dl->arr=NULL; 
    dl->size=dl->cap=0; 
}

// Genera tutte le diagonali valide con pruning locale
// Vincoli applicati:
// - primo elemento: prec==0 e ingresso frontale (1)
// - elementi successivi: start_dir == prev_end
// - somma difficoltà della diagonale <= DD
// - se elemento ha final==1, la diagonale si chiude
// - ogni diagonale deve avere almeno un acrobatico
static void gen_diagonals_rec(Elements **e, int n, int DD,
                              int pos, int prev_end,
                              int seq[], int len,
                              int curr_diff, float curr_val,
                              int has_acro, int last_was_acro, int has_two_acro_seq,
                              int has_forward, int has_backward,
                              DiagList *out){
    // registra la diagonale corrente (se non vuota e valida)
    if (len > 0 && curr_diff <= DD) {
        Diag d; 
        d.len=len; 
        d.diff=curr_diff; 
        d.val=curr_val; 
        d.has_two_acro_seq=has_two_acro_seq;
        d.has_forward=has_forward; 
        d.has_backward=has_backward; 
        d.last_diff = e[seq[len-1]]->difficulty;
        memcpy(d.idx, seq, len*sizeof(int));
        if (has_acro)
            diaglist_push(out, d);
    }

    // Stop se raggiunto il massimo numero di elementi
    if (len == N_E_DIAG) return;

    // Prova ad aggiungere ciascun elemento
    for (int i=0;i<n;i++){
        if (len==0){
            if (e[i]->prec==1) continue;      // non può essere primo
            if (e[i]->start_dir!=1) continue; // deve iniziare frontalmente
        } else {
            if (e[i]->start_dir!=prev_end) continue; // compatibilità direzioni
        }
        int new_diff = curr_diff + e[i]->difficulty;
        if (new_diff > DD) continue; // limite sulla difficoltà di diagonale
        float new_val = curr_val + e[i]->value;
        int is_acro = (e[i]->type!=0);
        int new_has_acro = has_acro || is_acro;
        int new_has_two = has_two_acro_seq || (last_was_acro && is_acro);
        int new_has_fwd = has_forward || (e[i]->type==2);
        int new_has_bwd = has_backward || (e[i]->type==1);

        seq[len] = i;
        int must_stop = (e[i]->final==1);
        if (must_stop){
            // Registra e non estendere
            Diag d; 
            d.len=len+1; 
            d.diff=new_diff; 
            d.val=new_val; 
            d.has_two_acro_seq=new_has_two;
            d.has_forward=new_has_fwd; 
            d.has_backward=new_has_bwd; 
            d.last_diff = e[i]->difficulty;
            memcpy(d.idx, seq, d.len*sizeof(int));
            if (new_has_acro) 
                diaglist_push(out, d);
        } else {
            // Continua estensione della diagonale
            gen_diagonals_rec(e,n,DD,
                              pos+1, e[i]->end_dir,
                              seq, len+1,
                              new_diff, new_val,
                              new_has_acro, is_acro, new_has_two,
                              new_has_fwd, new_has_bwd,
                              out);
        }
    }
}

// Funzione Wrapper per generare tutte le diagonali
static void gen_diagonals(Elements **e, int n, int DD, DiagList *out){
    int seq[N_E_DIAG];
    gen_diagonals_rec(e,n,DD,0,1,seq,0,0,0.0f,0,0,0,0,0,out);
}

// Scelta della miglior terna di diagonali sotto DP e vincoli globali
// Vincoli globali:
// - almeno un acro avanti e almeno uno indietro nel programma
// - almeno una diagonale con due acrobatici consecutivi
// BONUS: 1.5x sull'ultima diagonale se l'ultimo elemento ha difficoltà >= 8
static void choose_best(const DiagList *dl, int DP,
                        float *best, int best_idx[N_DIAG]){
    *best = -1.0f;
    int idx[N_DIAG] = {-1,-1,-1};
    for (int i=0;i<dl->size;i++){
        for (int j=0;j<dl->size;j++){
            for (int k=0;k<dl->size;k++){
                int tot_diff = dl->arr[i].diff + dl->arr[j].diff + dl->arr[k].diff;
                if (tot_diff > DP) continue; // bound sulla difficoltà totale programma
                int has_fwd = dl->arr[i].has_forward || dl->arr[j].has_forward || dl->arr[k].has_forward;
                int has_bwd = dl->arr[i].has_backward || dl->arr[j].has_backward || dl->arr[k].has_backward;
                int has_two = dl->arr[i].has_two_acro_seq || dl->arr[j].has_two_acro_seq || dl->arr[k].has_two_acro_seq;
                if (!(has_fwd && has_bwd && has_two)) continue; // vincoli globali
                float val3 = dl->arr[k].val;
                if (dl->arr[k].last_diff >= 8) 
                    val3 *= 1.5f; // applica bonus all'ultima diagonale
                float tot_val = dl->arr[i].val + dl->arr[j].val + val3;
                if (tot_val > *best){ //Trovato nuovo best
                    *best = tot_val; 
                    idx[0]=i; 
                    idx[1]=j; 
                    idx[2]=k; 
                }
            }
        }
    }
    if (*best >= 0.0f){ 
        best_idx[0]=idx[0]; 
        best_idx[1]=idx[1]; 
        best_idx[2]=idx[2]; 
    }
}
