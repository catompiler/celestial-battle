#include <stdlib.h>
#include <iostream>
#include "log/log.h"
#include "window/window.h"
#include "glcontext/glcontext.h"
#include "input/input.h"
#include <GL/gl.h>


GLWindow* w = NULL;
GLContext* cxt = NULL;

class WindowedApp{
public:
    WindowedApp(){
        closed = false;
    }
    void onClose(GLWindow::CloseEvent* e){
        std::cout << "onClose()" << std::endl;
        closed = true;
    }
    void onResize(GLWindow::ResizeEvent* e){
        std::cout << e->width() << "x" << e->height() << std::endl;
        glViewport(0, 0, e->width(), e->height());
    }
    void onCreate(GLWindow::CreateEvent* e){
        std::cout << "onCreate()" << std::endl;
    }
    void onPaint(GLWindow::PaintEvent* e){
        std::cout << "onPaint()" << std::endl;
        glClear(GL_COLOR_BUFFER_BIT);
        w->swapBuffers();
        
    }
    bool closed;
};

int main(int argc, char** argv)
{
    log(Log::Information) << "Hello, Log!" << std::endl;
    
    WindowedApp wapp;
    
    GLWindow::PixelAttribs pa;
    pa.alphaSize = 8;
    pa.blueSize = 8;
    pa.depthSize = 24;
    pa.doubleBuffer = true;
    pa.greenSize = 8;
    pa.redSize = 8;
    pa.sampleBuffers = 0;
    pa.samples = 0;
    pa.stencilSize = 0;
    
    w = GLWindow::create("X11 Window", 100, 100, 250, 250, pa);
    if(w == NULL){
        log(Log::Error) << "Error creating window" << std::endl;
        return 1;
    }
    
    cxt = GLContext::create(w, GLContext::Version(2,1));
    if(cxt == NULL){
        log(Log::Error) << "Error creating context" << std::endl;
        GLWindow::destroy(w);
        return 1;
    }
    
    w->makeCurrent(cxt);
    
    w->onClose().addHandler(make_delegate(&wapp, &WindowedApp::onClose));
    w->onCreate().addHandler(make_delegate(&wapp, &WindowedApp::onCreate));
    w->onResize().addHandler(make_delegate(&wapp, &WindowedApp::onResize));
    w->onPaint().addHandler(make_delegate(&wapp, &WindowedApp::onPaint));
    
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    while(wapp.closed == false){
        GLWindow::processEvents();
        //input::mouse::state_t* state = input::mouse::state();
        //std::cout << state->x << "x" << state->y << std::endl;
    }
    
    w->makeCurrent(NULL);
    
    GLContext::destroy(cxt);
    
    w->onClose().removeHandler(&wapp);
    w->onCreate().removeHandler(&wapp);
    w->onResize().removeHandler(&wapp);
    w->onPaint().removeHandler(&wapp);
    
    GLWindow::destroy(w);
    
    return (EXIT_SUCCESS);
}

