#include "Stone.h"

const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent,
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Blue,
};

Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
{
    Stone::RectangleShape::setPosition(startPos);
    Stone::RectangleShape::setSize(rozmiar);
    m_punktyZycia = L;
    m_jestZniszczony = false;
    Stone::RectangleShape::setOutlineThickness(2.f);
    aktualizujKolor();
}

void Stone::trafienie()
{    
    if (m_jestZniszczony == true)
    {
        return;
    }
    m_punktyZycia= m_punktyZycia - 1;
    aktualizujKolor();
    if (m_punktyZycia <= 0)
    {
        m_jestZniszczony = true;
    }
}

void Stone::aktualizujKolor()
{
    Stone::RectangleShape::setFillColor(m_colorLUT[m_punktyZycia]);
}