#include "window.h"
#include "osal/osdef.h"

#ifdef OS_WINDOWS
#include "win/win_window.h"
#endif

#ifdef OS_LINUX
#include "x11/x11_window.h"
#endif



WindowEvent::WindowEvent(Window* window_)
    :ObjectEvent(window_), _window(window_)
{
}

WindowEvent::~WindowEvent()
{
    //_onClose();
}

Window* WindowEvent::window() const
{
    return _window;
}


Window::ResizeEvent::ResizeEvent(Window* window_, int width_, int height_)
    :WindowEvent(window_), _width(width_), _height(height_)
{
}

Window::ResizeEvent::~ResizeEvent()
{
}

int Window::ResizeEvent::width() const
{
    return _width;
}

int Window::ResizeEvent::height() const
{
    return _height;
}


Window::OnCreateEvent::Base& Window::onCreate()
{
    return _onCreate;
}

Window::OnCloseEvent::Base& Window::onClose()
{
    return _onClose;
}

Window::OnPaintEvent::Base& Window::onPaint()
{
    return _onPaint;
}

Window::OnResizeEvent::Base& Window::onResize()
{
    return _onResize;
}



Window::WindowsMap Window::_windowsMap;


Window::Window()
{
    _id = 0;
}


Window::~Window()
{
}

windowid_t Window::id()
{
    return _id;
}

Window* Window::create(const std::string& title_,
                      int left_, int top_,
                      int width_, int height_,
                      const PixelAttribs& pixelAttribs_)
{
    return
    #ifdef OS_WINDOWS
        WinWindow::create(title_, left_, top_, width_, height_, pixelAttribs_)
    #else
    #ifdef OS_LINUX
        X11Window::create(title_, left_, top_, width_, height_, pixelAttribs_)
    #else
        NULL
    #endif
    #endif
    ; // return
}

void Window::destroy(Window* window_)
{
    delete window_;
}

int Window::processEvents()
{
    return
    #ifdef OS_WINDOWS
        WinWindow::processEvents()
    #else
    #ifdef OS_LINUX
        X11Window::processEvents()
    #else
        0
    #endif
    #endif
    ; // return
}

Window* Window::getWindow(windowid_t id_)
{
    WindowsMap::iterator it = _windowsMap.find(id_);
    if(it == _windowsMap.end()){
        return NULL;
    }
    return (*it).second;
}

bool Window::addWindow(windowid_t id_, Window* window_)
{
    WindowsMap::iterator it = _windowsMap.find(id_);
    if(it == _windowsMap.end()){
        //set handle value!
        window_->_id = id_;
        _windowsMap[id_] = window_;
        return true;
    }
    return false;
}

bool Window::removeWindow(windowid_t id_)
{
    WindowsMap::iterator it = _windowsMap.find(id_);
    if(it == _windowsMap.end()){
        return false;
    }
    _windowsMap.erase(it);
    return true;
}

