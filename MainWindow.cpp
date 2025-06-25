#include <Windows.h>
#include <iostream>
#include <thread>
#include <thorvg.h>
#include "Util.h"
#include "MainWindow.h"


MainWindow::MainWindow()
{
	initWinPosSize();
    initWindow();
    text = LR"(破阵子·为陈同甫赋壮词以寄之
辛弃疾 · 宋 · XinQiJi(1140年－1207年) 

醉里挑灯看剑，梦回吹角连营。
八百里分麾下炙，五十弦翻塞外声，沙场秋点兵。
马作的卢飞快，弓如霹雳弦惊。
了却君王天下事，赢得生前身后名。可怜白发生！
)";
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

void MainWindow::mouseMove(const int& x, const int& y)
{
}
void MainWindow::mouseDrag(const int& x, const int& y) {

}
void MainWindow::mouseRelease(const int& x, const int& y)
{
}
void MainWindow::mousePress(const int& x, const int& y)
{
}

void MainWindow::mousePressRight(const int& x, const int& y)
{
}

void MainWindow::mouseDBClick(const int& x, const int& y)
{
}

void MainWindow::paint(tvg::Canvas* canvas)
{
    //auto str = Util::ConvertToUTF8(text);
    //auto result = tvg::Text::load("C:\\Windows\\Fonts\\Arial.ttf");
    //auto text = tvg::Text::gen();
    //text->font("Arial", 80);
    //text->text("THORVG Text");
    //text->fill(255, 255, 255);
    //canvas->push(std::move(text));

    auto caret = tvg::Shape::gen();
    caret->appendRect(290, 10, 22, 92);
    if (flag) {

        caret->fill(116, 125, 255);
    }
    else {
        caret->fill(0, 0, 0,0);
    }
	flag = !flag;    
    canvas->push(std::move(caret));

    //auto bg = tvg::Shape::gen();
    //bg->appendRect(w - 200, h - 200, 160, 160);
    //bg->fill(116, 125, 255);
    //canvas->push(std::move(bg));
    canvas->draw(true);
    canvas->sync();
	RECT rect;
	rect.left = 290;
	rect.top = 10;
	rect.right = 290 + 22;
	rect.bottom = 10 + 92;
	InvalidateRect(hwnd, nullptr, false);
}
