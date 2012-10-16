#ifndef _X11_DISPLAY_H
#define _X11_DISPLAY_H

#define Window XWindow
#define Display XDisplay
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#undef Window
#undef Display

#include <vector>
#include <utility>
#include "exception/exception.h"



class Display
{
public:
    
    struct Mode{
        Mode()
                :width(0), height(0), refresh_rate(0)
        {}
        Mode(int width_, int height_, int rr_)
                :width(width_), height(height_), refresh_rate(rr_)
        {}
        int width;
        int height;
        int refresh_rate;
    };
    
    Display();
    ~Display();
    
    static XDisplay* display(){
        return _display;
    }
    
    static int width();
    static int height();
    static int wdpi();
    static int hdpi();
    
    static size_t modesCount();
    static const Mode& mode(int n) throw(Exception&);
    static bool setMode(const Mode& mode_);
    static bool setMode(int n);
    static bool restoreMode();
    
private:
    static XDisplay* _display;
    static int _counter;
    
    static bool _desktopModeSaved;
    static XF86VidModeModeInfo _desktopMode;
    
    typedef std::vector<std::pair<Mode, XF86VidModeModeInfo> > Modes;
    static Modes* _modes;
    
    static void _init();
    static void _clean();
    static bool _getModes();
    static float _round(float value_);
};

static Display __init_display;

#endif  //_X11_DISPLAY_H
