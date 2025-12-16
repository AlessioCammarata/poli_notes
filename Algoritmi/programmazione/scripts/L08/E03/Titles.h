#ifndef TITLS_H_DEFINED
#define TITLS_H_DEFINED

#define NMAX 21 //20 + 1

#include "DateTime.h"
#include "DailyQuote.h"
#include <stdio.h>
#include <string.h>

// ADT I classe - Titolo
typedef struct Title_s *Title_t;
// ADT I classe - Collezione di titoli
/*
Per la collezione di titoli si faccia uso di una lista ordinata 
(si usi il codice del titolo comechiave di ordinamento).
*/
typedef struct TitleCollection_s *TitleCollection_t;

TitleCollection_t INITlist();
Title_t searchTitle(TitleCollection_t TC, char *title);
//Aggiungo un titolo alla lista
Title_t addTitle(TitleCollection_t TC, char *title);
//Ottengo le DailyQuote
DailyQuoteCollection_t getCollection(Title_t title);
//LIbera tutta la lista
void freeTC(TitleCollection_t TC);

#endif // TITLS_H_DEFINED