#include "win_glcontext.h"
#include "window/window.h"

#include "osal/osdef.h"


#ifdef OS_WINDOWS

#include <windows.h>


#ifndef GL_CONTEXT_MAJOR_VERSION
#define GL_CONTEXT_MAJOR_VERSION 0x2091
#endif
#ifndef GL_CONTEXT_MINOR_VERSION
#define GL_CONTEXT_MINOR_VERSION 0x2092
#endif

WGLContext::wglCreateContextAttribsARBProc WGLContext::wglCreateContextAttribsARB = 0;



WGLContext::WGLContext()
    :GLContext()
{
}

WGLContext::~WGLContext()
{
    if(_id != 0 && _not_destroy == false) wglDeleteContext(reinterpret_cast<HGLRC>(_id));
}

GLContext* WGLContext::create(const GLWindow* window_, const Version& version_)
{
    return create(window_, version_, NULL);
}

GLContext* WGLContext::create(const GLWindow* window_, const Version& version_,
                              const GLContext* glcxt_)//not copy - share!
{
    HDC window_dc = 0;
    HGLRC res_glcxt = 0;

    HGLRC origcxt = 0;
    HDC origDc = 0;

    HGLRC tmpglcxt = 0;
    HGLRC shared = 0;
    
    //save current context state
    origDc = wglGetCurrentDC();
    origcxt = wglGetCurrentContext();
    
    window_dc = GetDC(static_cast<HWND>(window_->id()));
    
    if(glcxt_ != NULL) shared = static_cast<HGLRC>(glcxt_->id());

    //if need CreateContextAttribs
    if(version_.major > 2){
        //if current context == 0
        if(origcxt == 0){
            //create context
            tmpglcxt = wglCreateContext(window_dc);
            if(tmpglcxt == 0){
                return NULL;
            }
            if(!wglMakeCurrent(window_dc, tmpglcxt)){
                return NULL;
            }
        }

        if(wglCreateContextAttribsARB == NULL){
            //get proc address
            if(NULL == (wglCreateContextAttribsARB = reinterpret_cast<wglCreateContextAttribsARBProc>(wglGetProcAddress("wglCreateContextAttribsARB")))){
                //OpenGL 3.0 is not supported
                wglMakeCurrent(origDc, origcxt);
                return NULL;
            }
        }
        
        int context_attribs[]={
            GL_CONTEXT_MAJOR_VERSION, version_.major,
            GL_CONTEXT_MINOR_VERSION, version_.minor,
            //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            0
        };

        //if tmpglcxt created
        if(tmpglcxt != NULL){
            //destroy tmp context
            wglMakeCurrent(0, 0);
            wglDeleteContext(tmpglcxt);
        }

        //create new, gl3 context
        res_glcxt = static_cast<HGLRC>(
                        wglCreateContextAttribsARB(window_dc, shared, context_attribs)
                    );
        if(res_glcxt == 0){
            wglMakeCurrent(origDc, origcxt);
            return NULL;
        }
        //
    }else{
        //create context
        res_glcxt = wglCreateContext(window_dc);
        if(res_glcxt == NULL){
            return NULL;
        }
        if(shared && !wglShareLists(res_glcxt, shared)){
            wglDeleteContext(res_glcxt);
            return NULL;
        }
    }

    wglMakeCurrent(origDc, origcxt);
    
    WGLContext* res = new WGLContext();
    res->_id = res_glcxt;

    return res;
}

GLContext* WGLContext::current()
{
    glcontext_t cur_glcxt = wglGetCurrentContext();
    if(cur_glcxt == 0) return NULL;
    
    WGLContext* res = new WGLContext();
    
    res->_id = cur_glcxt;
    res->_not_destroy = true;
    
    return res;
}

void WGLContext::destroy(GLContext* glcxt_)
{
    delete glcxt_;
}

#endif  //OS_WINDOWS
