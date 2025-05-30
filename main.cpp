#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <math.h>
#include "button_state.cpp"

int main()
{
    u_int32_t width = 2048U;
    u_int32_t height = 1024U;

    sf::RenderWindow window(sf::VideoMode({width, height}), "SFML works! | Regina was here :D",sf::Style::Default);
    
    sf::RectangleShape bound({width -58.0f, height - 144.0f});
    bound.setOrigin(bound.getGeometricCenter());
    bound.setPosition({static_cast<float>(width)/2,static_cast<float>(height)/2});
    bound.setFillColor( sf::Color(0xDCDCDCFF));
    Input input = {};

    sf::RectangleShape player1({69.f,100.0f});
    player1.setFillColor(sf::Color::Blue);
    player1.setOrigin(player1.getGeometricCenter());
    player1.setPosition({bound.getPosition().x/2 , bound.getPosition().y + bound.getSize().y/2 - player1.getSize().y/2});
    
    sf::RectangleShape player2({69.f,100.0f});
    player2.setFillColor(sf::Color::Red);
    player2.setOrigin(player2.getGeometricCenter());
    player2.setPosition({static_cast<float>(width)*3/4, static_cast<float>(height)- player2.getSize().y/2});
    
    window.setFramerateLimit(60);
    window.setMinimumSize(sf::Vector2u(200u,200u));

    
    const sf::Keyboard::Scancode ButtonKeys[BUTTON_COUNT] = {
        sf::Keyboard::Scancode::Up,
        sf::Keyboard::Scancode::Down,
        sf::Keyboard::Scancode::Left,
        sf::Keyboard::Scancode::Right,
    };

    
    while (window.isOpen())
    {
        for(int i = 0; i < BUTTON_COUNT; i++){
             input.buttons[i].changed = false;
        }

                // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()){
                std::cout << "Closing window \n";
                window.close();
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
             else if (const auto keypressed = event->getIf<sf::Event::KeyPressed>()){
               if(keypressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                    std::cout << "Closeing window \n";
                } 
             }
        }


        for(int i = 0; i < BUTTON_COUNT; i++){
            if(sf::Keyboard::isKeyPressed(ButtonKeys[i])){
                if(!input.buttons[i].is_down){
                    input.buttons[i].changed = true;
                    input.buttons[i].time_down.restart();
                }
                input.buttons[i].is_down = true;
            }
            else{
                if(input.buttons [i].is_down){
                input.buttons[i].changed = true;
                input.buttons [i].time_down.reset();     
                }
                input.buttons [i].is_down = false;
            }
        }
        //simulate game
        
        std::cout << player1.getPosition().y << "\n";
        //std::cout << bound.getPosition().y << " " << bound.getSize().y << " \n";
        if(input.buttons[BUTTON_UP].is_down == true){
          if(player1.getPosition().y - player1.getSize().y/2 > bound.getPosition().y - bound.getSize().y/2){
            player1.move({0, -.1f*input.buttons [BUTTON_UP].time_down.getElapsedTime().asMilliseconds()});
          }
          else
          player1.setPosition({player1.getPosition().x, bound.getPosition().y - bound.getSize().y/2 + player1.getSize().y/2 });
            
        } 
        if(input.buttons[BUTTON_DOWN].is_down == true){
          if(player1.getPosition().y + player1.getSize().y/2 < bound.getPosition().y + bound.getSize().y/2){
            player1.move({0, .1f*input.buttons [BUTTON_DOWN].time_down.getElapsedTime().asMilliseconds()});
          }
          else
          player1.setPosition({player1.getPosition().x, bound.getPosition().y + bound.getSize().y/2 - player1.getSize().y/2 });
          
        } 
        if(input.buttons[BUTTON_LEFT].is_down == true){
          if(player1.getPosition().x - player1.getSize().x/2 > bound.getPosition().x - bound.getSize().x/2){
            player1.move({-.1f*input.buttons [BUTTON_LEFT].time_down.getElapsedTime().asMilliseconds() ,0});
          }
          else
          player1.setPosition({bound.getPosition().x - bound.getSize().x/2 + player1.getSize().x/2 , player1.getPosition().y});
                     
        } 
        if(input.buttons[BUTTON_RIGHT].is_down == true){
          if(player1.getPosition().x + player1.getSize().x/2 < bound.getPosition().x + bound.getSize().x/2){
            player1.move({.1f*input.buttons [BUTTON_RIGHT].time_down.getElapsedTime().asMilliseconds() ,0});
          }
          else
          player1.setPosition({bound.getPosition().x + bound.getSize().x/2 - player1.getSize().x/2 , player1.getPosition().y});
                               
        } 

        //rendering
        window.clear();
        window.draw(bound);
        window.draw(player2);
        window.draw(player1);
        window.display();
    }

}