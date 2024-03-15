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
        void mov_vxvy();
        void or_vxvy();
        void and_vxvy();
        void xor_vxvy();
        void mov_vxnn();
        void mvi_nnn();
        
        void rand_vxnn();
        void jump_nnn();        
        void jump0_nnn();
        void sdelay_vx();
        void ssound_vx();
        void gdelay_vx();

        void ifVxNotEqualsNN();
        void ifVxEqualsNN();
        void ifVxNotEqualsVy();
        void ifVxEqualsVy();

};

#endif
