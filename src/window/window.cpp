#include "window.h"
#include "osal/osdef.h"
#include "win/win_window.h"



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



Window::~Window()
{
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
        NULL
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
        0
    #endif
    ; // return
}

