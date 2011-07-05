#include "windowslist.h"
#include "window/window.h"

WindowsList::WindowsMap WindowsList::_windowsMap;

Window* WindowsList::getWindow(windowid_t id_)
{
    WindowsMap::iterator it = _windowsMap.find(id_);
    if(it == _windowsMap.end()){
        return NULL;
    }
    return (*it).second;
}

bool WindowsList::addWindow(windowid_t id_, Window* window_)
{
    WindowsMap::iterator it = _windowsMap.find(id_);
    if(it == _windowsMap.end()){
        _windowsMap[id_] = window_;
        return true;
    }
    return false;
}

bool WindowsList::removeWindow(windowid_t id_)
{
    WindowsMap::iterator it = _windowsMap.find(id_);
    if(it == _windowsMap.end()){
        return false;
    }
    _windowsMap.erase(it);
    return true;
}
