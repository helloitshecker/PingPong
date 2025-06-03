#include "Text.hpp"

// A-Z,0-9
static const std::array<const std::string, 36> typefaces = {
    "  ___          / _ \        / /_\ \       |  _  |       | | | |        \_| |_/          ",
    "______        | ___ \       | |_/ /       | ___ \       | |_/ /        \____/           ",
    " _____        /  __ \       | /  \/       | |           | \__/\         \____/          ",
    "______        |  _  \       | | | |       | | | |       | |/ /         |___/            ",
    " _____        |  ___|       | |__         |  __|        | |___         \____/           ",
    "______        |  ___|       | |_          |  _|         | |            \_|              ",
    " _____        |  __ \       | |  \/       | | __        | |_\ \         \____/          ",
    " _   _        | | | |       | |_| |       |  _  |       | | | |        \_| |_/          ",
    " _____        |_   _|         | |           | |          _| |_          \___/           ",
    "   ___          |_  |           | |           | |       /\__/ /        \____/           ",
    " _   __       | | / /       | |/ /        |    \        | |\  \        \_| \_/          ",
    " _            | |           | |           | |           | |____        \_____/          ",
    "___  ___      |  \/  |      | .  . |      | |\/| |      | |  | |       \_|  |_/         ",
    " _   _        | \ | |       |  \| |       | . ` |       | |\  |        \_| \_/          ",
    " _____        |  _  |       | | | |       | | | |       \ \_/ /         \___/           ",
    "______        | ___ \       | |_/ /       |  __/        | |            \_|              ",
    " _____        |  _  |       | | | |       | | | |       \ \/' /         \_/\_\          ",
    "______        | ___ \       | |_/ /       |    /        | |\ \         \_| \_|          ",
    " _____        /  ___|       \ `--.         `--. \       /\__/ /        \____/           ",
    " _____        |_   _|         | |           | |           | |            \_/            ",
    " _   _        | | | |       | | | |       | | | |       | |_| |         \___/           ",
    " _   _        | | | |       | | | |       | | | |       \ \_/ /         \___/           ",
    " _    _       | |  | |      | |  | |      | |/\| |      \  /\  /        \/  \/          ",
    "__   __       \ \ / /        \ V /         /   \        / /^\ \        \/   \/          ",
    "__   __       \ \ / /        \ V /          \ /           | |            \_/            ",
    " ______       |___  /          / /          / /         ./ /___        \_____/          ",
    " _____        |  _  |       | |/' |       |  /| |       \ |_/ /         \___/           ",
    " __           /  |          `| |           | |          _| |_          \___/            ",
    " _____        / __  \       `' / /'         / /         ./ /___        \_____/          ",
    " _____        |____ |           / /           \ \       .___/ /        \____/           ",
    "   ___          /   |        / /| |       / /_| |       \___  |            |_/          ",
    " _____        |  ___|       |___ \            \ \       /\__/ /        \____/           ",
    "  ____         / ___|       / /___        | ___ \       | \_/ |        \_____/          ",
    " ______       |___  /          / /          / /         ./ /           \_/              ",
    " _____        |  _  |        \ V /         / _ \        | |_| |        \_____/          ",
    " _____        |  _  |       | |_| |       \____ |       .___/ /        \____/           "
};
static const std::array<const char, 36> typefacemaps = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I','J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };


void Text::print(Framebuffer& fb, Vec2& coord, const std::string& text) {
    constexpr int char_width = 14;
    constexpr int char_height = 6;

    for (char ch : text) {
        auto it = std::find(typefacemaps.begin(), typefacemaps.end(), ch);
        if (it == typefacemaps.end()) continue;

        int index = std::distance(typefacemaps.begin(), it);
        const std::string& art = typefaces[index];

        for (int row = 0; row < char_height; ++row) {
            for (int col = 0; col < char_width; ++col) {
                char pixel = art[row * char_width + col];
                fb.set(coord.r + row, coord.c + col, pixel);
            }
        }

        coord.c += char_width; // move cursor to next character slot
    }
}

void Text::printsingle(Framebuffer& fb, Vec2& coord, const std::string& text) {
    for (int i = coord.c; i < text.length() + coord.c; i++) {
        fb.set(coord.r, i, text.at(i - coord.c));
    }
}