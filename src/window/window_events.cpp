#include "window_events.h"
#include "window/window.h"


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


ResizeEvent::ResizeEvent(Window* window_, int width_, int height_)
    :WindowEvent(window_), _width(width_), _height(height_)
{
}

ResizeEvent::~ResizeEvent()
{
}

int ResizeEvent::width() const
{
    return _width;
}

int ResizeEvent::height() const
{
    return _height;
}


KeyEvent::KeyEvent(Window* window_, const Utf8Char& c_, unsigned char key_)
        :WindowEvent(window_)
{
    _c = c_;
    _key = key_;
}

KeyEvent::~KeyEvent()
{
}

const Utf8Char& KeyEvent::character() const
{
    return _c;
}

unsigned char KeyEvent::key() const
{
    return _key;
}


MouseEvent::MouseEvent(Window* window_, int x_, int y_, int button_)
        :WindowEvent(window_)
{
    _x = x_;
    _y = y_;
    _button = button_;
}

MouseEvent::~MouseEvent()
{
}

int MouseEvent::x() const
{
    return _x;
}

int MouseEvent::y() const
{
    return _y;
}

int MouseEvent::button() const
{
    return _button;
}


FocusChangeEvent::FocusChangeEvent(Window* window_, bool focus_)
        :WindowEvent(window_)
{
    _focus = focus_;
}

FocusChangeEvent::~FocusChangeEvent()
{
}

bool FocusChangeEvent::focus() const
{
    return _focus;
}
