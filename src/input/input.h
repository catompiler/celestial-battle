#ifndef _INPUT_H
#define _INPUT_H

namespace input{

namespace mouse{

struct buttons{
    enum buttons_values{
        left = 1, right = 2, middle = 4
    };
};

struct State{
    int x;
    int y;
    unsigned int buttons_mask;
};
typedef State state_t;

state_t* state();
void setpos(int x, int y);

}//mouse

}//input

#endif  //_INPUT_H
