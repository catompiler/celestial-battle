#include <stdlib.h>
#include <iostream>
#include "log/log.h"
#include "window/window.h"

class WindowedApp{
public:
    WindowedApp(){
        closed = false;
    }
    void onClose(Window::CloseEvent* e){
        std::cout << "onClose()" << std::endl;
        closed = true;
    }
    void onResize(Window::ResizeEvent* e){
        std::cout << e->width() << "x" << e->height() << std::endl;
    }
    void onCreate(Window::CreateEvent* e){
        std::cout << "onCreate()" << std::endl;
    }
    bool closed;
};

int main(int argc, char** argv)
{
    log(Log::Information) << "Hello, Log!" << std::endl;
    
    WindowedApp wapp;
    
    Window::PixelAttribs pa;
    pa.alphaSize = 8;
    pa.blueSize = 8;
    pa.depthSize = 24;
    pa.doubleBuffer = true;
    pa.greenSize = 8;
    pa.redSize = 8;
    pa.sampleBuffers = 0;
    pa.samples = 0;
    pa.stencilSize = 0;
    Window* w = Window::create("X11 Window", 100, 100, 250, 250, pa);
    
    if(w == NULL){
        log(Log::Error) << "Error creating window" << std::endl;
        return 1;
    }
    
    w->onClose().addHandler(make_delegate(&wapp, &WindowedApp::onClose));
    w->onCreate().addHandler(make_delegate(&wapp, &WindowedApp::onCreate));
    w->onResize().addHandler(make_delegate(&wapp, &WindowedApp::onResize));
    
    while(wapp.closed == false){
        Window::processEvents();
    }
    
    w->onClose().removeHandler(&wapp);
    w->onCreate().removeHandler(&wapp);
    w->onResize().removeHandler(&wapp);
    
    return (EXIT_SUCCESS);
}

