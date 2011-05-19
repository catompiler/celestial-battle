#include "osal/osdef.h"
#ifdef OS_LINUX

#include "x11_display.h"
#include <stdlib.h>


namespace display{

struct DisplayOpener{
    
    DisplayOpener()
    {
        if(_counter++ == 0){
            //open display
            display = XOpenDisplay(getenv("DISPLAY"));
            if(display == NULL){
                return;
            }
            //test connection to X
            if(!XNoOp(display)){
                XCloseDisplay(display);
                display = NULL;
            }
        }
    }

    ~DisplayOpener()
    {
        if(_counter != 0){
            if(--_counter == 0){
                //close display
                if(display != NULL){
                    XCloseDisplay(display);
                    display = NULL;
                }
            }
        }
    }
    
    static Display* display;
    static int _counter;
};

Display* DisplayOpener::display = NULL;
int DisplayOpener::_counter = 0;

static DisplayOpener _opener;

Display* get_x11_display()
{
    return DisplayOpener::display;
}


int x11_width()
{
    return XDisplayWidth(DisplayOpener::display,XDefaultScreen(DisplayOpener::display));
}

int x11_height()
{
    return XDisplayHeight(DisplayOpener::display,XDefaultScreen(DisplayOpener::display));
}

}//display

#endif  //OS_LINUX
