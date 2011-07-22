#include <string>
#include "glresource.h"


OPENGL_NAMESPACE_BEGIN


Resource::Resource()
{
    _id = 0;
}

Resource::Resource(GLuint id_)
{
    _id = id_;
}

Resource::~Resource()
{
}

GLuint Resource::id()
{
    return _id;
}

Resource::operator GLuint()
{
    return _id;
}

OPENGL_NAMESPACE_END
