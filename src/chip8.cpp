#include "chip8.hpp"

Chip8::Chip8(std::string_view fileName)
    : screen{},
      memory{},
      V{},
      keyboard{},
      stack{},
      sp{0},
      opcode{0},
      pc{0},
      I{0},
      drawFlag{0},
      delayTimer{0},
      soundTimer{0}
{
}

void Chip8::nextInstruction()
{
    pc += 2;
}

void Chip8::skipInstruction()
{
    pc += 4;
}

void Chip8::updateTimers()
{
    if (delayTimer > 0)
        --delayTimer;

    if (soundTimer > 0)
    {
        --soundTimer;
    }    
}

void Chip8::loadGame(std::string_view fileName)
{
    std::ifstream inFile(fileName.data(), std::ios::binary | std::ios::ate);

    if(!inFile)
    {
        std::cerr << "ERROR: Couldn't read from the file!" << std::endl;
        std::exit(1);       
    }

    size_t fileSize = inFile.tellg();

    size_t maxSize = MEMORY_SIZE - START_ADDRESS;

    if (fileSize > maxSize)
    {
        std::cerr << "ERROR: File too big" << std::endl;
        std::exit(1);
    }

    inFile.seekg(0, std::ios::beg);
    inFile.read(reinterpret_cast<char*>(&memory[START_ADDRESS]), fileSize);
}

void Chip8::fetchOpcode()
{
    opcode = memory[pc] << 8 | memory[pc + 1];
}