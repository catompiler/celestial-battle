#ifndef WINDOW_H
#define	WINDOW_H

#include <string>
#include "event/event.h"
#include "object/object.h"

class GLContext;


class Window;

class WindowEvent
    :public ObjectEvent
{
public:
    WindowEvent(Window* window_);
    ~WindowEvent();

    Window* window() const;

protected:
    Window* _window;
};


class Window
    :public Object
{
public:
    
    struct PixelAttribs{
        bool doubleBuffer;
        int redSize;
        int greenSize;
        int blueSize;
        int alphaSize;
        int depthSize;
        int stencilSize;
        int sampleBuffers;
        int samples;
    };

    
    typedef WindowEvent CreateEvent;
    typedef WindowEvent CloseEvent;
    typedef WindowEvent PaintEvent;

    class ResizeEvent
        :public WindowEvent
    {
    public:
        ResizeEvent(Window* window_, int width_, int height_);
        ~ResizeEvent();
    
        int width() const;
        int height() const;
    
    protected:
        int _width;
        int _height;
    };
    
    typedef UnaryEvent<CreateEvent*> OnCreateEvent;
    typedef UnaryEvent<CloseEvent*> OnCloseEvent;
    typedef UnaryEvent<PaintEvent*> OnPaintEvent;
    typedef UnaryEvent<ResizeEvent*> OnResizeEvent;
    
    
    OnCreateEvent::Base& onCreate();
    OnCloseEvent::Base& onClose();
    OnPaintEvent::Base& onPaint();
    OnResizeEvent::Base& onResize();
    
    
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
    
    
    static Window* create(const std::string& title_,
                          int left_, int top_,
                          int width_, int height_,
                          const PixelAttribs& pixelAttribs_);
    
    static void destroy(Window* window_);
    
    static int processEvents();
    
protected:

    OnCreateEvent _onCreate;
    OnCloseEvent _onClose;
    OnPaintEvent _onPaint;
    OnResizeEvent _onResize;
};

#endif	/* WINDOW_H */

