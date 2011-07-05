#include "event.h"

Event::Event()
{
}

Event::~Event()
{
}

void Event::operator()()
{
    for(
#if __GNUC__ > 3
            typename
#endif
            DelegateList::iterator it = _delegate_list.begin();
            it != _delegate_list.end(); ++it){
        (*it)();
    }
}

