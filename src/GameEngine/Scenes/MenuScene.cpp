#include "MenuScene.h"

#include "../GameEngine.h"

MenuScene::MenuScene(GameEngine& engine)
    : Scene(engine)
{
}

void MenuScene::Init()
{
    RegisterAction(sf::Mouse::Button::Left, "mouse_left");
    RegisterAction(MouseMove::Move, "mouse_move");
    _mouseClickAction = actionMap["mouse_left"];
    _mouseMoveAction = actionMap["mouse_move"];

    const uint8_t white[3] = {255, 255, 255};
    _title = std::make_shared<Text>("../../Fonts/futura.ttf", "Level Maker", 48, white);

    _title->SetPosition({420.f, 120.f});

    const uint8_t playTextColor[3] = {255, 255, 255};
    const uint8_t playBgColor[3] = {50, 150, 50};
    const sf::Vector2f playSize = {250.f, 80.f};

    _playButton = std::make_shared<Button>("../../Fonts/futura.ttf", "Play", 32, playSize, playTextColor, playBgColor);

    _playButton->SetPosition({515.f, 300.f});

    _playButton->SetCallback([this]()
    {
        std::cout << "Play button clicked!\n";

        // TODO:
        // gameEngine.LoadScene<GameScene>();
    }); 


    const uint8_t exitTextColor[3] = {255, 255, 255};
    const uint8_t exitBgColor[3] = {180, 50, 50};

    _exitButton = std::make_shared<Button>("../../Fonts/futura.ttf", "Exit", 32, playSize, exitTextColor, exitBgColor);

    _exitButton->SetPosition({515.f, 420.f});

    _exitButton->SetCallback([this]()
    {
        std::cout << "Exit button clicked!\n";

        gameEngine.Quit();
    });
}

void MenuScene::Update(float delta)
{
    _playButton->Update(_mouseClickAction);
    _exitButton->Update(_mouseClickAction);
}

void MenuScene::Render()
{
    auto& window = gameEngine.Window();

    _title->Draw(window);

    _playButton->Draw(window);
    _exitButton->Draw(window);
}