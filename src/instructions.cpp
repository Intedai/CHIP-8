#include "cpu.hpp"
#include "instructions.hpp"

// OPCODE: 00E0
void instructions::clear(Screen& screen)
{
    screen.clearScreenBuffer();
}

// OPCODE: 6XNN
void instructions::setVx(size_t x, uint8_t nn, CPU& cpu)
{
    cpu.setV(x, nn);
}

// OPCODE: 7XNN
void instructions::addToVx(size_t x, uint8_t nn, CPU& cpu)
{
    cpu.setV(x, cpu.getV(x) + nn);
}

// OPCODE: ANNN
void instructions::setI(uint16_t nnn, CPU& cpu)
{
    cpu.setI(nnn);
}

// OPCODE: 1NNN
void instructions::jump(uint16_t nnn, CPU& cpu)
{
    cpu.setPC(nnn);
    cpu.lastInstruction(); // Go back since every cycle instruction is incremented by 2.
}

// OPCODE: DXYN
void instructions::drawSprite(uint8_t n, size_t x, size_t y, Screen& screen, CPU& cpu)
{
    // Faster than mod WIDTH and mod HEIGHT, works only with numbers that are powers of 2
    uint8_t x_pos = cpu.getV(x) & (WIDTH-1);
    uint8_t y_pos = cpu.getV(y) & (HEIGHT-1);
    
    cpu.setV(0xF, 0);

    // Sprite is n bytes tall starting at i in memory
    for(size_t curr_byte_pos = 0; curr_byte_pos < n; curr_byte_pos++)
    {
        // If reached the edge stop drawing
        if (y_pos + curr_byte_pos == HEIGHT)
            break;

        uint8_t spriteByte = cpu.readFromMem(cpu.getI() + curr_byte_pos);
        for (size_t pixel_pos = 0; pixel_pos < BYTE_SIZE; pixel_pos++)
        {
            
            // If reached the edge stop drawing
            if (x_pos + pixel_pos == WIDTH)
                break;
            
            // 0x80 is most significant bit in byte, so it checks if the bits are on
            if ((spriteByte & (0x80 >> pixel_pos)) != 0)
            {
                if(screen.flipPixel(x_pos + pixel_pos,y_pos + curr_byte_pos) == 0)
                    cpu.setV(0xF, 1);
            }
        }
    }
}

// OPCODE: 3XNN
void instructions::ifVxEqualsNN(size_t x, uint8_t nn, CPU& cpu)
{
    if(cpu.getV(x) == nn)
        cpu.nextInstruction();
}

// OPCODE: 4XNN
void instructions::ifVxDoesntEqualNN(size_t x, uint8_t nn, CPU& cpu)
{
    if(cpu.getV(x) != nn)
        cpu.nextInstruction();
}

// OPCODE: 5XY0
void instructions::ifVxEqualsVy(size_t x, size_t y, CPU& cpu)
{
    if(cpu.getV(x) == cpu.getV(y))
        cpu.nextInstruction();
}

// OPCODE: 9XY0
void instructions::ifVxDoesntEqualVy(size_t x, size_t y, CPU& cpu)
{
    if(cpu.getV(x) != cpu.getV(y))
        cpu.nextInstruction();
}

// OPCODE: 2NNN
void instructions::callSubroutine(uint16_t nnn, CPU& cpu)
{
    cpu.pushToStack(cpu.getPC());
    cpu.setPC(nnn);
    cpu.lastInstruction(); // Go back since every cycle instruction is incremented by 2.
}

// OPCODE: 00EE
void instructions::returnFromSub(CPU& cpu)
{
    cpu.setPC(cpu.popFromStack());
}

// OPCODE: 8XY0
void instructions::movVxVy(size_t x, size_t y, CPU& cpu)
{
    cpu.setV(x, cpu.getV(y));
}

// OPCODE: 8XY1
void instructions::orVxVy(size_t x, size_t y, CPU& cpu)
{
    cpu.setV(x, cpu.getV(x) | cpu.getV(y));
}

// OPCODE: 8XY2
void instructions::andVxVy(size_t x, size_t y, CPU& cpu)
{
    cpu.setV(x, cpu.getV(x) & cpu.getV(y));
}

// OPCODE: 8XY3
void instructions::xorVxVy(size_t x, size_t y, CPU& cpu)
{
    cpu.setV(x, cpu.getV(x) ^ cpu.getV(y));
}

// OPCODE: 8XY4
void instructions::addVxVy(size_t x, size_t y, CPU& cpu)
{
    int16_t sum = cpu.getV(x) + cpu.getV(y);
    cpu.setV(0xF, sum > 0xFF ? 1 : 0);
    cpu.setV(x, sum & 0xFF);
}

// OPCODE: 8XY5
void instructions::subVxVy(size_t x, size_t y, CPU& cpu)
{
    cpu.setV(0xF, cpu.getV(x) > cpu.getV(y) ? 1 : 0);
    cpu.setV(x, cpu.getV(x) - cpu.getV(y));
}

// OPCODE: 8XY7
void instructions::subVyVx(size_t x, size_t y, CPU& cpu)
{
    cpu.setV(0xF, cpu.getV(x) > cpu.getV(y) ? 1 : 0);
    cpu.setV(x, cpu.getV(y) - cpu.getV(x));
}

// OPCODE: 8XY6
void instructions::shiftRight(size_t x, size_t y, CPU& cpu)
{
    cpu.setV(0xF, cpu.getV(y) & 0x1);
    cpu.setV(x, cpu.getV(y) >> 1);
}

// OPCODE: 8XYE
void instructions::shiftLeft(size_t x, size_t y, CPU& cpu)
{
    cpu.setV(0xF, (cpu.getV(y) & 0x80) >> (BYTE_SIZE - 1));
    cpu.setV(x, cpu.getV(y) << 1);
}

// OPCODE: FX55
void instructions::writeV0toVXtoMEM(size_t x, CPU& cpu)
{
    for(uint8_t i = 0; i <= x; i++)
    {
        cpu.writeToMem(cpu.getI() + i, cpu.getV(i));
    }
}

// OPCODE: FX65
void instructions::readV0toVXfromMEM(size_t x, CPU& cpu)
{
    for(size_t i = 0; i <= x; i++)
    {
        cpu.setV(i,cpu.readFromMem(cpu.getI() + i));
    }
}

// OPCODE: FX33
void instructions::decimalConversion(size_t x, CPU& cpu)
{
    uint8_t value = cpu.getV(x);
    for(int i = 2; i >= 0; i--)
    {
        cpu.writeToMem(cpu.getI() + i, value % 10);
        value /= 10;
    }
}

// OPCODE: FX1E
void instructions::addVxNN(size_t x, CPU& cpu)
{
    cpu.setI(cpu.getI() + cpu.getV(x));
}

