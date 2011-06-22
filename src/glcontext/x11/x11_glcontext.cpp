#include "display/display.h"
#include "window/window.h"

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
    _id = 0;
    _not_destroy = false;
}


GLContext::~GLContext()
{
    if(_id != 0 && _not_destroy == false){
        glXDestroyContext(Display::display(), _id);
    }
}


GLContext* GLContext::create(const Window* window_, const Version& version_)
{
    return create(window_, version_, NULL);
}


GLContext* GLContext::create(const Window* window_, const Version& version_,
                              const GLContext* glcxt_)//not copy - share!
{
    glcontext_t res_glcxt = 0;


    glcontext_t origcxt = 0;
    XWindow origDrawWindow = 0;
    //winid_t origReadWindow = 0;
    XDisplay* origDisplay = NULL;


    glcontext_t tmpglcxt = 0;
    glcontext_t shared = 0;
    
    XVisualInfo visualinfo = {0};
    GLXFBConfig fbconfig = NULL;
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
        if(origcxt == NULL){
            //create context
            tmpglcxt = glXCreateContext(Display::display(), &visualinfo, 0, True);
            if(tmpglcxt == 0){
                return NULL;
            }
            if(!glXMakeCurrent(Display::display(), window, tmpglcxt)){
                glXDestroyContext(Display::display(), tmpglcxt);
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
                glXMakeCurrent(Display::display(), origDrawWindow, origcxt);
                return NULL;
            }
        }
        
        if(glXGetFBConfigFromVisualSGIX == NULL){
            if(NULL == (glXGetFBConfigFromVisualSGIX =
                reinterpret_cast<PFNGLXGETFBCONFIGFROMVISUALSGIXPROC>(
                    glXGetProcAddress(
                        reinterpret_cast<const GLubyte*>("glXGetFBConfigFromVisualSGIX")
            )))){
                glXMakeCurrent(Display::display(), origDrawWindow, origcxt);
                return NULL;
            }
        }
        
        fbconfig = glXGetFBConfigFromVisualSGIX(Display::display(), &visualinfo);
        
        if(fbconfig == NULL){
            glXMakeCurrent(Display::display(), origDrawWindow, origcxt);
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
            glXMakeCurrent(Display::display(), 0, 0);
            glXDestroyContext(Display::display(), tmpglcxt);
        }


        //create new, gl3 context
        res_glcxt = glXCreateContextAttribsARB(Display::display(),
                                fbconfig, shared, True, context_attribs);
        if(!res_glcxt){
            glXMakeCurrent(Display::display(), origDrawWindow, origcxt);
            return NULL;
        }
        //
    }else{
        //create context
        res_glcxt = glXCreateContext(Display::display(), &visualinfo, shared, True);
        if(res_glcxt == NULL){
            return NULL;
        }
    }


    glXMakeCurrent(Display::display(), origDrawWindow, origcxt);


    GLContext* res = new GLContext();
    res->_id = res_glcxt;
    
    return res;
}


GLContext* GLContext::current()
{
    glcontext_t cur_glcxt = glXGetCurrentContext();
    if(cur_glcxt == 0) return NULL;
    
    GLContext* res = new GLContext();
    
    res->_id = cur_glcxt;
    res->_not_destroy = true;
    
    return res;
}


void GLContext::destroy(GLContext* glcxt_)
{
    delete glcxt_;
}


void (*GLContext::getProcAddress(const char* procname_))()
{
    return glXGetProcAddress(reinterpret_cast<const GLubyte*>(procname_));
} 
