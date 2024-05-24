#include "instructions.hpp"

Instructions::Instructions(Chip8& chip8Ref)
    : chip8(chip8Ref)
{}

//00E0
void Instructions::clear()
{
    chip8.screen.fill(0);
}

//8xy0
void Instructions::mov_vxvy(size_t x, size_t y)
{
    chip8.V[x] = chip8.V[y];
}

//8xy3
void Instructions::xor_vxvy(size_t x, size_t y)
{    
    chip8.V[x] ^=  chip8.V[y];
}

//8xy1
void Instructions::or_vxvy(size_t x, size_t y)
{    
    chip8.V[x] |=  chip8.V[y];
}

//8xy2
void Instructions::and_vxvy(size_t x, size_t y)
{
    chip8.V[x] &=  chip8.V[y];
}

//6xnn
void Instructions::mov_vxnn(size_t x, uint8_t nn)
{
    chip8.V[x] += nn;
}

//Annn
void Instructions::mvi_nnn(uint16_t nnn)
{
    chip8.I = nnn;
}

//Fx15
void Instructions::sdelay_vx(size_t x)
{
    chip8.delayTimer = chip8.V[x];
}

//Fx18
void Instructions::ssound_vx(size_t x)
{
    chip8.soundTimer = chip8.V[x];
}

//Fx07
void Instructions::gdelay_vx(size_t x)
{
    chip8.V[x] = chip8.delayTimer;
}

//1nnn
void Instructions::jump_nnn(uint16_t nnn)
{
    chip8.pc = nnn;
}

//Bnnn
void Instructions::jump0_nnn(uint16_t nnn)
{
    chip8.pc = nnn + chip8.V[0];
}

//Cxnn
void Instructions::rand_vxnn(size_t x, uint8_t nn)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(0, 255);
    chip8.V[x] = dis(gen) & nn;
}

//3xnn
void Instructions::ifVxEqualsNN(size_t x, uint8_t nn)
{
    if (chip8.V[x] == nn)
        chip8.nextInstruction();
}

//4xnn
void Instructions::ifVxNotEqualsNN(size_t x, uint8_t nn)
{
    if (chip8.V[x] != nn)
        chip8.nextInstruction();
}

//5xy0
void Instructions::ifVxEqualsVy(size_t x, size_t y)
{
    if (chip8.V[x] == chip8.V[y])
        chip8.nextInstruction();
}

//9xy0
void Instructions::ifVxNotEqualsVy(size_t x, size_t y)
{
    if (chip8.V[x] != chip8.V[y])
        chip8.nextInstruction();
}

//8xy4
void Instructions::add_vxvy(size_t x, size_t y)
{
    uint16_t sum = chip8.V[x] + chip8.V[y];
    chip8.V[0xF] = (sum > 0xFF) ? 1 : 0;
    chip8.V[x] = sum & 0xFF;
}

//7xnn
void Instructions::add_vxnn(size_t x, uint8_t nn)
{
    chip8.V[x] += nn;
}

//Fx1E
void Instructions::add_ivx(size_t x)
{
    chip8.I += chip8.V[x];
}

//8xy5
void Instructions::sub_vxvy(size_t x, size_t y)
{
    chip8.V[0xF] = (chip8.V[x] > chip8.V[y]) ? 1 : 0;
    chip8.V[x] -= chip8.V[y];
}

//8xy7
void Instructions::nsub_vxvy(size_t x, size_t y)
{
    chip8.V[0xF] = (chip8.V[y] > chip8.V[x]) ? 1 : 0;
    chip8.V[x] = chip8.V[y] - chip8.V[x];
}

//Fx33
void Instructions::bcd(size_t x)
{
    uint8_t value = chip8.V[x];
    chip8.memory[chip8.I + 2] = value % 10;
    value /= 10;
    chip8.memory[chip8.I + 1] = value % 10;
    value /= 10;
    chip8.memory[chip8.I] = value % 10;
}

//8xy6
void Instructions::rightShift(size_t x, size_t y)
{
    chip8.V[0xF] = chip8.V[y] & 0x1;
    chip8.V[x] = chip8.V[y] >> 1;
}

//8xyE
void Instructions::leftShift(size_t x, size_t y)
{
    chip8.V[0xF] = (chip8.V[y] & 0x80) >> 7;
    chip8.V[x] = chip8.V[y] << 1;
}

//2nnn
void Instructions::callNNN(uint16_t nnn)
{
    chip8.stack[chip8.sp] = chip8.pc;
    chip8.sp++;
    chip8.pc = nnn;
}

//00EE
void Instructions::returnFromSub()
{
    chip8.sp--;
    chip8.pc = chip8.stack[chip8.sp];
}

//Fx55
void Instructions::writeV0toVXtoMEM(uint8_t x)
{
    for (uint8_t i = 0; i <= x; ++i)
    {
        chip8.memory[chip8.I + i] = chip8.V[i];
    }
}

//Fx65
void Instructions::readV0toVXtoMEM(uint8_t x)
{
    for (uint8_t i = 0; i <= x; ++i)
    {
        chip8.V[i] = chip8.memory[chip8.I + i];
    }
}

//Dxyn
void Instructions::drawSprite(uint8_t x, uint8_t y, uint8_t n)
{
    chip8.V[0xF] = 0;
    for (uint8_t i = 0; i < n; ++i)
    {
        uint8_t spriteByte = chip8.memory[chip8.I + i];
        for (uint8_t j = 0; j < 8; ++j)
        {
            if ((spriteByte & (0x80 >> j)) != 0)
            {
                size_t index = (chip8.V[x] + j + ((chip8.V[y] + i) * WIDTH)) % (WIDTH * HEIGHT);
                if (chip8.screen[index])
                {
                    chip8.V[0xF] = 1;
                }
                chip8.screen[index] ^= 1;
            }
        }
    }
}

//Fx29
void Instructions::setItoHex(uint8_t x)
{
    chip8.I = chip8.V[x] * 5;
}

//Ex9E
void Instructions::skipIfPressed(uint8_t x)
{
    if (chip8.keyboard[chip8.V[x]])
    {
        chip8.nextInstruction();
    }
}

//ExA1
void Instructions::skipIfNotPressed(uint8_t x)
{
    if (!chip8.keyboard[chip8.V[x]])
    {
        chip8.nextInstruction();
    }
}

//Fx0A
void Instructions::getKey(uint8_t x)
{
    for (uint8_t i = 0; i < chip8.keyboard.size(); ++i)
    {
        if (chip8.keyboard[i])
        {
            chip8.V[x] = i;
            return;
        }
    }
    chip8.pc -= 2; // Repeat the instruction if no key was pressed
}
