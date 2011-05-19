#include "glresource.h"

GLResource::GLResource()
{
    _id = 0;
}

GLResource::~GLResource()
{
}

GLResource::operator GLuint()
{
    return _id;
}

