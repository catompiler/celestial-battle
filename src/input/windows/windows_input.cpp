#include <windows.h>


namespace input{


namespace mouse{


static state_t _state;
    
state_t* state()
{
    POINT p;
    GetCursorPos(&p);
    
    _state.x = p.x;
    _state.y = p.y;


    _state.buttons_mask = 0;
    if((GetKeyState(VK_LBUTTON) & 0x80) != 0){
        _state.buttons_mask |= buttons::left;
    }
    if((GetKeyState(VK_MBUTTON) & 0x80) != 0){
        _state.buttons_mask |= buttons::middle;
    }
    if((GetKeyState(VK_RBUTTON) & 0x80) != 0){
        _state.buttons_mask |= buttons::right;
    }
    
    return &_state;
}


void setpos(int x, int y)
{
    SetCursorPos(x,y);
}


}//mouse


}//input