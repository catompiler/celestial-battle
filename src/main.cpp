#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "log/log.h"
#include "delegate/delegate.h"
#include "event/event.h"
#include <functional>

class Foo{
public:
    void func(){
        std::cout << "Foo::func()" << std::endl;
    }
    void ufunc(int a1){
        std::cout << "Foo::func(" << a1 << ")" << std::endl;
    }
    void bfunc(int a1, float a2){
        std::cout << "Foo::func(" << a1 << ", " << a2 << ")" << std::endl;
    }
};

int main(int argc, char** argv)
{
    log(Log::Information) << "Hello, Log!" << std::endl;
    
    int array[]={12,23,56,34,45};
    Foo f;
    std::for_each(array, array + 5, make_delegate(&f, &Foo::ufunc));
    
    BinaryEvent<int, float> event;
    event.addHandler(make_delegate(&f, &Foo::bfunc));
    
    event(10, 3.14);
    
    event.removeHandler(&f);
    
    return (EXIT_SUCCESS);
}

