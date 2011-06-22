#define Window XWindow
#define Display XDisplay
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <X11/Xatom.h>
#undef Window
#undef Display
#include "display/display.h"
#include "glcontext/glcontext.h"
#include "log/log.h"


static int _counter = 0;

static Atom _atom_del_win = 0;
static Cursor _nullCursor = None;

typedef int (*X11ErrorHandler)(XDisplay*, XErrorEvent *);
static X11ErrorHandler _orig_handler = NULL;
static int _errorHandler(XDisplay* display_, XErrorEvent* e);


static bool _init_x11()
{
    _orig_handler = static_cast<X11ErrorHandler>(XSetErrorHandler(_errorHandler));
    
    /*#define _XPrivDisplay _XPrivDisplay
    XSelectInput(Display::display(), DefaultRootWindow(Display::display()), SubstructureNotifyMask);*/
    
    //get DEL_WIN atom
    _atom_del_win = XInternAtom(Display::display(), "WM_DELETE_WINDOW", False);
    
    return true;
}


static void _term_x11()
{
    //free cursor
    if(_nullCursor != None) {
        XFreeCursor(Display::display(), _nullCursor);
        _nullCursor = None;
    }
    
    XSetErrorHandler(_orig_handler);
}


static int _errorHandler(XDisplay* display_, XErrorEvent* e)
{
    #define MAX_ERROR_TEXT_LEN 64
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



Window::Window()
{
    _id = 0;
}

Window::~Window()
{
    if(_id != 0){
        XDestroyWindow(Display::display(), _id);
        removeWindow(_id);
    }
}


int Window::left() const
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(Display::display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    return x;
}


void Window::setLeft(int left_)
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(Display::display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    XMoveWindow(Display::display(), _id, left_, y);
}


int Window::top() const
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(Display::display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    return y;
}


void Window::setTop(int top_)
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(Display::display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    XMoveWindow(Display::display(), _id, x, top_);
}


unsigned int Window::width() const
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(Display::display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    return w;
}


void Window::setWidth(unsigned int width_)
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(Display::display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    XResizeWindow(Display::display(), _id, width_, h);
}


unsigned int Window::height() const
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(Display::display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    return h;
}


void Window::setHeight(unsigned int height_)
{
    windowid_t rootwin;
    int x, y;
    unsigned int w, h, tmp;
    
    XGetGeometry(Display::display(), _id, &rootwin, &x, &y, &w, &h, &tmp, &tmp);
    
    XResizeWindow(Display::display(), _id, w, height_);
}


std::string Window::title() const
{
    char* name;
    std::string res;
    if(XFetchName(Display::display(), _id, &name) != 0){
        res = name;
        XFree(name);
    }
    
    return res;
}


void Window::setTitle(const std::string& title_)
{
    XStoreName(Display::display(), _id, title_.c_str());
}


bool Window::active() const
{
    windowid_t activeWin;
    int focusState;
    
    XGetInputFocus(Display::display(), &activeWin, &focusState);


    return activeWin == _id;
}


bool Window::showCursor(bool show_)
{
    if(show_ == false){
        if(_nullCursor == None){
            //create a null cursor
            char bm[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
            Pixmap pix = XCreateBitmapFromData(Display::display(), _id, bm, 8, 8);


            XColor black = {0};
            //memset(&black, 0, sizeof(XColor));
            black.flags = DoRed | DoGreen | DoBlue;


            _nullCursor = XCreatePixmapCursor(Display::display(), pix, pix, &black, &black, 0, 0);
            XFreePixmap(Display::display(), pix);
        }
        XDefineCursor(Display::display(), _id, _nullCursor);
    }
    else{
        XUndefineCursor(Display::display(), _id);
    }
    return show_;
}


bool Window::makeCurrent(GLContext* glcxt_) /* const */
{
    if(glcxt_ == NULL){
        return glXMakeCurrent(Display::display(), 0, 0);
    }
    return glXMakeCurrent(Display::display(), _id, glcxt_->id());
}


void Window::swapBuffers() /* const */
{
    glXSwapBuffers(Display::display(), _id);
}


Window* Window::create(const std::string& title_,
                      int left_, int top_,
                      int width_, int height_,
                      const Window::PixelAttribs& pixelAttribs_)
{
    Window* window;
    
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
    if(Display::display() == NULL){
        return NULL;
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
    fbconfigs = glXChooseFBConfig(Display::display(), XDefaultScreen(Display::display()),
                                  attribs, &nfbconfigs);
    if(fbconfigs == NULL){
        return NULL;
    }


    //Log::instance()->log(Log::LOG_ERROR,"Found framebuffer configs: %d",fbconfigs);


    for(int i=0;i<nfbconfigs;i++){
        //get visual info
        visualinfo = glXGetVisualFromFBConfig(Display::display(),fbconfigs[i]);
        if(visualinfo != NULL){
            //get sample buffer and samples count from fbconfig
            glXGetFBConfigAttrib(Display::display(),fbconfigs[i],GLX_SAMPLE_BUFFERS,&sample_buffers);
            glXGetFBConfigAttrib(Display::display(),fbconfigs[i],GLX_SAMPLES,&samples);
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
    visualinfo = glXGetVisualFromFBConfig(Display::display(),fbconfigs[best_fbc]);


    //create color map
    colormap = XCreateColormap(Display::display(),
            XRootWindow(Display::display(), XDefaultScreen(Display::display())),
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
    winid = XCreateWindow(Display::display(), //display
                XRootWindow(Display::display(), XDefaultScreen(Display::display())), //parent
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
        //free visualinfo
        XFree(visualinfo);
        //free fbconfig
        XFree(fbconfigs);
        return NULL;
    }
    
    window = new Window();
    window->_id = winid;
    addWindow(winid, window);

    //init x11
    if(_counter++ == 0){
        _init_x11();
    }

    if(_atom_del_win){
        XSetWMProtocols(Display::display(), winid, &_atom_del_win, True);
    }


    //set window text
    XStoreName(Display::display(), winid, title_.c_str());
    //map|show window
    XMapWindow(Display::display(), winid);


    //free visualinfo
    XFree(visualinfo);
    //free fbconfig
    XFree(fbconfigs);
    
    return window;
}


void Window::destroy(Window* window_)
{
    delete window_;
    if(_counter != 0){
        if(--_counter == 0){
            _term_x11();
        }
    }
}


int Window::processEvents()
{
    size_t events_processed = 0;


    Window* window;
    windowid_t wid;
    //message
    XEvent event;
    while(XPending(Display::display()) > 0){
        //if(XPeekEvent(display,&event)){
        XNextEvent(Display::display(),&event);
        
        wid = event.xany.window;
        window = static_cast<Window*>(getWindow(wid));
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


