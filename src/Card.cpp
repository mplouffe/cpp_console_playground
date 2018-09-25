#include <Card.h>
#include <iostream>

// Use to display each individual card
void Card::DisplayCard(HANDLE hStdOut, COORD currentCoOrds) const
{
    short currentColumn = currentCoOrds.X;
    short currentRow = currentCoOrds.Y;

    SetConsoleCursorPosition(hStdOut, currentCoOrds);
    std::cout << "*-----------*";
    for(int i = 0; i < 6; i += 1) {
        currentRow += 1;
        SetConsoleCursorPosition(hStdOut, {currentColumn, currentRow});
        std::cout << "|           |";
    }
    currentRow += 1;
    SetConsoleCursorPosition(hStdOut, {currentColumn, currentRow});
    std::cout << "*-----------*";
}