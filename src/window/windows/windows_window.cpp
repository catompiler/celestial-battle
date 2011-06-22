#include <windows.h>
#include "glcontext/glcontext.h"


static const char* _winClassName = "_WINDOW_";
static int _regclass_count = 0;

Window::Window()
{
    _id = 0;
}

Window::~Window()
{
    if(_id != 0){
        DestroyWindow(_id);
        removeWindow(_id);
    }
    if(_regclass_count != 0){
        if(--_regclass_count == 0){
            UnregisterClass(_winClassName, GetModuleHandle(NULL));
        }
    }
}


int Window::left() const
{
    RECT r;
    GetWindowRect(_id, &r);
    return r.left;
}


void Window::setLeft(int left_)
{
    RECT r;
    //get current rect
    GetWindowRect(_id, &r);
    //calc width
    int w = r.right - r.left;
    r.left = left_;
    r.right = left_ + w;
    //set
    SetWindowPos(_id, 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}


int Window::top() const
{
    RECT r;
    GetWindowRect(_id, &r);
    return r.top;
}


void Window::setTop(int top_)
{
    RECT r;
    //get current rect
    GetWindowRect(_id, &r);
    //calc width
    int h = r.bottom - r.top;
    r.top = top_;
    r.bottom = top_ + h;
    //set
    SetWindowPos(_id, 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}


unsigned int Window::width() const
{
    RECT r;
    GetWindowRect(_id, &r);
    return r.right - r.left;
}


void Window::setWidth(unsigned int width_)
{
    RECT r;
    //get current rect
    GetWindowRect(_id, &r);
    r.right = r.left + width_;
    //set
    SetWindowPos(_id, 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}


unsigned int Window::height() const
{
    RECT r;
    GetWindowRect(_id, &r);
    return r.bottom - r.top;
}


void Window::setHeight(unsigned int height_)
{
    RECT r;
    //get current rect
    GetWindowRect(_id, &r);
    r.bottom = r.top + height_;
    //set
    SetWindowPos(_id, 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}


std::string Window::title() const
{
    int title_len = GetWindowTextLength(_id);
    
    char title_buf[title_len + 1];
    
    int count = GetWindowText(_id, title_buf, title_len);
    title_buf[count] = 0x0;
    
    return std::string(title_buf);
}


void Window::setTitle(const std::string& title_)
{
    SetWindowText(_id, title_.c_str());
}


bool Window::active() const
{
    HWND activeWin;


    activeWin = GetActiveWindow();


    return activeWin == _id;
}


bool Window::showCursor(bool show_)
{
    ShowCursor(show_);
    return show_;
}


bool Window::makeCurrent(GLContext* glcxt_) /* const */
{
    return wglMakeCurrent(GetDC(_id), glcxt_ == NULL ? 0 : static_cast<HGLRC>(glcxt_->id()));
}


void Window::swapBuffers() /* const */
{
    SwapBuffers(GetDC(_id));
}



Window* Window::create(const std::string& title_,
                      int left_, int top_,
                      int width_, int height_,
                      const Window::PixelAttribs& pixelAttribs_)
{
    HINSTANCE hInst = GetModuleHandle(NULL);
    HWND hwnd;
    PIXELFORMATDESCRIPTOR pfd={0};
    int pf;
    HDC dc;
    Window* window;
    
    //register class
    if(_regclass_count++ == 0){
        WNDCLASS wc = {0};
        //set wc structure
        wc.hCursor = LoadCursor(NULL,IDC_ARROW);
        wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
        wc.hInstance = hInst;
        wc.hbrBackground = reinterpret_cast <HBRUSH>(COLOR_BTNFACE + 1);
        wc.lpszClassName = _winClassName;
        wc.lpfnWndProc = _WndProc;
        
        RegisterClass(&wc);
        //return NULL;
    }
    
    window = new Window();
    
    hwnd = CreateWindowEx(
                          0 /*dwExStyle*/,
                          _winClassName /*lpClassName*/,
                          title_.c_str() /*lpWindowName*/,
                          WS_OVERLAPPEDWINDOW /*dwStyle*/,
                          left_ /*x*/,
                          top_ /*y*/,
                          width_ /*nWidth*/,
                          height_ /*nHeight*/,
                          0 /*hWndParent*/,
                          0 /*hMenu*/,
                          hInst /*hInstance*/,
                          reinterpret_cast<void*>(window) /*lpParam*/
                        );
    
    if(hwnd == 0){
        delete window;
        window = NULL;
    }
    
    //setup PFD structure
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    if(pixelAttribs_.doubleBuffer) pfd.dwFlags |= PFD_DOUBLEBUFFER;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cRedBits = pixelAttribs_.redSize;
    pfd.cGreenBits = pixelAttribs_.greenSize;
    pfd.cBlueBits = pixelAttribs_.blueSize;
    pfd.cAlphaBits = pixelAttribs_.alphaSize;
    pfd.cDepthBits = pixelAttribs_.depthSize;
    pfd.cStencilBits = pixelAttribs_.stencilSize;
    pfd.iPixelType = PFD_TYPE_RGBA;
    
    #warning ignoring multisampling settings
    
    //get HDC
    dc = GetDC(hwnd);
    //choose pixel format
    pf = ChoosePixelFormat(dc, &pfd);
    //set pixel format
    SetPixelFormat(dc, pf, &pfd);
    
    
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    
    return window;
}


void Window::destroy(Window* window_)
{
    delete window_;
}


int Window::processEvents()
{
    int events_processed = 0;


    //message
    MSG msg;
    while(PeekMessage(&msg,NULL,PM_NOREMOVE,0,0)){
        if(GetMessage(&msg,NULL,0,0)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);


            ++ events_processed;
        }
    }
    return events_processed;
}


LRESULT CALLBACK Window::_WndProc(HWND  hWnd, UINT  uMsg, WPARAM  wParam, LPARAM  lParam)
{
    CREATESTRUCT* createStruct = NULL;
    Window* window = NULL;
    
    switch(uMsg){
        case WM_CREATE:
            createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
            window = static_cast<Window*>(createStruct->lpCreateParams);
        
            window->_id = hWnd;
            addWindow(hWnd, window);
        
            { Window::CreateEvent e(window);
            window->_onCreate(&e); }
            break;
            
        case WM_CLOSE:
            window = static_cast<Window*>(getWindow(hWnd));
            if(window == NULL) break;
            
            { Window::CloseEvent e(window);
            window->_onClose(&e); }
            break;
            
        case WM_DESTROY:
            removeWindow(hWnd);
            break;
            
        case WM_PAINT:
            window = static_cast<Window*>(getWindow(hWnd));
            if(window == NULL) break;
            
            { Window::PaintEvent e(window);
            window->_onPaint(&e); }
            break;
            
        case WM_SIZE:
            window = static_cast<Window*>(getWindow(hWnd));
            if(window == NULL) break;
            
            { Window::ResizeEvent e(window , LOWORD(lParam), HIWORD(lParam));
            window ->_onResize(&e); }
            break;
            
        default:
            break;
    }
    
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

