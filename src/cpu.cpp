#include "cpu.hpp"
#include "instructions.hpp"

CPU::CPU(std::string_view fileName)
    : memory{},
      V{},
      stack{},
      sp{0},
      opcode{0},
      pc{0},
      I{0},
      delayTimer{0},
      soundTimer{0},
      IPF{STARTING_IPF}
{
    loadFontSet();
    loadGameToMem(fileName);
}

void CPU::fetchOpcode()
{
    opcode = memory[pc] << BYTE_SIZE | memory[pc + 1];
}

void CPU::executeInstruction(Screen& screen)
{
    switch (opcode & 0xF000)
    {
    // JUST A HACK, FIX
    case 0x0000: 
        instructions::clear(screen);
        break;
    case 0xD000:
        instructions::drawSprite(N(),X(),Y(), screen, *this);
        break;
    case 0x6000:
        instructions::setVx(X(),NN(), *this);
        break;
    case 0xA000:
        instructions::setI(NNN(), *this);
        break;
    case 0x1000:
        instructions::jump(NNN(), *this);
        break;
    case 0x7000:
        instructions::addToVx(X(), NN(), *this);
        break;
    default:
        break;
    }

    nextInstruction();
}

void CPU::loadFontSet()
{
    for (size_t i = 0; i < FONT_SIZE; ++i)
    {
        memory[i] = fontSet[i];
    }
}

void CPU::loadGameToMem(std::string_view fileName)
{
    // Start from the end to get the size
    std::ifstream inFile(fileName.data(), std::ios::ate);

    if (!inFile)
    {
        std::cerr << "ERROR: Couldn't read from the file!" << std::endl;
        std::exit(1);
    }

    size_t fileSize = inFile.tellg();

    size_t maxSize = MEMORY_SIZE - START_ADDRESS;

    // Check if file fits in memory
    if (fileSize > maxSize)
    {
        std::cerr << "ERROR: File too big" << std::endl;
        std::exit(1);
    }

    // Go to start and write the game to memory
    inFile.seekg(0, std::ios::beg);
    inFile.read(reinterpret_cast<char*>(&memory[START_ADDRESS]), fileSize);
}

void CPU::setPC(uint16_t value)
{
    pc = value;
}

void CPU::nextInstruction()
{
    pc += 2;
}

void CPU::lastInstruction()
{
    pc -= 2;
}

uint8_t CPU::getV(size_t index)
{
    return V[index];
}

void CPU::setV(size_t index, uint8_t value)
{
    V[index] = value;
}

uint16_t CPU::getI()
{
    return I;
}

void CPU::setI(uint16_t value)
{
    I = value;
}

uint8_t CPU::readFromMem(size_t index)
{
    return memory[index];
}
void CPU::writeToMem(size_t index, uint8_t value)
{
    memory[index] = value;
}

int CPU::getIPF()
{
    return IPF;
}
