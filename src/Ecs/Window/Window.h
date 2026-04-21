#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "imgui.h"
#include "imgui-SFML.h"

#include "../Systems/SystemsManager.h"
#include "../World/World.h"
#include "../Window/Window.h"
#include "../../Sample/Systems/EntityFactory.h"
#include "../ReadConfig/ReadConfig.h"
#include "../../UI/Text.h"
#include "../Managers/ScoreManager.h"
#include "../Managers/RestartManager.h"
#include "../../Sample/Systems/AsteroidSpawnSystem.h"
#include "../../Sample/Components/PositionComponent.h"

class Window {
    sf::RenderWindow _window;
    World _world;
    std::shared_ptr<SystemsManager> _systems;
    std::shared_ptr<EntityFactory> _entityFactory;
    sf::Texture _texture;
    int _spawnCd;
    std::filesystem::path _fontPath;

    sf::Clock _deltaClock;

    bool _isRun;
    bool _gameActive = true;

    std::shared_ptr<AsteroidSpawnSystem> _asteroidSpawn;
    std::shared_ptr<ScoreManager> _scoreManager;
    std::shared_ptr<RestartManager> _restartManager;

    std::vector<std::shared_ptr<Text>> _uiText;

    ComponentStorage<PositionComponent>& _positionComponents;

    void Initialize();
    void UpdateInputLogic();
    void UpdateGUI();

public:
    Window(const WindowConfig windCfg, const ShooterConfig shootCfg, const ImageConfig imgCfg, const AsteroidConfig astCfg, const SpawnConfig spCfg, const TextConfig txtCfg);
    
    void Run();

    void EndGame();

    sf::RenderWindow& GetWindow()
    {
        return _window;
    }
};

#endif //WINDOW_H