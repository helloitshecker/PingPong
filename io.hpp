#include <Windows.h>
#include <utility>
#include <string>
#include <vector>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void print(const char* c) {
	WriteConsoleA(hConsole, c, lstrlenA(c), NULL, NULL);
}

void hidecursor() {
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void unhidecursor() {
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

std::pair<int, int> getConsoleSize() {
    if (hConsole == INVALID_HANDLE_VALUE) {
        return { 0, 0 };  // error case
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return { 0, 0 };  // error case
    }

    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return { columns, rows };
}

void renderFrame(const std::vector<std::vector<char>>& screenBuffer) {
    COORD pos = { 0, 0 };
    SetConsoleCursorPosition(hConsole, pos);

    std::string frame;
    for (const auto& row : screenBuffer) {
        for (char ch : row)
            frame += ch;
    }

    DWORD written;
    WriteConsoleA(hConsole, frame.c_str(), frame.size(), &written, nullptr);
}


void moveCursorToTopLeft() {
    COORD pos = { 0, 0 };
    SetConsoleCursorPosition(hConsole, pos);
}


void playMP3Async(const char* filename) {
    mciSendStringA(("open \"" + std::string(filename) + "\" type mpegvideo alias mp3").c_str(), NULL, 0, NULL);
    mciSendStringA("play mp3", NULL, 0, NULL);
}