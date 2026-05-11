#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "../Scene.h"

#include "../../UI/Button.h"
#include "../../UI/Text.h"

class MenuScene : public Scene
{
    std::shared_ptr<Button> _playButton;
    std::shared_ptr<Button> _exitButton;

    std::shared_ptr<Text> _title;
    std::shared_ptr<InputAction> _mouseClickAction;
    std::shared_ptr<InputAction> _mouseMoveAction;



public:
    MenuScene(GameEngine& engine);

    void Init() override;
    void Update(float delta) override;
    void Render() override;
};

#endif // MENUSCENE_H
