#include "Wynik.h"

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
    t.setPosition(sf::Vector2f(5.f, 5.f));
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