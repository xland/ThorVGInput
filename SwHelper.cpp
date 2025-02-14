#include "SwHelper.h"

SwHelper::SwHelper(HWND hwnd):hwnd{hwnd}
{

}

SwHelper::~SwHelper()
{
}

void SwHelper::resize()
{
    {
        RECT rect;
        GetClientRect(hwnd, &rect);
        w = rect.right - rect.left;
        h = rect.bottom - rect.top;
    }
    buffer.resize(w * h);
    canvas.reset(tvg::SwCanvas::gen());
    canvas->target(buffer.data(), w, w, h, tvg::ColorSpace::ARGB8888);
}

void SwHelper::blitToScreen(HDC hdc)
{
    BITMAPINFO bmi = { sizeof(BITMAPINFOHEADER), w, 0 - h, 1, 32, BI_RGB, h * 4 * w, 0, 0, 0, 0 };
    SetDIBitsToDevice(hdc, 0, 0, w, h, 0, 0, 0, h, buffer.data(), &bmi, DIB_RGB_COLORS);
}

tvg::Canvas* SwHelper::getCanvas()
{
    return canvas.get();
}
