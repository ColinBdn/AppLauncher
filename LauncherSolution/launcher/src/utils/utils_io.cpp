#include "utils_io.h"

#define NOMINMAX
#include <Windows.h>


void clearConsoleInputBuffer()
{
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD numEvents;
    INPUT_RECORD* buffer;
    GetNumberOfConsoleInputEvents(handle, &numEvents);
    buffer = new INPUT_RECORD[numEvents];
    ReadConsoleInput(handle, buffer, numEvents, &numEvents);
    delete[] buffer;
}
