#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    if (!font.openFromFile("arial.ttf"))
    {
        std::cout << "Nie mozna zaladowac czcionki!" << std::endl;
        return;
    }
    
    sf::Text t(font);
    
    t.setFillColor(sf::Color::Cyan);
    t.setStyle(sf::Text::Bold);
    t.setString("Nowa gra");
    t.setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 1));
    menu.push_back(t);

    t.setFillColor(sf::Color::White);
    t.setStyle(sf::Text::Regular);
    t.setString("Wczytaj gre");
    t.setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
    menu.push_back(t);
    
    t.setFillColor(sf::Color::White);
    t.setString("Wyjscie");
    t.setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));
    menu.push_back(t);
}

void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::przesunG()
{
    if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem--;
        if (selectedItem < 0)
            selectedItem = MAX_LICZBA_POZIOMOW - 1;
        menu[selectedItem].setFillColor(sf::Color::Cyan);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }
}

void Menu::przesunD()
{
    if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem++;
        if (selectedItem >= MAX_LICZBA_POZIOMOW)
            selectedItem = 0;
        menu[selectedItem].setFillColor(sf::Color::Cyan);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }
}