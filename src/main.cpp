#include <TGUI/TGUI.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>

#include<Player.h>
#include<Projectile.h>
#include<Resource.h>
#include<StaticBody2D.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Survival Game");

    window.setFramerateLimit(60);

    //////////////////////////// GAME OBJECTS /////////////////////////

    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    sf::Vector2f map_size(window.getSize().x, window.getSize().y);

    sf::Vector2f center(0, 0);
    
    // ------ projectiles here ----
    std::vector<Projectile> bulletVec;
    
    // player initialize
    Player player(window.getSize().x / 2, window.getSize().x / 2, sf::Vector2f(50, 50));
    float playerSpeed = 300;

    // ----- resources here -----
    int treeCount = 10;
    int rockCount = 10;
    int berryCount = 10;

    std::vector<Resource> treeVec;
    std::vector<Resource> rockVec;
    std::vector<Resource> berryVec;

    for(int i = 0; i < treeCount; i++) {
        Resource newTree(rand() % int(map_size.x), rand() % int(map_size.y), sf::Vector2f(80, 80), sf::Color(0, 255, 0), rand()%180);
        treeVec.push_back(newTree);
    }
    for(int i = 0; i < rockCount; i++) {
        Resource newRock(rand() % int(map_size.x), rand() % int(map_size.y), sf::Vector2f(80, 80), sf::Color(195, 195, 195), rand()%180);
        treeVec.push_back(newRock);
    }
    for(int i = 0; i < berryCount; i++) {
        Resource newBerry(rand() % int(map_size.x), rand() % int(map_size.y), sf::Vector2f(80, 80), sf::Color(222, 59, 10), rand()%180);
        treeVec.push_back(newBerry);
    }


    std::cout << treeVec.size() << std::endl;

    // GUI scenes enum used to switch between it
    enum GUI_SCENES_ENUM {
        MAIN,
        SETTINGS,
        CREDITS,
        GAME
    };

    GUI_SCENES_ENUM GUI_SCENES;
    GUI_SCENES = MAIN;

 
 //   sf::Texture alienBG_TXT;
 //   if(!alienBG_TXT.loadFromFile("alien_bg.jpg")) return(-1);
 //   sf::Sprite alienBG_S(alienBG_TXT);
 //   alienBG_S.scale(window.getSize().x / alienBG_S.getGlobalBounds().width, window.getSize().y / alienBG_S.getGlobalBounds().height);
 


 //////////////////// initialize GUI Elements /////////////////

    tgui::Theme blackTheme{"nanogui.style"};

    tgui::Gui gui{window};

    ////////// Main Menu ///////////
    auto MainMenuScene = tgui::Group::create();
    gui.add(MainMenuScene);

    auto Selection_PNL =  tgui::Panel::create();
    Selection_PNL->setRenderer(blackTheme.getRenderer("Panel"));
    Selection_PNL->setPosition(window.getSize().x / 2 - 140, window.getSize().y / 2 - 145);
    Selection_PNL->setSize(280, 290);
    MainMenuScene->add(Selection_PNL);
    

    auto Start_BTN = tgui::Button::create();
    Start_BTN->setRenderer(blackTheme.getRenderer("Button"));
    Start_BTN->setPosition(15, 25);
    Start_BTN->setSize(250, 50);
    Start_BTN->setText("Start");
    Start_BTN->connect("pressed", [&](){ ButtonSignalHandler(0); });
    Selection_PNL->add(Start_BTN, "Start_BTN");

    auto Settings_BTN = tgui::Button::create();
    Settings_BTN->setRenderer(blackTheme.getRenderer("Button"));
    Settings_BTN->setPosition(15, 85);
    Settings_BTN->setSize(250, 50);
    Settings_BTN->setText({"Settings"});
    Settings_BTN->connect("pressed", [&](){ ButtonSignalHandler(1); });
    Selection_PNL->add(Settings_BTN, "Settings_BTN");

    auto Credits_BTN = tgui::Button::create();
    Credits_BTN->setRenderer(blackTheme.getRenderer("Button"));
    Credits_BTN->setPosition(15, 145);
    Credits_BTN->setSize(250, 50);
    Credits_BTN->setText("Credits");
    Credits_BTN->connect("pressed", [&](){ ButtonSignalHandler(2); });
    Selection_PNL->add(Credits_BTN, "Credits_BTN");

    auto Quit_BTN = tgui::Button::create();
    Quit_BTN->setRenderer(blackTheme.getRenderer("Button"));
    Quit_BTN->setPosition(15, 205);
    Quit_BTN->setSize(250, 50);
    Quit_BTN->setText("Quit");
    Quit_BTN->connect("pressed", [&](){ ButtonSignalHandler(3); });
    Selection_PNL->add(Quit_BTN, "Quit_BTN");

    ////////////////////////////////////////////////////////

    sf::RectangleShape r1(sf::Vector2f(40, 40));
    r1.setRotation(60);
    r1.setFillColor(sf::Color(255, 0, 0));
    r1.setPosition( 500, 500);
    

    bool keyboardButtonDown = false;

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

                case sf::Event::KeyPressed:
                    keyboardButtonDown = true;
                    break;

                case sf::Event::KeyReleased:
                    keyboardButtonDown = false;
                    break;

                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        Projectile newProjectile(player.getPosition().x, player.getPosition().y, sf::Vector2f(30, 10), mouse, 1500);
                        bulletVec.push_back(newProjectile);
                        std::cout << bulletVec.size() << std::endl;
                }
            }
            gui.handleEvent(event);
        }

        ///////////////////// GUI /////////////////

        switch(GUI_SCENES)
        {
            case MAIN:
                break;

        }

        if(r1.getGlobalBounds().contains(mouse.x, mouse.y)) std::cout << "collided" << std::endl;

        ///////////// PLAYER MOVEMENTS ////////////////////
        player.look_at_mouse(sf::Vector2f(mouse.x, mouse.y));

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player.move(0.f, -playerSpeed * deltaTime);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player.move(0.f, playerSpeed * deltaTime);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.move(-playerSpeed * deltaTime, 0.f);
		}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.move(playerSpeed * deltaTime, 0.f);
		}

        //////////////// UPDATE BULLET ////////////////
        for(int i  = 0; i < bulletVec.size(); i++) {
            bulletVec[i].update(deltaTime);
        }

        
        window.clear(sf::Color(55, 165, 105));

        for(int i = 0; i < bulletVec.size(); i++) {
            window.draw(bulletVec[i]);
        }
        
        window.draw(player);
        
    //    window.draw(alienBG_S);

/*
        for(int i = 0; i < treeVec.size(); i++) {
            window.draw(treeVec[i]);
        }
        for(int i = 0; i < rockVec.size(); i++) {
            window.draw(rockVec[i]);
        }
        for(int i = 0; i < berryVec.size(); i++) {
            window.draw(berryVec[i]);
        }*/

     //   gui.draw();

        window.draw(r1);

        window.display();
    }



    return EXIT_SUCCESS;
}
