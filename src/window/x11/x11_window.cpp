#include "x11_window.h"

#include "glcontext/glcontext.h"
#include "log/log.h"

#ifdef OS_LINUX

#include <X11/Xutil.h>
#include <GL/glx.h>
#include "glcontext/x11/x11_glcontext.h"
#include "display/x11/x11_display.h"

int X11Window::_counter = 0;
Atom X11Window::_atom_del_win = 0;
Cursor X11Window::_nullCursor = None;
X11Window::X11ErrorHandler X11Window::_orig_handler = NULL;



X11Window::X11Window()
        :GLWindow()
{
}

X11Window::~X11Window()
{
    if(_id != 0) XDestroyWindow(display::get_x11_display(), _id);
    if(_counter != 0){
        if(--_counter == 0){
            _term_x11();
        }
    }
}

int X11Window::left() const
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(display::get_x11_display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    return x;
}

void X11Window::setLeft(int left_)
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(display::get_x11_display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    XMoveWindow(display::get_x11_display(), _id, left_, y);
}

int X11Window::top() const
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(display::get_x11_display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    return y;
}

void X11Window::setTop(int top_)
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(display::get_x11_display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    XMoveWindow(display::get_x11_display(), _id, x, top_);
}

unsigned int X11Window::width() const
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(display::get_x11_display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    return w;
}

void X11Window::setWidth(unsigned int width_)
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(display::get_x11_display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    XResizeWindow(display::get_x11_display(), _id, width_, h);
}

unsigned int X11Window::height() const
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(display::get_x11_display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    return h;
}

void X11Window::setHeight(unsigned int height_)
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(display::get_x11_display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    XResizeWindow(display::get_x11_display(), _id, w, height_);
}

std::string X11Window::title() const
{
    char* name;
    std::string res;
    if(XFetchName(display::get_x11_display(), _id, &name) != 0){
        res = name;
        XFree(name);
    }
    
    return res;
}

void X11Window::setTitle(const std::string& title_)
{
    XStoreName(display::get_x11_display(), _id, title_.c_str());
}

bool X11Window::active() const
{
    windowid_t activeWin;
    int focusState;
    
    XGetInputFocus(display::get_x11_display(), &activeWin, &focusState);

    return activeWin == _id;
}

bool X11Window::showCursor(bool show_)
{
    if(show_ == false){
        if(_nullCursor == None){
            //create a null cursor
            char bm[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
            Pixmap pix = XCreateBitmapFromData(display::get_x11_display(), _id, bm, 8, 8);

            XColor black = {0};
            //memset(&black, 0, sizeof(XColor));
            black.flags = DoRed | DoGreen | DoBlue;

            _nullCursor = XCreatePixmapCursor(display::get_x11_display(), pix, pix, &black, &black, 0, 0);
            XFreePixmap(display::get_x11_display(), pix);
        }
        XDefineCursor(display::get_x11_display(), _id, _nullCursor);
    }
    else{
        XUndefineCursor(display::get_x11_display(), _id);
    }
    return show_;
}

bool X11Window::makeCurrent(GLContext* glcxt_) /* const */
{
    if(glcxt_ == NULL){
        return glXMakeCurrent(display::get_x11_display(), 0, 0);
    }
    return glXMakeCurrent(display::get_x11_display(), _id,
            static_cast<GLXContext>(glcxt_->id()));
}

void X11Window::swapBuffers() /* const */
{
    glXSwapBuffers(display::get_x11_display(), _id);
}


X11Window* X11Window::create(const std::string& title_,
                      int left_, int top_,
                      int width_, int height_,
                      const GLWindow::PixelAttribs& pixelAttribs_)
{
    X11Window* window;
    
    windowid_t winid;
    XVisualInfo *visualinfo;//visual info
    int nfbconfigs;//framebuffer configs count
    int best_fbc = 0; // selected fbconfig
    int sample_buffers;// samble buffers count
    int samples; // samples count
    int best_sample_buffers = 0; //most appropriate sample buffers count
    int best_samples = 0; //most appropriate samples
    GLXFBConfig* fbconfigs;//framebuffer config
    Colormap colormap;//color map
    //gl attribs
    int attribs[]={GLX_RENDER_TYPE,GLX_RGBA_BIT,
        GLX_DRAWABLE_TYPE,GLX_WINDOW_BIT,
        GLX_X_VISUAL_TYPE,GLX_TRUE_COLOR,
        GLX_DOUBLEBUFFER,True,
        GLX_RED_SIZE,8,
        GLX_GREEN_SIZE,8,
        GLX_BLUE_SIZE,8,
        GLX_ALPHA_SIZE,8,
        GLX_DEPTH_SIZE,24,
        GLX_STENCIL_SIZE,0,
        None
    };

    //win attribs
    XSetWindowAttributes winattribs = {0};
    
    //if display not opened
    if(display::get_x11_display() == NULL){
        return NULL;
    }
    //init x11
    if(_counter++ == 0){
        if(_init_x11() == false){
            return NULL;
        }
    }
    
    //setup attribs
    attribs[7] = pixelAttribs_.doubleBuffer;
    attribs[9] = pixelAttribs_.redSize;
    attribs[11] = pixelAttribs_.greenSize;
    attribs[13] = pixelAttribs_.blueSize;
    attribs[15] = pixelAttribs_.alphaSize;
    attribs[17] = pixelAttribs_.depthSize;
    attribs[19] = pixelAttribs_.stencilSize;
    
    //get framebuffer configs
    fbconfigs = glXChooseFBConfig(display::get_x11_display(), XDefaultScreen(display::get_x11_display()),
                                  attribs, &nfbconfigs);
    if(fbconfigs == NULL){
        return NULL;
    }

    //Log::instance()->log(Log::LOG_ERROR,"Found framebuffer configs: %d",fbconfigs);

    for(int i=0;i<nfbconfigs;i++){
        //get visual info
        visualinfo = glXGetVisualFromFBConfig(display::get_x11_display(),fbconfigs[i]);
        if(visualinfo != NULL){
            //get sample buffer and samples count from fbconfig
            glXGetFBConfigAttrib(display::get_x11_display(),fbconfigs[i],GLX_SAMPLE_BUFFERS,&sample_buffers);
            glXGetFBConfigAttrib(display::get_x11_display(),fbconfigs[i],GLX_SAMPLES,&samples);
            //Log::instance()->log(Log::LOG_ERROR,"FBConfig %d; SAMPLE_BUFFERS %d; SAMPLES %d",i,sample_buffers,samples);
            //if values less requested
            if(sample_buffers <= pixelAttribs_.sampleBuffers &&
                    samples <= pixelAttribs_.samples){
                //if values greater than finded
                if(sample_buffers >= best_sample_buffers && samples > best_samples){
                    best_sample_buffers = sample_buffers;
                    best_samples = samples;
                    best_fbc = i;
                }
            }
            //free visualinfo
            XFree(visualinfo);
            //if values is requested
            if(best_sample_buffers == pixelAttribs_.sampleBuffers &&
                    best_samples == pixelAttribs_.samples){
                break;
            }
        }
    }

    //"Selected framebuffer config with %d sample buffers and %d samples.",best_sample_buffers,best_samples);
    
    //get visual info
    visualinfo = glXGetVisualFromFBConfig(display::get_x11_display(),fbconfigs[best_fbc]);

    //create color map
    colormap = XCreateColormap(display::get_x11_display(),
            XRootWindow(display::get_x11_display(), XDefaultScreen(display::get_x11_display())),
            visualinfo->visual, AllocNone);

    winattribs.colormap = colormap;
    winattribs.event_mask = StructureNotifyMask | ExposureMask;
            /*KeyPressMask | StructureNotifyMask |
                SubstructureNotifyMask |
                PointerMotionMask | ButtonMotionMask |
                ButtonPressMask | ButtonReleaseMask |
                FocusChangeMask | ExposureMask |
                Button3MotionMask;*/
    winattribs.background_pixmap = None;
    winattribs.border_pixel = 0;

    //create window
    winid = XCreateWindow(display::get_x11_display(), //display
                XRootWindow(display::get_x11_display(), XDefaultScreen(display::get_x11_display())), //parent
                left_, //left
                top_, //top
                width_,    //width
                height_, //height
                0, //border
                visualinfo->depth,//depth
                InputOutput,//class
                visualinfo->visual,//visual
                CWBorderPixel | CWColormap | CWEventMask, &winattribs);

    if(!winid){
        return NULL;
    }
    
    window = new X11Window();
    window->_id = winid;
    addWindow(winid, window);

    if(_atom_del_win){
        XSetWMProtocols(display::get_x11_display(), winid, &_atom_del_win, True);
    }

    //set window text
    XStoreName(display::get_x11_display(), winid, title_.c_str());
    //map|show window
    XMapWindow(display::get_x11_display(), winid);

    //free visualinfo
    XFree(visualinfo);
    //free fbconfig
    XFree(fbconfigs);
    
    return window;
}

void X11Window::destroy(X11Window* window_)
{
    delete window_;
}

int X11Window::processEvents()
{
    size_t events_processed = 0;

    X11Window* window;
    windowid_t wid;
    //message
    XEvent event;
    while(XPending(display::get_x11_display()) > 0){
        //if(XPeekEvent(display,&event)){
        XNextEvent(display::get_x11_display(),&event);
        
        wid = event.xany.window;
        window = static_cast<X11Window*>(getWindow(wid));
        if(window == NULL) continue;

        ++ events_processed;

        switch(event.type){
            case CreateNotify:
                { CreateEvent e(window);
                window->_onCreate(&e); }
                break;
                
            case ClientMessage:
                //close window
                //onClose();
                if(static_cast<Atom>(event.xclient.data.l[0]) == _atom_del_win){
                    //_done = true;
                    CloseEvent e(window);
                    window->_onClose(&e);
                }
                break;
                
            case DestroyNotify:
                removeWindow(wid);
                break;
                
            case KeyPress://key press
                break;
            case ButtonPress://mouse button press
                break;
            case ButtonRelease://mouse button release
                break;
            case MotionNotify://mouse motion notify
                break;
            case FocusIn://focus in
                break;
            case FocusOut://focus out
                break;
            case Expose://repaint
                //onDraw();
                { PaintEvent e(window);
                window->_onPaint(&e); }
                break;
                
            case ConfigureNotify://resize
                //onResize(event.xconfigure.width, event.xconfigure.height);
                { ResizeEvent e(window , event.xconfigure.width,
                                         event.xconfigure.height);
                window ->_onResize(&e); }
                break;
                
            case MapNotify:
                break;
            case ReparentNotify:
                break;
            default:
                break;
        }
    }
    return events_processed;
}

bool X11Window::_init_x11()
{
    _orig_handler = static_cast<X11ErrorHandler>(XSetErrorHandler(_errorHandler));
    
    /*#define _XPrivDisplay _XPrivDisplay
    XSelectInput(display::get_x11_display(), DefaultRootWindow(display::get_x11_display()), SubstructureNotifyMask);*/
    
    //get DEL_WIN atom
    _atom_del_win = XInternAtom(display::get_x11_display(), "WM_DELETE_WINDOW", False);
    
    return true;
}

void X11Window::_term_x11()
{
    //free cursor
    if(_nullCursor != None) {
        XFreeCursor(display::get_x11_display(), _nullCursor);
        _nullCursor = None;
    }
    
    XSetErrorHandler(_orig_handler);
}

int X11Window::_errorHandler(Display* display_, XErrorEvent* e)
{
    #define MAX_ERROR_TEXT_LEN 31
    char error_text_buf[MAX_ERROR_TEXT_LEN + 1];
    
    /*#define MAX_ERROR_DB_TEXT_LEN 255
    char error_db_text_buf[MAX_ERROR_DB_TEXT_LEN + 1];*/
    
    XGetErrorText(display_, e->error_code, error_text_buf, MAX_ERROR_TEXT_LEN);
    //std::cout << error_text_buf << std::endl;
    
    /*XGetErrorDatabaseText(display_, "XlibMessage", "XRequest",
            "Unknown error", error_db_text_buf, MAX_ERROR_DB_TEXT_LEN);*/
    
    log(Log::Error) << "X11 Error: " << error_text_buf
        << "; Major reques opcode: " << static_cast<unsigned int>(e->request_code)
        << "; Minor reques opcode: " << static_cast<unsigned int>(e->minor_code)
        << std::endl;
    
    return 0;
}

Display* X11Window::display()
{
    return display::get_x11_display();
}


#endif  //OS_LINUX
