#ifndef TITLS_H_DEFINED
#define TITLS_H_DEFINED

#define NMAX 21 //20 + 1

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
DailyQuoteCollection_t getCollection(Title_t TC);

#endif // TITLS_H_DEFINED