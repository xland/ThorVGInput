#include <Windows.h>
#include <iostream>
#include <thread>
#include <thorvg.h>
#include "Util.h"
#include "MainWindow.h"

#define IDT_TIMER1 1000000

MainWindow::MainWindow()
{
	initWinPosSize();
    initWindow();
}

MainWindow::~MainWindow()
{
}


void MainWindow::initWinPosSize()
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    w = 1000;
    h = 800;
    x = (screenWidth - w) / 2;
    y = (screenHeight - h) / 2;
}
void MainWindow::initCanvas()
{
    {
        RECT rect;
        GetClientRect(hwnd, &rect);
        w = rect.right - rect.left;
        h = rect.bottom - rect.top;
        buffer.resize(w * h);
        buffer.shrink_to_fit();
    }
    if (!canvas.get()) {
        canvas.reset(tvg::SwCanvas::gen());
    }
    canvas->target(buffer.data(), w, w, h, tvg::ColorSpace::ARGB8888);
    if (!text) {
        tvg::Text::load("C:\\Windows\\Fonts\\Arial.ttf");
        text = tvg::Text::gen();
        text->font("Arial", 80);
        text->text("THORVG Text");
        text->fill(255, 255, 255);
        canvas->push(text);
    }
    if (!caret) {
        caret = tvg::Shape::gen();
        caret->appendRect(290, 10, 22, 92);
        caret->fill(116, 125, 255);
        caret->strokeFill(0, 0, 255);
        caret->strokeWidth(0);
        canvas->push(caret);
    }
    canvas->draw(true);
    canvas->sync();
}
void MainWindow::initWindow()
{
    WNDCLASSEX wcx{};
    auto hinstance = GetModuleHandle(NULL);
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // | CS_OWNDC | CS_BYTEALIGNCLIENT
    wcx.lpfnWndProc = &MainWindow::routeWinMsg;
    wcx.cbWndExtra = sizeof(MainWindow*);
    wcx.hInstance = hinstance;
    wcx.hIcon = LoadIcon(hinstance, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_IBEAM);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = L"ScreenCapture";
    RegisterClassEx(&wcx);
    auto style = WS_OVERLAPPEDWINDOW;
    hwnd = CreateWindowEx(NULL, L"ScreenCapture", L"ScreenCapture", style, x, y, w, h, NULL, NULL, hinstance, NULL);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    SetTimer(hwnd, IDT_TIMER1, 600, nullptr);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    SetCursor(LoadCursor(nullptr, IDC_ARROW));
}
LRESULT MainWindow::routeWinMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    auto obj = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (!obj) {
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    switch (msg)
    {
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
    case WM_MOVE: {
        obj->x = LOWORD(lParam);
        obj->y = HIWORD(lParam);
        return 0;
    }
    case WM_SIZE: {
        //todo minimize
        obj->w = LOWORD(lParam);
        obj->h = HIWORD(lParam);
        obj->initCanvas();
        return 0;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        auto hdc = BeginPaint(obj->hwnd, &ps);
        BITMAPINFO bmi = { sizeof(BITMAPINFOHEADER), obj->w, 0 - obj->h, 1, 32, BI_RGB, obj->h * 4 * obj->w, 0, 0, 0, 0 };
        SetDIBitsToDevice(hdc, 0, 0, obj->w, obj->h, 0, 0, 0, obj->h, obj->buffer.data(), &bmi, DIB_RGB_COLORS);
        EndPaint(obj->hwnd, &ps);
        return 0;
    }
    case WM_TIMER:
    {
        if (wParam == IDT_TIMER1) {
            obj->paint();
        }
        break;
    }


    default: {
        return DefWindowProc(obj->hwnd, msg, wParam, lParam);
    }
    }
}
void MainWindow::paint()
{
    if (flag) {
        caret->opacity(255);
    }
    else {
        caret->opacity(0);
    }
    flag = !flag;
    canvas->update();
    canvas->draw(false);
    canvas->sync();
    InvalidateRect(hwnd, nullptr, false);
}
