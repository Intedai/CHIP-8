#include "oscillator.hpp"

Oscillator::Oscillator()
{
    initBuffer();
    initSound();
}

void Oscillator::initBuffer()
{
    std::vector<sf::Int16> samples;

    for (int time = 0; time < SAMPLE_RATE; time++)
    {
        double ticksPerSecond = SAMPLE_RATE / frequency;
        double cycles = time / ticksPerSecond;
        double radian = 2 * M_PI * cycles;
        short amplitude = SINE_UPPERBOUND; // Could be multiplied by a number between 0 and 1 to change volume 
    
        samples.push_back(static_cast<short>(amplitude * std::sin(radian)));
    }

    buffer.loadFromSamples(&samples[0], samples.size(), 1, SAMPLE_RATE);
}

void Oscillator::initSound()
{
    sound.setBuffer(buffer);
    sound.setLoop(true);
}

void Oscillator::playBeepSound()
{
    if (sound.getStatus() == sf::Sound::Playing)
        return;
    sound.play();
}

void Oscillator::stopBeepSound()
{
    if (sound.getStatus() == sf::Sound::Stopped)
        return;
    sound.stop();
}
