#ifndef _WINDOW_TYPES_H
#define _WINDOW_TYPES_H

#include "osal/osdef.h"

#ifdef OS_WINDOWS
#include "win/win_window_types.h"
#endif

#ifdef OS_LINUX
#include "x11/x11_window_types.h"
#endif

#endif  //_WINDOW_TYPES_H
