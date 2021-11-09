#ifdef _WIN32
#include <windows.h>
#endif // Win 32

#include <iostream>

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif // WIN 32

    return 0;
}