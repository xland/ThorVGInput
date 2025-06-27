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
    if (flag) {
        swHelper->caret->opacity(255);
    }
    else {
        swHelper->caret->opacity(0);
    }
    flag = !flag;
    canvas->draw();  //remove param true
    canvas->sync();
    InvalidateRect(hwnd, nullptr, false);
}
