#include "GameScene.h"

#include "../GameEngine.h"
#include <iostream>

#include "../../Sample/Systems/RenderSystem.h"
#include "../../Sample/Systems/FollowXCameraSystem.h"
#include "../../Sample/Systems/MovementSystem.h"

void GameScene::Init()
{
    RegisterAction(sf::Keyboard::Key::A, "move_left");
    RegisterAction(sf::Keyboard::Key::D, "move_right");
    RegisterAction(sf::Keyboard::Key::W, "jump");

    _actions["move_left"] = actionMap["move_left"];
    _actions["move_right"] = actionMap["move_right"];
    _actions["jump"] = actionMap["jump"];

    entityFactory = std::make_shared<EntityFactory>(world, gameEngine.Assets());

    sf::Vector2u size = gameEngine.Window().getSize();
    sf::Vector2f sizeF(static_cast<float>(size.x), static_cast<float>(size.y));
    entityFactory->CreateEntity(EntityType::FollowXCamera, sizeF);
    _render = std::make_shared<RenderSystem>(world, gameEngine.Window());
    systemsManager.AddSystem(std::make_shared<FollowXCameraSystem>(world));
    systemsManager.AddSystem(std::make_shared<MovementSystem>(world, _actions));
    
    _render->OnInit();
    systemsManager.Initialize();

    LoadLevel();
}

void GameScene::Update(float delta)
{
    systemsManager.Update();
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

    _render->OnUpdate();

    // TODO: draw world entities (sprites, tiles etc.)
    _grid.Draw(window);

    window.setView(window.getDefaultView());
}

void GameScene::LoadLevel()
{
    const auto& levelObjects = gameEngine.Level();

    for (const auto& obj : levelObjects)
    {
        sf::Vector2f worldPos = _grid.GridToWorld(
            sf::Vector2i(obj.x, obj.y)
        );
        if (obj.name == "Player")
        {
            entityFactory->CreateEntity(EntityType::Player, worldPos);
        }
        else if (obj.name == "Tile")
        {
            entityFactory->CreateEntity(EntityType::Tile, worldPos);
        }
        else if (obj.name == "Tile1")
        {
            entityFactory->CreateEntity(EntityType::Tile1, worldPos);
        }
        else if (obj.name == "Brick_Tile")
        {
            entityFactory->CreateEntity(EntityType::BrickTile, worldPos);
        }
        else if (obj.name == "BigHill")
        {
            entityFactory->CreateEntity(EntityType::BigHill, worldPos);
        }
        else if (obj.name == "PipeR")
        {
            entityFactory->CreateEntity(EntityType::PipeRight, worldPos);
        }
        else if (obj.name == "PipeL")
        {
            entityFactory->CreateEntity(EntityType::PipeLeft, worldPos);
        }
    }

    std::cout<< "[GameScene] Loaded "<< levelObjects.size()<< " level objects\n";
}