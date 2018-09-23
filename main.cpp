#include <SFML/Graphics.hpp>
#include "snake.h"
#include "apple.h"

int main()
{
    sf::Vector2i windowSize = sf::Vector2i(500, 500);
    sf::Vector2i cellSize = sf::Vector2i(25, 25);
    sf::Vector2i gridSize = sf::Vector2i(windowSize.x/cellSize.x, windowSize.y/cellSize.y);
    
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Snake", sf::Style::Close | sf::Style::Titlebar);
    sf::Clock clock;

    sf::Font font;
    if (!font.loadFromFile("resources/font.ttf"))
        return -1;
    
    sf::Text statusText("", font, 25);
    statusText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = statusText.getLocalBounds();
    statusText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    statusText.setPosition((float)windowSize.x/2, (float)windowSize.y/2);

    sf::Texture snakeTexture;
    sf::Texture snakeHeadTexture;
    sf::Texture appleTexture;
    if (!snakeTexture.loadFromFile("resources/snake.png") || !appleTexture.loadFromFile("resources/apple.png") || !snakeHeadTexture.loadFromFile("resources/snakehead.png"))
        return -1;

    Snake snake(sf::Vector2i(1,1), cellSize, sf::Vector2i(0,0), &snakeHeadTexture);
    Apple apple(snake, gridSize, cellSize, sf::Vector2i(1,1), &appleTexture);

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        sf::Time deltaTime = clock.restart();
        snake.update(deltaTime, gridSize, statusText, windowSize);
        apple.update(snake, gridSize, &snakeTexture);

        window.clear(sf::Color(51, 51, 51));
        snake.draw(window);
        apple.draw(window);
        window.draw(statusText);
        window.display();
    }

    return 0;
}