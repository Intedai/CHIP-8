#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <array>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <cstddef>
#include "globals.hpp"

class Screen {
    private:
        std::array<uint8_t,WIDTH * HEIGHT> screen;
        sf::Image screenImage;
        sf::Texture screenTexture;
        sf::Sprite textureSprite;
        void updateImage();

    public:
        sf::RenderWindow& window;
        Screen(sf::RenderWindow& windowRef);
        uint8_t flipPixel(size_t x, size_t y);
        void clearScreenBuffer();
        void render();
};

#endif
