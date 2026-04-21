#include "ScoreManager.h"

ScoreManager::ScoreManager(sf::Vector2f pos, std::filesystem::path fontPath, uint8_t color[3])
{
    _text = std::make_shared<Text>(fontPath, "0", 40, color);
    float textX = pos.x;
    float textY = _text->GetCharacterSize();
    _text->SetPosition({textX, textY});
}

std::shared_ptr<Text> ScoreManager::GetText()
{
    return _text;
}

void ScoreManager::UpdateScore(int i)
{
    _score+=i;
    _text->SetText(std::to_string(_score));
}

int ScoreManager::GetScore()
{
    return _score;
}

void ScoreManager::ToggleScore()
{
    _text->Toggle();
}

void ScoreManager::RestartScore()
{
    _score = 0;
    _text->SetText(std::to_string(_score));
}
