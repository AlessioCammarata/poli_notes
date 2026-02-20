#include <stdio.h>
#include <stdlib.h>

int disp(int pos,int *val,int *sol,int *mark, int n, int k,int cnt);
int disp_rep(int pos,int *val,int *sol, int n, int k,int cnt);
int perm(int pos, int *val, int *sol, int *mark, int n, int cnt);
int perm_rep(int pos, int *dist_val, int *val, int *sol, int *mark, int n, int n_dist, int cnt);
int comb(int pos, int *val, int *sol, int n, int k, int start, int cnt);
int comb_rep(int pos, int *val, int *sol, int n, int k, int start, int cnt);

int main(void){
    //Settings
    int n = 4, k = 2;
    int rep = 1;
    int chose = 0;
    int cnt = 0;

    int *val = malloc(n * sizeof(int));
    int *sol = malloc(k * sizeof(int));

    for(int i = 0; i<n; i++){
        // if(i != 2)
            val[i] = i;
        // else 
        //     val[i] = 1;
    }
    for(int i = 0; i<n; i++) printf("%d ", val[i]);
    printf("\n");
    int *mark = calloc(n, sizeof(int));


    printf("Inserisci il tipo di ricerca che vuoi fare\n");
    scanf("%d",&chose);

    switch (chose)
    {
    case 0:
        
        if(rep) cnt = disp_rep(0, val, sol, n, k, 0);
        else cnt = disp(0, val, sol, mark, n, k, 0);
        printf("Il numero di disposizioni %s è: %d\n", rep ? "ripetute" : "semplici",cnt);
        break;
    case 1:
        if(rep){
            int *dist_values = malloc(n*sizeof(int));
            int c = 0, flag = 0;
            for(int i = 0; i<n; i++){
                for(int j=i+1; j<n; j++)
                    if(val[i] == val[j])
                        flag++;
                
                if (!flag) dist_values[c++] = val[i];
                else mark[c]++;
                mark[i]++;
                flag = 0;
            }
            cnt = perm_rep(0, dist_values, val, sol, mark, n, c, 0);
        }else cnt = perm(0, val, sol, mark, n, 0);
        printf("Il numero di permutazioni %s è: %d\n", rep ? "ripetute" : "semplici",cnt);
        break;
    case 2:
        if(rep) cnt = comb_rep(0, val, sol, n, k, 0, 0);
        else cnt = comb(0, val, sol, n, k, 0, 0);
        printf("Il numero di combinazioni %s è: %d\n", rep ? "ripetute" : "semplici",cnt);
        break;
    default:
        break;
    }   
}


int disp(int pos,int *val,int *sol,int *mark, int n, int k, int cnt){
	int i; 
	if (pos >= k){ // Condizione di terminazione
		for (i=0; i<k; i++) 
            printf("%d ", sol[i]); 
		printf("\n"); 
		return cnt+1; 
	} 
	for (i=0; i<n; i++){ // iterazione sulle n scelte
		if (mark[i] == 0) { // Controllo ripetizione
			mark[i] = 1; //marcamento e scelta
			sol[pos] = val[i]; 
			cnt = disp(pos+1, val, sol, mark, n, k,cnt); //Ricorsione
			mark[i] = 0; //Smarcamento
		} 
	} 
	return cnt; 
}


int disp_rep(int pos,int *val,int *sol, int n, int k, int cnt){
	int i; 
	if (pos >= k){ // Condizione di terminazione
		for (i=0; i<k; i++) 
            printf("%d ", sol[i]); 
		printf("\n"); 
		return cnt+1; 
	} 
	for (i=0; i<n; i++){ // iterazione sulle n scelte
        sol[pos] = val[i]; 
        cnt = disp_rep(pos+1, val, sol, n, k,cnt); //Ricorsione
	} 
	return cnt; 
}

int perm(int pos, int *val, int *sol, int *mark, int n, int cnt){
    int i;
    if(pos >= n){
        for (i=0; i<n; i++) 
            printf("%d ", sol[i]); 
		printf("\n"); 
		return cnt+1; 
    }

    for(i = 0; i<n; i++){
        if(!mark[i]){
            sol[pos] = val[i];
            mark[i] = 1;
            cnt = perm(pos+1, val, sol, mark, n, cnt);
            mark[i] = 0;
        }
    }

    return cnt;
}

int perm_rep(int pos, int *dist_val, int *val, int *sol, int *mark, int n, int n_dist, int cnt){
    int i;
    if(pos >= n){
        for (i=0; i<n; i++) 
            printf("%d ", sol[i]); 
		printf("\n"); 
		return cnt+1; 
    }

    for(i = 0; i<n_dist; i++){
        if(mark[i] > 0){
            sol[pos] = dist_val[i];
            mark[i]--;
            cnt = perm_rep(pos+1, dist_val, val, sol, mark, n, n_dist, cnt);
            mark[i]++;
        }
    }

    return cnt;
}

int comb(int pos, int *val, int *sol, int n, int k, int start, int cnt){
    int i;
    if(pos >= k){
        for (i=0; i<k; i++) 
            printf("%d ", sol[i]); 
		printf("\n"); 
		return cnt+1;
    }

    for(i = start; i<n; i++){
        sol[pos] = val[i];
        cnt = comb(pos+1, val, sol, n, k, i+1, cnt);
    }

    return cnt;
}

int comb_rep(int pos, int *val, int *sol, int n, int k, int start, int cnt){
    int i;
    if(pos >= k){
        for (i=0; i<k; i++) 
            printf("%d ", sol[i]); 
		printf("\n"); 
		return cnt+1;
    }

    for(i = start; i<n; i++){
        sol[pos] = val[i];
        cnt = comb(pos+1, val, sol, n, k, i, cnt);
    }

    return cnt;
}