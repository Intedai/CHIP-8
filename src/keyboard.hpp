#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <array>
#include <cstdint>
#include <cstddef>

constexpr int KEY_COUNT = 0x10;

class Keyboard {
    private:
        std::array<uint8_t, KEY_COUNT> keys;
    public:
        Keyboard();
        bool isKeyHeldDown(size_t key);
};

#endif
