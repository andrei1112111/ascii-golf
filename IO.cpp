#include "IO.h"

#include <iostream>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

char getCharNonBlocking()
{
#ifdef _WIN32
    if (_kbhit())
    {
        return _getch();
    }
    return '\0';
#else
    struct termios oldt{}, newt{};
    char ch = '\0';

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO); // turn on canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    if (read(STDIN_FILENO, &ch, 1) < 0)
    {
        ch = '\0';
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return ch;
#endif
}
