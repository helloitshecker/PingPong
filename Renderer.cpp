#include "Renderer.hpp"

#include <Windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Renderer::setcursorvisibility(bool hidden) {
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = hidden ? FALSE : TRUE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Renderer::draw(std::string& fb) {
	// Set Cursor Position to top left
	COORD pos = { 0,0 };
	SetConsoleCursorPosition(hConsole, pos);

	WriteConsoleA(hConsole, fb.c_str(), fb.size(), NULL, NULL);
}

Vec2 Renderer::getframesize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	return Vec2{ csbi.srWindow.Bottom - csbi.srWindow.Top + 1, csbi.srWindow.Right - csbi.srWindow.Left + 1 };
}

void Renderer::sleep(double time) {
	Sleep(time);
}