#include <windows.h>

int Display::width()
{
    return GetSystemMetrics(SM_CXSCREEN);
}

int Display::height()
{
    return GetSystemMetrics(SM_CYSCREEN);
}


