#include "GameState.h"


void GameState::capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones, const wynik& currentscore) {
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

bool GameState::saveToFile(const std::string& filename) {
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

bool GameState::loadFromFile(const std::string& filename) {
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

void GameState::apply(Paletka& p, Pilka& b, std::vector<Stone>& stones, sf::Vector2f blockSize, wynik& score) {
    p.setPosition(paddlePosition.x, paddlePosition.y);
    
    b.setPilka(ballPosition.x, ballPosition.y, ballVelocity.x, ballVelocity.y);
    
    score.SetScore(saved_score);
    stones.clear();
    for (const auto& data : blocks) 
    {
        stones.emplace_back(sf::Vector2f(data.x, data.y), blockSize, data.hp);
    }
}