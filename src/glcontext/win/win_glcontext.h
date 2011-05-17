#ifndef _WIN_GLCONTEXT_H
#define _WIN_GLCONTEXT_H

#include "osal/osdef.h"

#ifdef OS_WINDOWS

#include "glcontext/glcontext.h"
#include "win_glcontext_types.h"

class WGLContext
    :public GLContext
{
public:
    ~WGLContext();

    static GLContext* create(const GLWindow* window_, const Version& version_);
    static GLContext* create(const GLWindow* window_, const Version& version_,
                             const GLContext* glcxt_);//not copy - share!
    static GLContext* current();
    static void destroy(GLContext* glcxt_);

protected:
    WGLContext();

    typedef glcontext_t (*wglCreateContextAttribsARBProc)(void*, glcontext_t, const int *);
    static wglCreateContextAttribsARBProc wglCreateContextAttribsARB;
};

#endif  //OS_WINDOWS

#endif	/* _WIN_GLCONTEXT_H */

