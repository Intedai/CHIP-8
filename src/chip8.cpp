#include "chip8.hpp"

Chip8::Chip8(std::string_view fileName,sf::RenderWindow& windowRef)
    : screen(windowRef),
      cpu(fileName)
{
    
}

void Chip8::run()
{
    sf::Clock clock; // do something with this
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
            case sf::Event::KeyPressed:
                // do something
                break;
            
            default:
                break;
            }
        }

        cpu.updateTimers();
        
        for(int i = 0; i < cpu.getIPF(); i++)
        {
            cpu.fetchOpcode();
            cpu.executeInstruction(screen);
        }

        sf::Time elapsed = clock.getElapsedTime();

        if (cycleTime > elapsed)
            sf::sleep(cycleTime - clock.getElapsedTime());

        //screen.window.clear(); // <==== I Dont think it's needed but here incase im wrong
        screen.render();
    }
}
