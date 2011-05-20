#ifndef _GLRESOURCE_H
#define _GLRESOURCE_H

#include "opengl/opengl.h"
#include <string>

class GLResource
{
public:
    GLResource(const std::string& name_ = std::string());
    virtual ~GLResource();
    
    const std::string& name() const;
    
    operator GLuint();

protected:
    std::string _name;
    GLuint _id;
};

#endif  //_GLRESOURCE_H
