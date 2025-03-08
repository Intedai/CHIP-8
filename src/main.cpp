#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "chip8.hpp"
#include <string>
int main() {
    std::string rom;
    std::cin >> rom;
    sf::RenderWindow window(sf::VideoMode({WIDTH * 10, HEIGHT * 10}), "CHIP8 EMULATOR");
    Chip8 chip8(rom, window);

    chip8.run();
    return 0;
}
