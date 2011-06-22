#include "display/display.h"



namespace input{


namespace mouse{


static state_t _state;

state_t* state()
{
    XWindow tmpwin;//returned windows
    int tmp;//returned child coordinates
    unsigned int bm;
    
    XQueryPointer(Display::display(), //display
                XRootWindow(Display::display(),
                XDefaultScreen(Display::display())), //window
                &tmpwin, &tmpwin, //root & child windows
                &_state.x, &_state.y, //root return
                &tmp, &tmp,//child return
                &bm /* mask */);


    //bm = (bm >> 8) & 0x7;
    _state.buttons_mask = 0;
    if(bm & Button1Mask) //left
        _state.buttons_mask |= buttons::left;
    if(bm & Button3Mask) //right
        _state.buttons_mask |= buttons::right;
    if(bm & Button2Mask) //middle
        _state.buttons_mask |= buttons::middle;
    
    return &_state;
}


void setpos(int x, int y)
{
    XWindow rootwin = XRootWindow(Display::display(),
                        XDefaultScreen(Display::display()));
    XWarpPointer(Display::display(),
            rootwin,
            rootwin,
            0,0,
            0,0,
            x,y);
}


}//mouse


}//input
