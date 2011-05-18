#ifndef _WIN_DISPLAY_H
#define _WIN_DISPLAY_H

#include "osal/osdef.h"
#ifdef OS_WINDOWS

namespace display{

int win_width();
int win_height();

}//display

#endif //OS_WINDOWS

#endif  //_WIN_DISPLAY_H
