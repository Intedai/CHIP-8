#include "cpu.hpp"

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

void CPU::updateTimers()
{
    if (soundTimer > 0)
    {
        soundTimer--;
        // Sound placeholder
        std::cout << "BEEP";
        std::cout << "\a";
    }

    if (delayTimer > 0)
        delayTimer--;
}

void CPU::executeInstruction(Screen& screen, Keyboard& keyboard)
{
    switch (opcode & 0xF000)
    {
        case 0x0000:
            switch (opcode & 0xFFF)
            {
                case 0x0E0:
                    instructions::clear(screen);
                    break;
                case 0x0EE:
                    instructions::returnFromSub(*this);
                    break;
                default:
                    
                    break;
            }

            break;
            
        case 0x1000:
            instructions::jump(NNN(), *this);
            break;
        case 0x2000:
            instructions::callSubroutine(NNN(),*this);
            break;
        case 0x3000:
            instructions::ifVxEqualsNN(X(),NN(), *this);
            break;
        case 0x4000:
            instructions::ifVxDoesntEqualNN(X(), NN(), *this);
            break;
        case 0x5000:
            instructions::ifVxEqualsVy(X(), NN(), *this);
            break;
        case 0x6000:
            instructions::setVx(X(),NN(), *this);
            break;
        case 0x7000:
            instructions::addToVx(X(), NN(), *this);
            break;
        case 0x8000:
            switch(opcode & 0x000F)
            {
                case 0x0000:
                    instructions::movVxVy(X(), Y(), *this);
                    break;
                case 0x0001:
                    instructions::orVxVy(X(), Y(), *this);
                    break;
                case 0x0002:
                    instructions::andVxVy(X(), Y(), *this);
                    break;
                case 0x0003:
                    instructions::xorVxVy(X(), Y(), *this);
                    break;
                case 0x0004:
                    instructions::addVxVy(X(), Y(), *this);
                    break;
                case 0x0005:
                    instructions::subVxVy(X(), Y(), *this);
                    break;
                case 0x0006:
                    instructions::shiftRight(X(), Y(), *this);
                    break;
                case 0x0007:
                    instructions::subVyVx(X(), Y(), *this);
                    break;
                case 0x000E:
                    instructions::shiftLeft(X(), Y(), *this);
                    break;
                default:
                    
                    break;
            }

            break;

        case 0x9000:
            instructions::ifVxDoesntEqualVy(X(), Y(), *this);
            break;
        case 0xA000:
            instructions::setI(NNN(), *this);
            break;
        case 0xB000:
            instructions::jumpPlusV0(NNN(), *this);
            break;
        case 0xD000:
            instructions::drawSprite(N(),X(),Y(), screen, *this);
            break;
        case 0xE000:
            switch (opcode & 0x00FF)
            {
                case 0x009E:
                    instructions::skipIfPressed(X(),keyboard,*this);
                    break;
                case 0x00A1:
                    instructions::skipIfNotPressed(X(),keyboard,*this);
                    break;     
                default:

                    break;
            }
            break;
        case 0xF000:
            switch(opcode & 0x0FF)
            {
                case 0x001E:
                    instructions::addVxNN(X(), *this);
                    break;
                
                case 0x0033:
                    instructions::decimalConversion(X(),*this);
                    break;
                
                case 0x0055:
                    instructions::writeV0toVXtoMEM(X(),*this);
                    break;
                case 0x0065:
                    instructions::readV0toVXfromMEM(X(),*this);
                    break;
                case 0x0029:
                    instructions::setItoFontChar(X(),*this);
                    break;
                case 0x0007:
                    instructions::setVxToDelayTimer(X(), *this);
                    break;
                case 0x015:
                    instructions::setDelayTimerToVx(X(),*this);
                    break;
                case 0x018:
                    instructions::setSoundTimerToVx(X(), *this);
                    break;
                default:

                    break;
            }

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

uint16_t CPU::getPC()
{
    return pc;
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

void CPU::pushToStack(uint16_t value)
{
    stack[sp] = value;
    sp++;
}

uint16_t CPU::popFromStack()
{
    sp--;
    return stack[sp];
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

void CPU::setDelayTimer(uint8_t value)
{
    delayTimer = value;
}

uint8_t CPU::getDelayTimer()
{
    return delayTimer;
}

void CPU::setSoundTimer(uint8_t value)
{
    soundTimer = value;
}