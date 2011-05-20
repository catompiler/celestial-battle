#include <string>

#include "glresource.h"

GLResource::GLResource(const std::string& name_)
{
    _name = name_;
    _id = 0;
}

GLResource::~GLResource()
{
}

const std::string& GLResource::name() const
{
    return _name;
}

GLResource::operator GLuint()
{
    return _id;
}

