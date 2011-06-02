#ifndef _GLCONTEXT_TYPES_H
#define _GLCONTEXT_TYPES_H

#include "osal/osdef.h"

#ifdef OS_WINDOWS
#include "win/win_glcontext_types.h"
#elif defined OS_LINUX
#include "x11/x11_glcontext_types.h"
#endif

#endif  //_GLCONTEXT_TYPES_H
