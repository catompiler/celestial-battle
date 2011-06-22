#include "glcontext.h"

#include "osal/osdef.h"
#include PLATFORM_FILE(WINDOW_SYSTEM, glcontext.cpp)


glcontext_t GLContext::id() const
{
    return _id;
}
