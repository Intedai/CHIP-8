#include "screen.hpp"
#include <iostream>

Screen::Screen(sf::RenderWindow& windowRef)
    : screen{},
      window(windowRef)
{
    screenImage.create(WIDTH, HEIGHT);
}

void Screen::updateImage()
{
    for(int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            if (screen[i * WIDTH + j])
                screenImage.setPixel(j,i, COLOR_ON);
            else
                screenImage.setPixel(j,i, COLOR_OFF);
        }
    }
}

void Screen::clearScreenBuffer()
{
    screen.fill(0);
}

uint8_t Screen::flipPixel(size_t x, size_t y)
{
    size_t pos = y * WIDTH + x;
    screen[pos] ^= 1;

    return screen[pos];

}

void Screen::render() {
    updateImage();
    screenTexture.loadFromImage(screenImage);

    textureSprite.setTexture(screenTexture);
    textureSprite.setScale(10,10);

    window.draw(textureSprite);
    window.display();

}
