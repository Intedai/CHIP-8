#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <random>
#include <cstdint>
#include "chip8.hpp"
#include "globals.hpp"

class Instructions
{
public:
    Instructions(Chip8& chip8);
    void clear();
    void mov_vxvy(size_t x, size_t y);
    void xor_vxvy(size_t x, size_t y);
    void or_vxvy(size_t x, size_t y);
    void and_vxvy(size_t x, size_t y);
    void mov_vxnn(size_t x, uint8_t nn);
    void mvi_nnn(uint16_t nnn);
    void sdelay_vx(size_t x);
    void ssound_vx(size_t x);
    void gdelay_vx(size_t x);
    void jump_nnn(uint16_t nnn);
    void jump0_nnn(uint16_t nnn);
    void rand_vxnn(size_t x, uint8_t nn);
    void ifVxNotEqualsNN(size_t x, uint8_t nn);
    void ifVxEqualsNN(size_t x, uint8_t nn);
    void ifVxNotEqualsVy(size_t x, size_t y);
    void ifVxEqualsVy(size_t x, size_t y);
    void add_vxvy(size_t x, size_t y);
    void add_vxnn(size_t x, uint8_t nn);
    void add_ivx(size_t x);
    void sub_vxvy(size_t x, size_t y);
    void nsub_vxvy(size_t x, size_t y);
    void bcd(size_t x);
    void rightShift(size_t x, size_t y);
    void leftShift(size_t x, size_t y);
    void callNNN(uint16_t nnn);
    void returnFromSub();
    void writeV0toVXtoMEM(uint8_t x);
    void readV0toVXtoMEM(uint8_t x);
    void drawSprite(uint8_t x, uint8_t y, uint8_t n);
    void setItoHex(uint8_t x);
    void skipIfPressed(uint8_t x);
    void skipIfNotPressed(uint8_t x);
    void getKey(uint8_t x);

private:
    Chip8& chip8;
};

#endif
