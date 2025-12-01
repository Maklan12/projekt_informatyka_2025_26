#ifndef PILKA_H
#define PILKA_H

#include <SFML/Graphics.hpp>
#include "Paletka.h"
#include "Stone.h"

class Pilka
{
private:
    float x;
    float y;
    float vx;
    float vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float x_in, float y_in, float vx_in, float vy_in, float radius_in);
    void move();
    void bounceX();
    void bounceY();
    void collideWalls(float width, float height);
    bool collidePaddle(const Paletka& p);
    void collideStone(Stone& s);
    void draw(sf::RenderTarget& target);

    float getX() const {return x;}
    float getY() const {return y;}
    float getVX() const {return vx;}
    float getVY() const {return vy;}
    float getRadius() const {return radius;}
};

#endif