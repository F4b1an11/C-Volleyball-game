#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({500, 500}), "SFML works! | Regina was here :D");
    sf::RenderWindow window(sf::VideoMode({500, 500}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(sf::Vector2(0.f, 0.f));

    sf::CircleShape shapeR(100.f);
    shapeR.setFillColor(sf::Color::Blue);
    shapeR.setPosition(sf::Vector2(150.f, 150.f));

    int num = 1; 
    while (window.isOpen())
    {
        
                // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()){
                std::cout << "Closing window \n";
                window.close();
                }
            else if (event->is<sf::Event::MouseButtonPressed>()){
                std::cout << "Mouse Click" << std::endl;
            }

            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::A)
                    std::cout << "A was typed \n";
            }
        }
        

        window.clear();
        window.draw(shape);
        window.draw(shapeR);
        window.display();
    }
}