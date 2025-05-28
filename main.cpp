#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode({2048, 1024}), "SFML works! | Regina was here :D",sf::Style::Default);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(sf::Vector2(0.f, 0.f));
    sf::RectangleShape player1({69.f,100.0f});
    player1.setFillColor(sf::Color::Blue);
    player1.setPosition(player1.getGeometricCenter());
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
                sf::Vector2f right = {10.0f,0.0f};
                sf::Vector2f left = {-10.0f,0.0f};
                sf::Vector2f up = {0.0f,-10.0f};
                sf::Vector2f down = {0.0f,10.0f};
                if(keypressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                }
                else if(keypressed->scancode == sf::Keyboard::Scancode::Right){
                    player1.move(right);
                }
                else if(keypressed->scancode == sf::Keyboard::Scancode::Left){
                    player1.move(left);
                }
                else if(keypressed->scancode == sf::Keyboard::Scancode::Up){
                    player1.move(up);
                }
                else if(keypressed->scancode == sf::Keyboard::Scancode::Down){
                    player1.move(down);
                }
            }
            else if (event->is<sf::Event::Resized>()){
                sf::Vector2u size = window.getSize();
                std::cout << "width = " << size.x << " height = " << size.y << "\n" ;
            }
            else if (event->is<sf::Event::MouseButtonPressed>()){
                std::cout << "Mouse Click" << std::endl;
            }
        }
        

        window.clear();
        window.draw(shape);
        window.draw(player1);
        window.display();
    }
}