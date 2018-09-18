#include <iostream>
#include <windows.h>

void ClearScreen();
void DisplayDataSizes();

int main()
{
    char response;
    DisplayCard();
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

void DisplayBoard()
{
    HANDLE              hStdOut;
    COORD               currentCoOrds = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;


}

void DisplayCard(HANDLE hStdOut, COORD currentCoOrds)
{
    int currentColumn = currentCoOrds.Y + 2;
    int currentRow = currentCoOrds.X + 2;

    SetConsoleCursorPosition(hStdOut, currentCoOrds);
    for(int i = 0; i < 7; i += 1) {
        std::cout << "*";
    }

    currentCoOrds = {currentColumn, currentRow};
    SetConsoleCursorPosition(hStdOut, currentCoOrds);
    for(int i = 0; i < 7; i += 1) {
        std::cout << "*";
    }
}