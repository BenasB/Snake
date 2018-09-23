#include "apple.h"
#include <stdlib.h>
#include <time.h>

void Apple::update(Snake &snake, sf::Vector2i gridSize, sf::Texture *texture)
{
    if (!snake.dead && deadLastFrame)
    {
        move(getRandomPosition(gridSize, snake) - position);
    }

    if (position == snake.position)
    {
        move(getRandomPosition(gridSize, snake) - position);
        snake.grow(texture);
    }

    deadLastFrame = snake.dead;
}

sf::Vector2i Apple::getRandomPosition(sf::Vector2i gridSize, Snake snake)
{
    srand(time(NULL));
    sf::Vector2i randomPosition;
    do
    {
        randomPosition = sf::Vector2i(rand() % gridSize.x, rand() % gridSize.y);
    } while (snake.onTail(randomPosition) || snake.position == randomPosition || randomPosition == position);

    return randomPosition;
}