#include <stdlib.h>

XDisplay* Display::_display = NULL;
int Display::_counter = 0;

static Display display;

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
        }
    }
}

Display::~Display()
{
    if(_counter != 0){
        if(--_counter == 0){
            //close display
            if(_display != NULL){
                XCloseDisplay(_display);
                _display = NULL;
            }
        }
    }
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

