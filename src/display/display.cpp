#include "display.h"

#include "osal/osdef.h"
#ifdef OS_WINDOWS
#include "win/win_display.h"
#else
#ifdef OS_LINUX
#include "x11/x11_display.h"
#else
#endif  //OS_LINUX
#endif  //OS_WINDOWS

namespace display{

int width()
{
    return 
    #ifdef OS_WINDOWS
        win_width()
    #else
    #ifdef OS_LINUX
        x11_width()
    #else
        0
    #endif  //OS_LINUX
    #endif  //OS_WINDOWS
    ;//return
}

int height()
{
    return 
    #ifdef OS_WINDOWS
        win_height()
    #else
    #ifdef OS_LINUX
        x11_height()
    #else
        0
    #endif  //OS_LINUX
    #endif  //OS_WINDOWS
    ;//return
}

}//display
