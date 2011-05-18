#ifndef _X11_INPUT_H
#define _X11_INPUT_H

#include "osal/osdef.h"
#ifdef OS_LINUX

#include "input/input.h"

namespace input{

namespace mouse{

state_t* x11_state();
void x11_setpos(int x, int y);

}//mouse

}//input

#endif  //OS_LINUX

#endif  //_X11_INPUT_H
