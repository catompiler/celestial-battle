#include <stdlib.h>
#include <iostream>
#include "log/log.h"
#include "window/window.h"
#include "glcontext/glcontext.h"
#include "input/input.h"
#include "iconv/iconv.h"
#include <GL/gl.h>
//#include <locale>
#include "thread/thread.h"


Window* w = NULL;
GLContext* cxt = NULL;

class WindowedApp{
public:
    WindowedApp(){
        closed = false;
    }
    void onClose(CloseEvent* e){
        std::cout << "onClose()" << std::endl;
        closed = true;
    }
    void onResize(ResizeEvent* e){
        std::cout << "onResize()" << std::endl;
        std::cout << e->width() << "x" << e->height() << std::endl;
        glViewport(0, 0, e->width(), e->height());
    }
    void onCreate(CreateEvent* e){
        std::cout << "onCreate()" << std::endl;
    }
    void onPaint(PaintEvent* e){
        std::cout << "onPaint()" << std::endl;
        glClear(GL_COLOR_BUFFER_BIT);
        w->swapBuffers();
    }
    void onKeyPress(KeyPressEvent* e){
        std::cout << "onKeyPress()" << std::endl;
        std::cout << "key: '" << Iconv::toLocal(e->character().toSrting()) <<
                "' (" << e->key() << ")" << std::endl;
    }
    void onMousePress(MousePressEvent* e){
        std::cout << "onMousePress()" << std::endl;
        std::cout << "(" << e->x() << ", " << e->y() <<
                     ") - " << e->button() << std::endl;
    }
    void onMouseRelease(MouseReleaseEvent* e){
        std::cout << "onMouseRelease()" << std::endl;
        std::cout << "(" << e->x() << ", " << e->y() <<
                     ") - " << e->button() << std::endl;
    }
    void onMouseMotion(MouseMotionEvent* e){
        std::cout << "onMouseMotion()" << std::endl;
        std::cout << "(" << e->x() << ", " << e->y() <<
                     ") - " << e->button() << std::endl;
    }
    void onFocusChange(FocusChangeEvent* e){
        std::cout << "onFocusChange()" << std::endl;
        std::cout << "Focus " << (e->focus() ? "in" : "out") << std::endl;
    }
    
    void* threadProc(void* arg){
        long res = 0;
        for(long i = 1; i <= reinterpret_cast<long>(arg); i++){
            res += i + i;
            std::cout << "thread" << std::endl;
        }
        return reinterpret_cast<void*>(res);
    }
    
    bool closed;
};

int main(int /*argc*/, char** /*argv*/)
{
    //std::locale::global(std::locale(""));
    
    log(Log::Information) << "Hello, Log!" << std::endl;
    
    WindowedApp wapp;
    
    PixelAttribs pa;
    pa.alphaSize = 8;
    pa.blueSize = 8;
    pa.depthSize = 24;
    pa.doubleBuffer = true;
    pa.greenSize = 8;
    pa.redSize = 8;
    pa.sampleBuffers = 0;
    pa.samples = 0;
    pa.stencilSize = 0;
    
    w = Window::create("X11 Window", 100, 100, 250, 250, pa);
    if(w == NULL){
        log(Log::Error) << "Error creating window" << std::endl;
        return 1;
    }
    
    cxt = GLContext::create(w, GLContext::Version(2,1));
    if(cxt == NULL){
        log(Log::Error) << "Error creating context" << std::endl;
        Window::destroy(w);
        return 1;
    }
    
    w->makeCurrent(cxt);
    
    w->onClose().addHandler(make_delegate(&wapp, &WindowedApp::onClose));
    w->onCreate().addHandler(make_delegate(&wapp, &WindowedApp::onCreate));
    w->onResize().addHandler(make_delegate(&wapp, &WindowedApp::onResize));
    w->onPaint().addHandler(make_delegate(&wapp, &WindowedApp::onPaint));
    w->onKeyPress().addHandler(make_delegate(&wapp, &WindowedApp::onKeyPress));
    w->onMousePress().addHandler(make_delegate(&wapp, &WindowedApp::onMousePress));
    w->onMouseRelease().addHandler(make_delegate(&wapp, &WindowedApp::onMouseRelease));
    w->onMouseMotion().addHandler(make_delegate(&wapp, &WindowedApp::onMouseMotion));
    w->onFocusIn().addHandler(make_delegate(&wapp, &WindowedApp::onFocusChange));
    w->onFocusOut().addHandler(make_delegate(&wapp, &WindowedApp::onFocusChange));
    
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    Thread thread(make_delegate(&wapp, &WindowedApp::threadProc));
    
    thread.start(reinterpret_cast<void*>(10000LL));
    
    while(wapp.closed == false){
        Window::processEvents();
    }
    
    thread.join();
    
    long res = reinterpret_cast<long>(thread.value());
    std::cout << "thread res: " << res << std::endl;
    
    w->makeCurrent(NULL);
    
    GLContext::destroy(cxt);
    
    w->onClose().removeHandler(&wapp);
    w->onCreate().removeHandler(&wapp);
    w->onResize().removeHandler(&wapp);
    w->onPaint().removeHandler(&wapp);
    w->onKeyPress().removeHandler(&wapp);
    w->onMousePress().removeHandler(&wapp);
    w->onMouseRelease().removeHandler(&wapp);
    w->onMouseMotion().removeHandler(&wapp);
    w->onFocusIn().removeHandler(&wapp);
    w->onFocusOut().removeHandler(&wapp);
    
    Window::destroy(w);
    
    return (EXIT_SUCCESS);
}
