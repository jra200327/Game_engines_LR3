#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "../../UI/Text.h"


class ScoreManager {
    
    std::shared_ptr<Text> _text;
    int _score = 0;
   
public:
    ScoreManager(sf::Vector2f pos, std::filesystem::path fontPath, uint8_t color[3]);

    void UpdateScore(int i);
    int GetScore();
    std::shared_ptr<Text> GetText();

    void ToggleScore();
    void RestartScore();
};

#endif //SCOREMANAGER_H