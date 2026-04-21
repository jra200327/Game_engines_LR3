#include "RenderSystem.h"

void RenderSystem::OnInit()
{

}

void RenderSystem::OnUpdate()
{
    for (auto ent : _drawables)
    {
         auto& position = _positionComponents.Get(ent);
         auto& sprite = _spriteComponents.Get(ent);

         sprite.sprite->setPosition(sf::Vector2f(position.X, position.Y));
         _window.draw(*sprite.sprite);
    }
}