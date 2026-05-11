#include "GameEngine.h"

#include <imgui-SFML.h>
#include <imgui.h>

void GameEngine::Render(float delta)
{
    // ToDo: Логика рендера окна и ui
        ImGui::SFML::Update(_window, delta);

        _window.clear(sf::Color::Black);
        ImGui::SFML::Render(_window);
        _window.display();
}

GameEngine::GameEngine(const GameEngineConfiguration& config) : _config(config)
{
     _window.create(sf::VideoMode({static_cast<unsigned int>(_config.Width), static_cast<unsigned int>(_config.Height)}), "Asteroid");
     auto desktop = sf::VideoMode::getDesktopMode();
    _window.setPosition({ (int) (desktop.size.x / 2 - _config.Width / 2), (int) (desktop.size.y / 2 - _config.Height / 2) });

    _window.setFramerateLimit(60);

    ImGui::SFML::Init(_window);

    Initialize();
}

void GameEngine::Initialize()
{
   Run();
}

void GameEngine::Run()
{
     while (_window.isOpen())
    {
        const float delta = _deltaClock.restart().asSeconds();

        auto scene = CurrentScene();

        _inputManager->ProcessInput(_currentScene);

        scene->Update(delta);

        Render(delta);
    }

    ImGui::SFML::Shutdown();
}

void GameEngine::Quit()
{
    // ToDo: Закрытие и остановка движка
}