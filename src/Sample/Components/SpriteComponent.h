#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

struct SpriteComponent
{
    sf::Vector2i size;
    sf::Vector2i atlasPos;
    std::shared_ptr<sf::Sprite> sprite;
    float rotation;
    float scale;
    SpriteComponent(sf::Vector2i size_, sf::Vector2i atlasPos_, const sf::Texture& tex, float rotat, float scal)
        : size(size_),
          atlasPos(atlasPos_),
          rotation(rotat),
          scale(scal)
    {
        sprite = std::make_shared<sf::Sprite>(tex);
        sprite->setTextureRect(sf::IntRect(atlasPos, size));
        sprite->rotate(sf::degrees(rotation));
        sprite->setScale(sf::Vector2f(scale,scale));
    }

    SpriteComponent() : size({0, 0}), atlasPos({0, 0}), sprite(nullptr) {}
};

#endif //SPRITECOMPONENT_H
