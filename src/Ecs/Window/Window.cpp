#include "Window.h"

#include <random>

#include "../../Sample/Systems/InitSystem.h"
#include "../../Sample/Systems/InputSystem.h"
#include "../../Sample/Systems/MovementSystem.h"
#include "../../Sample/Systems/CollisionSystem.h"
#include "../../Sample/Systems/CollisionResolveSystem.h"
#include "../../Sample/Systems/RenderSystem.h"
#include "../../Sample/Systems/ShootingSystem.h"
#include "../../Sample/Systems/BoundariesSystem.h"


Window::Window(const WindowConfig windCfg, const ShooterConfig shootCfg, const ImageConfig imgCfg, const AsteroidConfig astCfg, const SpawnConfig spCfg, const TextConfig txtCfg): 
_world(), _spawnCd(spCfg.cd), _fontPath(txtCfg.path), _positionComponents(_world.GetStorage<PositionComponent>())
{
    _window.create(sf::VideoMode({static_cast<unsigned int>(windCfg.width), static_cast<unsigned int>(windCfg.height)}), "Asteroid");
     auto desktop = sf::VideoMode::getDesktopMode();
    _window.setPosition({ (int) (desktop.size.x / 2 - windCfg.width / 2), (int) (desktop.size.y / 2 - windCfg.height / 2) });

    _window.setFramerateLimit(60);

    _texture.loadFromFile(imgCfg.path);

    _systems = std::make_shared<SystemsManager>(_world);
    _entityFactory = std::make_shared<EntityFactory>(_world, _texture, astCfg, shootCfg);

    ImGui::SFML::Init(_window);

    Initialize();
}

void Window::Initialize()
{
    uint8_t color[3] = {255, 255, 255};
    sf::Vector2f textPos(_window.getSize().x/2, _window.getSize().y/2);

    _scoreManager = std::make_shared<ScoreManager>(textPos, _fontPath, color);
    _restartManager = std::make_shared<RestartManager>(textPos, _fontPath, color, _world);

    _systems->AddInitializer(std::make_shared<InitSystem>(_world, _texture, *_entityFactory));
    _systems->AddSystem(std::make_shared<InputSystem>(_world, _window));
    _systems->AddSystem(std::make_shared<MovementSystem>(_world));
    _systems->AddSystem(std::make_shared<CollisionSystem>(_world));
    _systems->AddSystem(std::make_shared<RenderSystem>(_world, _window, _texture));
    _systems->AddSystem(std::make_shared<ShootingSystem>(_world, *_entityFactory));
    _systems->AddSystem(std::make_shared<CollisionResolveSystem>(_world, *_scoreManager, *this));
    _asteroidSpawn = std::make_shared<AsteroidSpawnSystem>(_world, *_entityFactory, _spawnCd, _window.getSize().x);
    _systems->AddSystem(_asteroidSpawn);
    _systems->AddSystem(std::make_shared<BoundariesSystem>(_world, _window));

    _uiText.push_back(_scoreManager->GetText());
    _uiText.push_back(_restartManager->GetGameOverText());
    _uiText.push_back(_restartManager->GetScoreText());
}

void Window::Run()
{
    while (_window.isOpen()) {

        sf::Time delta = _deltaClock.restart();
        ImGui::SFML::Update(_window, delta);

        _window.clear(sf::Color::Black);
        if(_gameActive)
            _systems->Update();
        else
        {
             UpdateInputLogic();
        }

        for (auto text : _uiText)
        {
            text->Draw(_window);
        }
        UpdateGUI();
        ImGui::SFML::Render(_window);
        _window.display();
        _world.Flush();
    }

    _window.close();
    ImGui::SFML::Shutdown();
}

void Window::EndGame()
{
    _scoreManager->ToggleScore();
    _gameActive = false;
    _restartManager->EndGame(_scoreManager->GetScore());
}

void Window::UpdateGUI()
{
    ImGui::Begin("Config settings");
    ImGui::Text("Asteroid parameters");

    ImGui::InputFloat("Min speed", &_entityFactory->GetMinSpeed(), 0.1f, 1.0f, "%.3f");
    ImGui::InputFloat("Max speed", &_entityFactory->GetMaxSpeed(), 0.1f, 1.0f, "%.3f");
    ImGui::InputFloat("Asteroid spawn cooldown", &_asteroidSpawn->GetCd(), 10, 1.0f, "%.3f");
    if (ImGui::Button("Spawn Asteroid"))
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, _window.getSize().x);
        int value = dist(gen);
        _entityFactory->CreateEntity(EntityType::Asteroid, sf::Vector2f(value, -100));
    }

    for (auto entity : _positionComponents.Entities())
    {
        const auto& pos = _positionComponents.Get(entity);
        ImGui::Text("Entity %d | x: %.2f | y: %.2f", entity, pos.X, pos.Y);
    }

    ImGui::End();
}

void Window::UpdateInputLogic()
{
    while (const std::optional event = _window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(_window, *event);
        if (event->is<sf::Event::Closed>())
        {
            _window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if(!_gameActive)
            {
                _restartManager->Restart();
                _systems->RestartSystems();
                _scoreManager->ToggleScore();
                _scoreManager->RestartScore();
                _gameActive = true;
            }
        }
    }
}