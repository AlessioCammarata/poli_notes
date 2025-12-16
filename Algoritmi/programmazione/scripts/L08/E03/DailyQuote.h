#ifndef DAILYQUOTE_H_DEFINED
#define DAILYQUOTE_H_DEFINED

#include "DateTime.h"

/*
Per la collezione di quotazioni si faccia uso di un BST (con data come chiave di ricerca e ordinamento). 
Per gli inserimenti di dati nel BST sono sufficienti gli inserimenti in foglia
*/
typedef struct DailyQuoteCollection_s *DailyQuoteCollection_t;
// Quasi ADT - Quota Giornaliera
typedef struct DailyQuote_s *DailyQuote_t;
struct DailyQuote_s{
    DateTime_t day;
    float WeightedSum;  // Value * Quantità Titoli
    float totTitles;     // Quantità Titoli
};

DailyQuoteCollection_t INITcollection();

//Calcola il valore effettivo ddella DailyQuote
float CalcDailyQuote(DailyQuote_t quote);
//Inserimento nell'albero delle DailyQuote
void insertQuoteInBST(DailyQuoteCollection_t DQ, DateTime_t day, float value, int quantity);
//Libera la collezione
void FREEcollection(DailyQuoteCollection_t DQ);

#endif // DAILYQUOTE_H_DEFINED