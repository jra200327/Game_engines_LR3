#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Drawable.h"

class Button : public Drawable
{
    sf::RectangleShape _background;

    sf::Font _font;
    sf::Text _text;

    sf::String _str;

    bool _shouldDraw = true;
    bool _hovered = false;

    std::function<void()> _onClick;

    void Transfer(const Button& other);

public:
    Button() = default;

    Button(const Button& other);
    Button(Button&& other);

    Button(
        const std::filesystem::path& fontPath,
        const sf::String& text,
        int fontSize,
        const sf::Vector2f& size,
        const uint8_t textColor[3],
        const uint8_t backgroundColor[3]);

    ~Button() override = default;

    void Draw(sf::RenderTarget& target) override;
    void Update() override;

    void SetPosition(const sf::Vector2f position);

    void SetText(const sf::String& str);

    void SetCallback(std::function<void()> callback);

    void HandleEvent(
        const sf::Event& event,
        const sf::RenderWindow& window);

    void Toggle();

    bool IsHovered() const;

    sf::FloatRect GetBounds() const;

    Button& operator=(const Button& other);
    Button& operator=(Button&& other);
};

#endif // BUTTON_H