#include "gameObject.h"

GameObject::GameObject(sf::Vector2i size, sf::Vector2i cellSize, sf::Vector2i gridPosition, sf::Texture *texture)
{
    initializeShape(sf::Vector2f((float)size.x * cellSize.x, (float)size.y * cellSize.y), texture);
    position = gridPosition;
    shape.setPosition(getPositionFromGrid(gridPosition));
}

void GameObject::initializeShape(sf::Vector2f size, sf::Texture *texture)
{
    shape = sf::RectangleShape(size);
    shape.setTexture(texture);
}

void GameObject::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

void GameObject::move(sf::Vector2i gridOffset)
{
    position += gridOffset;
    shape.move(getPositionFromGrid(gridOffset));
}

sf::Vector2f GameObject::getPositionFromGrid(sf::Vector2i gridPosition)
{
    sf::Vector2f size = shape.getSize();
    return sf::Vector2f((float)gridPosition.x * size.x, (float)gridPosition.y * size.y);
}