#ifndef _X11_DISPLAY_H
#define _X11_DISPLAY_H

#include "osal/osdef.h"
#ifdef OS_LINUX

#include <X11/Xlib.h>

namespace display{

Display* get_x11_display(); //get x11 display


int x11_width();
int x11_height();

}//display

#endif  //OS_LINUX

#endif  //_X11_DISPLAY_H
