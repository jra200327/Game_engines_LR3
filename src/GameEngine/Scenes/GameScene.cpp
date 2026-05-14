#include "GameScene.h"

#include "../GameEngine.h"
#include <iostream>

void GameScene::Init()
{

    RegisterAction(sf::Mouse::Button::Left, "mouse_left");
    RegisterAction(MouseMove::Move, "mouse_move");

    _mouseClickAction = actionMap["mouse_left"];
    _mouseMoveAction = actionMap["mouse_move"];

    LoadLevel();
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

void GameScene::LoadLevel()
{
    // Get level objects from the configuration
    const auto& levelObjects = gameEngine.Level();
    
    auto& posStorage = world.GetStorage<PositionComponent>();

    // Iterate through all level objects from config
    for (const auto& obj : levelObjects)
    {
        // Convert grid coordinates to world position
        sf::Vector2f worldPos = _grid.GridToWorld({obj.x, obj.y});

        // Create entity
        int entity = world.CreateEntity();

        // Add position component
        posStorage.Add(entity, PositionComponent(worldPos.x, worldPos.y));

        // Add components based on object type
        if (obj.name == "Player")
        {
            // Add player tag and components
            // Example:
            // world.GetStorage<PlayerTag>().Add(entity, PlayerTag{});
            // world.GetStorage<VelocityComponent>().Add(entity, VelocityComponent(0, 0));
            // world.GetStorage<BoundingBoxComponent>().Add(entity, BoundingBoxComponent(30, 30));
        }
        else if (obj.name == "Tile")
        {
            // Add tile components
            // Example:
            // world.GetStorage<TileComponent>().Add(entity, TileComponent{});
            // Add sprite component with tile texture
        }
        else if (obj.name == "Brick")
        {
            // Add brick components
            // Example:
            // world.GetStorage<BrickComponent>().Add(entity, BrickComponent{});
            // world.GetStorage<DestructibleComponent>().Add(entity, DestructibleComponent{});
        }
        else if (obj.name == "BigHill")
        {
            // Add decoration component for hills
            // world.GetStorage<DecorationComponent>().Add(entity, DecorationComponent("BigHill"));
        }
        else if (obj.name == "Pipe1" || obj.name == "Pipe2")
        {
            // Add pipe components
            // world.GetStorage<PipeComponent>().Add(entity, PipeComponent(obj.name == "Pipe1" ? 1 : 2));
        }
    }
    
    std::cout << "[GameScene] Loaded " << levelObjects.size() << " level objects\n";
}