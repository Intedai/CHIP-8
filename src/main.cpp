#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "chip8.hpp"
#include <filesystem>
#include <unordered_map>
#include <string_view>
#include <string>

const std::unordered_map<std::string, std::string> tests {
    {"1", "tests/1-chip8-logo.ch8"},
    {"2", "tests/2-ibm-logo.ch8"},
    {"3", "tests/3-corax+.ch8"},
    {"4", "tests/4-flags.ch8"},
    {"5", "tests/5-quirks.ch8"},
    {"6", "tests/6-keypad.ch8"},
    {"7", "tests/7-beep.ch8"},
    {"random", "tests/random_number_test.ch8"}
};

int main(int argc, char* argv[])
{
    std::string rom;

    if (argc == 2)
    {
        rom = std::string(argv[1]);
        if (std::filesystem::path(rom).extension() != std::string(".ch8"))
        {
            std::cerr << "ERROR: File extension must be .ch8" << std::endl;
            return 1;
        }
    }
    else if (argc == 3 && std::string(argv[1]) == "-t")
    {
        std::string test = std::string(argv[2]);
        if(tests.find(test) == tests.end())
        {
            std::cerr << "ERROR: Test does not exist! (enter \"1\" - \"7\" or \"random\")" << std::endl;
            return 1;
        }

        rom = tests.at(test);
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << " [-t test (\"1\" - \"7\" or \"random\")] | [.ch8 file]" << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode({WIDTH * 10, HEIGHT * 10}), "CHIP8 EMULATOR");
    Chip8 chip8(rom, window);

    chip8.run();
    return 0;
}
