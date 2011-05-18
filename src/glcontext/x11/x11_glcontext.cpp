#include "x11_glcontext.h"
#include "window/window.h"

#include "osal/osdef.h"


#ifdef OS_LINUX

#include "display/x11/x11_display.h"


#ifndef GL_CONTEXT_MAJOR_VERSION
#define GL_CONTEXT_MAJOR_VERSION 0x2091
#endif
#ifndef GL_CONTEXT_MINOR_VERSION
#define GL_CONTEXT_MINOR_VERSION 0x2092
#endif

PFNGLXCREATECONTEXTATTRIBSARBPROC X11GLContext::glXCreateContextAttribsARB = NULL;
PFNGLXGETFBCONFIGFROMVISUALSGIXPROC X11GLContext::glXGetFBConfigFromVisualSGIX = NULL;



X11GLContext::X11GLContext()
    :GLContext()
{
}

X11GLContext::~X11GLContext()
{
    if(_id != 0 && _not_destroy == false){
        glXDestroyContext(display::get_x11_display(), static_cast<GLXContext>(_id));
    }
}

GLContext* X11GLContext::create(const GLWindow* window_, const Version& version_)
{
    return create(window_, version_, NULL);
}

GLContext* X11GLContext::create(const GLWindow* window_, const Version& version_,
                              const GLContext* glcxt_)//not copy - share!
{
    GLXContext res_glcxt = 0;

    GLXContext origcxt = 0;
    Window origDrawWindow = 0;
    //winid_t origReadWindow = 0;
    Display* origDisplay = NULL;

    GLXContext tmpglcxt = 0;
    GLXContext shared = 0;
    
    XVisualInfo visualinfo = {0};
    GLXFBConfig fbconfig = NULL;
    XWindowAttributes winattribs = {0};

    Window window = window_->id();
    
    
    if(glcxt_ != NULL) shared = static_cast<GLXContext>(glcxt_->id());
    
    XGetWindowAttributes(display::get_x11_display(), window, &winattribs);
    
    visualinfo.visual = winattribs.visual;
    visualinfo.visualid = XVisualIDFromVisual(winattribs.visual);
    visualinfo.screen = XScreenNumberOfScreen(winattribs.screen);
    visualinfo.depth = winattribs.depth;

    //save current context state
    origcxt = glXGetCurrentContext();
    origDrawWindow = glXGetCurrentDrawable();
    //origReadWindow = glXGetCurrentReadDrawable();
    origDisplay = glXGetCurrentDisplay();
    
    
    //if need CreateContextAttribs
    if(version_.major > 2){
        //if current context == NULL
        if(origcxt == NULL){
            //create context
            tmpglcxt = glXCreateContext(display::get_x11_display(), &visualinfo, 0, True);
            if(tmpglcxt == 0){
                return NULL;
            }
            if(!glXMakeCurrent(display::get_x11_display(), window, tmpglcxt)){
                glXDestroyContext(display::get_x11_display(), tmpglcxt);
                return NULL;
            }
        }

        if(glXCreateContextAttribsARB == NULL){
            //get proc address
            if(NULL == (glXCreateContextAttribsARB =
                reinterpret_cast<PFNGLXCREATECONTEXTATTRIBSARBPROC>(
                    glXGetProcAddress(
                        reinterpret_cast<const GLubyte*>("glXCreateContextAttribsARB")
            )))){
                //OpenGL 3.0 is not supported
                glXMakeCurrent(display::get_x11_display(), origDrawWindow, origcxt);
                return NULL;
            }
        }
        
        if(glXGetFBConfigFromVisualSGIX == NULL){
            if(NULL == (glXGetFBConfigFromVisualSGIX =
                reinterpret_cast<PFNGLXGETFBCONFIGFROMVISUALSGIXPROC>(
                    glXGetProcAddress(
                        reinterpret_cast<const GLubyte*>("glXGetFBConfigFromVisualSGIX")
            )))){
                glXMakeCurrent(display::get_x11_display(), origDrawWindow, origcxt);
                return NULL;
            }
        }
        
        fbconfig = glXGetFBConfigFromVisualSGIX(display::get_x11_display(), &visualinfo);
        
        if(fbconfig == NULL){
            glXMakeCurrent(display::get_x11_display(), origDrawWindow, origcxt);
            return NULL;
        }

        int context_attribs[]={
            GL_CONTEXT_MAJOR_VERSION, version_.major,
            GL_CONTEXT_MINOR_VERSION, version_.minor,
            //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            None
        };

        //if tmpglcxt created
        if(tmpglcxt != 0){
            //destroy tmp context
            glXMakeCurrent(display::get_x11_display(), 0, 0);
            glXDestroyContext(display::get_x11_display(), tmpglcxt);
        }

        //create new, gl3 context
        res_glcxt = glXCreateContextAttribsARB(display::get_x11_display(),
                                fbconfig, shared, True, context_attribs);
        if(!res_glcxt){
            glXMakeCurrent(display::get_x11_display(), origDrawWindow, origcxt);
            return NULL;
        }
        //
    }else{
        //create context
        res_glcxt = glXCreateContext(display::get_x11_display(), &visualinfo, shared, True);
        if(res_glcxt == NULL){
            return NULL;
        }
    }

    glXMakeCurrent(display::get_x11_display(), origDrawWindow, origcxt);

    X11GLContext* res = new X11GLContext();
    res->_id = static_cast<glcontext_t>(res_glcxt);
    
    return res;
}

GLContext* X11GLContext::current()
{
    glcontext_t cur_glcxt = glXGetCurrentContext();
    if(cur_glcxt == 0) return NULL;
    
    X11GLContext* res = new X11GLContext();
    
    res->_id = cur_glcxt;
    res->_not_destroy = true;
    
    return res;
}

void X11GLContext::destroy(GLContext* glcxt_)
{
    delete glcxt_;
}

#endif  //OS_LINUX
