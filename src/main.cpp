#include <stdlib.h>
#include <iostream>
#include "log/log.h"
#include "config/config.h"
#include "window/window.h"
#include "glcontext/glcontext.h"
#include "input/input.h"
#include "iconv/iconv.h"
#include "opengl/opengl.h"
#include <locale>
#include "glbuffer/glbuffer.h"
#include "display/display.h"
#include "resources/resources.h"
#include "readers/tgareader.h"
#include "readers/mesh3dreader.h"
#include "tokenizer/parseexception.h"

static Window* w = NULL;
static GLContext cxt;

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
    std::locale::global(std::locale(""));
    
    log(Log::Information) << "Hello, Log!" << std::endl;
    
    log(Log::Information) << "Reading config" << std::endl;
    
    const std::string config_filename = "config.cfg";
    Config config;
    
    try{
        config.read(config_filename);
    }catch(ParseException& pe_){
        log(Log::Error) << "Error: " << pe_.what()
                        << "; line: " << pe_.position().line()
                        << " col: " << pe_.position().col()
                        << std::endl;
    }
    
    int width = config.value<int>("video.width", 800);//1440;
    int height = config.value<int>("video.height", 600);//900;
    int freq = config.value<int>("video.freq", 60);
    bool fullscreen = config.value<int>("video.fullscreen", 0);
    
    if(fullscreen){
        log(Log::Information) << "Setting video mode" << std::endl;
        if(!Display::setMode(Display::Mode(width, height, freq))){
            log(Log::Warning) << "Error set video mode - continues in windowed mode" << std::endl;
            fullscreen = false;
        }
    }
    
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
    
    log(Log::Information) << "Creating a window" << std::endl;
    w = Window::create("GL Window", 0, 0, width, height, fullscreen, pa);
    if(w == nullptr){
        log(Log::Error) << "Error creating window" << std::endl;
        return 1;
    }
    
    log(Log::Information) << "Creating a OpenGL context" << std::endl;
    if(cxt.create(w, GLContext::Version(4, 2)) == false){
        log(Log::Error) << "Error creating context" << std::endl;
        Window::destroy(w);
        return 1;
    }
    
    log(Log::Information) << "Setting the current OpenGL context" << std::endl;
    if(!w->makeCurrent(&cxt)){
        log(Log::Error) << "Error setting current context" << std::endl;
        cxt.destroy();
        Window::destroy(w);
        return 1;
    }
    
    log(Log::Information) << "Adding event handlers" << std::endl;
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
    
    
    log(Log::Information) << "Initializing OpenGL functions..." << std::endl;
    GL::initFunctions();
    
    GL::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    
    {
        Rage::Resources resources;
        Rage::TgaReader tgareader;
        Rage::Mesh3dReader mesh3dreader;

        if(resources.addReader(&tgareader)){
            log(Log::Information) << "TGA reader registered" << std::endl;
        }
        if(resources.addReader(&mesh3dreader)){
            log(Log::Information) << "Mesh3D reader registered" << std::endl;
        }
        {
            texture2d_ptr ptex1 = resources.get<GL::Texture2D>("/tmp/wall.tga");
            texture2d_ptr ptex2 = resources.get<GL::Texture2D>("/tmp/wall.tga");
            mesh_ptr pmesh = resources.get<Rage::Mesh>("/tmp/cube.msh3d");
            std::cout << "pmesh refs count: " << pmesh.use_count() << std::endl;
            
            texture_ptr ptex = std::static_pointer_cast<GL::Texture>(ptex2);

            std::cout << "ptex refs count: " << ptex.use_count() << std::endl;
            
            resources.release(ptex1);
            
            std::cout << "ptex refs count: " << ptex.use_count() << std::endl;
            
            for(Rage::Resources::iterator<GL::Texture2D> it =
                    resources.begin<GL::Texture2D>();
                    it != resources.end<GL::Texture2D>(); ++it){
                std::cout << it.filename() << std::endl;
            }
            
            ptex = nullptr;
            //resources.release(ptex);
            resources.gc();
        }
        resources.removeReader(&mesh3dreader);
        resources.removeReader(&tgareader);
    }//*/
    
    
    while(wapp.closed == false){
        Window::processEvents();
    }
    
    w->makeCurrent(nullptr);
    
    cxt.destroy();
    
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
    
    config.write(config_filename);
    
    return (EXIT_SUCCESS);
}
