#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <string_view>
#include <SFML/System.hpp>

#include "instructions.hpp"
#include "screen.hpp"
#include "cpu.hpp"

class Chip8 {
    private:
        Screen screen;
        CPU cpu;
    public:
        Chip8(std::string_view fileName,sf::RenderWindow& windowRef);
        void run();
};

#endif
