#ifndef _X11_GLCONTEXT_H
#define _X11_GLCONTEXT_H

#include "osal/osdef.h"

#ifdef OS_LINUX

#include "glcontext/glcontext.h"
#include "x11_glcontext_types.h"

#include <GL/glx.h>
#include <GL/glxext.h>


class X11GLContext
    :public GLContext
{
public:
    ~X11GLContext();

    static GLContext* create(const GLWindow* window_, const Version& version_);
    static GLContext* create(const GLWindow* window_, const Version& version_,
                             const GLContext* glcxt_);//not copy - share!
    static GLContext* current();
    static void destroy(GLContext* glcxt_);

protected:
    X11GLContext();

    static PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
    static PFNGLXGETFBCONFIGFROMVISUALSGIXPROC glXGetFBConfigFromVisualSGIX;
};

#endif  //OS_LINUX

#endif	/* _X11_GLCONTEXT_H */

