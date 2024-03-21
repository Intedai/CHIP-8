#include "instructions.hpp"

//TODO: make a friend class of chip8 called instructions and restructure
//TODO: Remove next instruction to
//TODO: Check if it is needed to: I += x+1 in fx65 and fx55

//00E0
void Chip8::clear()
{
    screen.fill(0);
    drawFlag = 1;
}

//8xy0
void Chip8::mov_vxvy(size_t x, size_t y)
{
    V[x] = V[y];
}

//8xy3
void Chip8::xor_vxvy(size_t x, size_t y)
{    
    V[x] ^=  V[y];
}

//8xy1
void Chip8::or_vxvy(size_t x, size_t y)
{    
    V[x] |=  V[y];
}

//8xy2
void Chip8::and_vxvy(size_t x, size_t y)
{
    V[x] &=  V[y];
}

//6xnn
void Chip8::mov_vxnn(size_t x, uint8_t nn)
{
    V[x] += nn;
}

//Annn
void Chip8::mvi_nnn(uint16_t nnn)
{
    I = nnn;
}

//Fx15
void Chip8::sdelay_vx(size_t x)
{
    delayTimer = V[x];
}

//Fx18
void Chip8::ssound_vx(size_t x)
{
    soundTimer = V[x];
}

//Fx07
void Chip8::gdelay_vx(size_t x)
{
    V[x] = delayTimer;
}

//1nnn
void Chip8::jump_nnn(uint16_t nnn)
{
    pc = nnn;
}

//Bnnn
void Chip8::jump0_nnn(uint16_t nnn)
{
    pc = nnn + V[0];
}

//Cxnn
void Chip8::rand_vxnn(size_t x, uint8_t nn)
{
    // Static to initialize once instead of every call
    static std::random_device rd;
    static std::mt19937 eng(rd());

    // Range is 0 to 255 because the random number is a byte
    std::uniform_int_distribution<> distr(0, (1 << BYTE_SIZE) - 1);

    uint8_t randomNumber = static_cast<uint8_t>(distr(eng));

    V[x] = randomNumber & nn;
}

//3xnn
void Chip8::ifVxNotEqualsNN(size_t x, uint8_t nn)
{
    if(V[x] == nn)
        nextInstruction();
}

//4xnn
void Chip8::ifVxEqualsNN(size_t x, uint8_t nn)
{
    if(V[x] != nn)
        nextInstruction();
}

//5xy0
void Chip8::ifVxNotEqualsVy(size_t x, size_t y)
{
    if(V[x] == V[y])
        nextInstruction();
}

//9xy0
void Chip8::ifVxEqualsVy(size_t x ,size_t y)
{
    if(V[x] != V[y])
        nextInstruction();
}

//8xy4
void Chip8::add_vxvy(size_t x, size_t y)
{
    const int sum = V[x] + V[y];
    V[x] = static_cast<uint8_t>(sum);
    
    // Smallest overflow is 0xFF + 0x1 = 0x100 and biggest overflow is 0xFF + 0xFF= 0x1FE
    V[0xF] = static_cast<uint8_t>(sum >> BYTE_SIZE);
}

//7xnn
void Chip8::add_vxnn(size_t x, uint8_t nn)
{
    V[x] += nn;
}

//Fx1E
void Chip8::add_ivx(size_t x)
{
    I += V[x];
}

//8xy5
void Chip8::sub_vxvy(size_t x, size_t y)
{
    const int flag = V[x] >= V[y];

    V[x] -= V[y];

    V[0xF] = flag;
}

//8xy7
void Chip8::nsub_vxvy(size_t x, size_t y)
{
    const int flag = V[y] >= V[x];

    V[x] = V[y] - V[x];
    
    V[0xF] = flag;
}

//Fx33
void Chip8::bcd(size_t x)
{
    memory[I] = V[x] / 100;
    memory[I + 1] = (V[x] / 10) % 10;
    memory[I + 2] = V[x] % 10;
}

//8xy6
void Chip8::rightShift(size_t x, size_t y)
{
    const int rightBit = 0x1 & V[y];
    V[x] = (V[y] >> 1);
    V[0xF] = rightBit;
}

//8xyE
void Chip8::leftShift(size_t x, size_t y)
{
    const int leftBit = V[y] >> (BYTE_SIZE - 1);
    V[x] = (V[y] << 1);
    V[0xF] = leftBit;
}

//2NNN
void Chip8::callNNN(uint16_t nnn)
{
    stack[sp++ & 0xF] = pc;
    pc = nnn;
}

//00EE
void Chip8::returnFromSub()
{
    pc = stack[--sp & 0xF];
}

//fx55
void Chip8::writeV0toVXtoMEM(uint8_t x)
{
    for(uint8_t i = 0; i <= x; ++i)
    {
        memory[I+i] = V[i];
    }
    //I += x+1;
}

//fx65
void Chip8::readV0toVXtoMEM(uint8_t x)
{
    for(uint8_t i = 0; i <= x; ++i)
    {
        V[i] = memory[I+i];
    }
    //I += x+1;
}

//Dxyn
void Chip8::drawSprite(uint8_t x, uint8_t y, uint8_t n)
{
    uint8_t xCoord = V[x] & 0x3F;
    uint8_t yCoord = V[y] & 0x1F;
    V[0xF] = 0;

    for(int row = 0; row < n; ++row)
    {
        // Stop drawing if reached the bottom
        if (yCoord + row >= HEIGHT)
            break;

        uint8_t spriteRow = memory[I + row];

        // Width is always 8
        for(int col = 0; col < BYTE_SIZE; ++col)
        {
            // Stop drawing current row if reached the right edge of the screen
            if (xCoord + col >= WIDTH) 
                break;

            // Get current pixel from MSB to LSB
            uint8_t pixel = (spriteRow >> (7 - col)) & 1;
            size_t screenIndex = (yCoord + row) * WIDTH + (xCoord + col);

            if(pixel)
            {
                if(screen[screenIndex] == 1)
                {
                    V[0xF] = 1;
                }
                screen[screenIndex] ^= 1;
            }
        }
    }
}

