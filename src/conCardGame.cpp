#include <iostream>
#include <windows.h>
#include <Card.h>

void ClearScreen();
void DisplayBoard(Card[]);

int main()
{
    char response;
    Card[9] deck;
    for(int i=0; i<9; i++){
        deck[i] = Card();
    }
    DisplayBoard(deck);
    std::cin >> response;
    return 0;
}



void ClearScreen()
{
    HANDLE                      hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO  csbi;
    DWORD                       count;
    DWORD                       cellCount;
    COORD                       homeCoords = {0,0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;
    
    /* Get the number of cells in the current Buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}

// Use to display all the current cards on the board (3x3 grid)
void DisplayBoard(Card[] deck)
{
    HANDLE              hStdOut;
    COORD               currentCoOrds = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    short cardWidth = 14;
    short cardHeight = 8;

    for(int i = 0; i < 3; i += 1) {
        for(int j =0; j < 3; j += 1) {
            deck[i+j].DisplayCard(hStdOut, currentCoOrds);
            currentCoOrds = {currentCoOrds.X + cardWidth, currentCoOrds.Y};
        }
        currentCoOrds = {0, currentCoOrds.Y + cardHeight};
    }

    std::cout << std::endl;
}

