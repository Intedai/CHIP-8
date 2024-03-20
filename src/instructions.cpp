#include "instructions.hpp"

//TODO: make a friend class of chip8 called instructions and restructure

//00E0
void Chip8::clear()
{
    screen.fill(0);
    drawFlag = 1;

    nextInstruction();
}

//8xy0
void Chip8::mov_vxvy(size_t x, size_t y)
{
    V[x] = V[y];
    nextInstruction();
}

//8xy3
void Chip8::xor_vxvy(size_t x, size_t y)
{    
    V[x] ^=  V[y];
    nextInstruction();
}

//8xy1
void Chip8::or_vxvy(size_t x, size_t y)
{    
    V[x] |=  V[y];
    nextInstruction();
}

//8xy2
void Chip8::and_vxvy(size_t x, size_t y)
{
    V[x] &=  V[y];
    nextInstruction();
}

//6xnn
void Chip8::mov_vxnn(size_t x, uint8_t nn)
{
    V[x] += nn;
    nextInstruction();
}

//Annn
void Chip8::mvi_nnn(uint16_t nnn)
{
    I = nnn;
    nextInstruction();
}

//Fx15
void Chip8::sdelay_vx(size_t x)
{
    delayTimer = V[x];
    nextInstruction();
}

//Fx18
void Chip8::ssound_vx(size_t x)
{
    soundTimer = V[x];
    nextInstruction();
}

//Fx07
void Chip8::gdelay_vx(size_t x)
{
    V[x] = delayTimer;
    nextInstruction();
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
    nextInstruction();
}

//3xnn
void Chip8::ifVxNotEqualsNN(size_t x, uint8_t nn)
{
    if(V[x] != nn)
        nextInstruction();
    else
        skipInstruction();
}

//4xnn
void Chip8::ifVxEqualsNN(size_t x, uint8_t nn)
{
    if(V[x] == nn)
        nextInstruction();
    else
        skipInstruction();
}

//5xy0
void Chip8::ifVxNotEqualsVy(size_t x, size_t y)
{
    if(V[x] != V[y])
        nextInstruction();
    else
        skipInstruction();
}

//9xy0
void Chip8::ifVxEqualsVy(size_t x ,size_t y)
{
    if(V[x] == V[y])
        nextInstruction();
    else
        skipInstruction();
}

//8xy4
void Chip8::add_vxvy(size_t x, size_t y)
{
    const int sum = V[x] + V[y];
    V[x] = static_cast<uint8_t>(sum);
    
    // Smallest overflow is 0xFF + 0x1 = 0x100 and biggest overflow is 0xFF + 0xFF= 0x1FE
    V[0xF] = static_cast<uint8_t>(sum >> BYTE_SIZE);
    
    nextInstruction();
}

//7xnn
void Chip8::add_vxnn(size_t x, uint8_t nn)
{
    V[x] += nn;
    nextInstruction();
}

//Fx1E
void Chip8::add_ivx(size_t x)
{
    I += V[x];
    nextInstruction();
}

//8xy5
void Chip8::sub_vxvy(size_t x, size_t y)
{
    const int flag = V[x] >= V[y];

    V[x] -= V[y];

    V[0xF] = flag;
    
    nextInstruction();
}

//8xy7
void Chip8::nsub_vxvy(size_t x, size_t y)
{
    const int flag = V[y] >= V[x];

    V[x] = V[y] - V[x];
    
    V[0xF] = flag;
    
    nextInstruction();
}

//Fx33
void Chip8::bcd(size_t x)
{
    memory[I] = V[x] / 100;
    memory[I + 1] = (V[x] / 10) % 10;
    memory[I + 2] = V[x] % 10;

    nextInstruction();
}

//8xy6
void Chip8::rightShift(size_t x, size_t y)
{
    const int rightBit = 0x1 & V[y];
    V[x] = (V[y] >> 1);
    V[0xF] = rightBit;
    nextInstruction();
}

//8xyE
void Chip8::leftShift(size_t x, size_t y)
{
    const int leftBit = V[y] >> (BYTE_SIZE - 1);
    V[x] = (V[y] << 1);
    V[0xF] = leftBit;
    nextInstruction();
}
