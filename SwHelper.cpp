#include "SwHelper.h"
#include "Util.h"

SwHelper::SwHelper(HWND hwnd):hwnd{hwnd}
{

}

SwHelper::~SwHelper()
{
}

void SwHelper::resize()  //when hwnd init or resize
{
    {
        RECT rect;
        GetClientRect(hwnd, &rect);
        w = rect.right - rect.left;
        h = rect.bottom - rect.top;
    }
    buffer.resize(w * h);  //std::vector<uint32_t> buffer;
    buffer.shrink_to_fit();
    canvas.reset(tvg::SwCanvas::gen());  //std::unique_ptr<tvg::SwCanvas> canvas;
    canvas->target(buffer.data(), w, w, h, tvg::ColorSpace::ARGB8888);

    tvg::Text::load("C:\\Windows\\Fonts\\Arial.ttf");
    text = tvg::Text::gen();
    text->font("Arial", 80);
    text->text("THORVG Text");
    text->fill(255, 255, 255);
    canvas->push(text);

    caret = tvg::Shape::gen();
    caret->appendRect(290, 10, 22, 92);
    caret->fill(116, 125, 255);
    caret->strokeFill(0, 0, 255);
    caret->strokeWidth(0);
    canvas->push(caret);

    canvas->draw(true);
    canvas->sync();
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
