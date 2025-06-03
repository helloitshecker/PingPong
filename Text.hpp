#pragma once

#include <array>
#include <string>

#include "Dats.hpp"
#include "Framebuffer.hpp"

class Text {
public:
    static void print(Framebuffer& fb, Vec2& coord, const std::string& text);
    static void printsingle(Framebuffer& fb, Vec2& coord, const std::string& text);
};