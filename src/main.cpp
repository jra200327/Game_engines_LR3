#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "GameEngine/GameEngine.h"
#include "GameEngine/GameEngineConfiguration.h"

int main() {
    GameEngineConfiguration config;
    GameEngine engine(config);
    engine.Run();

    return 0;
}