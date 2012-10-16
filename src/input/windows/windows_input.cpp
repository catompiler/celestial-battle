#include <windows.h>
#include <string.h>
#include "windows_input.h"
#include <iostream>


//cat ./keys.h | awk '{print "_keys_table[  ] = "$2";"}'
    
int Input::_counter = 0;
Input::MouseState Input::_mouseState = {0};

const int Input::_keys_table_size = 256;
unsigned char* Input::_keys_table = NULL;
const int Input::_max_keys_count = 256;
Input::key_t* Input::_keys_state = NULL;


Input::Input()
{
    if(++ _counter){
        _init();
    }
}

Input::~Input()
{
    if(_counter){
        if(-- _counter == 0){
            _clean();
        }
    }
}

Input::MouseState* Input::mouseState()
{
    POINT p;
    GetCursorPos(&p);
    
    _mouseState.x = p.x;
    _mouseState.y = p.y;

    
    _mouseState.buttons_mask = 0;
    if((GetKeyState(VK_LBUTTON) & 0x80) != 0){
        _mouseState.buttons_mask |= MOUSE_LEFT;
    }
    if((GetKeyState(VK_MBUTTON) & 0x80) != 0){
        _mouseState.buttons_mask |= MOUSE_MIDDLE;
    }
    if((GetKeyState(VK_RBUTTON) & 0x80) != 0){
        _mouseState.buttons_mask |= MOUSE_RIGHT;
    }
    
    return &_mouseState;
}

void Input::setMousePos(int x, int y)
{
    SetCursorPos(x,y);
}

Input::key_t* Input::keyboardState()
{
    unsigned char keys[256];
    GetKeyboardState(keys);
    for(int i = 0; i < 256; i ++){
        if(keys[i] & 128){
            _keys_state[_keys_table[i]] = KEY_PRESSED;
        }
    }
    return _keys_state;
}

Input::key_t Input::keycodeToKey(unsigned char kc_)
{
    return _keys_table[kc_];
}

void Input::_init()
{
    _keys_table = new key_t[_keys_table_size];
    _init_table();
    _keys_state = new key_t[_max_keys_count];
    memset(_keys_state, 0x0, _max_keys_count * sizeof(key_t));
}

void Input::_clean()
{
    delete[] _keys_table;
    delete[] _keys_state;
}

void Input::_init_table()
{
    memset(_keys_table, 0x0, _keys_table_size * sizeof(key_t));
    
    _keys_table[ VK_ESCAPE ] = KEY_ESCAPE;
    _keys_table[ VK_F1 ] = KEY_F1;
    _keys_table[ VK_F2 ] = KEY_F2;
    _keys_table[ VK_F3 ] = KEY_F3;
    _keys_table[ VK_F4 ] = KEY_F4;
    _keys_table[ VK_F5 ] = KEY_F5;
    _keys_table[ VK_F6 ] = KEY_F6;
    _keys_table[ VK_F7 ] = KEY_F7;
    _keys_table[ VK_F8 ] = KEY_F8;
    _keys_table[ VK_F9 ] = KEY_F9;
    _keys_table[ VK_F10 ] = KEY_F10;
    _keys_table[ VK_F11 ] = KEY_F11;
    _keys_table[ VK_F12 ] = KEY_F12;
    _keys_table[ VK_OEM_3 ] = KEY_TILDA;
    _keys_table[ 0x30 ] = KEY_0;
    _keys_table[ 0x31 ] = KEY_1;
    _keys_table[ 0x32 ] = KEY_2;
    _keys_table[ 0x33 ] = KEY_3;
    _keys_table[ 0x34 ] = KEY_4;
    _keys_table[ 0x35 ] = KEY_5;
    _keys_table[ 0x36 ] = KEY_6;
    _keys_table[ 0x37 ] = KEY_7;
    _keys_table[ 0x38 ] = KEY_8;
    _keys_table[ 0x39 ] = KEY_9;
    _keys_table[ 0xbd ] = KEY_MINUS;//VK_OEM_MINUS
    _keys_table[ 0xbb ] = KEY_EQUAL;//VK_OEM_PLUS - EQUAL o_O
    _keys_table[ VK_OEM_5 ] = KEY_BACKSLASH;
    _keys_table[ VK_BACK ] = KEY_BACKSPACE;
    _keys_table[ VK_TAB ] = KEY_TAB;
    _keys_table[ VK_CAPITAL ] = KEY_CAPS;
    _keys_table[ VK_LSHIFT ] = KEY_LSHIFT;
    _keys_table[ VK_LCONTROL ] = KEY_LCTRL;
    _keys_table[ VK_LWIN ] = KEY_LSUPER;
    _keys_table[ VK_LMENU ] = KEY_LALT;
    _keys_table[ VK_SPACE ] = KEY_SPACE;
    _keys_table[ VK_RMENU ] = KEY_RALT;
    _keys_table[ VK_RWIN ] = KEY_RSUPER;
    _keys_table[ VK_APPS ] = KEY_CONTEXT;
    _keys_table[ VK_RCONTROL ] = KEY_RCTRL;
    _keys_table[ VK_RSHIFT ] = KEY_RSHIFT;
    _keys_table[ VK_RETURN ] = KEY_ENTER;
    _keys_table[ 0x41 ] = KEY_a;
    _keys_table[ 0x42 ] = KEY_b;
    _keys_table[ 0x43 ] = KEY_c;
    _keys_table[ 0x44 ] = KEY_d;
    _keys_table[ 0x45 ] = KEY_e;
    _keys_table[ 0x46 ] = KEY_f;
    _keys_table[ 0x47 ] = KEY_g;
    _keys_table[ 0x48 ] = KEY_h;
    _keys_table[ 0x49 ] = KEY_i;
    _keys_table[ 0x4a ] = KEY_j;
    _keys_table[ 0x4b ] = KEY_k;
    _keys_table[ 0x4c ] = KEY_l;
    _keys_table[ 0x4d ] = KEY_m;
    _keys_table[ 0x4e ] = KEY_n;
    _keys_table[ 0x4f ] = KEY_o;
    _keys_table[ 0x50 ] = KEY_p;
    _keys_table[ 0x51 ] = KEY_q;
    _keys_table[ 0x52 ] = KEY_r;
    _keys_table[ 0x53 ] = KEY_s;
    _keys_table[ 0x54 ] = KEY_t;
    _keys_table[ 0x55 ] = KEY_u;
    _keys_table[ 0x56 ] = KEY_v;
    _keys_table[ 0x57 ] = KEY_w;
    _keys_table[ 0x58 ] = KEY_x;
    _keys_table[ 0x59 ] = KEY_y;
    _keys_table[ 0x5a ] = KEY_z;
    _keys_table[ VK_OEM_4 ] = KEY_LEFTBRACKET;
    _keys_table[ VK_OEM_6 ] = KEY_RIGHTBRACKET;
    _keys_table[ VK_OEM_1 ] = KEY_SEMICOLON;
    _keys_table[ VK_OEM_7 ] = KEY_QUOTE;
    _keys_table[ 0xbc ] = KEY_COMMA;
    _keys_table[ 0xbe ] = KEY_DOT;
    _keys_table[ VK_OEM_2 ] = KEY_SLASH;
    _keys_table[ VK_SNAPSHOT ] = KEY_SYSRQ;
    _keys_table[ VK_SCROLL ] = KEY_SCROLL;
    _keys_table[ VK_PAUSE ] = KEY_PAUSE;
    _keys_table[ VK_INSERT ] = KEY_INSERT;
    _keys_table[ VK_HOME ] = KEY_HOME;
    _keys_table[ VK_DELETE ] = KEY_DELETE;
    _keys_table[ VK_END ] = KEY_END;
    _keys_table[ VK_PRIOR ] = KEY_PAGEUP;
    _keys_table[ VK_NEXT ] = KEY_PAGEDOWN;
    _keys_table[ VK_UP ] = KEY_UP;
    _keys_table[ VK_LEFT ] = KEY_LEFT;
    _keys_table[ VK_DOWN ] = KEY_DOWN;
    _keys_table[ VK_RIGHT ] = KEY_RIGHT;
    _keys_table[ VK_NUMLOCK ] = KEY_NUM;
    _keys_table[ VK_DIVIDE ] = KEY_NUMSLASH;
    _keys_table[ VK_MULTIPLY ] = KEY_NUMASTERISK;
    _keys_table[ VK_SUBTRACT ] = KEY_NUMMINUS;
    //_keys_table[  ] = KEY_NUMENTER;
    _keys_table[ VK_ADD ] = KEY_NUMPLUS;
    _keys_table[ VK_DECIMAL ] = KEY_NUMDOT;
    _keys_table[ VK_NUMPAD0 ] = KEY_NUM0;
    _keys_table[ VK_NUMPAD1 ] = KEY_NUM1;
    _keys_table[ VK_NUMPAD2 ] = KEY_NUM2;
    _keys_table[ VK_NUMPAD3 ] = KEY_NUM3;
    _keys_table[ VK_NUMPAD4 ] = KEY_NUM4;
    _keys_table[ VK_NUMPAD5 ] = KEY_NUM5;
    _keys_table[ VK_NUMPAD6 ] = KEY_NUM6;
    _keys_table[ VK_NUMPAD7 ] = KEY_NUM7;
    _keys_table[ VK_NUMPAD8 ] = KEY_NUM8;
    _keys_table[ VK_NUMPAD9 ] = KEY_NUM9;/**/
}

