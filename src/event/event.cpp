#include "event.h"

Event::Event()
{
}

Event::~Event()
{
}

void Event::operator()()
{
    for(typename DelegateList::iterator it = _delegate_list.begin();
            it != _delegate_list.end(); ++it){
        (*it)();
    }
}
