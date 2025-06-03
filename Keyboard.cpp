#include "Keyboard.hpp"

#include <Windows.h>

bool Keyboard::isKeyDown(int keycode) {
	return GetAsyncKeyState(keycode) & 0x8000;
}