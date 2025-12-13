#include "DateTime.h"

//Funzione che serve per mettere le quote nel BST
int cmpDate(DateTime_t d1, DateTime_t d2){
    if(d1->year > d2->year) return 1;
    else if(d1->year < d2->year) return -1;

    if(d1->month > d2->month) return 1;
    else if(d1->month < d2->month) return -1;

    if(d1->day > d2->day) return 1;
    else if(d1->day < d2->day) return -1;

    return 0;
}