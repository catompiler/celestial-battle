#include "glcontext.h"
#include "window/window.h"

#include "osal/osdef.h"

#ifdef OS_WINDOWS
    #include "win/win_glcontext.h"
#endif

#ifdef OS_LINUX
    #include "x11/x11_glcontext.h"
#endif

GLContext::GLContext()
{
    _id = 0;
    _not_destroy = false;
}

GLContext::~GLContext()
{
}

glcontext_t GLContext::id() const
{
    return _id;
}

GLContext* GLContext::create(const GLWindow* window_, const Version& version_)
{
    return
#ifdef OS_WINDOWS
    WGLContext::create(window_, version_)
#else
#ifdef OS_LINUX
    X11GLContext::create(window_, version_)
#else
    NULL
#endif
#endif
    ;//return
}

GLContext* GLContext::create(const GLWindow* window_, const Version& version_,
                             const GLContext* glcxt_)//not copy - share!
{
    return
#ifdef OS_WINDOWS
    WGLContext::create(window_, version_, glcxt_)
#else
#ifdef OS_LINUX
    X11GLContext::create(window_, version_, glcxt_)
#else
    NULL
#endif
#endif
    ;//return
}

GLContext* GLContext::current()
{
    return
#ifdef OS_WINDOWS
    WGLContext::current()
#else
#ifdef OS_LINUX
    X11GLContext::current()
#else
    NULL
#endif
#endif
    ;//return
}

void GLContext::destroy(GLContext* glcxt_)
{
#ifdef OS_WINDOWS
    WGLContext::destroy(glcxt_);
#else
#ifdef OS_LINUX
    X11GLContext::destroy(glcxt_);
#else
#endif
#endif
}

void (*GLContext::getProcAddress(const char* procname_))()
{
    return
#ifdef OS_WINDOWS
    WGLContext::getProcAddress(procname_)
#else
#ifdef OS_LINUX
    X11GLContext::getProcAddress(procname_)
#else
    NULL
#endif
#endif
    ;//return
}

