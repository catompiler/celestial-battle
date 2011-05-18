#ifndef _WIN_INPUT_H
#define _WIN_INPUT_H

#include "input/input.h"


#include "osal/osdef.h"
#ifdef OS_WINDOWS

namespace input{

namespace mouse{

state_t* win_state();
void win_setpos(int x, int y);

}//mouse

}//input

#endif  //OS_WINDOWS

#endif  //_WIN_INPUT_H
