#ifndef CPU_HPP
#define CPU_HPP

#include <array>
#include <string_view>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstddef>

#include "instructions.hpp"
#include "globals.hpp"

#define X() ((opcode & 0x0F00) >> BYTE_SIZE)
#define Y() ((opcode & 0x00F0) >> NIBBLE_SIZE)
#define N() (opcode & 0x000F)
#define NN() (opcode & 0x00FF)
#define NNN() (opcode & 0x0FFF)

constexpr int MEMORY_SIZE = 0x1000;
constexpr int REGISTER_COUNT = 0x10;
constexpr int START_ADDRESS = 0x200;
constexpr int FONT_SIZE = 0x50;
constexpr int STARTING_IPF = 10; 

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

class CPU {
    private:
        std::array<uint8_t, MEMORY_SIZE> memory;
        std::array<uint8_t, REGISTER_COUNT> V;
        std::array<uint16_t, REGISTER_COUNT> stack;
        uint16_t sp;
        uint16_t opcode;
        uint16_t pc;
        uint16_t I;
        uint8_t delayTimer;
        uint8_t soundTimer;
        int IPF;

        void loadFontSet();
        void loadGameToMem(std::string_view fileName);
    public:
        CPU(std::string_view fileName);

        void fetchOpcode();
        void updateTimers();
        void executeInstruction(Screen& screen);
        
        uint16_t getPC();
        void setPC(uint16_t value);

        void nextInstruction();
        void lastInstruction();

        uint8_t getV(size_t index);
        void setV(size_t index, uint8_t value);

        uint16_t getI();
        void setI(uint16_t value);

        uint8_t readFromMem(size_t index);
        void writeToMem(size_t index, uint8_t value);

        void pushToStack(uint16_t value);
        uint16_t popFromStack();

        int getIPF();


};

#endif
