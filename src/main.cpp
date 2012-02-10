#include <stdlib.h>
#include <iostream>
#include "log/log.h"
#include "window/window.h"
#include "glcontext/glcontext.h"
#include "input/input.h"
#include "iconv/iconv.h"
#include "opengl/opengl.h"
//#include <locale>
#include "glbuffer/glbuffer.h"
#include "display/display.h"
#include "resources/resources.h"

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
        if(e->key() == KEY_ESCAPE) closed = true;
    }
    void onMousePress(MousePressEvent* e){
        std::cout << "onMousePress()" << std::endl;
        std::cout << "(" << e->x() << ", " << e->y() <<
                     ") - " << e->button() << std::endl;
        if(e->button() & MOUSE_RIGHT) closed = true;
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
    
    bool closed;
};


/*
std::ostream& operator<<(std::ostream& ost, const vec3_t& v)
{
    ost << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return ost;
}

std::ostream& operator<<(std::ostream& ost, const quat_t& q)
{
    vec3_t axis;
    try{
        axis = q.axis();
    }catch(...){}
    ost << "(" << axis << ", " << degrees(q.angle()) << ")";
    return ost;
}

std::ostream& operator<<(std::ostream& ost, const Rage::Transform& t)
{
    ost << "posit: " << t.position << std::endl <<
           "rotat: " << t.rotation << std::endl <<
           "scale: " << t.scaling << std::endl;
    return ost;
}
*/



int main(int /*argc*/, char** /*argv*/)
{
    //std::locale::global(std::locale(""));
    
    log(Log::Information) << "Hello, Log!" << std::endl;
    
    int width = 800;//1440;
    int height = 600;//900;
    int freq = 60;
    bool fullscreen = false;
    
    if(fullscreen && !Display::setMode(Display::Mode(width, height, freq))){
        std::cout << "Error set video mode" << std::endl;
        fullscreen = false;
    }
    
    std::cout << "width: " << Display::width() << std::endl;
    std::cout << "height: " << Display::height() << std::endl;
    
    std::cout << "width dpi: " << Display::wdpi() << std::endl;
    std::cout << "height dpi: " << Display::hdpi() << std::endl;
    
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
    
    w = Window::create("X11 Window", 0, 0, width, height, fullscreen, pa);
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
    
    
    std::cout << "Init gl functions..." << std::endl;
    GL::initFunctions();
    std::cout << "GL_EXT_gpu_shader4 == " << GL::GL_EXT_gpu_shader4_supported << std::endl;
    
    std::cout << "glBindBuffer == " << (void*)GL::glBindBuffer << std::endl;
    std::cout << "glBindBufferARB == " << (void*)GL::glBindBufferARB << std::endl;
    
    if(GL::GL_VERSION_1_5_supported){
        GL::Buffer buf;
        buf.bind(GL_ARRAY_BUFFER);
        GL::Buffer::setData(GL_ARRAY_BUFFER, 0x100, NULL, GL_STATIC_DRAW);
        GL::Buffer::unbind(GL_ARRAY_BUFFER);
    }
    
    GL::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    Rage::Resources resources;
    
    smart_ptr<GL::Texture2D> ptex = resources.get<GL::Texture2D>();
    
    if(ptex){
        std::cout << "Texture2D created: " << ptex.refs_count() << std::endl;
    }
    
    smart_ptr<int> pi = resources.get<int>();
    
    if(!pi){
        std::cout << "int not created: " << pi.refs_count() << std::endl;
    }
    
    while(wapp.closed == false){
        Window::processEvents();
    }
    
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
    
    Display::restoreMode();
    
    return (EXIT_SUCCESS);
}
