#include "chip8.hpp"


//00E0
void Chip8::clear()
{
    std::fill(screen.begin(), screen.end(), 0);
    pc+=2;
    drawFlag = 1;
}

//8xy0
void Chip8::mov_vxvy()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);
    size_t y = (opcode & 0x00F0) >> NIBBLE_SIZE;

    V[x] = V[y];
    pc+=2;
}

void Chip8::xor_vxvy()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);
    size_t y = (opcode & 0x00F0) >> NIBBLE_SIZE;
    
    V[x] ^=  V[y];
    pc+=2;
}

void Chip8::or_vxvy()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);
    size_t y = (opcode & 0x00F0) >> NIBBLE_SIZE;
    
    V[x] |=  V[y];
    pc+=2;
}

void Chip8::and_vxvy()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);
    size_t y = (opcode & 0x00F0) >> NIBBLE_SIZE;
    
    V[x] &=  V[y];
    pc += 2;
}

//6xnn
void Chip8::mov_vxnn()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);
    uint8_t nn = opcode & 0x00FF;
    
    V[x] += nn;
    pc += 2;
}

//Annn
void Chip8::mvi_nnn()
{
    I = opcode & 0x0FFF;
    pc += 2;
}