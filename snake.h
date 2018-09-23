#ifndef SNAKE_H
#define SNAKE_H
#include "gameObject.h"
#include <vector>

class Snake : public GameObject
{
public:
    Snake(sf::Vector2i size, sf::Vector2i cellSize, sf::Vector2i gridPosition, sf::Texture *texture) : GameObject(size, cellSize, gridPosition, texture) {}
    
    bool dead = false;

    void update(sf::Time deltaTime, sf::Vector2i gridSize, sf::Text &statusText, sf::Vector2i windowSize);
    void draw(sf::RenderWindow &window);
    void move(sf::Vector2i gridOffset);
    void grow(sf::Texture *texture);
    bool onTail(sf::Vector2i gridPosition);
private:
    float movementDelay = 0.2f;
    float startingMovementDelay = movementDelay;
    float movementSpeedup = 0.005f;
    float minimumDelay = 0.04f;
    float movementCounter = 0.0f;
    std::vector<GameObject> tail;
    float deathTime = 2.0f;
    sf::Clock deathTimer;

    sf::Vector2i direction = sf::Vector2i(1, 0);
    sf::Vector2i temporaryDirection = direction;

    void reset();
    void handleInput();
    void moveTail();
};

#endif