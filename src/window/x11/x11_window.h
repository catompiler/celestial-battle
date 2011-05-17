#ifndef _X11_WINDOW_H
#define _X11_WINDOW_H

#include "osal/osdef.h"

#ifdef OS_LINUX

#include "window/window.h"
namespace X{
#include <X11/X.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
}


class X11Window
    :public Window
{
public:
    ~X11Window();

    int left() const;
    void setLeft(int left_);
    
    int top() const;
    void setTop(int top_);
    
    unsigned int width() const;
    void setWidth(unsigned int width_);
    
    unsigned int height() const;
    void setHeight(unsigned int height_);
    
    std::string title() const;
    void setTitle(const std::string& title_);
    
    bool active() const;
    
    bool showCursor(bool show_);
    
    
    bool makeCurrent(GLContext* glcxt_) /* const */;
    
    void swapBuffers() /* const */;
    
    
    static X11Window* create(const std::string& title_,
                          int left_, int top_,
                          int width_, int height_,
                          const Window::PixelAttribs& pixelAttribs_);
    
    static int processEvents();

protected:
    X11Window();
    
    static int _counter;
    
    static X::Display* _display;
    static X::Atom _atom_del_win;
    static X::Cursor _nullCursor;
    
    static bool _init_x11();
    static void _term_x11();
};

#endif  //OS_LINUX

#endif  //_X11_WINDOW_H
