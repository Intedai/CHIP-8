#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <array>
#include <cstdint>
#include <SFML/Window/Keyboard.hpp>
#include <cstddef>

constexpr int KEY_COUNT = 0x10;

class Keyboard {
    private:
        std::array<uint8_t, KEY_COUNT> keys;
        std::array<uint8_t, KEY_COUNT> keysLastFrame;
    public:
        Keyboard();
        void update();
        bool isKeyHeldDown(size_t key);
        bool isKeyReleased(size_t key);
};

#endif
