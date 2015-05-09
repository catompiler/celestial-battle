#include <stdlib.h>
#include <iostream>
#include "engine/engine.h"
#include "log/log.h"
#include "settings/settings.h"
#include "window/window.h"
#include "glcontext/glcontext.h"
#include "input/input.h"
#include "iconv/iconv.h"
#include "opengl/opengl.h"
#include <locale>
#include "glbuffer/glbuffer.h"
#include "resources/resources.h"
#include "readers/tgareader.h"
#include "readers/mesh3dreader.h"
#include "tokenizer/parseexception.h"
/*#include <iostream>
#include "glmath/glmath.h"*/

static Window* w;
static GLContext cxt;

static const std::string config_filename = "config.cfg";

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



/*std::ostream& operator<<(std::ostream& ost, const vec3_t& v)
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
}*/

/*std::ostream& operator<<(std::ostream& ost, const Rage::Transform& t)
{
    ost << "posit: " << t.position << std::endl <<
           "rotat: " << t.rotation << std::endl <<
           "scale: " << t.scaling << std::endl;
    return ost;
}*/



/*void test()
{
    vec3_t p1(-1, 1, 0), v1(0,1,0);
    vec3_t p2(-1, 2, 0);
    vec3_t p3(2, 1, 0);
    line_t l(p1, v1);
    float d = distance(l, p2);
    std::cout << "dist == " << d << std::endl;
    std::cout << cross(p1, p1) << std::endl;
}*/


int main(int /*argc*/, char** /*argv*/)
{
    std::locale::global(std::locale(""));
    
    /*test();
    return 0;*/
    
    log(Log::Information) << "Hello, Log!" << std::endl;
    
    Rage::Engine engine;
    engine.setConfigFile(config_filename);
    engine.readSettings();
    engine.initVideo("Rage is Another Game Engine");
    
    w = engine.window();
    WindowedApp wapp;
    
    log(Log::Information) << "Creating a OpenGL context" << std::endl;
    if(cxt.create(w, GLContext::Version(4, 3)) == false){
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
            texture2d_ptr ptex1 = resources.get<GL::Texture2D>("/tmp/res/textures/wall.tga");
            texture2d_ptr ptex2 = resources.get<GL::Texture2D>("/tmp/res/textures/wall.tga");
            mesh_ptr pmesh = resources.get<Rage::Mesh>("/tmp/res/models/cube.msh3d");
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
    
    engine.destroyVideo();
    engine.writeSettings();
    
    return (EXIT_SUCCESS);
}
