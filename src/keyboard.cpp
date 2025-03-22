#include "keyboard.hpp"
#include <iostream>
Keyboard::Keyboard()
    : keys{},
      keysLastFrame{}
{
}
void Keyboard::update()
{
    // Deep copy
    keysLastFrame = keys;

    keys.fill(0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        keys[1] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        keys[2] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        keys[3] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        keys[0xC] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        keys[4] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        keys[5] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        keys[6] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        keys[0xD] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        keys[7] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        keys[8] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        keys[9] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        keys[0xE] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        keys[0xA] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        keys[0] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
    {
        keys[0xB] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
    {
        keys[0xF] = 1;
    }

    //debug
    /*
    for(uint8_t key : keys)
    {
        if (key == 0)
            std::cout << "0";
        else
        std::cout << "1"; 
    }
    std::cout << std::endl;
    //*/
}

bool Keyboard::isKeyHeldDown(size_t key)
{
    return keys[key];
}

bool Keyboard::isKeyReleased(size_t key)
{
    return keysLastFrame[key] && !keys[key]; 
}