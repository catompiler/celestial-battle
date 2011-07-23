#include "display/display.h"
//#include <iostream>


int Display::_counter = 0;
Display::Modes* Display::_modes = NULL;



Display::Display()
{
    if(_counter++ == 0){
        _init();
    }
}

Display::~Display()
{
    if(_counter != 0){
        if(--_counter == 0){
            _clean();
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

int Display::width()
{
    return GetSystemMetrics(SM_CXSCREEN);
}

int Display::height()
{
    return GetSystemMetrics(SM_CYSCREEN);
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
    return ChangeDisplaySettings(&_modes->at(n).second, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL;
}

bool Display::restoreMode()
{
    return ChangeDisplaySettings(NULL, 0) == DISP_CHANGE_SUCCESSFUL;
}

bool Display::_getModes()
{
    DEVMODE devmode = {0};
    
    int w, h;
    int f;
    int i = 0;
    while(EnumDisplaySettings(NULL, i, &devmode)){
        w = devmode.dmPelsWidth;
        h = devmode.dmPelsHeight;
        f = devmode.dmDisplayFrequency;
        
        //std::cout << "Mode[" << i << "]: " << w << "x" << h << "@" << f << std::endl;
        
        _modes->push_back(std::make_pair(
                Mode(w, h, f),
                devmode));
        i++;
    }
    
    _modes->resize(i);
    
    return true;
}
