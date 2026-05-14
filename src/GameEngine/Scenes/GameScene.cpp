#include "GameScene.h"

#include "../GameEngine.h"
#include <iostream>

void GameScene::Init()
{

    RegisterAction(sf::Mouse::Button::Left, "mouse_left");
    RegisterAction(MouseMove::Move, "mouse_move");

    _mouseClickAction = actionMap["mouse_left"];
    _mouseMoveAction = actionMap["mouse_move"];

    LoadLevel("../../Levels/level1.txt");
}

void GameScene::Update(float delta)
{
}

void GameScene::Render()
{
    auto& window = gameEngine.Window();

    window.clear(sf::Color(0x64, 0x64, 0xff));

    for (auto e : _cameras)
    {
        auto& cam = _cameraComponents.Get(e);
        window.setView(cam.View);
        break;
    }

    // TODO: draw world entities (sprites, tiles etc.)
    _grid.Draw(window);

    window.setView(window.getDefaultView());
}

void GameScene::LoadLevel(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Cannot open level file\n";
        return;
    }

    std::string line;

    auto& posStorage = world.GetStorage<PositionComponent>();

    while (std::getline(file, line))
    {
        // пропуск пустых строк и комментариев
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream iss(line);

        std::string name;
        int gx, gy;

        iss >> name >> gx >> gy;

        sf::Vector2f worldPos = _grid.GridToWorld({gx, gy});

        int entity = world.CreateEntity();

        posStorage.Add(entity, PositionComponent(worldPos.x, worldPos.y));

        // дальше можно развешивать компоненты по типу
        if (name == "Player")
        {
            // tag / player component
        }
        else if (name == "Tile")
        {
            // tile component / sprite
        }
        else if (name == "Brick")
        {
            // brick component
        }
        else if (name == "BigHill")
        {
            // decoration
        }
        else if (name == "Pipe1" || name == "Pipe2")
        {
            // pipe logic
        }
    }
}