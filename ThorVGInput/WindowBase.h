#pragma once
#include <Windows.h>
#include "SwHelper.h"

class WindowBase
{
public:
	WindowBase();
	~WindowBase();
	void show();
public:
	int x, y, w, h;
	HWND hwnd;
protected:
	void initWindow();
	virtual void paint(tvg::Canvas* canvas) {};
	virtual void mousePress(const int& x, const int& y) {};
	virtual void mousePressRight(const int& x, const int& y) {};
	virtual void mouseDBClick(const int& x, const int& y) {};
	virtual void mouseMove(const int& x, const int& y) {};
	virtual void mouseDrag(const int& x, const int& y) {};
	virtual void mouseRelease(const int& x, const int& y) {};
private:
	static LRESULT CALLBACK routeWinMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK processWinMsg(UINT msg, WPARAM wParam, LPARAM lParam);
private:
	std::unique_ptr<SwHelper> swHelper;
};

