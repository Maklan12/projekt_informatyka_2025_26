#include "Game.h"
#include <iostream>

Game::Game() 
    : m_paletka(320.f, 440.f, 100.f, 20.f, 8.f)
    , m_pilka(320.f, 300.f, 4.f, 3.f, 8.f)
    , ROZMIAR_BLOKU_X((WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN)
{
    float posX = 2.f;
    float posY = 50.f;
    int L;

    for (int i = 0; i < ILOSC_WIERSZY; i++)
    {
        for (int j = 0; j < ILOSC_KOLUMN; j++)
        {
            L = (i < 1) ? 3 : (i < 3) ? 2 : 1;
            m_bloki.emplace_back(sf::Vector2f({posX, posY}), sf::Vector2f({ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y}), L);
            posX = 2.f + posX + ROZMIAR_BLOKU_X;
        }
        
        posY = 2.f + posY + ROZMIAR_BLOKU_Y;
        posX = 2.f;
    }
}

void Game::update(sf::Time dt)
{
    if (m_gameOver) return;

    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);

    for (int k = 0; k < m_bloki.size(); k++)
    {
        m_pilka.collideStone(m_bloki[k]);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) { 
        m_paletka.moveLeft(); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) { 
        m_paletka.moveRight(); 
    }
    m_paletka.clmapToBounds(WIDTH);

    if (m_pilka.collidePaddle(m_paletka))
    {
        std::cout << "HIT PADDLE\n"; 
    }
    
    if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT)
    {
        std::cout << "MISS! KONIEC GRY\n";
        m_gameOver = true;
    }
    
    if (m_deltaClock.getElapsedTime().asSeconds() >= 2)
    {
        std::cout << "x=" << m_pilka.getX() << "\t y=" << m_pilka.getY() 
                  << "\t vx=" << m_pilka.getVX() << "\t vy=" << m_pilka.getVY() << std::endl;
        m_deltaClock.restart(); 
    }
}

void Game::render(sf::RenderTarget& target)
{
    for (int l = 0; l < m_bloki.size(); l++)
    {
        target.draw(m_bloki[l]);
    }

    m_paletka.draw(target);
    m_pilka.draw(target);
}

void Game::resetGame()
{
    m_gameOver = false;
    m_pilka = Pilka(320.f, 300.f, 4.f, 3.f, 8.f);
    m_paletka = Paletka(320.f, 440.f, 100.f, 20.f, 8.f);
    

    
    m_bloki.clear(); 
    
    float posX = 2.f;
    float posY = 50.f;
    int L;

    for (int i = 0; i < ILOSC_WIERSZY; i++)
    {
        for (int j = 0; j < ILOSC_KOLUMN; j++)
        {
            L = (i < 1) ? 3 : (i < 3) ? 2 : 1;
            m_bloki.emplace_back(sf::Vector2f({posX, posY}), sf::Vector2f({ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y}), L);
            posX = 2.f + posX + ROZMIAR_BLOKU_X;
        }
        
        posY = 2.f + posY + ROZMIAR_BLOKU_Y;
        posX = 2.f;
    }
}

void Game::saveGame(const std::string& filename)
{
    GameState gs;
    gs.capture(m_paletka, m_pilka, m_bloki);
    if(gs.saveToFile(filename)) {
        std::cout << "Gra zapisana!" << std::endl;
    } else {
        std::cout << "Blad zapisu gry!" << std::endl;
    }
}

bool Game::loadGame(const std::string& filename)
{
    GameState gs;
    if (gs.loadFromFile(filename)) {
        gs.apply(m_paletka, m_pilka, m_bloki, sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y));
        m_gameOver = false;
        return true;
    }
    return false;
}