#include "input.h"

#include "osal/osdef.h"
#ifdef OS_WINDOWS
#include "win/win_input.h"
#elif defined OS_LINUX
#include "x11/x11_input.h"
#endif

namespace input{

namespace mouse{

state_t* state()
{
    return 
    #ifdef OS_WINDOWS
        win_state()
    #elif defined OS_LINUX
        x11_state()
    #else
        NULL
    #endif
    ;//return
}

void setpos(int x, int y)
{
    #ifdef OS_WINDOWS
        win_setpos(x, y);
    #elif defined OS_LINUX
        x11_setpos(x, y);
    #endif
}

}//mouse

}//input
