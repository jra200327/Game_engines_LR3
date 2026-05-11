#include "Button.h"

Button::Button(const Button& other)
{
    Transfer(other);
}

Button::Button(Button&& other)
{
    Transfer(other);
}

Button::Button(
    const std::filesystem::path& fontPath,
    const sf::String& text,
    int fontSize,
    const sf::Vector2f& size,
    const uint8_t textColor[3],
    const uint8_t backgroundColor[3])
    : _str(text)
{
    if (!_font.openFromFile(fontPath))
    {
        std::cerr << "Could not load font!\n";
        std::exit(-1);
    }

    _text = sf::Text(_font, _str, fontSize);

    _text.setFillColor(
        sf::Color(
            textColor[0],
            textColor[1],
            textColor[2]));

    _background.setSize(size);

    _background.setFillColor(
        sf::Color(
            backgroundColor[0],
            backgroundColor[1],
            backgroundColor[2]));

    // Центрируем текст внутри кнопки
    sf::FloatRect textBounds = _text.getLocalBounds();

    _text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f
    });

    _text.setPosition({
        size.x / 2.f,
        size.y / 2.f
    });
}

void Button::Draw(sf::RenderTarget& target)
{
    if (!_shouldDraw)
    {
        return;
    }

    target.draw(_background);
    target.draw(_text);
}

void Button::Update()
{
    if (_hovered)
    {
        _background.setScale({1.05f, 1.05f});
    }
    else
    {
        _background.setScale({1.f, 1.f});
    }
}

void Button::SetPosition(const sf::Vector2f position)
{
    _background.setPosition(position);

    sf::Vector2f size = _background.getSize();

    _text.setPosition({
        position.x + size.x / 2.f,
        position.y + size.y / 2.f
    });
}

void Button::SetText(const sf::String& str)
{
    _str = str;

    _text.setString(_str);

    sf::FloatRect textBounds = _text.getLocalBounds();

    _text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f
    });
}

void Button::SetCallback(std::function<void()> callback)
{
    _onClick = callback;
}

void Button::HandleEvent(
    const sf::Event& event,
    const sf::RenderWindow& window)
{
    if (!_shouldDraw)
    {
        return;
    }

    if (const auto* mouseMoved =
        event.getIf<sf::Event::MouseMoved>())
    {
        const sf::Vector2f mousePos(
            static_cast<float>(mouseMoved->position.x),
            static_cast<float>(mouseMoved->position.y));

        _hovered =
            _background.getGlobalBounds().contains(mousePos);
    }

    if (const auto* mousePressed =
        event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            const sf::Vector2f mousePos(
                static_cast<float>(mousePressed->position.x),
                static_cast<float>(mousePressed->position.y));

            if (_background.getGlobalBounds().contains(mousePos))
            {
                if (_onClick)
                {
                    _onClick();
                }
            }
        }
    }
}

void Button::Toggle()
{
    _shouldDraw = !_shouldDraw;
}

bool Button::IsHovered() const
{
    return _hovered;
}

sf::FloatRect Button::GetBounds() const
{
    return _background.getGlobalBounds();
}

Button& Button::operator=(const Button& other)
{
    Transfer(other);

    return *this;
}

Button& Button::operator=(Button&& other)
{
    Transfer(other);

    return *this;
}

void Button::Transfer(const Button& other)
{
    _font = other._font;

    _text = other._text;
    _text.setFont(_font);

    _background = other._background;

    _str = other._str;

    _shouldDraw = other._shouldDraw;
    _hovered = other._hovered;

    _onClick = other._onClick;
}