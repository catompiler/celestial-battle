#ifndef _WINDOWS_WINDOW_TYPES_H
#define _WINDOWS_WINDOW_TYPES_H

#include <windows.h>
//fucking windows with fucking defines like "#define Foo FooA"
#undef CreateEvent

typedef HWND windowid_t;

#endif
