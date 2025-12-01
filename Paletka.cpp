#include "Paletka.h"

Paletka::Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float predkosc_in)
{
    x = x_in;
    y = y_in;
    szerokosc = szerokosc_in;
    wysokosc = wysokosc_in;
    predkosc = predkosc_in;
    
    shape.setSize({szerokosc,wysokosc});
    shape.setOrigin({szerokosc/2,wysokosc/2});
    shape.setPosition({x,y});
    shape.setFillColor(sf::Color::White);
}

void Paletka::moveLeft()
{
    x = x - predkosc;
    shape.setPosition({x,y});
}

void Paletka::moveRight()
{
    x = x + predkosc;
    shape.setPosition({x,y});
}

void Paletka::clmapToBounds(float width)
{
    if (x-szerokosc/2 < 0)
    {
        x= szerokosc/2;
        shape.setPosition({x,y});
    }
    
    if (x+szerokosc/2 > width)
    {
        x= width-szerokosc/2;
        shape.setPosition({x,y});
    }
}

void Paletka::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}