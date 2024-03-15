#include "instructions.hpp"

//TODO: make a friend class of chip8 called instructions and restructure

//00E0
void Chip8::clear()
{
    screen.fill(0);
    pc += 2;
    drawFlag = 1;
}

//8xy0
void Chip8::mov_vxvy()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);
    size_t y = (opcode & 0x00F0) >> NIBBLE_SIZE;

    V[x] = V[y];
    pc += 2;
}

//8xy3
void Chip8::xor_vxvy()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);
    size_t y = (opcode & 0x00F0) >> NIBBLE_SIZE;
    
    V[x] ^=  V[y];
    pc += 2;
}

//8xy1
void Chip8::or_vxvy()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);
    size_t y = (opcode & 0x00F0) >> NIBBLE_SIZE;
    
    V[x] |=  V[y];
    pc += 2;
}

//8xy2
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

//Fx15
void Chip8::sdelay_vx()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);

    delayTimer = V[x];
    pc += 2;
}

//Fx18
void Chip8::ssound_vx()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);

    soundTimer = V[x];
    pc += 2;
}

//Fx07
void Chip8::gdelay_vx()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);

    V[x] = delayTimer;
    pc += 2;
}

//1nnn
void Chip8::jump_nnn()
{
    uint8_t nnn = opcode & 0x0FFF;
    pc = nnn;
}

//Bnnn
void Chip8::jump0_nnn()
{
    uint8_t nnn = opcode & 0x0FFF;
    pc = nnn + I;
}

//Cxnn
void Chip8::rand_vxnn()
{
    size_t x = (opcode & 0x0F00) >> (NIBBLE_SIZE * 2);
    uint8_t nn = opcode & 0x00FF;

    // Static to initialize once instead of every call
    static std::random_device rd;
    static std::mt19937 eng(rd());

    // Range is 0 to 255 because the random number is a byte
    std::uniform_int_distribution<> distr(0, (1 << BYTE_SIZE) - 1);

    uint8_t randomNumber = static_cast<uint8_t>(distr(eng));

    V[x] = randomNumber & nn;
    pc += 2;
}