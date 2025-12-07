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

wynik::wynik() : t(font)
{    if (!font.openFromFile("arial.ttf"))
    {
        std::cout << "Nie mozna zaladowac czcionki!" << std::endl;
        return;
    }
    score = 0;
    
    t.setFont(font);
    t.setFillColor(sf::Color::White);
    t.setStyle(sf::Text::Bold);
    t.setPosition(sf::Vector2f(240.f, 400.f));
    t.setString("Wynik: 0");

}
void wynik::wynik_update()
{
    score ++;
    std::string str_score = std::to_string(score);
    t.setString("Wynik: " + str_score);


}

void wynik::draw(sf::RenderTarget& target)
{
    target.draw(t);
}

void wynik::SetScore(int wynik_in)
{
    score = wynik_in;
    t.setString("Wynik: " + std::to_string(score));
}

#endif