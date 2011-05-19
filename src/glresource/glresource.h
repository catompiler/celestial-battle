#ifndef _GLRESOURCE_H
#define _GLRESOURCE_H

#include "opengl/opengl.h"

class GLResource
{
public:
    GLResource();
    virtual ~GLResource();
    
    operator GLuint();

protected:
    GLuint _id;
};

#endif  //_GLRESOURCE_H
