#include <windows.h>
#include "window/window.h"


#ifndef GL_CONTEXT_MAJOR_VERSION
#define GL_CONTEXT_MAJOR_VERSION 0x2091
#endif
#ifndef GL_CONTEXT_MINOR_VERSION
#define GL_CONTEXT_MINOR_VERSION 0x2092
#endif


typedef glcontext_t (*wglCreateContextAttribsARBProc)(void*, glcontext_t, const int *);
static wglCreateContextAttribsARBProc wglCreateContextAttribsARB = NULL;



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
    HDC window_dc = 0;
    glcontext_t res_glcxt = 0;


    glcontext_t origcxt = 0;
    HDC origDc = 0;


    glcontext_t tmpglcxt = 0;
    glcontext_t shared = 0;
    
    //save current context state
    origDc = wglGetCurrentDC();
    origcxt = wglGetCurrentContext();
    
    window_dc = GetDC(window_->id());
    
    if(glcxt_ != nullptr) shared = static_cast<glcontext_t>(glcxt_->id());


    //if need CreateContextAttribs
    if(version_.major > 2){
        //if current context == 0
        if(origcxt == 0){
            //create context
            tmpglcxt = wglCreateContext(window_dc);
            if(tmpglcxt == 0){
                return false;
            }
            if(!wglMakeCurrent(window_dc, tmpglcxt)){
                return false;
            }
        }


        if(wglCreateContextAttribsARB == nullptr){
            //get proc address
            if(nullptr == (wglCreateContextAttribsARB = reinterpret_cast<wglCreateContextAttribsARBProc>(wglGetProcAddress("wglCreateContextAttribsARB")))){
                //OpenGL 3.0 is not supported
                wglMakeCurrent(origDc, origcxt);
                return false;
            }
        }
        
        int context_attribs[]={
            GL_CONTEXT_MAJOR_VERSION, version_.major,
            GL_CONTEXT_MINOR_VERSION, version_.minor,
            //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            0
        };


        //if tmpglcxt created
        if(tmpglcxt != 0){
            //destroy tmp context
            wglMakeCurrent(0, 0);
            wglDeleteContext(tmpglcxt);
        }


        //create new, gl3 context
        res_glcxt = static_cast<glcontext_t>(
                        wglCreateContextAttribsARB(window_dc, shared, context_attribs)
                    );
        if(res_glcxt == 0){
            wglMakeCurrent(origDc, origcxt);
            return false;
        }
        //
    }else{
        //create context
        res_glcxt = wglCreateContext(window_dc);
        if(res_glcxt == 0){
            return false;
        }
        if(shared && !wglShareLists(res_glcxt, shared)){
            wglDeleteContext(res_glcxt);
            return false;
        }
    }


    wglMakeCurrent(origDc, origcxt);
    
    _shared_id->data = res_glcxt;
    _contexts[_shared_id->data] = this;

    return true;
}


GLContext GLContext::current()
{
    glcontext_t cur_glcxt = wglGetCurrentContext();
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
        wglDestroyContext(_shared_id->data);
        delete _shared_id;
    }
    _shared_id = new SharedId();
}


void (*GLContext::getProcAddress(const char* procname_))()
{
    return reinterpret_cast<void (*)()>(wglGetProcAddress(procname_));
}
