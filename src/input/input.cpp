#include "input.h"

#include "osal/osdef.h"
#ifdef OS_WINDOWS
#include "win/win_input.h"
#else
#ifdef OS_LINUX
#include "x11/x11_input.h"
#else
#endif  //OS_LINUX
#endif  //OS_WINDOWS

namespace input{

namespace mouse{

state_t* state()
{
    return 
    #ifdef OS_WINDOWS
        win_state()
    #else
    #ifdef OS_LINUX
        x11_state()
    #else
        NULL
    #endif  //OS_LINUX
    #endif  //OS_WINDOWS
    ;//return
}

void setpos(int x, int y)
{
    #ifdef OS_WINDOWS
        win_setpos(x, y);
    #else
    #ifdef OS_LINUX
        x11_setpos(x, y);
    #else
    #endif  //OS_LINUX
    #endif  //OS_WINDOWS
}

}//mouse

}//input
