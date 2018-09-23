#ifndef APPLE_H
#define APPLE_H
#include "gameObject.h"
#include "snake.h"

class Apple : public GameObject
{
public:
    Apple(Snake snake, sf::Vector2i gridSize, sf::Vector2i cellSize, sf::Vector2i size, sf::Texture *texture) : GameObject(size, cellSize, getRandomPosition(gridSize, snake), texture) {}

    void update(Snake &snake, sf::Vector2i gridSize, sf::Texture *texture);
private:
    bool deadLastFrame = false;
    sf::Vector2i getRandomPosition(sf::Vector2i gridSize, Snake snake);
};

#endif