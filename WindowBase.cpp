#include <thread>
#include <windowsx.h>
#include "WindowBase.h"

#define IDT_TIMER1 1

WindowBase::WindowBase()
{
	
}

WindowBase::~WindowBase()
{
}

void WindowBase::initWindow()
{
    WNDCLASSEX wcx{};
    auto hinstance = GetModuleHandle(NULL);
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // | CS_OWNDC | CS_BYTEALIGNCLIENT
    wcx.lpfnWndProc = &WindowBase::routeWinMsg;
    wcx.cbWndExtra = sizeof(WindowBase*);
    wcx.hInstance = hinstance;
    wcx.hIcon = LoadIcon(hinstance, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_IBEAM);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = L"ScreenCapture";
    RegisterClassEx(&wcx);
    auto style = WS_OVERLAPPEDWINDOW;
    hwnd = CreateWindowEx(NULL, L"ScreenCapture", L"ScreenCapture", style, x, y, w, h, NULL, NULL, hinstance, NULL);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    swHelper = std::make_unique<SwHelper>(hwnd);
    SetTimer(hwnd, IDT_TIMER1, 600, nullptr);
}
void WindowBase::show()
{
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    SetCursor(LoadCursor(nullptr, IDC_ARROW));
}
LRESULT WindowBase::routeWinMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    auto obj = reinterpret_cast<WindowBase*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (!obj) {
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    switch (msg)
    {
        //case WM_NCCALCSIZE:
        //{
        //    if (wParam == TRUE) {
        //        NCCALCSIZE_PARAMS* pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);
        //        pncsp->rgrc[0] = pncsp->rgrc[1]; //窗口客户区覆盖整个窗口
        //        return 0; //确认改变窗口客户区
        //    }
        //    return DefWindowProc(hWnd, msg, wParam, lParam);
        //}
    case WM_ERASEBKGND:
    {
        return TRUE;
    }
    case WM_CLOSE:
    {
        DestroyWindow(hWnd);
        return 0;
    }
    case WM_DESTROY:
    {
        SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
        UnregisterClass(L"ScreenCapture", nullptr);
        return 0;
    }
    default:
    {
        return obj->processWinMsg(msg, wParam, lParam);
    }
    }
}
LRESULT WindowBase::processWinMsg(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_MOVE: {
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        return 0;
    }
    case WM_SIZE: {
        //todo minimize
        w = LOWORD(lParam);
        h = HIWORD(lParam);
        swHelper->resize();
        return 0;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        auto hdc = BeginPaint(hwnd, &ps);
        //paint(swHelper->getCanvas());
        swHelper->blitToScreen(hdc);
        ReleaseDC(hwnd, hdc);
        EndPaint(hwnd, &ps);
        return 0;
    }    
    case WM_TIMER:
    {
        if (wParam == IDT_TIMER1) {
            paint(swHelper->getCanvas());
        }
        break;
    }
    case WM_LBUTTONDOWN:
    {
        mousePress(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
    }
    case WM_MOUSEMOVE:
    {
        if (wParam & MK_LBUTTON) {
            mouseDrag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        else {
            mouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        return 0;
    }
    case WM_LBUTTONDBLCLK:
    {
        mouseDBClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
    }
    case WM_LBUTTONUP:
    {
        mouseRelease(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
    }
    case WM_RBUTTONDOWN:
    {
        mousePressRight(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
    }
    case WM_KEYDOWN:
    {
        if (wParam == VK_BACK || wParam == VK_DELETE) {
            //removeShape();
            return true;
        }
        else if (wParam == VK_ESCAPE) {
            //escPress();
            return true;
        }
        else if (wParam == VK_LEFT) {
            //moveByKey(0);
            return true;
        }
        else if (wParam == VK_UP) {
            //moveByKey(1);
            return true;
        }
        else if (wParam == VK_RIGHT) {
            //moveByKey(2);
            return true;
        }
        else if (wParam == VK_DOWN) {
            //moveByKey(3);
            return true;
        }
        else if ((GetKeyState(VK_CONTROL) & 0x8000) != 0) {
            if (wParam == 'Z') {
                //undo(); 撤销
                return true;
            }
            else if (wParam == 'Y') {
                //redo(); 重做
                return true;
            }
            else if (wParam == 'H') {
                //copyColor(0); Hex
                return true;
            }
            else if (wParam == 'R') {
                //copyColor(1); RGB
                return true;
            }
        }
        break;
    }
    default: {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    }
    return 0;
}
