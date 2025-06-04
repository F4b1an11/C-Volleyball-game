#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <math.h>
#include "button_state.cpp"

int main()
{
    u_int32_t width = 1420U;
    u_int32_t height = 720U;

    sf::RenderWindow window(sf::VideoMode({width, height}), "SFML works! | Regina was here :D",sf::Style::Default);
    
    sf::RectangleShape bound({width -58.0f, height - 144.0f});
    bound.setOrigin(bound.getGeometricCenter());
    bound.setPosition({static_cast<float>(width)/2,static_cast<float>(height)/2});
    bound.setFillColor( sf::Color(0xFD5E53FF));
    Input input = {};

    sf::RectangleShape bottomBound({static_cast<float>(width), 50.0f});
    bottomBound.setOrigin(bottomBound.getGeometricCenter());
    bottomBound.setFillColor(sf::Color(0xDFDFDFFF));
    bottomBound.setPosition({static_cast<float>(width)/2.0f,static_cast<float>(height)-50.0f});

    sf::RectangleShape player1({69.f,100.0f});
    player1.setFillColor(sf::Color::Blue);
    player1.setOrigin(player1.getGeometricCenter());
    player1.setPosition({bottomBound.getPosition().x/2 , static_cast<float>(height)});
    
    sf::RectangleShape player2({69.f,100.0f});
    player2.setFillColor(sf::Color::Red);
    player2.setOrigin(player2.getGeometricCenter());
    player2.setPosition({static_cast<float>(width)*3/4, static_cast<float>(height)- player2.getSize().y/2});
    Input input2 = {};
    
    window.setFramerateLimit(120);
    window.setMinimumSize(sf::Vector2u(200u,200u));

    
    const sf::Keyboard::Scancode ButtonKeys[BUTTON_COUNT] = {
        sf::Keyboard::Scancode::Up,
        sf::Keyboard::Scancode::Down,
        sf::Keyboard::Scancode::Left,
        sf::Keyboard::Scancode::Right,
    };

    const sf::Keyboard::Scancode WasdKeys[BUTTON_COUNT] = {
        sf::Keyboard::Scancode::W,
        sf::Keyboard::Scancode::S,
        sf::Keyboard::Scancode::A,
        sf::Keyboard::Scancode::D,
    };

    sf::Vector2f velocity = {0.0f,0.0f};
    sf::Vector2f acceleration = {0.0f, 0.0f};
    sf::Vector2f velocity2 = {0.0f,0.0f};
    sf::Vector2f acceleration2 = {0.0f, 0.0f};
    sf::Clock timeDelta;
    const float ACC = 0.01f;
    const float fr = 0.95f;
    const float gravity = -0.015f;
    float dt = timeDelta.restart().asMilliseconds();

    while (window.isOpen())
    {
        dt = timeDelta.restart().asMilliseconds();
        for(int i = 0; i < BUTTON_COUNT; i++){
             input.buttons[i].changed = false;
             input2.buttons[i].changed = false;
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
                }
                input.buttons[i].is_down = true;
            }
            else{
                if(input.buttons [i].is_down){
                input.buttons[i].changed = true;
                }
                input.buttons [i].is_down = false;
            }
        }

        //P2 WASD
        for(int i = 0; i < BUTTON_COUNT; i++){
            if(sf::Keyboard::isKeyPressed(WasdKeys[i])){
                if(!input2.buttons[i].is_down){
                    input2.buttons[i].changed = true;
                }
                input2.buttons[i].is_down = true;
            }
            else{
                if(input2.buttons[i].is_down){
                input2.buttons[i].changed = true;
                }
                input2.buttons[i].is_down = false;
            }
        }
        //simulate game
        

        acceleration = {0.0f,0.0f};

        if(input.buttons[BUTTON_UP].is_down && ((bottomBound.getPosition().y - bottomBound.getSize().y/2)-(player1.getPosition().y + player1.getSize().y/2) < 1)){
            acceleration.y  = -ACC*75;
        }
        else if (input.buttons[BUTTON_DOWN].is_down){
            acceleration.y = ACC;
        }
        if (input.buttons[BUTTON_LEFT].is_down){
            acceleration.x = -ACC;
        }
        else if (input.buttons[BUTTON_RIGHT].is_down){
            acceleration.x = ACC;
        }
        //std:: cout << (bottomBound.getPosition().y - bottomBound.getSize().y/2)-(player1.getPosition().y + player1.getSize().y/2)<< "\n";
        std::cout << player1.getPosition().x << " = x, " << player1.getPosition().y << " = y\n";
        acceleration.y -= gravity; 
        velocity += acceleration * dt;
        velocity *= fr;
        std::cout << dt << " time \n";
        if(dt < 20) player1.move(velocity * dt);
        
        if(bottomBound.getGlobalBounds().findIntersection(player1.getGlobalBounds())){
            player1.setPosition({player1.getPosition().x ,bottomBound.getPosition().y - bottomBound.getSize().y/2 - player1.getSize().y/2 +1 });
        }
        
        //P2 WASD
        acceleration2 = {0.0f,0.0f};
        if(input2.buttons[BUTTON_UP].is_down && ((bottomBound.getPosition().y - bottomBound.getSize().y/2)-(player2.getPosition().y + player2.getSize().y/2) < 1)){
            acceleration2.y  = -ACC*75;
        }
        else if (input2.buttons[BUTTON_DOWN].is_down){
            acceleration2.y = ACC;
        }
        if (input2.buttons[BUTTON_LEFT].is_down){
            acceleration2.x = -ACC;
        }
        else if (input2.buttons[BUTTON_RIGHT].is_down){
            acceleration2.x = ACC;
        }
        //std:: cout << (bottomBound.getPosition().y - bottomBound.getSize().y/2)-(player1.getPosition().y + player1.getSize().y/2)<< "\n";
        std::cout << player2.getPosition().x << " = x, " << player2.getPosition().y << " = y\n";
        acceleration2.y -= gravity; 
        velocity2 += acceleration2 * dt;
        velocity2 *= fr;
        std::cout << dt << " time \n";
        if(dt < 20) player2.move(velocity2 * dt);
        
        if(bottomBound.getGlobalBounds().findIntersection(player2.getGlobalBounds())){
            player2.setPosition({player2.getPosition().x ,bottomBound.getPosition().y - bottomBound.getSize().y/2 - player2.getSize().y/2 +1 });
        }
        

        window.clear();
        window.draw(bound);
        window.draw(bottomBound);
        window.draw(player2);
        window.draw(player1);
        window.display();
    }

}