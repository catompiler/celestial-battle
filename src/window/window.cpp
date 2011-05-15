#include "window.h"

Window::~Window() {
}

Window::CreateEvent::Base& Window::createEvent()
{
    return _createEvent;
}

Window::CloseEvent::Base& Window::closeEvent()
{
    return _closeEvent;
}

Window::PaintEvent::Base& Window::paintEvent()
{
    return _paintEvent;
}

Window::ResizeEvent::Base& Window::resizeEvent()
{
    return _resizeEvent;
}
