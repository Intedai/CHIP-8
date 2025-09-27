#include "keyboard.hpp"
#include <iostream>
Keyboard::Keyboard()
    : keys{},
      keysLastFrame{}
{
}

void Keyboard::setKeybind(int index, sf::Keyboard::Key key)
{
    keybinds[index] = key;
}

void Keyboard::update()
{
    // Deep copy
    keysLastFrame = keys;

    keys.fill(0);

    for (int i = 0; i < KEY_COUNT; i++)
    {
        if (sf::Keyboard::isKeyPressed(keybinds[i]))
            keys[i] = 1;
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