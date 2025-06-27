#pragma once
#include <Windows.h>
#include <stdint.h>
#include <thorvg.h>
#include <memory>
class SwHelper
{
	public:
		SwHelper(HWND hwnd);
		~SwHelper();
		void resize();
		void blitToScreen(HDC hdc);
		tvg::Canvas* getCanvas();
		std::vector<uint32_t> buffer;
		tvg::Shape* caret;
		tvg::Text* text;
	private:
		HWND hwnd;
		std::unique_ptr<tvg::SwCanvas> canvas;
		uint32_t w, h;
};

