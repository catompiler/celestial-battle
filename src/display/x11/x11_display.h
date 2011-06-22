#ifndef _X11_DISPLAY_H
#define _X11_DISPLAY_H

#define Window XWindow
#define Display XDisplay
#include <X11/Xlib.h>
#undef Window
#undef Display

class Display
{
public:
    Display();
    ~Display();
    
    static XDisplay* display(){
        return _display;
    }
    
    static int width();
    static int height();
    
private:
    static XDisplay* _display;
    static int _counter;
};

#endif  //_X11_DISPLAY_H
