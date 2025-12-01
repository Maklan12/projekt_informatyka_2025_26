#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.cpp"
#include "Game.cpp"

enum class GameState { Menu, Playing, Scores, Exiting };

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
    GameState currentState = GameState::Menu;
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
                    if (currentState == GameState::Playing)
                    {
                        currentState = GameState::Menu;
                        game.resetGame();
                    }
                }
                
                if (currentState == GameState::Menu)
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
                                currentState = GameState::Playing;
                                game.resetGame();
                                std::cout << "Uruchamiam gre..." << std::endl;
                                break;
                            case 1: // Ostatnie wyniki
                                currentState = GameState::Scores;
                                std::cout << "Najlepsze wyniki..." << std::endl;
                                break;
                            case 2: // Wyjście
                                currentState = GameState::Exiting;
                                window.close();
                                break;
                        }
                    }
                }
            }
        }

        if (currentState == GameState::Playing)
        {
            sf::Time deltaTime = deltaClock.restart();
            game.update(deltaTime);
            
            if (game.isGameOver())
            {
                currentState = GameState::Menu;
                game.resetGame();
            }
        }

        window.clear();

        switch (currentState)
        {
            case GameState::Menu:
                menu.draw(window);
                break;
            case GameState::Playing:
                game.render(window);
                break;
            case GameState::Scores:
                menu.draw(window); 
                break;
            case GameState::Exiting:
                break;
        }

        window.display();
    }

    return 0;
}