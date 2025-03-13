#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <array>
#include <cstdint>

constexpr int KEY_COUNT = 0x10;

class Keyboard {
    private:
        std::array<bool, KEY_COUNT> keyboard;
    public:
        Keyboard();
};

#endif
