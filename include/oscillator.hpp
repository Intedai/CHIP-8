#ifndef OSCILLATOR_HPP
#define OSCILLATOR_HPP

#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>

constexpr int SINE_UPPERBOUND = 32767;
constexpr int SAMPLE_RATE = 44100;
constexpr double frequency = 440;

class Oscillator {
    private:
        sf::SoundBuffer buffer;
        sf::Sound sound;
        void initBuffer();
        void initSound();
        

    public:
        Oscillator();
        void playBeepSound();
        void stopBeepSound();
};

#endif
