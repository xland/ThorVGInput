#include "SwHelper.h"
#include "Util.h"

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
    buffer.shrink_to_fit(); //todo 尝试释放多余的内存
    canvas.reset(tvg::SwCanvas::gen());
    canvas->target(buffer.data(), w, w, h, tvg::ColorSpace::ARGB8888);

    auto result = tvg::Text::load("C:\\Windows\\Fonts\\Arial.ttf");
    auto text = tvg::Text::gen();
    text->font("Arial", 80);
    text->text("THORVG Text");
    text->fill(255, 255, 255);
    canvas->push(std::move(text));

    auto bg = tvg::Shape::gen();
    bg->appendRect(w - 200, h - 200, 160, 160);
    bg->fill(116, 125, 255);
    canvas->push(std::move(bg));
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
