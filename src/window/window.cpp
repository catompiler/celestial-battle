#include "window.h"
#include "glcontext/glcontext.h"

#include "osal/osdef.h"

#ifdef OS_WINDOWS
#include "win/win_window.h"
#elif defined OS_LINUX
#include "x11/x11_window.h"
#endif



WindowEvent::WindowEvent(GLWindow* window_)
    :ObjectEvent(window_), _window(window_)
{
}

WindowEvent::~WindowEvent()
{
    //_onClose();
}

GLWindow* WindowEvent::window() const
{
    return _window;
}


GLWindow::ResizeEvent::ResizeEvent(GLWindow* window_, int width_, int height_)
    :WindowEvent(window_), _width(width_), _height(height_)
{
}

GLWindow::ResizeEvent::~ResizeEvent()
{
}

int GLWindow::ResizeEvent::width() const
{
    return _width;
}

int GLWindow::ResizeEvent::height() const
{
    return _height;
}


GLWindow::OnCreateEvent::Base& GLWindow::onCreate()
{
    return _onCreate;
}

GLWindow::OnCloseEvent::Base& GLWindow::onClose()
{
    return _onClose;
}

GLWindow::OnPaintEvent::Base& GLWindow::onPaint()
{
    return _onPaint;
}

GLWindow::OnResizeEvent::Base& GLWindow::onResize()
{
    return _onResize;
}



GLWindow::WindowsMap GLWindow::_windowsMap;


GLWindow::GLWindow()
{
    _id = 0;
}

GLWindow::~GLWindow()
{
    if(_id) removeWindow(_id);
}

windowid_t GLWindow::id() const
{
    return _id;
}

GLWindow* GLWindow::create(const std::string& title_,
                      int left_, int top_,
                      int width_, int height_,
                      const PixelAttribs& pixelAttribs_)
{
    return
    #ifdef OS_WINDOWS
        WinWindow::create(title_, left_, top_, width_, height_, pixelAttribs_)
    #elif defined OS_LINUX
        X11Window::create(title_, left_, top_, width_, height_, pixelAttribs_)
    #else
        NULL
    #endif
    ; // return
}

void GLWindow::destroy(GLWindow* window_)
{
    #ifdef OS_WINDOWS
        WinWindow::destroy(static_cast<WinWindow*>(window_));
    #elif defined OS_LINUX
        X11Window::destroy(static_cast<X11Window*>(window_));
    #endif
}

int GLWindow::processEvents()
{
    return
    #ifdef OS_WINDOWS
        WinWindow::processEvents()
    #elif defined OS_LINUX
        X11Window::processEvents()
    #else
        0
    #endif
    ; // return
}

GLWindow* GLWindow::getWindow(windowid_t id_)
{
    WindowsMap::iterator it = _windowsMap.find(id_);
    if(it == _windowsMap.end()){
        return NULL;
    }
    return (*it).second;
}

bool GLWindow::addWindow(windowid_t id_, GLWindow* window_)
{
    WindowsMap::iterator it = _windowsMap.find(id_);
    if(it == _windowsMap.end()){
        _windowsMap[id_] = window_;
        return true;
    }
    return false;
}

bool GLWindow::removeWindow(windowid_t id_)
{
    WindowsMap::iterator it = _windowsMap.find(id_);
    if(it == _windowsMap.end()){
        return false;
    }
    _windowsMap.erase(it);
    return true;
}

