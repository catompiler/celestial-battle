#ifndef _WIN_WINDOW_H
#define _WIN_WINDOW_H

#include <windows.h>
#include "window/window.h"
#include <map>

class WinWindow
    :public Window
{
public:
    WinWindow();
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
    
    
    bool makeCurrent(const GLContext& glcxt_) /* const */;
    
    void swapBuffers() /* const */;
    
    
    static WinWindow* create(const std::string& title_,
                          int left_, int top_,
                          int width_, int height_,
                          const PixelAttribs& pixelAttribs_);
    
    static int processEvents();

protected:
    
    typedef std::map<HWND, WinWindow*> WindowsMap;
    static WindowsMap _windowsMap;
    static const char* _winClassName;
    static int _regclass_count;

    static LRESULT CALLBACK _WndProc(HWND  hWnd, UINT  uMsg, WPARAM  wParam, LPARAM  lParam);

    static WinWindow* getWindow(HWND hWnd_);
    static bool addWindow(HWND hWnd_, WinWindow* window_);
    static bool removeWindow(HWND hWnd_);

    HWND _hWnd;

};

#endif
