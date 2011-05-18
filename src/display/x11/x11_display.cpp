#include "osal/osdef.h"
#ifdef OS_LINUX

#include "x11_display.h"
#include <stdlib.h>


namespace display{

struct Opener{
    
    Opener()
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

    ~Opener()
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

Display* Opener::display = NULL;
int Opener::_counter = 0;

static Opener _opener;

Display* get_x11_display()
{
    return Opener::display;
}


int x11_width()
{
    return XDisplayWidth(Opener::display,XDefaultScreen(Opener::display));
}

int x11_height()
{
    return XDisplayHeight(Opener::display,XDefaultScreen(Opener::display));
}

}//display

#endif  //OS_LINUX
