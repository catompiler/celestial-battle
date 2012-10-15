#include "glcontext.h"

#include "osal/osdef.h"
#include PLATFORM_FILE(WINDOW_SYSTEM, glcontext.cpp)

GLContext::Contexts GLContext::_contexts;

glcontext_t GLContext::id() const
{
    return _shared_id->data;
}

bool GLContext::valid() const
{
    return _shared_id->data != 0;
}
