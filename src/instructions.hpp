#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <cstdint>
#include <cstddef>

#include "screen.hpp"
#include "keyboard.hpp"

class CPU;

namespace instructions {
    void clear(Screen& screen);
    void setVx(size_t x, uint8_t nn, CPU& cpu);
    void addToVx(size_t x, uint8_t nn, CPU& cpu);
    void setI(uint16_t nnn, CPU& cpu);
    void jump(uint16_t nnn, CPU& cpu);
    void jumpPlusV0(uint16_t nnn, CPU& cpu);
    void drawSprite(uint8_t n, size_t x, size_t y, Screen& screen, CPU& cpu);
    void ifVxEqualsNN(size_t x, uint8_t nn, CPU& cpu);
    void ifVxDoesntEqualNN(size_t x, uint8_t nn, CPU& cpu);
    void ifVxEqualsVy(size_t x, size_t y, CPU& cpu);
    void ifVxDoesntEqualVy(size_t x, size_t y, CPU& cpu);
    void callSubroutine(uint16_t nnn, CPU& cpu);
    void returnFromSub(CPU& cpu);
    void movVxVy(size_t x, size_t y, CPU& cpu);
    void orVxVy(size_t x, size_t y, CPU& cpu);
    void andVxVy(size_t x, size_t y, CPU& cpu);
    void xorVxVy(size_t x, size_t y, CPU& cpu);
    void addVxVy(size_t x, size_t y, CPU& cpu);
    void subVxVy(size_t x, size_t y, CPU& cpu);
    void subVyVx(size_t x, size_t y, CPU& cpu);
    void shiftRight(size_t x, size_t y, CPU& cpu);
    void shiftLeft(size_t x, size_t y, CPU& cpu);
    void writeV0toVXtoMEM(size_t x, CPU& cpu);
    void readV0toVXfromMEM(size_t x, CPU& cpu);
    void decimalConversion(size_t x, CPU& cpu);
    void addVxNN(size_t x, CPU& cpu);
    void setItoFontChar(size_t x, CPU& cpu);
    void setVxToDelayTimer(size_t x, CPU& cpu);
    void setDelayTimerToVx(size_t x, CPU& cpu);
    void setSoundTimerToVx(size_t x, CPU& cpu);
    void skipIfPressed(size_t x, Keyboard& Keyboard, CPU& cpu);
    void skipIfNotPressed(size_t x, Keyboard& Keyboard, CPU& cpu);
}

#endif
