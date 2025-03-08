#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <cstdint>
#include <cstddef>

#include "screen.hpp"
class CPU;

namespace instructions {
    void clear(Screen& screen);
    void setVx(size_t x, uint8_t nn, CPU& cpu);
    void addToVx(size_t x, uint8_t nn, CPU& cpu);
    void setI(uint16_t nnn, CPU& cpu);
    void jump(uint16_t nnn, CPU& cpu);
    void drawSprite(uint8_t n, uint8_t x, uint8_t y, Screen& screen, CPU& cpu);
};

#endif
