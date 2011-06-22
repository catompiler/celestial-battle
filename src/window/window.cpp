#include "window.h"
#include "glcontext/glcontext.h"

#include "osal/osdef.h"
#include PLATFORM_FILE(WINDOW_SYSTEM, window.cpp)



Window::WindowEvent::WindowEvent(Window* window_)
    :ObjectEvent(window_), _window(window_)
{
}

Window::WindowEvent::~WindowEvent()
{
    //_onClose();
}

Window* Window::WindowEvent::window() const
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

windowid_t Window::id() const
{
    return _id;
}
