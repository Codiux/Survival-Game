#include "Projectile.hpp"
#include "Player.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Survival Game");

    window.setFramerateLimit(60);

    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    sf::Vector2f map_size(window.getSize().x, window.getSize().y);
    
    std::vector<Projectile> bulletVec;
    
    Player player(window.getSize().x / 2, window.getSize().x / 2, sf::Vector2f(50, 50));
    float playerSpeed = 200;
    

    sf::Clock clock;
    while(window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseMoved:
                    mouse = sf::Mouse::getPosition(window);
                    
                    break;

                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        Projectile newProjectile(player.getPosition().x, player.getPosition().y, sf::Vector2f(30, 10), mouse, 1000);
                        bulletVec.push_back(newProjectile);
                        std::cout << bulletVec.size() << std::endl;
                    }
            }
        }


        ///////////// PLAYER MOVEMENTS ////////////////////
        player.look_at_mouse(sf::Vector2f(mouse.x, mouse.y));

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player.move(0.f, -playerSpeed * deltaTime);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player.move(0.f, playerSpeed * deltaTime);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.move(-playerSpeed * deltaTime, 0.f);
		}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.move(playerSpeed * deltaTime, 0.f);
		}

        //////////////// UPDATE BULLET ////////////////
        for(int i  = 0; i < bulletVec.size(); i++) {
            bulletVec[i].update(deltaTime);
        }

        
        window.clear();

        for(int i = 0; i < bulletVec.size(); i++) {
            window.draw(bulletVec[i]);
        }
        
        window.draw(player);

        window.display();
    }


   return EXIT_SUCCESS;
}
