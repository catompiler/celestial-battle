#ifndef _WINDOWS_DISPLAY_H
#define _WINDOWS_DISPLAY_H


#include <windows.h>
#undef CreateEvent
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
    
    static int width();
    static int height();
    
    static size_t modesCount();
    static const Mode& mode(int n) throw(Exception&);
    static bool setMode(const Mode& mode_);
    static bool setMode(int n);
    static bool restoreMode();
    
private:
    static int _counter;
    typedef std::vector<std::pair<Mode, DEVMODE> > Modes;
    static Modes* _modes;
    
    static void _init();
    static void _clean();
    static bool _getModes();
};

static Display __init_display;

#endif  //_WINDOWS_DISPLAY_H
