#ifndef WYNIK_H
#define WYNIK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> 
#include <string>


class wynik
{
private:
    int score;
    sf::Font font;
    sf::Text t;
public:
    wynik();
    void wynik_update();
    void draw(sf::RenderTarget& target);
    int GetScore()const {return score;};
    void SetScore (int wynik_in);
};



#endif