#include "keyboard.hpp"

Keyboard::Keyboard()
    : keys{}
{
}

bool Keyboard::isKeyHeldDown(size_t key)
{
    return keys[key];
}
