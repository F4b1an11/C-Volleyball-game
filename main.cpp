#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({500, 500}), "SFML works! | Regina was here :D");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(sf::Vector2(0.f, 0.f));

    sf::CircleShape shapeR(100.f);
    shapeR.setFillColor(sf::Color::Blue);
    shapeR.setPosition(sf::Vector2(150.f, 150.f));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(shapeR);
        window.display();
    }
}