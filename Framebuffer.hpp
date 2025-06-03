#pragma once

#include <string>

class Framebuffer {
public:
	Framebuffer(size_t rows, size_t columns);

	void resize(size_t rows, size_t columns);
	void clear();

	void set(size_t r, size_t c, char ch);

	std::string& get();
};