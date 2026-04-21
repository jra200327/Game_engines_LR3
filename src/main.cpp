#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Ecs/Systems/SystemsManager.h"
#include "Ecs/World/World.h"
#include "Ecs/Window/Window.h"

#include "Sample/Systems/InitSystem.h"
#include "Sample/Systems/InputSystem.h"
#include "Sample/Systems/MovementSystem.h"
#include "Sample/Systems/CollisionSystem.h"
#include "Sample/Systems/RenderSystem.h"
#include "Ecs/ReadConfig/ReadConfig.h"

int main() {
    setlocale(LC_ALL, "");

    WindowConfig windowCfg;
    ShooterConfig shootCfg;
    ImageConfig imgCfg;
    AsteroidConfig astCfg;
    SpawnConfig spCfg;
    TextConfig txtCfg;

    ReadConfig(windowCfg, shootCfg, imgCfg, astCfg, spCfg, txtCfg);

    const int wWidth = 1280;
    const int wHeight = 720;
    Window window(windowCfg, shootCfg, imgCfg, astCfg, spCfg, txtCfg);

    window.Run();

    return 0;
}