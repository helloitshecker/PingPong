#pragma once

#define KEY_UP 0x26
#define KEY_DOWN 0x28
#define KEY_LEFT 0x25
#define KEY_RIGHT 0x27
#define KEY_ESCAPE 0x1B

class Keyboard {
public:
	static bool isKeyDown(int keycode);
};