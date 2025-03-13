#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "chip8.hpp"
#include <string>

int main() {
    int test;
    std::string rom;
    std::cout << "Enter test:";
    std::cin >> test;
    switch (test)
    {
        case 1:
            rom = "tests/1-chip8-logo.ch8";
            break;
        case 2:
            rom = "tests/2-ibm-logo.ch8";
            break;
        case 3:
            rom = "tests/3-corax+.ch8";
            break;
        case 4:
            rom = "tests/4-flags.ch8";
            break;
        case 5:
            rom = "tests/5-quirks.ch8";
            break;
        case 6:
            rom = "tests/6-quirks.ch8";
            break;
        default:
            std::cout << "Test doesnt exist!";
            exit(1);
            break;
    }
    sf::RenderWindow window(sf::VideoMode({WIDTH * 10, HEIGHT * 10}), "CHIP8 EMULATOR");
    Chip8 chip8(rom, window);

    chip8.run();
    return 0;
}
