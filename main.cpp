#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <math.h>
#include "button_state.cpp" 

    u_int32_t width = 1420U;
    u_int32_t height = 720U;
    int consecutiveTouch = 0;
    bool ballInsidePlayer;
void setBall(sf::RectangleShape& ball,sf::Vector2f& ballVelocity , sf::Vector2f ballAcceleration, int player){
    if(player == 1){
        ball.setPosition({static_cast<float>(width)*3/4,static_cast<float>(height)*3/4});
    }
    else if(player == 2){
        ball.setPosition({static_cast<float>(width)*1/4,static_cast<float>(height)*3/4});
    }
    else{
        std::cerr << "setBall does not recognise player:  " << player << "\n";
    }
    ballVelocity = {0,0};
    ballAcceleration = {0,0};
    consecutiveTouch = 0;
}

int main()
{
    
    sf::Vector2u size = {width,height};

    sf::RenderWindow window(sf::VideoMode(size), "SFML works! | Regina was here :D",sf::Style::Default);
    
    sf::RectangleShape background({static_cast<float>(width), static_cast<float>(height)});
    background.setOrigin(background.getGeometricCenter());
    background.setPosition({static_cast<float>(width)/2,static_cast<float>(height)/2});
    background.setFillColor( sf::Color(0xFD5E53FF));
    Input input = {};

    sf::RectangleShape bottomBound({static_cast<float>(width), 100.0f});
    bottomBound.setOrigin(bottomBound.getGeometricCenter());
    bottomBound.setFillColor(sf::Color(0xDFDFDFFF));
    bottomBound.setPosition({static_cast<float>(width)/2.0f,static_cast<float>(height)+35.0f});

    sf::RectangleShape topBound({static_cast<float>(width), 100.0f});
    topBound.setOrigin(topBound.getGeometricCenter());
    topBound.setFillColor(sf::Color(0xDFDFDFFF));
    topBound.setPosition({static_cast<float>(width)/2.0f,-35.0f});

    sf::RectangleShape leftBound({100.0f,static_cast<float>(width) });
    leftBound.setOrigin(leftBound.getGeometricCenter());
    leftBound.setFillColor(sf::Color(0xDFDFDFFF));
    leftBound.setPosition({-35,static_cast<float>(height)/2});

    sf::RectangleShape rightBound({100.0f, static_cast<float>(width)});
    rightBound.setOrigin(rightBound.getGeometricCenter());
    rightBound.setFillColor(sf::Color(0xDFDFDFFF));
    rightBound.setPosition({static_cast<float>(width)+35.0f,static_cast<float>(height)/2});

    sf::RectangleShape net({30.0f, 200.0f});
    net.setOrigin(net.getGeometricCenter());
    net.setFillColor(sf::Color(0x6F6F6FFF));
    net.setPosition({static_cast<float>(width)/2,bottomBound.getPosition().y - 100.0f});

    sf::RectangleShape player2({120.f,100.0f});
    player2.setFillColor(sf::Color::Blue);
    player2.setOrigin(player2.getGeometricCenter());
    player2.setPosition({bottomBound.getPosition().x/2 , static_cast<float>(height)});
    
    sf::RectangleShape player1({120.f,100.0f});
    player1.setFillColor(sf::Color::Red);
    player1.setOrigin(player1.getGeometricCenter());
    player1.setPosition({static_cast<float>(width)*3/4, static_cast<float>(height)- player2.getSize().y/2});
    Input input2 = {};

    sf::RectangleShape ball({20.0f,20.0f});
    ball.setFillColor(sf::Color(0xFFFFFFFF));
    ball.setOrigin(ball.getGeometricCenter());
    ball.setPosition({static_cast<float>(width)/3,static_cast<float>(height)*3/4});


    
    window.setFramerateLimit(120);
    window.setMinimumSize(sf::Vector2u(200U,200U));

    
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

    sf::Vector2f ballVelocity = {0.0f,0.0f};
    sf::Vector2f ballAcceleration = {0.0f, 0.0f};

    sf::Clock timeDelta;
    const float ACC = 0.006f;
    const float fr = 0.95f;
    const float gravity = -0.015f;
    float dt = timeDelta.restart().asMilliseconds();
    int lastTouch = 0;
    int p1Points = 0;
    int p2Points = 0; 

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
        ballAcceleration = {0.0f,0.0f};


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
        std::cout << "Ball position  " << ball.getPosition().x << " = x, " << ball.getPosition().y << " = y \n";
        acceleration.y -= gravity; 
        velocity += acceleration * dt;
        velocity *= fr;
        std::cout << dt << " time \n";
        if(dt < 20) player1.move(velocity * dt);
        
        if(bottomBound.getGlobalBounds().findIntersection(player1.getGlobalBounds())){
            player1.setPosition({player1.getPosition().x ,bottomBound.getPosition().y - bottomBound.getSize().y/2 - player1.getSize().y/2 +1 });
        }
        if(leftBound.getGlobalBounds().findIntersection(player1.getGlobalBounds())){
            velocity.x = .2;
            acceleration.y = .2;
        }
        if(rightBound.getGlobalBounds().findIntersection(player1.getGlobalBounds())){
            velocity.x = -.2;
            acceleration.y = -.2;
        }
        if(net.getGlobalBounds().findIntersection(player1.getGlobalBounds())){
            if(player1.getPosition().x > net.getPosition().x){
                velocity.x = .2;
            } 
            else{
                velocity.x = -.2;
            }
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
        acceleration2.y -= gravity; 
        velocity2 += acceleration2 * dt;
        velocity2 *= fr;
        if(dt < 20) player2.move(velocity2 * dt);
        
        if(bottomBound.getGlobalBounds().findIntersection(player2.getGlobalBounds())){
            player2.setPosition({player2.getPosition().x ,bottomBound.getPosition().y - bottomBound.getSize().y/2 - player2.getSize().y/2 +1 });
        }
        if(leftBound.getGlobalBounds().findIntersection(player2.getGlobalBounds())){
            velocity2.x = .2;
            acceleration2.y = .2;
        }
        if(rightBound.getGlobalBounds().findIntersection(player2.getGlobalBounds())){
            velocity2.x = -.2;
            acceleration2.y = -.2;
        }
        if(net.getGlobalBounds().findIntersection(player2.getGlobalBounds())){
            if(player2.getPosition().x > net.getPosition().x){
                velocity2.x = .2;
            } 
            else{
                velocity2.x = -.2;
            }
        }
        
        
        bool changed = false;//Sometimes the ball is inside the player for multiple frames, this bool along with ballInsidePlayer helps keep track of that
        //player and ball connect
        if(ball.getGlobalBounds().findIntersection(player1.getGlobalBounds())){
            if(ballInsidePlayer == false){
                changed = true;
            }
            ballInsidePlayer = true;
            if(consecutiveTouch == 3 && lastTouch == 1 && changed){
                p2Points++;
                setBall(ball,ballVelocity,ballAcceleration,2);
                consecutiveTouch = 0;
            }
            else{
                ballVelocity.x = (ball.getPosition().x - player1.getPosition().x)/60;
                if(velocity.y < -1){
                    ballVelocity.y = velocity.y;
                }
                else{
                    ballVelocity.y = -1;
                }
                
                if(lastTouch == 1){
                    consecutiveTouch++;
                }
                else{
                    consecutiveTouch = 1;
                }
                lastTouch = 1;
            }   
        }
        else if(ball.getGlobalBounds().findIntersection(player2.getGlobalBounds())){
            if(ballInsidePlayer == false){
                changed = true;
            }
            ballInsidePlayer = true;
            if(consecutiveTouch == 3 && lastTouch == 2 && changed){
                p1Points++;
                setBall(ball,ballVelocity,ballAcceleration,1);
                consecutiveTouch = 0;
            }
            else{
                ballVelocity.x = (ball.getPosition().x - player2.getPosition().x)/60;
                ballVelocity.y = -1;
                if(lastTouch == 2){
                    consecutiveTouch++;
                }
                else{
                    consecutiveTouch =1;
                }
                lastTouch = 2;   
            } 
        }
        else{
            if(ballInsidePlayer == true){
                changed = true;
            }
            ballInsidePlayer = false;
        }
        


        //ball and bounds connect
        if(bottomBound.getGlobalBounds().findIntersection(ball.getGlobalBounds())){
            ballAcceleration.y = -.01;
            ballVelocity.y *= -1;
            if(ball.getPosition().x > width/2){
                p2Points++;
                setBall(ball, ballVelocity, ballAcceleration, 2);
            }
            else{
                p1Points++;
                setBall(ball ,ballVelocity, ballAcceleration, 1);
            }
        }
        if(topBound.getGlobalBounds().findIntersection(ball.getGlobalBounds())){
            ballAcceleration.y = .01;
            ballVelocity.y *= -1;
        }
        if(leftBound.getGlobalBounds().findIntersection(ball.getGlobalBounds())){
            ballAcceleration.x = .01;
            ballVelocity.x *= -1;
        }
        if(rightBound.getGlobalBounds().findIntersection(ball.getGlobalBounds())){
            ballAcceleration.x = -.01;
            ballVelocity.x *= -1;
        }
        if(net.getGlobalBounds().findIntersection(ball.getGlobalBounds())){
            if(ball.getPosition().y < net.getPosition().y - 45){
                ballVelocity.y = -1;
            }
            else{
                ballVelocity.x *= -1;  
            }
        }

        //ballVelocity *= .999f;
        //ballAcceleration.y += .0001;
        //ballVelocity += ballAcceleration * dt;
        if(dt < 20)ball.move(ballVelocity * dt);



        window.clear();
        window.draw(background);
        window.draw(bottomBound);
        window.draw(topBound);
        window.draw(leftBound);
        window.draw(rightBound);
        window.draw(player2);
        window.draw(player1);
        window.draw(net);
        window.draw(ball);
        window.display();
    }

}