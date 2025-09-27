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
        std::array<sf::Keyboard::Key, KEY_COUNT> keybinds;

    public:
        Keyboard();
        void update();
        void setKeybind(int index, sf::Keyboard::Key key);
        bool isKeyHeldDown(size_t key);
        bool isKeyReleased(size_t key);
};

#endif
