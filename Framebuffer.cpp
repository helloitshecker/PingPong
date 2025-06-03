#include "Framebuffer.hpp"

#include <vector>


size_t r{};
size_t c{};
std::vector<char> fb;
std::string forout;

Framebuffer::Framebuffer(size_t rows, size_t columns) {
	fb = std::vector<char>(rows * columns, ' ');
	r = rows;
	c = columns;
}

void Framebuffer::resize(size_t rows, size_t columns) {
	fb.resize(rows * columns);
	r = rows;
	c = columns;
}

void Framebuffer::clear() {
	std::fill(fb.begin(), fb.end(), ' ');
}

std::string& Framebuffer::get() {
	forout = std::string(fb.data(), fb.size());
	return forout;
}

void Framebuffer::set(size_t row, size_t column, char ch) {
	size_t index = row * c + column;
	//if (index >= fb.size()) return;
	fb[index] = ch;
}
