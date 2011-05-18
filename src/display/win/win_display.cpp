#include "win_display.h"
#include <windows.h>

namespace display{

int win_width()
{
    return GetSystemMetrics(SM_CXSCREEN);
}

int win_height()
{
    return GetSystemMetrics(SM_CYSCREEN);
}

}//display
