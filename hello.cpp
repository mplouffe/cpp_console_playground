#include <iostream>
#include <windows.h>

void ClearScreen();
void DisplayDataSizes();
void DisplayCard(HANDLE hStdOut, COORD currentCoOrds);
void DisplayBoard();

int main()
{
    char response;
    DisplayBoard();
    std::cin >> response;
    return 0;
}

// Just curious about the datasizes on this system
void DisplayDataSizes()
{
    std::cout << "The size of an int is:\t\t"
        << sizeof(int) << " bytes." << std::endl;
    std::cout << "The size of a short int is:\t"
        << sizeof(short) << " bytes." << std::endl;
    std::cout << "The size of a long int is:\t"
        << sizeof(long) << " bytes." << std::endl;
    std::cout << "The size of a char is:\t\t"
        << sizeof(char) << " bytes." << std::endl;
    std::cout << "The size of a float is:\t\t"
        << sizeof(float) << " bytes." << std::endl;
    std::cout << "The size of a double is:\t"
        << sizeof(double) << " bytes." << std::endl;
    std::cout << "The size of a bool is:\t\t"
        << sizeof(bool) << " bytes." << std::endl;
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
void DisplayBoard()
{
    HANDLE              hStdOut;
    COORD               currentCoOrds = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    short cardWidth = 14;
    short cardHeight = 8;

    for(int i = 0; i < 3; i += 1) {
        for(int j =0; j < 3; j += 1) {
            DisplayCard(hStdOut, currentCoOrds);
            currentCoOrds = {currentCoOrds.X + cardWidth, currentCoOrds.Y};
        }
        currentCoOrds = {0, currentCoOrds.Y + cardHeight};
    }

    std::cout << std::endl;
}

// Use to display each individual card
void DisplayCard(HANDLE hStdOut, COORD currentCoOrds)
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