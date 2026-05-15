#include "Grid.h"

Grid::Grid(float cellSize)
    : _cellSize(cellSize)
    , _gridColor(80, 80, 80)
{
}

void Grid::Draw(sf::RenderTarget& target) const
{
    auto size = target.getSize();

    sf::VertexArray lines(sf::PrimitiveType::Lines);

    for (float x = 0.f; x <= size.x; x += _cellSize)
    {
        lines.append(sf::Vertex({x, 0.f}, _gridColor));
        lines.append(sf::Vertex({x, static_cast<float>(size.y)}, _gridColor));
    }

    for (float y = 0.f; y <= size.y; y += _cellSize)
    {
        lines.append(sf::Vertex({0.f, y}, _gridColor));
        lines.append(sf::Vertex({static_cast<float>(size.x), y}, _gridColor));
    }

    target.draw(lines);
}

sf::Vector2i Grid::WorldToGrid(sf::Vector2f worldPos) const
{
    return {
        static_cast<int>(worldPos.x / _cellSize),
        static_cast<int>(worldPos.y / _cellSize)
    };
}

sf::Vector2f Grid::GridToWorld(sf::Vector2i gridPos) const
{
    return {
        gridPos.x * _cellSize + _cellSize * 0.5f,
        gridPos.y * _cellSize + _cellSize * 0.5f
    };
}

float Grid::CellSize() const
{
    return _cellSize;
}