#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode({512, 512}), "SFML works! | Regina was here :D",sf::Style::Default);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(sf::Vector2(0.f, 0.f));

    sf::CircleShape shapeR(100.f);
    shapeR.setFillColor(sf::Color::Blue);
    shapeR.setPosition(sf::Vector2(150.f, 150.f));
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        
                // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()){
                std::cout << "Closing window \n";
                window.close();
                }
            else if (const auto keypressed = event->getIf<sf::Event::KeyPressed>()){
                if(keypressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                }
            }
            else if (event->is<sf::Event::Resized>()){
                sf::Vector2u size = window.getSize();
                std::cout << "width = " << size.x << " height = " << size.y << "\n" ;
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