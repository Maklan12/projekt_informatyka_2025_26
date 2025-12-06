#include "Pilka.h"
#include <cmath>
#include <iostream>

Pilka::Pilka(float x_in, float y_in, float vx_in, float vy_in, float radius_in)
{
    x = x_in;
    y = y_in;
    vx = vx_in;
    vy = vy_in;
    radius = radius_in;

    shape.setRadius(radius);
    shape.setPosition({x,y});
    shape.setOrigin({radius,radius});
    shape.setFillColor(sf::Color::Magenta);
}

void Pilka::move()
{
    x += vx;
    y += vy;
    shape.setPosition({x,y});
}

void Pilka::bounceX()
{
    vx = -vx;
}

void Pilka::bounceY()
{   
    vy = -vy;
}

void Pilka::collideWalls(float width, float height)
{
    if (x-radius <= 0 || x+radius >= width)
        {
            bounceX();        
        }

    if (y-radius <= 0)
        {
            bounceY();        
        }
}

bool Pilka::collidePaddle(const Paletka& p)
{
    
    if (x>=p.getX()-p.getSzerokosc()/2 && x<=p.getX()+p.getSzerokosc()/2 && 
    y+ radius>= p.getY()-p.getWysokosc()/2 && y-radius < p.getY()-p.getWysokosc()/2)
        {
            vy=-std::abs(vy);   
            y = p.getY()-p.getWysokosc()/2 - radius;
            shape.setPosition({x,y});
            return true;
        }
    return false;
}

void Pilka::collideStone(Stone& s)
{
    if (s.isDestroyed()== true)
    {
        return;
    }
    
    if (x-radius <= s.getPosition().x + s.getSize().x && x+radius >= s.getPosition().x && y-radius <= s.getPosition().y+s.getSize().y
     && y + radius >= s.getPosition().y )
    {
        s.trafienie();

        // Priorytet: jeśli kolizja z boku, odbij w X, w przeciwnym razie w Y
        if (x + radius >= s.getPosition().x && x < s.getPosition().x || 
        x - radius <= s.getPosition().x + s.getSize().x && x > s.getPosition().x + s.getSize().x) {
            bounceX();
        } 
        else if (y + radius >= s.getPosition().y && y < s.getPosition().y || 
        y - radius <= s.getPosition().y + s.getSize().y && y > s.getPosition().y + s.getSize().y) {
            bounceY();
        }
    }
}

void Pilka::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}

void Pilka::setPilka(float setX, float setY, float setVX, float setVY)
{
    x = setX;
    y = setY;
    vx = setVX;
    vy = setVY;
    shape.setPosition({x, y});
}