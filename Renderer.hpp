#pragma once

#include <string>
#include "Dats.hpp"

class Renderer {
public:
	
	static void setcursorvisibility(bool hidden);
	static void draw(std::string& fb);
	static Vec2 getframesize();
	static void sleep(double time);
};