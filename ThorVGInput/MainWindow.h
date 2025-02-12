#pragma once
#include <Windows.h>
#include "WindowBase.h"
#include <string>

class MainWindow:public WindowBase
{
public:
	MainWindow();
    ~MainWindow();
public:
protected:
	void mousePress(const int& x, const int& y) override;
	void mousePressRight(const int& x, const int& y) override;
	void mouseDBClick(const int& x, const int& y) override;
	void mouseMove(const int& x, const int& y) override;
	void mouseDrag(const int& x, const int& y) override;
	void mouseRelease(const int& x, const int& y) override;
	void paint(tvg::Canvas* canvas) override;
private:
	void initWinPosSize();
private:
	std::wstring text;
};
