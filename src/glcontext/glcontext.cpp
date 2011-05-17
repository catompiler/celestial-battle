#include "glcontext.h"

GLContext::GLContext()
{
    _id = 0;
}

GLContext::~GLContext()
{
}

glcontext_t GLContext::id()
{
    return _id;
}

