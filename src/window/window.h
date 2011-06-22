#ifndef _GLWINDOW_H
#define	_GLWINDOW_H

#include <string>
#include <map>
#include "event/event.h"
#include "object/object.h"
#include "window_types.h"

class GLContext;


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
    
    
    windowid_t id() const;
    
    
    static Window* create(const std::string& title_,
                          int left_, int top_,
                          int width_, int height_,
                          const PixelAttribs& pixelAttribs_);
    
    static void destroy(Window* window_);
    
    static int processEvents();
    
private:
    
    Window();
    ~Window();
    
    typedef std::map<windowid_t, Window*> WindowsMap;
    static WindowsMap _windowsMap;
    static Window* getWindow(windowid_t id_);
    static bool addWindow(windowid_t id_, Window* window_);
    static bool removeWindow(windowid_t id_);
    
    OnCreateEvent _onCreate;
    OnCloseEvent _onClose;
    OnPaintEvent _onPaint;
    OnResizeEvent _onResize;
    
    windowid_t _id;
};

#endif	/* _GLWINDOW_H */

