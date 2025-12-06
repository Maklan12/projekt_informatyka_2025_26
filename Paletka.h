#ifndef PALETKA_H
#define PALETKA_H

#include <SFML/Graphics.hpp>

class Paletka
{
private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float predkosc;
    sf::RectangleShape shape;

public:
    Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float predkosc_in);
    void moveLeft();
    void moveRight();
    void clmapToBounds(float width);
    void draw(sf::RenderTarget& target);

    float getX() const {return x;}
    float getY() const {return y;}
    float getSzerokosc() const {return szerokosc;}
    float getWysokosc() const {return wysokosc;}
    
    void setPosition(float setX, float setY);
};

#endif