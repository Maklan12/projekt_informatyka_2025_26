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
#include "wynik.h"


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
    // Zadanie 1: Capture [cite: 162]
    void capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones, const wynik& currentscore) {
        paddlePosition = {p.getX(), p.getY()};
        ballPosition = {b.getX(), b.getY()};
        ballVelocity = {b.getVX(), b.getVY()};
        saved_score = currentscore.GetScore();

        blocks.clear();
        for (const auto& stone : stones) 
        {
            if (!stone.isDestroyed()) 
            {
                blocks.push_back({stone.getPosition().x, stone.getPosition().y, stone.getHP()});
            }
        }
    }

    bool saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        file << "SCORE " << saved_score << "\n";
        file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
        file << "BALL " << ballPosition.x << " " << ballPosition.y << " " << ballVelocity.x << " " << ballVelocity.y << "\n";
        file << "BLOCKS_COUNT " << blocks.size() << "\n";

        for (const auto& block : blocks) {
            file << block.x << " " << block.y << " " << block.hp << "\n";
        }

        file.close();
        return true;
    }

    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        std::string label;
        
        if (!(file >> label >> saved_score)) return false;  

        if (!(file >> label >> paddlePosition.x >> paddlePosition.y)) return false;

        
        if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y)) return false;


        int blocksCount;
        if (!(file >> label >> blocksCount)) return false;
        
        blocks.clear();
        for (int i = 0; i < blocksCount; ++i) {
            float x, y;
            int hp;
            file >> x >> y >> hp;
            blocks.push_back({x, y, hp});
        }
        
        file.close();
        return true;
    }


    void apply(Paletka& p, Pilka& b, std::vector<Stone>& stones, sf::Vector2f blockSize, wynik& score) {
        p.setPosition(paddlePosition.x, paddlePosition.y);
        
        b.setPilka(ballPosition.x, ballPosition.y, ballVelocity.x, ballVelocity.y);
        
        score.SetScore(saved_score);

        stones.clear();
        for (const auto& data : blocks) 
        {
            stones.emplace_back(sf::Vector2f(data.x, data.y), blockSize, data.hp);
        }
    }
};

#endif