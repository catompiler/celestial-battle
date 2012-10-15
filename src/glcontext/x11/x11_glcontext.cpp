#include "display/display.h"
#include "window/window.h"
#include "x11_glcontext_types.h"

#ifndef GL_CONTEXT_MAJOR_VERSION
#define GL_CONTEXT_MAJOR_VERSION 0x2091
#endif
#ifndef GL_CONTEXT_MINOR_VERSION
#define GL_CONTEXT_MINOR_VERSION 0x2092
#endif

static PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = NULL;
static PFNGLXGETFBCONFIGFROMVISUALSGIXPROC glXGetFBConfigFromVisualSGIX = NULL;


GLContext::GLContext()
{
    _shared_id = new SharedId();
}


GLContext::~GLContext()
{
    destroy();
    delete _shared_id;
}


bool GLContext::create(const Window* window_, const Version& version_)
{
    return create(window_, version_, NULL);
}


bool GLContext::create(const Window* window_, const Version& version_,
                              const GLContext* glcxt_)//not copy - share!
{
    glcontext_t res_glcxt = 0;


    glcontext_t origcxt = 0;
    XWindow origDrawWindow = 0;
    //winid_t origReadWindow = 0;
    XDisplay* origDisplay = nullptr;


    glcontext_t tmpglcxt = 0;
    glcontext_t shared = 0;
    
    XVisualInfo visualinfo = {0};
    GLXFBConfig fbconfig = nullptr;
    XWindowAttributes winattribs = {0};


    XWindow window = window_->id();
    
    
    if(glcxt_ != NULL) shared = glcxt_->id();
    
    XGetWindowAttributes(Display::display(), window, &winattribs);
    
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
        if(origcxt == 0){
            //create context
            tmpglcxt = glXCreateContext(Display::display(), &visualinfo, 0, True);
            if(tmpglcxt == 0){
                return false;
            }
            if(!glXMakeCurrent(Display::display(), window, tmpglcxt)){
                glXDestroyContext(Display::display(), tmpglcxt);
                return false;
            }
        }


        if(glXCreateContextAttribsARB == nullptr){
            //get proc address
            if(nullptr == (glXCreateContextAttribsARB =
                reinterpret_cast<PFNGLXCREATECONTEXTATTRIBSARBPROC>(
                    glXGetProcAddress(
                        reinterpret_cast<const GLubyte*>("glXCreateContextAttribsARB")
            )))){
                //OpenGL 3.0 is not supported
                glXMakeCurrent(origDisplay, origDrawWindow, origcxt);
                return false;
            }
        }
        
        if(glXGetFBConfigFromVisualSGIX == nullptr){
            if(NULL == (glXGetFBConfigFromVisualSGIX =
                reinterpret_cast<PFNGLXGETFBCONFIGFROMVISUALSGIXPROC>(
                    glXGetProcAddress(
                        reinterpret_cast<const GLubyte*>("glXGetFBConfigFromVisualSGIX")
            )))){
                glXMakeCurrent(Display::display(), origDrawWindow, origcxt);
                return false;
            }
        }
        
        fbconfig = glXGetFBConfigFromVisualSGIX(Display::display(), &visualinfo);
        
        if(fbconfig == nullptr){
            glXMakeCurrent(Display::display(), origDrawWindow, origcxt);
            return false;
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
            glXMakeCurrent(Display::display(), 0, 0);
            glXDestroyContext(Display::display(), tmpglcxt);
        }


        //create new, gl3 context
        res_glcxt = glXCreateContextAttribsARB(Display::display(),
                                fbconfig, shared, True, context_attribs);
        if(!res_glcxt){
            glXMakeCurrent(Display::display(), origDrawWindow, origcxt);
            return false;
        }
        //
    }else{
        //create context
        res_glcxt = glXCreateContext(Display::display(), &visualinfo, shared, True);
        if(res_glcxt == nullptr){
            return false;
        }
    }


    glXMakeCurrent(Display::display(), origDrawWindow, origcxt);

    _shared_id->data = res_glcxt;
    _contexts[_shared_id->data] = this;
    
    return true;
}


GLContext GLContext::current()
{
    glcontext_t cur_glcxt = glXGetCurrentContext();
    if(cur_glcxt == 0) return GLContext();
    
    GLContext* res_cxt = nullptr;
    
    Contexts::iterator it = _contexts.find(cur_glcxt);
    if(it != _contexts.end()){
        res_cxt = (*it).second;
        res_cxt->_shared_id->acquire();
    }else{
        res_cxt = new GLContext();
        res_cxt->_shared_id->data = cur_glcxt;
        _contexts[res_cxt->_shared_id->data] = res_cxt;
    }
    
    return *res_cxt;
}


void GLContext::destroy()
{
    if(_shared_id->release()){
        _contexts.erase(_shared_id->data);
        glXDestroyContext(Display::display(), _shared_id->data);
        delete _shared_id;
    }
    _shared_id = new SharedId();
}


void (*GLContext::getProcAddress(const char* procname_))()
{
    return glXGetProcAddress(reinterpret_cast<const GLubyte*>(procname_));
} 
