#include "chip8.hpp"

Chip8::Chip8(std::string_view fileName,sf::RenderWindow& windowRef)
    : screen(windowRef),
      cpu(fileName),
      keyboard(),
      oscillator()
{
    
}

void Chip8::run()
{
    sf::Clock clock;
    while (screen.window.isOpen())
    {
        sf::Event event;
        while (screen.window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                        screen.window.close();
                        break;
            case sf::Event::Resized:
                break;
            default:
                break;
            }
        }

        keyboard.update();
        cpu.updateTimers(oscillator);
        
        for(int i = 0; i < cpu.getIPF(); i++)
        {
            cpu.fetchOpcode();
            cpu.nextInstruction();

            // Only allow one draw instruction per frame
            if (cpu.executeInstruction(screen, keyboard) == stopLoop)
                break;
        }

        screen.window.clear();
        screen.render();

        sf::Time elapsed = clock.getElapsedTime();

        if (cycleTime > elapsed)
            sf::sleep(cycleTime - elapsed);
        clock.restart();
    }
}
