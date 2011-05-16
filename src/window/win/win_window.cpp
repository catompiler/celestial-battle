#include "win_window.h"



const char* WinWindow::_winClassName = "_WINDOW_";

WinWindow::WindowsMap WinWindow::_windowsMap;

int WinWindow::_regclass_count = 0;


WinWindow::WinWindow()
{
    _hWnd = 0;
}

WinWindow::~WinWindow()
{
    if(_hWnd != 0) DestroyWindow(_hWnd);
    if(_regclass_count != 0){
        if(--_regclass_count == 0){
            UnregisterClass(_winClassName, GetModuleHandle(NULL));
        }
    }
}

int WinWindow::left() const
{
    RECT r;
    GetWindowRect(_hWnd, &r);
    return r.left;
}

void WinWindow::setLeft(int left_)
{
    RECT r;
    //get current rect
    GetWindowRect(_hWnd, &r);
    //calc width
    int w = r.right - r.left;
    r.left = left_;
    r.right = left_ + w;
    //set
    SetWindowPos(_hWnd, 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}

int WinWindow::top() const
{
    RECT r;
    GetWindowRect(_hWnd, &r);
    return r.top;
}

void WinWindow::setTop(int top_)
{
    RECT r;
    //get current rect
    GetWindowRect(_hWnd, &r);
    //calc width
    int h = r.bottom - r.top;
    r.top = top_;
    r.bottom = top_ + h;
    //set
    SetWindowPos(_hWnd, 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}

unsigned int WinWindow::width() const
{
    RECT r;
    GetWindowRect(_hWnd, &r);
    return r.right - r.left;
}

void WinWindow::setWidth(unsigned int width_)
{
    RECT r;
    //get current rect
    GetWindowRect(_hWnd, &r);
    r.right = r.left + width_;
    //set
    SetWindowPos(_hWnd, 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}

unsigned int WinWindow::height() const
{
    RECT r;
    GetWindowRect(_hWnd, &r);
    return r.bottom - r.top;
}

void WinWindow::setHeight(unsigned int height_)
{
    RECT r;
    //get current rect
    GetWindowRect(_hWnd, &r);
    r.bottom = r.top + height_;
    //set
    SetWindowPos(_hWnd, 0,
                 r.left, r.right,
                 r.right - r.left, r.bottom - r.top,
                 0);
}

std::string WinWindow::title() const
{
    int title_len = GetWindowTextLength(_hWnd);
    
    char title_buf[title_len + 1];
    
    int count = GetWindowText(_hWnd, title_buf, title_len);
    title_buf[count] = 0x0;
    
    return std::string(title_buf);
}

void WinWindow::setTitle(const std::string& title_)
{
    SetWindowText(_hWnd, title_.c_str());
}

bool WinWindow::active() const
{
    HWND activeWin;

    activeWin = GetActiveWindow();

    return activeWin == _hWnd;
}

bool WinWindow::showCursor(bool show_)
{
    ShowCursor(show_);
    return show_;
}

bool WinWindow::makeCurrent(const GLContext& glcxt_) /* const */
{
    //return wglMakeCurrent(GetDC(_hWnd),glcxt_.contextId());
    return false;
}

void WinWindow::swapBuffers() /* const */
{
    SwapBuffers(GetDC(_hWnd));
}


WinWindow* WinWindow::create(const std::string& title_,
                      int left_, int top_,
                      int width_, int height_,
                      const PixelAttribs& pixelAttribs_)
{
    HINSTANCE hInst = GetModuleHandle(NULL);
    HWND hwnd;
    //PIXELFORMATDESCRIPTOR pfd={0};
    //HDC dc;
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
    
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    
    return window;
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
    WindowsMap::iterator it;
    
    switch(uMsg){
        case WM_CREATE:
            createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
        
            it = _windowsMap.find(hWnd);
            if(it == _windowsMap.end()){
                window = reinterpret_cast<WinWindow*>(createStruct->lpCreateParams);
                //set handle value!
                window->_hWnd = hWnd;
                _windowsMap[hWnd] = window;
            }else{
                window = (*it).second;
            }
            
            { CreateEvent e(window);
            window->_onCreate(&e); }
            break;
            
        case WM_CLOSE:
            it = _windowsMap.find(hWnd);
            if(it == _windowsMap.end()){
                break;
            }
            window = (*it).second;
            
            { CloseEvent e(window);
            window->_onClose(&e); }
            break;
            
        case WM_DESTROY:
            it = _windowsMap.find(hWnd);
            if(it == _windowsMap.end()){
                break;
            }
            _windowsMap.erase(it);
            break;
            
        case WM_PAINT:
            it = _windowsMap.find(hWnd);
            if(it == _windowsMap.end()){
                break;
            }
            window = (*it).second;
            
            { PaintEvent e(window);
            window->_onPaint(&e); }
            break;
            
        case WM_SIZE:
            it = _windowsMap.find(hWnd);
            if(it == _windowsMap.end()){
                break;
            }
            window = (*it).second;
            
            { ResizeEvent e(window , LOWORD(lParam), HIWORD(lParam));
            window ->_onResize(&e); }
            break;
            
        default:
            break;
    }
    
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

