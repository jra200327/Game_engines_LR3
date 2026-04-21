#ifndef RESTARTMANAGER_H
#define RESTARTMANAGER_H

#include "../../UI/Text.h"
#include "../World/World.h"


class RestartManager {
    
    std::shared_ptr<Text> _gameOvertext;
    std::shared_ptr<Text> _scoretext;

    World& _world;
   
public:
    RestartManager(sf::Vector2f pos, std::filesystem::path fontPath, uint8_t color[3], World &world);

    void EndGame(int score);
    void Restart();
    std::shared_ptr<Text> GetGameOverText();
    std::shared_ptr<Text> GetScoreText();
};

#endif //RESTARTMANAGER_H