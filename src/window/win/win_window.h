#ifndef _WIN_WINDOW_H
#define _WIN_WINDOW_H

#include "osal/osdef.h"

#ifdef OS_WINDOWS

#include <windows.h>
#include "window/window.h"

class WinWindow
    :public Window
{
public:
    ~WinWindow();

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
    
    
    static WinWindow* create(const std::string& title_,
                          int left_, int top_,
                          int width_, int height_,
                          const Window::PixelAttribs& pixelAttribs_);
    
    static int processEvents();

protected:
    WinWindow();
    
    static const char* _winClassName;
    static int _regclass_count;

    static LRESULT CALLBACK _WndProc(HWND  hWnd, UINT  uMsg, WPARAM  wParam, LPARAM  lParam);

    HWND _id;

};

#endif  //OS_WINDOWS

#endif  //_WIN_WINDOW_H
