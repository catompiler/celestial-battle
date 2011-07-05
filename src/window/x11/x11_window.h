#ifndef _X11_WINDOW_H
#define	_X11_WINDOW_H

#include <string>
#include "window/windowslist.h"
#include "event/event.h"
#include "object/object.h"
#include "window/window_types.h"
#include "window/window_events.h"
#include "window/pixelattribs.h"

//#define USE_XIM

class GLContext;

//#define DECLARE_ONEVENT_METHOD(e) On ## e ## Event::Base& on ## e()

class Window
    :public Object
{
public:
    
    int left() const;
    void setLeft(int left_);
    
    int top() const;
    void setTop(int top_);
    
    unsigned int width() const;
    void setWidth(unsigned int width_);
    
    unsigned int height() const;
    void setHeight(unsigned int height_);
    
    std::string title() const;
    void setTitle(const std::string& title_);
    
    bool active() const;
    
    bool showCursor(bool show_);
    
    
    bool makeCurrent(GLContext* glcxt_) /* const */;
    
    void swapBuffers() /* const */;
    
    static Window* create(const std::string& title_,
                          int left_, int top_,
                          int width_, int height_,
                          const PixelAttribs& pixelAttribs_);
    
    static void destroy(Window* window_);
    
    static int processEvents();
    
    
    windowid_t id() const{
        return _id;
    }
    
    
    OnCreateEvent::Base& onCreate(){
        return _onCreate;
    }
    
    OnCloseEvent::Base& onClose(){
        return _onClose;
    }
    
    OnPaintEvent::Base& onPaint(){
        return _onPaint;
    }
    
    OnResizeEvent::Base& onResize(){
        return _onResize;
    }
    
    OnKeyPressEvent::Base& onKeyPress(){
        return _onKeyPress;
    }
    
    OnKeyReleaseEvent::Base& onKeyRelease(){
        return _onKeyRelease;
    }
    
    OnMousePressEvent::Base& onMousePress(){
        return _onMousePress;
    }
    
    OnMouseReleaseEvent::Base& onMouseRelease(){
        return _onMouseRelease;
    }
    
    OnMouseMotionEvent::Base& onMouseMotion(){
        return _onMouseMotion;
    }
    
    OnFocusInEvent::Base& onFocusIn(){
        return _onFocusIn;
    }
    
    OnFocusOutEvent::Base& onFocusOut(){
        return _onFocusOut;
    }
    
private:
    
    Window();
    ~Window();
    
    OnCreateEvent _onCreate;
    OnCloseEvent _onClose;
    OnPaintEvent _onPaint;
    OnResizeEvent _onResize;
    OnKeyPressEvent _onKeyPress;
    OnKeyReleaseEvent _onKeyRelease;
    OnMousePressEvent _onMousePress;
    OnMouseReleaseEvent _onMouseRelease;
    OnMouseMotionEvent _onMouseMotion;
    OnFocusInEvent _onFocusIn;
    OnFocusOutEvent _onFocusOut;
    
    windowid_t _id;
    
#ifdef USE_XIM
    XIC _ic;
#endif
};

#endif	/* _X11_WINDOW_H */

