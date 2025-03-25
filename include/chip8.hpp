#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <string_view>
#include <SFML/System.hpp>

#include "instructions.hpp"
#include "screen.hpp"
#include "keyboard.hpp"
#include "cpu.hpp"

constexpr int FPS = 60; 
const sf::Time cycleTime = sf::milliseconds(1000/FPS);

class Chip8 {
    private:
        Screen screen;
        CPU cpu;
        Keyboard keyboard;
    public:
        Chip8(std::string_view fileName,sf::RenderWindow& windowRef);
        void run();
};

#endif
