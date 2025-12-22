#ifndef DAILYQUOTE_H_DEFINED
#define DAILYQUOTE_H_DEFINED

#include "DateTime.h"

/*
Per la collezione di quotazioni si faccia uso di un BST (con data come chiave di ricerca e ordinamento). 
Per gli inserimenti di dati nel BST sono sufficienti gli inserimenti in foglia
*/
typedef struct BSTnode *link;
typedef struct DailyQuoteCollection_s *DailyQuoteCollection_t;
// Quasi ADT - Quota Giornaliera
typedef struct DailyQuote_s *DailyQuote_t;
struct DailyQuote_s{
    DateTime_t day;
    float WeightedSum;  // Value * Quantità Titoli
    int totTitles;     // Quantità Titoli
};

DailyQuoteCollection_t INITcollection();

//Calcola il valore effettivo ddella DailyQuote
float CalcDailyQuote(DailyQuote_t quote);
//Inserimento nell'albero delle DailyQuote
void insertQuoteInBST(DailyQuoteCollection_t DQ, DateTime_t day, float value, int quantity);
//Libera la collezione
void FREEcollection(DailyQuoteCollection_t DQ);

void printDQ(DailyQuoteCollection_t DQ);
//Trova la DQ dalla data
link findDQfromDate(DailyQuoteCollection_t DQ, DateTime_t date);
float getDQvalue(DailyQuoteCollection_t DQ, DateTime_t date);

//Intervallo
static void recursiveMINMAX(link x, link z, DateTime_t start, DateTime_t end, float *min, float *max);
void getDQvalueInterval(DailyQuoteCollection_t DQ, DateTime_t date1, DateTime_t date2, float *min, float *max); //Wrapper

//Bilanciamento
void balanceBST(DailyQuoteCollection_t DQ, int threshold);

#endif // DAILYQUOTE_H_DEFINED