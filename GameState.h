#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"
#include "Wynik.h"


struct BlockData {
    float x, y;
    int hp;
};

class GameState {
private:
    int saved_score;
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    void capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones, const wynik& currentscore);
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    void apply(Paletka& p, Pilka& b, std::vector<Stone>& stones, sf::Vector2f blockSize, wynik& score);
};

#endif