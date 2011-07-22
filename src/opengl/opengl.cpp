#include "opengl.h"
#include <string.h>



OPENGL_NAMESPACE_BEGIN


bool isExtensionSupported(const char* name, bool except) throw(Exception&)
{
    static char *exts = 0;
    if(exts == 0) exts = (char*)glGetString(GL_EXTENSIONS);

    int len = strlen(name);
    char *ext = strstr(exts, name);

    while(ext){
        if(ext[len] == ' ' || ext[len] == '\0') return true;
        ext = strstr(ext + 1, name);
    }

    if(except == true) throw (Exception(name));
    
    return false;
}


OPENGL_NAMESPACE_END

