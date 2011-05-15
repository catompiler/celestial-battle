#ifndef WINDOW_H
#define	WINDOW_H

#include <string>
#include "event/event.h"

class GLContext;

class Window {
public:
    
    typedef Event CreateEvent;
    typedef Event CloseEvent;
    typedef Event PaintEvent;
    typedef BinaryEvent<int, int> ResizeEvent;
    
    
    CreateEvent::Base& createEvent();
    CloseEvent::Base& closeEvent();
    PaintEvent::Base& paintEvent();
    ResizeEvent::Base& resizeEvent();
    
    
    virtual ~Window();
    
    
    virtual int left() const = 0;
    virtual void setLeft(int left_) = 0;
    
    virtual int top() const = 0;
    virtual void setTop(int top_) = 0;
    
    virtual unsigned int width() const = 0;
    virtual void setWidth(unsigned int width_) = 0;
    
    virtual unsigned int height() const = 0;
    virtual void setHeight(unsigned int height_) = 0;
    
    virtual std::string title() const = 0;
    virtual void setTitle(const std::string& title_) = 0;
    
    virtual bool active() const = 0;
    
    virtual bool showCursor(bool show_) = 0;
    
    
    virtual bool makeCurrent(const GLContext& glcxt_) /* const */ = 0;
    
    virtual void swapBuffers() /* const */ = 0;
    
protected:

    CreateEvent _createEvent;
    CloseEvent _closeEvent;
    PaintEvent _paintEvent;
    ResizeEvent _resizeEvent;
};

#endif	/* WINDOW_H */

