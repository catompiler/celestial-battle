#ifndef _X11_INPUT_H_ 
#define _X11_INPUT_H_

#include "display/display.h"
#include "input/keys.h"
#include "input/mouse_buttons.h"



class Input{
public:
    
    struct MouseState{
        int x;
        int y;
        unsigned int buttons_mask;
    };
    
    typedef unsigned char key_t;
    
    Input();
    ~Input();
    
    static MouseState* mouseState();
    static void setMousePos(int x, int y);
    
    static key_t* keyboardState();
    static key_t keycodeToKey(unsigned char kc_);
    
private:
    static int _counter;
    
    static MouseState _mouseState;
    
    static const int _keys_table_size;
    static key_t* _keys_table;
    static const int _max_keys_count;
    static key_t* _keys_state;
    
    static void _init();
    static void _clean();
    static void _init_table();
};

static Input __init_input;

#endif  //_X11_INPUT_H_
