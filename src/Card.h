#include <windows.h>
#include <iostream>

class Card {
    public:
        Card();
        ~Card();
        void DisplayCard(HANDLE hStdOut, COORD currentCoOrds) const;
}