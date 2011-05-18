#ifndef _X11_WINDOW_H
#define _X11_WINDOW_H

#include "window/window.h"


#include "osal/osdef.h"

#ifdef OS_LINUX


#include <X11/Xatom.h>
#include <X11/Xlib.h>


class X11Window
    :public GLWindow
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
                          const GLWindow::PixelAttribs& pixelAttribs_);
    
    static void destroy(X11Window* window_);
    
    static int processEvents();
    
    //static Display* display();

protected:
    X11Window();
    
    static int _counter;
    
    static Atom _atom_del_win;
    static Cursor _nullCursor;
    
    static bool _init_x11();
    static void _term_x11();
    
    typedef int (*X11ErrorHandler)(Display *, XErrorEvent *);
    static X11ErrorHandler _orig_handler;
    static int _errorHandler(Display *, XErrorEvent *);
};

#endif  //OS_LINUX

#endif  //_X11_WINDOW_H
