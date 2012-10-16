#ifndef _WINDOWSLIST_H_
#define _WINDOWSLIST_H_

#include <map>
#include "window/window_types.h"

class Window;

class WindowsList
{
public:
    static Window* getWindow(windowid_t id_);
    static bool addWindow(windowid_t id_, Window* window_);
    static bool removeWindow(windowid_t id_);
private:
    typedef std::map<windowid_t, Window*> WindowsMap;
    static WindowsMap _windowsMap;
};

#endif  //_WINDOWSLIST_H_
