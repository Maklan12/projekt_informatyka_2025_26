#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.cpp"
#include "Game.cpp"

enum class StanGry { Menu, Playing, Scores, Exiting };

// Funkcja opóźniająca
void myDelay(int opoznienie)
{
    sf::Clock zegar;
    sf::Time czas;
    while (true)
    {
        czas = zegar.getElapsedTime();
        if (czas.asMilliseconds() > opoznienie)
        {
            zegar.restart();
            break;
        }
    }	
}

int main()
{
    const unsigned int width = 640.f;
    const unsigned int height = 480.f;
    
    sf::RenderWindow window(sf::VideoMode({width, height}), "Arkanoid");
    window.setFramerateLimit(60);
    
    Menu menu(window.getSize().x, window.getSize().y);
    Game game;
    StanGry currentState = StanGry::Menu;
    sf::Clock deltaClock;

    while (window.isOpen())
    {

        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
                
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    if (currentState == StanGry::Playing)
                    {
                        currentState = StanGry::Menu;
                        game.resetGame();
                    }
                }
                
                if (currentState == StanGry::Playing && keyPressed->scancode == sf::Keyboard::Scancode::F5)
                {
                    game.saveGame("savegame.txt");
                }

                if (currentState == StanGry::Menu)
                {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                    {
                        myDelay(250);
                        menu.przesunG();
                    }
                    
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                    {
                        myDelay(250);
                        menu.przesunD();
                    }
                    
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
                    {
                        switch (menu.getSelectedItem())
                        {
                            case 0: // Nowa gra
                                currentState = StanGry::Playing;
                                game.resetGame();
                                std::cout << "Uruchamiam gre..." << std::endl;
                                break;
                            case 1: // Wczytaj grę (NOWE) [cite: 223]
                                std::cout << "Wczytuje gre..." << std::endl;
                                if (game.loadGame("savegame.txt")) {
                                    currentState = StanGry::Playing;
                                    std::cout << "Gra wczytana!" << std::endl;
                                } else {
                                    std::cout << "Blad wczytywania! (Brak pliku?)" << std::endl;
                                }
                                break;
                            case 2: // Ostatnie wyniki
                                currentState = StanGry::Scores;
                                std::cout << "Najlepsze wyniki..." << std::endl;
                                break;
                            case 3: // Wyjście
                                currentState = StanGry::Exiting;
                                window.close();
                                break;
                        }
                    }
                }
            }
        }

        if (currentState == StanGry::Playing)
        {
            sf::Time deltaTime = deltaClock.restart();
            game.update(deltaTime);
            
            if (game.isGameOver())
            {
                currentState = StanGry::Menu;
                game.resetGame();
            }
        }

        window.clear();

        switch (currentState)
        {
            case StanGry::Menu:
                menu.draw(window);
                break;
            case StanGry::Playing:
                game.render(window);
                break;
            case StanGry::Scores:
                menu.draw(window); 
                break;
            case StanGry::Exiting:
                break;
        }

        window.display();
    }

    return 0;
}