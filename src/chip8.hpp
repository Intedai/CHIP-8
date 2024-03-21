#ifndef CHIP8 
#define CHIP8

#include <array>
#include <cstdint>
#include <string_view>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "globals.hpp"

constexpr int WIDTH = 64;
constexpr int HEIGHT = 32;
constexpr int MEMORY_SIZE = 0x1000;
constexpr int REGISTER_COUNT = 0x10;
constexpr int KEY_COUNT = 0x10;
constexpr int START_ADDRESS = 0x200;
constexpr int FONT_SIZE = 0x50;

constexpr std::array<uint8_t, FONT_SIZE> fontSet = 
{ 
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class Chip8
{
    private:
        std::array<uint8_t,WIDTH * HEIGHT> screen;    
        std::array<uint8_t, MEMORY_SIZE> memory;
        std::array<uint8_t, REGISTER_COUNT> V;
        std::array<uint8_t, KEY_COUNT> keyboard;
        std::array<uint16_t, REGISTER_COUNT> stack;
        uint16_t sp;
        uint16_t opcode;
        uint16_t pc;
        uint16_t I;
        uint8_t drawFlag;
        uint8_t delayTimer;
        uint8_t soundTimer;
    
        void loadGame(std::string_view fileName);
        void fetchOpcode();
        void updateTimers();
        void nextInstruction();
        void skipInstruction();

    public:
        Chip8(std::string_view fileName);

        // Opcode handle functions
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
};

#endif
