#include "win_window.h"
#include "win_window_types.h"
#include "glcontext/glcontext.h"


#include "osal/osdef.h"

#ifdef OS_WINDOWS

const char* WinWindow::_winClassName = "_WINDOW_";

int WinWindow::_regclass_count = 0;


WinWindow::WinWindow()
        :GLWindow()
{
}

WinWindow::~WinWindow()
{
    if(_id != 0) DestroyWindow(static_cast<HWND>(_id));
    if(_regclass_count != 0){
        if(--_regclass_count == 0){
            UnregisterClass(_winClassName, GetModuleHandle(NULL));
        }
    }
}

int WinWindow::left() const
{
    RECT r;
    GetWindowRect(static_cast<HWND>(_id), &r);
    return r.left;
}

void WinWindow::setLeft(int left_)
{
    RECT r;
    //get current rect
    GetWindowRect(static_cast<HWND>(_id), &r);
    //calc width
    int w = r.right - r.left;
    r.left = left_;
    r.right = left_ + w;
    //set
    SetWindowPos(static_cast<HWND>(_id), 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}

int WinWindow::top() const
{
    RECT r;
    GetWindowRect(static_cast<HWND>(_id), &r);
    return r.top;
}

void WinWindow::setTop(int top_)
{
    RECT r;
    //get current rect
    GetWindowRect(static_cast<HWND>(_id), &r);
    //calc width
    int h = r.bottom - r.top;
    r.top = top_;
    r.bottom = top_ + h;
    //set
    SetWindowPos(static_cast<HWND>(_id), 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}

unsigned int WinWindow::width() const
{
    RECT r;
    GetWindowRect(static_cast<HWND>(_id), &r);
    return r.right - r.left;
}

void WinWindow::setWidth(unsigned int width_)
{
    RECT r;
    //get current rect
    GetWindowRect(static_cast<HWND>(_id), &r);
    r.right = r.left + width_;
    //set
    SetWindowPos(static_cast<HWND>(_id), 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}

unsigned int WinWindow::height() const
{
    RECT r;
    GetWindowRect(static_cast<HWND>(_id), &r);
    return r.bottom - r.top;
}

void WinWindow::setHeight(unsigned int height_)
{
    RECT r;
    //get current rect
    GetWindowRect(static_cast<HWND>(_id), &r);
    r.bottom = r.top + height_;
    //set
    SetWindowPos(static_cast<HWND>(_id), 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}

std::string WinWindow::title() const
{
    int title_len = GetWindowTextLength(static_cast<HWND>(_id));
    
    char title_buf[title_len + 1];
    
    int count = GetWindowText(static_cast<HWND>(_id), title_buf, title_len);
    title_buf[count] = 0x0;
    
    return std::string(title_buf);
}

void WinWindow::setTitle(const std::string& title_)
{
    SetWindowText(static_cast<HWND>(_id), title_.c_str());
}

bool WinWindow::active() const
{
    HWND activeWin;

    activeWin = GetActiveWindow();

    return activeWin == static_cast<HWND>(_id);
}

bool WinWindow::showCursor(bool show_)
{
    ShowCursor(show_);
    return show_;
}

bool WinWindow::makeCurrent(GLContext* glcxt_) /* const */
{
    return wglMakeCurrent(GetDC(static_cast<HWND>(_id)), glcxt_ == NULL ? 0 : static_cast<HGLRC>(glcxt_->id()));
}

void WinWindow::swapBuffers() /* const */
{
    SwapBuffers(GetDC(static_cast<HWND>(_id)));
}


WinWindow* WinWindow::create(const std::string& title_,
                      int left_, int top_,
                      int width_, int height_,
                      const GLWindow::PixelAttribs& pixelAttribs_)
{
    HINSTANCE hInst = GetModuleHandle(NULL);
    HWND hwnd;
    PIXELFORMATDESCRIPTOR pfd={0};
    int pf;
    HDC dc;
    WinWindow* window;
    
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
    
    window = new WinWindow();
    
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

void WinWindow::destroy(WinWindow* window_)
{
    delete window_;
}

int WinWindow::processEvents()
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

LRESULT CALLBACK WinWindow::_WndProc(HWND  hWnd, UINT  uMsg, WPARAM  wParam, LPARAM  lParam)
{
    CREATESTRUCT* createStruct = NULL;
    WinWindow* window = NULL;
    
    switch(uMsg){
        case WM_CREATE:
            createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
            window = static_cast<WinWindow*>(createStruct->lpCreateParams);
        
            window->_id = hWnd;
            addWindow(hWnd, window);
        
            #define CreateEventA CreateEvent
            { GLWindow::CreateEvent e(window);
            window->_onCreate(&e); }
            break;
            
        case WM_CLOSE:
            window = static_cast<WinWindow*>(getWindow(hWnd));
            if(window == NULL) break;
            
            { GLWindow::CloseEvent e(window);
            window->_onClose(&e); }
            break;
            
        case WM_DESTROY:
            removeWindow(hWnd);
            break;
            
        case WM_PAINT:
            window = static_cast<WinWindow*>(getWindow(hWnd));
            if(window == NULL) break;
            
            { GLWindow::PaintEvent e(window);
            window->_onPaint(&e); }
            break;
            
        case WM_SIZE:
            window = static_cast<WinWindow*>(getWindow(hWnd));
            if(window == NULL) break;
            
            { GLWindow::ResizeEvent e(window , LOWORD(lParam), HIWORD(lParam));
            window ->_onResize(&e); }
            break;
            
        default:
            break;
    }
    
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#endif  //OS_WINDOWS
