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
    cpu.lastInstruction(); // Go back since every cycle instruction is incremented by 2. TODO: CHECK IF NEEDED
}

// OPCODE: DXYN
void instructions::drawSprite(uint8_t n, uint8_t x, uint8_t y, Screen& screen, CPU& cpu)
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

        uint8_t spriteByte = cpu.readFromMem(static_cast<size_t>(cpu.getI()) + curr_byte_pos);
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
