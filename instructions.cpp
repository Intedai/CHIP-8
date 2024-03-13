#include "chip8.hpp"

void Chip8::clear()
{
    std::fill(screen.begin(), screen.end(), 0);
    pc+=2;
    drawFlag = 1;
}