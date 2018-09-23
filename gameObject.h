#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    GameObject(sf::Vector2i size, sf::Vector2i cellSize, sf::Vector2i gridPosition, sf::Texture *texture);

    sf::Vector2i position;
    void update(sf::Time deltaTime);
    virtual void draw(sf::RenderWindow &window);
    virtual void move(sf::Vector2i gridOffset);
protected:
    sf::RectangleShape shape;
private:
    void initializeShape(sf::Vector2f size, sf::Texture *texture);
    sf::Vector2f getPositionFromGrid(sf::Vector2i gridPosition);
};

#endif