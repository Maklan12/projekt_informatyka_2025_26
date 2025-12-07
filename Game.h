#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Pilka.cpp"
#include "Paletka.cpp"
#include "Stone.cpp"
#include "GameState.h"

#include "wynik.h"

#include <vector>

class Game
{
private:
    Paletka m_paletka;
    Pilka m_pilka;
    wynik m_score;
    std::vector<Stone> m_bloki;
    sf::Clock m_deltaClock;
    
    // Stałe
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    float ROZMIAR_BLOKU_X;

public:
    Game();
    void update(sf::Time dt);
    void render(sf::RenderTarget& target);
    
    bool isGameOver() const { return m_gameOver; }
    void resetGame();

    void saveGame(const std::string& filename);
    bool loadGame(const std::string& filename);

private:
    bool m_gameOver = false;
};

#endif