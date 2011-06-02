#include "display.h"

#include "osal/osdef.h"
#ifdef OS_WINDOWS
#include "win/win_display.h"
#elif defined OS_LINUX
#include "x11/x11_display.h"
#endif

namespace display{

int width()
{
    return 
    #ifdef OS_WINDOWS
        win_width()
    #elif defined OS_LINUX
        x11_width()
    #else
        0
    #endif
    ;//return
}

int height()
{
    return 
    #ifdef OS_WINDOWS
        win_height()
    #elif defined OS_LINUX
        x11_height()
    #else
        0
    #endif
    ;//return
}

}//display
