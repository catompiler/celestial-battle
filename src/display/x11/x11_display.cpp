#include <stdlib.h>
#include "x11_display.h"
#include <math.h>
//#include <iostream>



XDisplay* Display::_display = NULL;
int Display::_counter = 0;

bool Display::_desktopModeSaved = false;
XF86VidModeModeInfo Display::_desktopMode = {0};

Display::Modes* Display::_modes = NULL;

//static Display display;

Display::Display()
{
    if(_counter++ == 0){
        //open display
        _display = XOpenDisplay(getenv("DISPLAY"));
        if(_display == NULL){
            return;
        }
        //test connection to X
        if(!XNoOp(_display)){
            XCloseDisplay(_display);
            _display = NULL;
            return;
        }
        _init();
    }
}

Display::~Display()
{
    if(_counter != 0){
        if(--_counter == 0){
            //close display
            if(_display != NULL){
                _clean();
                XCloseDisplay(_display);
                _display = NULL;
            }
        }
    }
}

void Display::_init()
{
    _modes = new Modes;
    _getModes();
}

void Display::_clean()
{
    //restoreMode();
    delete _modes;
}

/*XDisplay* Display::display()
{
    return _display;
}*/

int Display::width()
{
    return XDisplayWidth(Display::display(),
                         XDefaultScreen(Display::display()));
}

int Display::height()
{
    return XDisplayHeight(Display::display(),
                          XDefaultScreen(Display::display()));
}

size_t Display::modesCount()
{
    return _modes->size();
}

const Display::Mode& Display::mode(int n) throw(Exception&)
{
    if(n < 0 || n >= _modes->size()) throw(Exception("mode index out of range"));
    return _modes->at(n).first;
}

bool Display::setMode(const Mode& mode_)
{
    for(int i = 0; i < _modes->size(); i++){
        if(mode_.width == _modes->at(i).first.width &&
           mode_.height == _modes->at(i).first.height &&
           mode_.refresh_rate == _modes->at(i).first.refresh_rate){
            return setMode(i);
        }
    }
    
    return false;
}

bool Display::setMode(int n)
{
    if(n < 0 || n >= _modes->size()) return false;
    if(XF86VidModeSwitchToMode(_display,
            XDefaultScreen(Display::display()),
            &_modes->at(n).second) &&
        XF86VidModeSetViewPort(_display,
            XDefaultScreen(Display::display()),
            0, 0)){
        return true;
    }
    return false;
}

bool Display::restoreMode()
{
    if(_desktopModeSaved){
        return XF86VidModeSwitchToMode(_display, XDefaultScreen(Display::display()), &_desktopMode);
    }
    return true;
}

bool Display::_getModes()
{
    int _modesCount = 0;
    XF86VidModeModeInfo** _xmodes = NULL;
    if(!XF86VidModeGetAllModeLines(_display, XDefaultScreen(Display::display()),
                                        &_modesCount, &_xmodes)){
        return false;
    }
    
    if(_desktopModeSaved == false){
        _desktopMode = *_xmodes[0];
        _desktopModeSaved = true;
    }
    
    _modes->reserve(_modesCount);
    
    int w, h;
    float f;
    for(int i = 0; i < _modesCount; i++){
        w = _xmodes[i]->hdisplay;
        h = _xmodes[i]->vdisplay;
        /*
         RR = DCF / (HFL * VFL)
         Refresh Rate = Dot Clock [or pixel clock?] / (Horizonal Sync Frequency * Vertical Sync Frequency)
         */
        f = static_cast<float>(_xmodes[i]->dotclock) * 1000.0f /
                                (_xmodes[i]->htotal * _xmodes[i]->vtotal);
        
        //std::cout << "Mode[" << i << "]: " << w << "x" << h << "@" << f << std::endl;
        
        _modes->push_back(std::make_pair(
                Mode(w, h, static_cast<int>(_round(f))),
                *_xmodes[i]));
    }
    
    XFree(_xmodes);
    
    return true;
}

float Display::_round(float value_)
{
    return floor(value_ + 0.5f);
}
