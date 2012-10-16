#include <windows.h>
#include "glcontext/glcontext.h"
#include "input/input.h"
#include "windows_window.h"
#include "iconv/iconv.h"
#include <iostream>


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
        WindowsList::removeWindow(_id);
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
                      bool is_fullscreen_window_,
                      const PixelAttribs& pixelAttribs_)
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
    
    int style = WS_OVERLAPPEDWINDOW;
    if(is_fullscreen_window_){
        style = WS_POPUP;
    }
    
    hwnd = CreateWindowEx(
                          0 /*dwExStyle*/,
                          _winClassName /*lpClassName*/,
                          title_.c_str() /*lpWindowName*/,
                          style /*dwStyle*/,
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
            WindowsList::addWindow(hWnd, window);
        
            { CreateEvent e(window);
            window->_onCreate(&e); }
            break;
            
        case WM_CLOSE:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { CloseEvent e(window);
            window->_onClose(&e); }
            break;
            
        case WM_DESTROY:
            WindowsList::removeWindow(hWnd);
            break;
            
        case WM_PAINT:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { PaintEvent e(window);
            window->_onPaint(&e); }
            break;
            
        case WM_SIZE:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { ResizeEvent e(window , LOWORD(lParam), HIWORD(lParam));
            window ->_onResize(&e); }
            break;
            
        case WM_KEYDOWN:
        case WM_KEYUP:
        //case WM_CHAR:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { /*char key_utf8[6] = {0};
            wchar_t wkey[2] = {0};
            unsigned char vkey = 0;
            unsigned char sc = 0;
            unsigned char keyb_st[256];
            std::string str_key;
            
            vkey = wParam & 0xff;
            sc = (lParam >> 16) & 8;
            GetKeyboardState(keyb_st);
            if(ToUnicodeEx(vkey, sc, keyb_st, wkey, 1, 0, GetKeyboardLayout(0)) > 0){
                std::cout << "wkey[0] = " << wkey[0] << std::endl;
                int n = WideCharToMultiByte(CP_UTF8, 0, wkey, 1, key_utf8, 5, NULL, NULL);
                std::cout << "res len = " << n << std::endl;
                str_key = std::string(key_utf8);
            }else{
                std::cout << "ToUnicodeEx" << std::endl;
            }*/
                
            char key_str[2] = {0};
            WORD wkey[2] = {0};
            unsigned char vkey = 0;
            unsigned char sc = 0;
            unsigned char keyb_st[256];
            std::string str_key;
            
            vkey = wParam & 0xff;
            sc = (lParam >> 16) & 8;
            GetKeyboardState(keyb_st);
            if(ToAsciiEx(vkey, sc, keyb_st, wkey, 0, GetKeyboardLayout(0)) > 0){
                //std::cout << "wkey[0] = " << wkey[0] << std::endl;
                key_str[0] = wkey[0];
                str_key = Iconv::fromLocal(std::string(key_str));
            }
            
            //str_key = Iconv::fromLocal(std::string(key_str));
            
            if(uMsg == WM_KEYDOWN){
                KeyPressEvent e(window,
                            Utf8Char(str_key.c_str()),Input::keycodeToKey(vkey));
                window->_onKeyPress(&e);
            }else if(uMsg == WM_KEYUP){
                KeyReleaseEvent e(window,
                            Utf8Char(str_key.c_str()),Input::keycodeToKey(vkey));
                window->_onKeyRelease(&e);
            }}
            break;
            
        case WM_LBUTTONDOWN:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            int button = MOUSE_LEFT;
            MousePressEvent e(window, x, y, button);
            window->_onMousePress(&e); }
            break;
            
        case WM_RBUTTONDOWN:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            int button = MOUSE_RIGHT;
            MousePressEvent e(window, x, y, button);
            window->_onMousePress(&e); }
            break;
            
        case WM_MBUTTONDOWN:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            int button = MOUSE_MIDDLE;
            MousePressEvent e(window, x, y, button);
            window->_onMousePress(&e); }
            break;
            
        case WM_LBUTTONUP:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            int button = MOUSE_LEFT;
            MouseReleaseEvent e(window, x, y, button);
            window->_onMouseRelease(&e); }
            break;
            
        case WM_RBUTTONUP:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            int button = MOUSE_RIGHT;
            MouseReleaseEvent e(window, x, y, button);
            window->_onMouseRelease(&e); }
            break;
            
        case WM_MBUTTONUP:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            int button = MOUSE_MIDDLE;
            MouseReleaseEvent e(window, x, y, button);
            window->_onMouseRelease(&e); }
            break;
            
        case WM_MOUSEWHEEL:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            int button = 0;
            
            int d = static_cast<short>(HIWORD(wParam));
            //std::cout << "wheel - " << d << std::endl;
            if(d < 0){ //down
                button = MOUSE_SCROLL_DOWN;
                MousePressEvent e(window, x, y, button);
                window->_onMousePress(&e);
            }else{
                button = MOUSE_SCROLL_UP;
                MouseReleaseEvent e(window, x, y, button);
                window->_onMouseRelease(&e);
            }}
            break;
            
        case WM_MOUSEMOVE:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            
            { int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            int button = 0;
            
            if(wParam & MK_LBUTTON) button |= MOUSE_LEFT;
            if(wParam & MK_RBUTTON) button |= MOUSE_RIGHT;
            if(wParam & MK_MBUTTON) button |= MOUSE_MIDDLE;
            
            MouseMotionEvent e(window, x, y, button);
            window->_onMouseMotion(&e); }
            break;
            
        case WM_ACTIVATEAPP:
            window = static_cast<Window*>(WindowsList::getWindow(hWnd));
            if(window == NULL) break;
            if(wParam == TRUE){
                FocusInEvent e(window, true);
                window->_onFocusIn(&e);
            }else{
                FocusOutEvent e(window, false);
                window->_onFocusOut(&e);
            }
            break;
            
        default:
            break;
    }
    
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

