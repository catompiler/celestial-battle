#include "osal/osdef.h"
#ifdef OS_LINUX


#include "x11_input.h"

#include <X11/Xlib.h>
#include "display/x11/x11_display.h"


namespace input{

namespace mouse{

static state_t _state;
    
state_t* x11_state()
{
    Window tmpwin;//returned windows
    int tmp;//returned child coordinates
    unsigned int bm;
    
    XQueryPointer(display::get_x11_display(), //display
                XRootWindow(display::get_x11_display(),
                        XDefaultScreen(display::get_x11_display())), //window
                &tmpwin, &tmpwin, //root & child windows
                &_state.x, &_state.y, //root return
                &tmp, &tmp,//child return
                &bm /* mask */);

    //bm = (bm >> 8) & 0x7;
    _state.buttons_mask = 0;
    if(bm & Button1Mask) //left
        _state.buttons_mask |= buttons::left;
    if(bm & Button2Mask) //right
        _state.buttons_mask |= buttons::right;
    if(bm & Button3Mask) //middle
        _state.buttons_mask |= buttons::middle;
    
    return &_state;
}

void x11_setpos(int x, int y)
{
    Window rootwin = XRootWindow(display::get_x11_display(),
                        XDefaultScreen(display::get_x11_display()));
    XWarpPointer(display::get_x11_display(),
            rootwin,
            rootwin,
            0,0,
            0,0,
            x,y);
}

}//mouse

}//input

#endif  //OS_LINUX
