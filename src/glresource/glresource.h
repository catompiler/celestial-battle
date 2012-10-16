#ifndef _GLRESOURCE_H
#define _GLRESOURCE_H

#include "opengl/opengl.h"


OPENGL_NAMESPACE_BEGIN

class Resource
{
public:
    Resource();
    Resource(GLuint id_);
    virtual ~Resource();
    
    GLuint id();
    operator GLuint();

protected:
    GLuint _id;
};

OPENGL_NAMESPACE_END

#endif  //_GLRESOURCE_H
