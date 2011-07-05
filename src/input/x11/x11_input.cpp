#include "x11_input.h"
#include <string.h>
#include "X11/keysym.h"


//cat ./keys.h | awk '{print "_keys_table[  ] = "$2";"}'
//cat ./keys.h | awk '{print "_keys_table[",$2,"]\t= XKeysymToKeycode(Display::display(), XK_);"}'
//cat ./keys.h | awk '{print "_keys_table[","XKeysymToKeycode(Display::display(), XK_)","] = "$2";"}'

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
    XWindow tmpwin;//returned windows
    int tmp;//returned child coordinates
    unsigned int bm;
    
    XQueryPointer(Display::display(), //display
                XRootWindow(Display::display(),
                XDefaultScreen(Display::display())), //window
                &tmpwin, &tmpwin, //root & child windows
                &_mouseState.x, &_mouseState.y, //root return
                &tmp, &tmp,//child return
                &bm /* mask */);


    //bm = (bm >> 8) & 0x7;
    _mouseState.buttons_mask = 0;
    if(bm & Button1Mask) //left
        _mouseState.buttons_mask |= MOUSE_LEFT;
    if(bm & Button3Mask) //right
        _mouseState.buttons_mask |= MOUSE_RIGHT;
    if(bm & Button2Mask) //middle
        _mouseState.buttons_mask |= MOUSE_MIDDLE;
    if(bm & Button4Mask) //scroll up
        _mouseState.buttons_mask |= MOUSE_SCROLL_UP;
    if(bm & Button5Mask) //scroll down
        _mouseState.buttons_mask |= MOUSE_SCROLL_DOWN;
    
    return &_mouseState;
}

void Input::setMousePos(int x, int y)
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

Input::key_t* Input::keyboardState()
{
    char keys_mask[32];
    int mask_byte_index;
    int mask_bit_index;
    
    memset(_keys_state, 0x0, _max_keys_count * sizeof(key_t));
    
    XQueryKeymap(Display::display(), keys_mask);
    
    for(int i = 0; i < 256; i ++){
        mask_byte_index = i / 8;
        mask_bit_index = i % 8;
        if(keys_mask[mask_byte_index] & (0x1 << mask_bit_index)){
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
    
    /*XDisplay* d = Display::display();
    KeyCode kc = XKeysymToKeycode(Display::display(), XK_Escape);*/

    _keys_table[ XKeysymToKeycode(Display::display(), XK_Escape) ] = KEY_ESCAPE;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F1) ] = KEY_F1;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F2) ] = KEY_F2;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F3) ] = KEY_F3;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F4) ] = KEY_F4;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F5) ] = KEY_F5;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F6) ] = KEY_F6;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F7) ] = KEY_F7;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F8) ] = KEY_F8;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F9) ] = KEY_F9;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F10) ] = KEY_F10;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F11) ] = KEY_F11;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_F12) ] = KEY_F12;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_grave) ] = KEY_TILDA;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_0) ] = KEY_0;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_1) ] = KEY_1;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_2) ] = KEY_2;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_3) ] = KEY_3;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_4) ] = KEY_4;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_5) ] = KEY_5;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_6) ] = KEY_6;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_7) ] = KEY_7;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_8) ] = KEY_8;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_9) ] = KEY_9;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_minus) ] = KEY_MINUS;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_equal) ] = KEY_EQUAL;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_backslash) ] = KEY_BACKSLASH;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_BackSpace) ] = KEY_BACKSPACE;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Tab) ] = KEY_TAB;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Caps_Lock) ] = KEY_CAPS;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Shift_L) ] = KEY_LSHIFT;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Control_L) ] = KEY_LCTRL;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Super_L) ] = KEY_LSUPER;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Alt_L) ] = KEY_LALT;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_space) ] = KEY_SPACE;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Alt_R) ] = KEY_RALT;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Super_R) ] = KEY_RSUPER;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Menu) ] = KEY_CONTEXT;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Control_R) ] = KEY_RCTRL;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Shift_R) ] = KEY_RSHIFT;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Return) ] = KEY_ENTER;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_a) ] = KEY_a;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_b) ] = KEY_b;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_c) ] = KEY_c;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_d) ] = KEY_d;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_e) ] = KEY_e;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_f) ] = KEY_f;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_g) ] = KEY_g;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_h) ] = KEY_h;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_i) ] = KEY_i;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_j) ] = KEY_j;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_k) ] = KEY_k;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_l) ] = KEY_l;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_m) ] = KEY_m;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_n) ] = KEY_n;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_o) ] = KEY_o;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_p) ] = KEY_p;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_q) ] = KEY_q;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_r) ] = KEY_r;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_s) ] = KEY_s;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_t) ] = KEY_t;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_u) ] = KEY_u;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_v) ] = KEY_v;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_w) ] = KEY_w;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_x) ] = KEY_x;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_y) ] = KEY_y;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_z) ] = KEY_z;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_bracketleft) ] = KEY_LEFTBRACKET;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_bracketright) ] = KEY_RIGHTBRACKET;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_semicolon) ] = KEY_SEMICOLON;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_apostrophe) ] = KEY_QUOTE;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_comma) ] = KEY_COMMA;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_period) ] = KEY_DOT;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_slash) ] = KEY_SLASH;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Sys_Req) ] = KEY_SYSRQ;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Scroll_Lock) ] = KEY_SCROLL;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Pause) ] = KEY_PAUSE;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Insert) ] = KEY_INSERT;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Home) ] = KEY_HOME;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Delete) ] = KEY_DELETE;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_End) ] = KEY_END;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Page_Up) ] = KEY_PAGEUP;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Page_Down) ] = KEY_PAGEDOWN;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Up) ] = KEY_UP;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Left) ] = KEY_LEFT;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Down) ] = KEY_DOWN;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Right) ] = KEY_RIGHT;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_Num_Lock) ] = KEY_NUM;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Divide) ] = KEY_NUMSLASH;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Multiply) ] = KEY_NUMASTERISK;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Subtract) ] = KEY_NUMMINUS;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Enter) ] = KEY_NUMENTER;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Add) ] = KEY_NUMPLUS;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Delete) ] = KEY_NUMDOT;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Insert) ] = KEY_NUM0;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_End) ] = KEY_NUM1;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Down) ] = KEY_NUM2;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Page_Down) ] = KEY_NUM3;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Left) ] = KEY_NUM4;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Begin) ] = KEY_NUM5;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Right) ] = KEY_NUM6;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Home) ] = KEY_NUM7;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Up) ] = KEY_NUM8;
    _keys_table[ XKeysymToKeycode(Display::display(), XK_KP_Page_Up) ] = KEY_NUM9;
}
