#ifndef _WINDOW_EVENTS_H_ 
#define _WINDOW_EVENTS_H_

#include "object/object.h"
#include "string/utf8char.h"

class Window;

class WindowEvent
    :public ObjectEvent
{
public:
    WindowEvent(Window* window_);
    ~WindowEvent();

    Window* window() const;

protected:
    Window* _window;
};


typedef WindowEvent CreateEvent;
typedef UnaryEvent<CreateEvent*> OnCreateEvent;

typedef WindowEvent CloseEvent;
typedef UnaryEvent<CloseEvent*> OnCloseEvent;

typedef WindowEvent PaintEvent;
typedef UnaryEvent<PaintEvent*> OnPaintEvent;


class ResizeEvent
    :public WindowEvent
{
public:
    ResizeEvent(Window* window_, int width_, int height_);
    ~ResizeEvent();

    int width() const;
    int height() const;

private:
    int _width;
    int _height;
};

typedef UnaryEvent<ResizeEvent*> OnResizeEvent;


class KeyEvent
    :public WindowEvent
{
public:
    KeyEvent(Window* window_, const Utf8Char& c_, unsigned char key_);
    ~KeyEvent();
    
    const Utf8Char& character() const;
    unsigned char key() const;
    
private:
    Utf8Char _c;
    unsigned char _key;
};

typedef KeyEvent KeyPressEvent;
typedef KeyEvent KeyReleaseEvent;

typedef UnaryEvent<KeyPressEvent*> OnKeyPressEvent;
typedef UnaryEvent<KeyReleaseEvent*> OnKeyReleaseEvent;


class MouseEvent
    :public WindowEvent
{
public:
    MouseEvent(Window* window_, int x_, int y_, int button_);
    ~MouseEvent();
    
    int x() const;
    int y() const;
    int button() const;
    
private:
    int _x;
    int _y;
    int _button;
};

typedef MouseEvent MouseButtonEvent;
typedef MouseButtonEvent MousePressEvent;
typedef MouseButtonEvent MouseReleaseEvent;
typedef MouseEvent MouseMotionEvent;

typedef UnaryEvent<MousePressEvent*> OnMousePressEvent;
typedef UnaryEvent<MouseReleaseEvent*> OnMouseReleaseEvent;
typedef UnaryEvent<MouseMotionEvent*> OnMouseMotionEvent;


class FocusChangeEvent
        :public WindowEvent
{
public:
    FocusChangeEvent(Window* window_, bool focus_);
    ~FocusChangeEvent();
    
    bool focus() const;
    
private:
    bool _focus;
};

typedef FocusChangeEvent FocusInEvent;
typedef FocusChangeEvent FocusOutEvent;

typedef UnaryEvent<FocusInEvent*> OnFocusInEvent;
typedef UnaryEvent<FocusOutEvent*> OnFocusOutEvent;

#endif  //_WINDOW_EVENTS_H_
