#include "RestartManager.h"

RestartManager::RestartManager(sf::Vector2f pos, std::filesystem::path fontPath, uint8_t color[3], World &world):
    _world(world)
{
    _gameOvertext = std::make_shared<Text>(fontPath, "Game Over", 80, color);
    float textX = pos.x - _gameOvertext->GetCharacterSize()*2;
    float textY = pos.y/2;
    _gameOvertext->SetPosition({textX, textY});

    _scoretext = std::make_shared<Text>(fontPath, "0", 40, color);
    textX = pos.x;
    textY = pos.y/2 + _gameOvertext->GetCharacterSize()*2;
    _scoretext->SetPosition({textX, textY});

    _gameOvertext->Toggle();
    _scoretext->Toggle();
}

void RestartManager::EndGame(int score)
{
    _scoretext->SetText(std::to_string(score));
    _gameOvertext->Toggle();
    _scoretext->Toggle();

    _world.RestartWorld();
}

std::shared_ptr<Text> RestartManager::GetGameOverText()
{
    return _gameOvertext;
}
std::shared_ptr<Text> RestartManager::GetScoreText()
{
    return _scoretext;
}

void RestartManager::Restart()
{
    _gameOvertext->Toggle();
    _scoretext->Toggle();
}