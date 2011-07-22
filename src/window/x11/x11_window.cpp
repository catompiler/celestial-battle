#define Window XWindow
#define Display XDisplay
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <X11/Xatom.h>
#undef Window
#undef Display
#include <vector>
#include "display/display.h"
#include "glcontext/glcontext.h"
#include "log/log.h"
#include "input/input.h"
#include "x11_window.h"
#include "iconv/iconv.h"

//#define USE_XIM

static int _counter = 0;

static Atom _atom_del_win = 0;
static Cursor _nullCursor = None;

typedef int (*X11ErrorHandler)(XDisplay*, XErrorEvent *);
static X11ErrorHandler _orig_handler = NULL;
static int _errorHandler(XDisplay* display_, XErrorEvent* e);

#ifdef USE_XIM
static XIM _im = NULL;
#endif

static bool _init_x11()
{
    _orig_handler = static_cast<X11ErrorHandler>(XSetErrorHandler(_errorHandler));
    
    /*#define _XPrivDisplay _XPrivDisplay
    XSelectInput(Display::display(), DefaultRootWindow(Display::display()), SubstructureNotifyMask);*/
    
    //get DEL_WIN atom
    _atom_del_win = XInternAtom(Display::display(), "WM_DELETE_WINDOW", False);
    
#ifdef USE_XIM
    _im = XOpenIM(Display::display(), NULL, NULL, NULL);
    //if(_im == NULL) return false;
#endif
    
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

#ifdef USE_XIM
    if(_im) XCloseIM(_im);
#endif
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
#ifdef USE_XIM
    _ic = NULL;
#endif
}

Window::~Window()
{
    if(_id != 0){
        XDestroyWindow(Display::display(), _id);
        WindowsList::removeWindow(_id);
    }
#ifdef USE_XIM
    if(_ic) XDestroyIC(_ic);
#endif
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
                      const PixelAttribs& pixelAttribs_)
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
    winattribs.event_mask = StructureNotifyMask | ExposureMask |
                                KeyPressMask | KeyReleaseMask |
                                ButtonPressMask | ButtonReleaseMask |
                                PointerMotionMask | ButtonMotionMask |
                                FocusChangeMask;
    winattribs.background_pixmap = None;
    winattribs.border_pixel = 0;
    winattribs.override_redirect = False; //True for undecorated window


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
                CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect,
                &winattribs);


    if(!winid){
        //free visualinfo
        XFree(visualinfo);
        //free fbconfig
        XFree(fbconfigs);
        return NULL;
    }
    
    //init x11
    if(_counter++ == 0){
        _init_x11();
    }
    
    window = new Window();
    window->_id = winid;
#ifdef USE_XIM
    if(_im){
        window->_ic = XCreateIC(_im,
                        XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                        XNClientWindow, winid,
                        NULL);
    }
#endif
    WindowsList::addWindow(winid, window);

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
        
        if(XFilterEvent(&event, None) == True){
            continue;
        }
        
        wid = event.xany.window;
        window = static_cast<Window*>(WindowsList::getWindow(wid));
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
                WindowsList::removeWindow(wid);
                break;
                
            case KeyPress://key press
            case KeyRelease:
                {
                    //std::string key_str;
                    KeyCode kc = 0;
                    KeySym ks = 0;
                    std::vector<char> buf;
                    std::string str_key;
                    size_t len = 4;//max utf8 char length || UCS4 char length
                    
                    bool good_key = false;
                    
#ifdef USE_XIM
                    if(window->_ic && event.type == KeyPress){
                        Status status = 0;

                        buf.resize(len + 1);
                        len = Xutf8LookupString(window->_ic, &event.xkey, &buf[0], len,
                                &ks, &status);

                        if(status == XBufferOverflow){
                            buf.resize(len + 1);

                            len = Xutf8LookupString(window->_ic, &event.xkey, &buf[0], len,
                                &ks, &status);
                        }

                        if(status != XLookupNone && ks != NoSymbol){
                            //key_str = &buf[0];
                            good_key = true;
                        }
                    }else
#endif
                    {
                        buf.resize(len + 1);
                        len = XLookupString(&event.xkey, &buf[0], len, &ks, NULL);
                        
                        if(ks != NoSymbol){
                            //key_str = &buf[0];
                            good_key = true;
                        }
                    }
                    
                    if(good_key == false) break;
                    
                    //kc = XKeysymToKeycode(Display::display(), ks);
                    kc = event.xkey.keycode & 0xff;
                    str_key = Iconv::fromLocal(std::string(&buf[0]));
                    
                    if(event.type == KeyPress){
                        KeyPressEvent e(window,
                                Utf8Char(str_key.c_str()),Input::keycodeToKey(kc));
                        window->_onKeyPress(&e);
                    }else if(event.type == KeyRelease){
                        KeyReleaseEvent e(window,
                                Utf8Char(str_key.c_str()),Input::keycodeToKey(kc));
                        window->_onKeyRelease(&e);
                    }
                }
                break;
                
            case ButtonPress://mouse button press
            case ButtonRelease://mouse button release
                {
                    int x = event.xbutton.x;
                    int y = event.xbutton.y;
                    int button = 0;
                    switch(event.xbutton.button){
                        case Button1:
                            button = MOUSE_LEFT;
                            break;
                        case Button3:
                            button = MOUSE_RIGHT;
                            break;
                        case Button2:
                            button = MOUSE_MIDDLE;
                            break;
                        case Button4:
                            button = MOUSE_SCROLL_UP;
                            break;
                        case Button5:
                            button = MOUSE_SCROLL_DOWN;
                            break;
                    }
                    if(event.type == ButtonPress){
                        MousePressEvent e(window, x, y, button);
                        window->_onMousePress(&e);
                    }else if(event.type == ButtonRelease){
                        MouseReleaseEvent e(window, x, y, button);
                        window->_onMouseRelease(&e);
                    }
                }
                break;
                
            case MotionNotify://mouse motion notify
                {
                    int x = event.xmotion.x;
                    int y = event.xmotion.y;
                    int button = 0;
                    if(event.xmotion.state & Button1Mask) button |= MOUSE_LEFT;
                    if(event.xmotion.state & Button3Mask) button |= MOUSE_RIGHT;
                    if(event.xmotion.state & Button2Mask) button |= MOUSE_MIDDLE;
                    if(event.xmotion.state & Button4Mask) button |= MOUSE_SCROLL_UP;
                    if(event.xmotion.state & Button5Mask) button |= MOUSE_SCROLL_DOWN;
                    MouseMotionEvent e(window, x, y, button);
                    window->_onMouseMotion(&e);
                }
                break;
                
            case FocusIn://focus in
                { FocusInEvent e(window, true);
                window->_onFocusIn(&e);}
                break;
                
            case FocusOut://focus out
                { FocusOutEvent e(window, false);
                window->_onFocusOut(&e);}
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


