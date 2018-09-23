#include "snake.h"
#include <sstream>

void Snake::update(sf::Time deltaTime, sf::Vector2i gridSize, sf::Text &statusText, sf::Vector2i windowSize)
{
    if (dead)
    {
        sf::Time currentDeathTime = deathTimer.getElapsedTime();
        if (currentDeathTime.asSeconds() >= deathTime)
        {
            statusText.setString("");
            reset();
        }
        else
            return;          
    }

    movementCounter += deltaTime.asSeconds();

    handleInput();

    if (movementCounter >= movementDelay)
    {
        if (tail.size()+1 == gridSize.x * gridSize.y) // Winning condition
        {
            printf("You won!");
            statusText.setString("You won!");
            sf::FloatRect textRect = statusText.getLocalBounds();
            statusText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            statusText.setPosition((float)windowSize.x/2, (float)windowSize.y/2);
        }

        direction = temporaryDirection;

        // Losing condition
        if (onTail(position + direction) || position.x + direction.x < 0 || position.y + direction.y < 0 || position.x + direction.x >= gridSize.x || position.y + direction.y >= gridSize.y)
        {
            printf("Game over! Score: %i\n", (int)tail.size());
            std::stringstream type;
		    type << tail.size();
            statusText.setString("Game over!\nScore: " + type.str());
            sf::FloatRect textRect = statusText.getLocalBounds();
            statusText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            statusText.setPosition((float)windowSize.x/2, (float)windowSize.y/2);

            shape.setFillColor(sf::Color::Red);
            dead = true;
            deathTimer.restart();
            return;
        }

        move(direction);
        movementCounter = 0;
    }
}

void Snake::handleInput()
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) && direction.x != 1)
        temporaryDirection = sf::Vector2i(-1, 0);
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) && direction.x != -1)
        temporaryDirection = sf::Vector2i(1, 0);
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && direction.y != 1)
        temporaryDirection = sf::Vector2i(0, -1);
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) && direction.y != -1)
        temporaryDirection = sf::Vector2i(0, 1);
}

void Snake::draw(sf::RenderWindow &window)
{
    GameObject::draw(window);
    for(int i = 0; i < tail.size(); i++)
        tail[i].draw(window);
}

void Snake::move(sf::Vector2i gridOffset)
{
    for(int i = tail.size() - 1; i >= 0; i--)
    {
        if (i == 0)
            tail[i].move(position - tail[i].position);
        else
            tail[i].move(tail[i-1].position - tail[i].position);
    }

    GameObject::move(gridOffset);
}

void Snake::grow(sf::Texture *texture)
{
    movementDelay -= movementSpeedup;
    if (movementDelay <= minimumDelay)
        movementDelay = minimumDelay;

    printf("Score: %i\n", (int)tail.size());
    GameObject piece(sf::Vector2i(1,1), sf::Vector2i((int)shape.getSize().x, (int)shape.getSize().y), tail.size() == 0 ? position : tail[tail.size()-1].position, texture);
    tail.push_back(piece);
}

bool Snake::onTail(sf::Vector2i gridPosition)
{   
    for(int i = 0; i < tail.size(); i++)
    {
        if (gridPosition == tail[i].position)
            return true;
    }

    return false;
}

void Snake::reset()
{
    tail = std::vector<GameObject>();
    movementDelay = startingMovementDelay;
    shape.setFillColor(sf::Color::White);
    direction = temporaryDirection = sf::Vector2i(1,0);
    move(-position);
    dead = false;
}