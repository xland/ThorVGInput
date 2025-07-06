#pragma once
#include <Windows.h>
#include <string>

class MainWindow
{
public:
	MainWindow();
    ~MainWindow();
public:
protected:
	void paint();
private:
	void initWindow();
	void initWinPosSize();
	void initCanvas();
	static LRESULT CALLBACK routeWinMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	int x, y, w, h;
	HWND hwnd;
	bool flag{ true };
	std::unique_ptr<tvg::SwCanvas> canvas;
	std::vector<uint32_t> buffer;
	tvg::Shape* caret;
	tvg::Text* text;
};
