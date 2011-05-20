#ifndef _OPENGL_H
#define _OPENGL_H

#include <GL/gl.h>
#include <GL/glext.h>
#include "glcontext/glcontext.h"
#include "exception/exception.h"



template <class T> bool getGLProcAddress(const char* name, T& proc, bool except = false) throw(Exception&)
{
    proc = reinterpret_cast<T>(GLContext::getProcAddress(name));
    if(proc == NULL){
        if(except == false) return false;
        throw(Exception(name));
    }
    return true;
}

bool isGLExtensionSupported(const char* name, bool except = false) throw(Exception&);

#endif  //_OPENGL_H
