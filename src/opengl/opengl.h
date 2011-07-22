#ifndef _OPENGL_H
#define _OPENGL_H

#include <GL/gl.h>
#include <GL/glext.h>
#include "glcontext/glcontext.h"
#include "exception/exception.h"


#define OPENGL_NAMESPACE_BEGIN namespace GL{
#define OPENGL_NAMESPACE_END }


#include "functions.h"


OPENGL_NAMESPACE_BEGIN


template <class T>
bool getProcAddress(const char* name, T& proc, bool except = false) throw(Exception&)
{
    proc = reinterpret_cast<T>(GLContext::getProcAddress(name));
    if(proc == NULL){
        if(except == false) return false;
        throw(Exception(name));
    }
    return true;
}

bool isExtensionSupported(const char* name, bool except = false) throw(Exception&);


OPENGL_NAMESPACE_END


#endif  //_OPENGL_H
