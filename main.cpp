#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

int main()
{
    u_int32_t width = 2048U;
    u_int32_t height = 1024U;

    sf::RenderWindow window(sf::VideoMode({width, height}), "SFML works! | Regina was here :D",sf::Style::Default);

    sf::RectangleShape player1({69.f,100.0f});
    player1.setFillColor(sf::Color::Blue);
    player1.setOrigin(player1.getGeometricCenter());
    player1.setPosition({static_cast<float>(width)/4, static_cast<float>(height)- player1.getSize().y/2});
    sf::RectangleShape player2({69.f,100.0f});
    player2.setFillColor(sf::Color::Red);
    player2.setOrigin(player2.getGeometricCenter());
    player2.setPosition({static_cast<float>(width)*3/4, static_cast<float>(height)- player2.getSize().y/2});
    window.setFramerateLimit(60);
    window.setMinimumSize(sf::Vector2u(200u,200u));
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
                    std::cout << "Closeing window \n";
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
                else if(keypressed->scancode == sf::Keyboard::Scancode::D){
                    player2.move(right);
                }
                else if(keypressed->scancode == sf::Keyboard::Scancode::A){
                    player2.move(left);
                }
                else if(keypressed->scancode == sf::Keyboard::Scancode::W){
                    player2.move(up);
                }
                else if(keypressed->scancode == sf::Keyboard::Scancode::S){
                    player2.move(down);
                }
            }
            else if (event->is<sf::Event::Resized>()){
                sf::Vector2u size = window.getSize();
                width = size.x;
                height = size.y;
                std::cout << "width = " << width << " height = " << height << "\n" ;
            }
            else if (event->is<sf::Event::MouseButtonPressed>()){
                std::cout << "Mouse Click" << std::endl;
            }
        }
        

        window.clear();
        window.draw(player2);
        window.draw(player1);
        window.display();
    }
}