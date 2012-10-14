#include "opengl.h"
#include <string.h>



OPENGL_NAMESPACE_BEGIN


static bool isExtensionSupported_impl_2(const char* name, bool except) throw(Exception&)
{
    static const char *exts = 0;
    if(exts == 0) exts = reinterpret_cast<const char*>(GL::glGetString(GL_EXTENSIONS));

    int len = strlen(name);
    const char *ext = strstr(exts, name);

    while(ext){
        if(ext[len] == ' ' || ext[len] == '\0') return true;
        ext = strstr(ext + 1, name);
    }

    if(except == true) throw (Exception(name));
    
    return false;
}

static bool isExtensionSupported_impl_3(const char* name, bool except) throw(Exception&)
{
    GLint count = 0;
    GL::glGetIntegerv(GL_NUM_EXTENSIONS, &count);
    for(GLint i = 0; i < count; i ++){
        if(strcmp(reinterpret_cast<const char*>(
                        GL::glGetStringi(GL_EXTENSIONS, i)
                  ), name) == 0){
            return true;
        }
    }
    
    if(except == true) throw (Exception(name));
    
    return false;
}

bool isExtensionSupported(const char* name, bool except) throw(Exception&)
{
    if(GL::glGetStringi != nullptr) return isExtensionSupported_impl_3(name, except);
    return isExtensionSupported_impl_2(name, except);
}


OPENGL_NAMESPACE_END

