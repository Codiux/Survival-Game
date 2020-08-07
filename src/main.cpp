#include <TGUI/TGUI.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>

class StaticBody2D : public sf::Drawable {
    public:
    StaticBody2D(float x, float y, sf::Vector2f size) 
    {
        pStaticBody2DShape.setSize(size);
        pStaticBody2DShape.setOutlineThickness(-2);
        pStaticBody2DShape.setOutlineColor(sf::Color(0, 0, 0));
    }   
    void setSize(sf::Vector2f size) {
        pStaticBody2DShape.setSize(size);
    }
    sf::Vector2f getSize() {
        return pStaticBody2DShape.getSize();
    }
    void setPostition(float x, float y) 
    {
        pStaticBody2DShape.setPosition(x, y);
    }
    sf::Vector2f getPosition() {
        return pStaticBody2DShape.getPosition();
    }
    sf::FloatRect getGlobalBounds() {
        return pStaticBody2DShape.getGlobalBounds();
    }
    void move(int x, int y) 
    {
        pStaticBody2DShape.setPosition(x, y);
    }
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(pStaticBody2DShape);
    }
    private:
    sf::RectangleShape pStaticBody2DShape;
};
/*
class TileMap : public sf::Drawable {
    public:
    TileMap(sf::Vector2f dim) 
    {
        for(int i = 0; i < dim.y; i++) {
            std::vector<int>temp;
            for(int i = 0; i < dim.x; i++) {
                temp.push_back(0);
            }
            TileMapDim.push_back(temp);
        }
    }
    bool addNewtile(std::string fileLocation) 
    {
        sf::Texture texture;  
        if(!texture.loadFromFile(fileLocation)) return(0);
        sf::Sprite newSprite(texture);
        tileTexture.push_back(newSprite);
    }
    void setTile(int x, int y, int tileType) 
    {
         
    }
    void setPosition(float x, float y) 
    {
        pPosition = sf::Vector2f(x, y);
    }
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        for(int y = 0; y < TileMapDim.size(); y++) {
            for(int x = 0; x < TileMapDim[y].size(); x++) {
                tileTexture[0].setPosition(30, 30);
                target.draw(tileTexture[TileMapDim[y][x]]);
            }
        }
    }
    private:
    std::vector<std::vector<int>> TileMapDim;
    std::vector<sf::Sprite> tileTexture;
    sf::Vector2f pTileSize;
    sf::Vector2f pPosition;
};*/



class MyEntity : public sf::Drawable, public sf::Transformable
{
    public:
        bool loadFromFile(const std::string& skin) {
            if(!m_texture.loadFromFile(skin)) return 0;


        }
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();

            states.texture = &m_texture;

            target.draw(m_vertices, states);
        }
        sf::VertexArray m_vertices;
        sf::Texture m_texture;
};

class Resource : public sf::Drawable {
    public:

    private:
        sf::RectangleShape collisionShape;

};

class Projectile : public sf::Drawable {
    public:
        Projectile() {
            //default
        }
        Projectile(int x, int y, sf::Vector2f collisionSize, sf::Vector2i mouse, float speed) {
            pCollisionShape.setPosition(x, y);

            pCollisionShape.setSize(collisionSize);

            pCollisionShape.setOrigin(pCollisionShape.getGlobalBounds().width / 2, pCollisionShape.getGlobalBounds().height / 2);

            pCollisionShape.setOutlineThickness(-2);

            pCollisionShape.setOutlineColor(sf::Color(60, 60, 60));

            float angle = atan2(mouse.y - pCollisionShape.getPosition().y, mouse.x - pCollisionShape.getPosition().x) * 180 / 3.14159;

            pCollisionShape.setRotation(angle);

            sf::Vector2f distance(mouse.x - pCollisionShape.getPosition().x, mouse.y - pCollisionShape.getPosition().y);
            
            float length = sqrt(distance.x * distance.x + distance.y * distance.y);

            velocity = (distance / length) * speed;
        }
        void setSize(sf::Vector2f size) {
            pCollisionShape.setSize(size);
            pCollisionShape.setOrigin(pCollisionShape.getGlobalBounds().width / 2, pCollisionShape.getGlobalBounds().height / 2);
        }
        void setPosition(int x, int y) {
            pCollisionShape.setPosition(x, y);
        }
        void update(float deltaTime) {
            sf::Vector2f amplifiedVelocity = sf::Vector2f(velocity.x, velocity.y);

            pCollisionShape.move(amplifiedVelocity * deltaTime);
        }
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(pCollisionShape, states);
        }
        sf::RectangleShape pCollisionShape;
        sf::Vector2f velocity;
        float speed;
};



class Player : public sf::Drawable {
    public:
        Player() 
        {
            // default..
        }
        Player(int x, int y, sf::Vector2f collisionShapeSize) {
            pCollisionShape.setPosition(x, y);
            pCollisionShape.setSize(collisionShapeSize);
            pCollisionShape.setOrigin(pCollisionShape.getGlobalBounds().width / 2, pCollisionShape.getGlobalBounds().height / 2);
            pCollisionShape.setOutlineThickness(-2);
            pCollisionShape.setOutlineColor(sf::Color(60, 60, 60));
        }
        void setPosition(float x, float y) {
            pCollisionShape.setPosition(x, y);
        }
        sf::Vector2f getPosition() {
            return pCollisionShape.getPosition();
        }
        void move(float x, float y) {
            pCollisionShape.move(x, y);
        }
        void look_at_mouse(sf::Vector2f mouse) {
            float angle = atan2(mouse.y - pCollisionShape.getPosition().y, mouse.x - pCollisionShape.getPosition().x) * 180 / 3.14159;

            pCollisionShape.setRotation(angle);
        }   
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(pCollisionShape, states);
        }
        sf::RectangleShape pCollisionShape;
        sf::Vector2i velocity;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Survival Game");

    window.setFramerateLimit(60);

    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    sf::Vector2f map_size(window.getSize().x, window.getSize().y);
    
    std::vector<Projectile> bulletVec;
    
    Player player(window.getSize().x / 2, window.getSize().x / 2, sf::Vector2f(50, 50));
    float playerSpeed = 200;

 //   /////////// initialize GUI Elements ///////////
 //   sf::Texture alienBG_TXT;
 //   if(!alienBG_TXT.loadFromFile("alien_bg.jpg")) return(-1);
 //   sf::Sprite alienBG_S(alienBG_TXT);
 //   alienBG_S.scale(window.getSize().x / alienBG_S.getGlobalBounds().width, window.getSize().y / alienBG_S.getGlobalBounds().height);

    tgui::Theme blackTheme{"assets/nanogui.style"};

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
		Start_BTN->connect("Pressed", [&](){MainMenuScene->setVisible(false);});
    Selection_PNL->add(Start_BTN, "Start_BTN");

    auto Settings_BTN = tgui::Button::create();
    Settings_BTN->setRenderer(blackTheme.getRenderer("Button"));
    Settings_BTN->setPosition(15, 85);
    Settings_BTN->setSize(250, 50);
    Settings_BTN->setText({"Settings"});
    Selection_PNL->add(Settings_BTN, "Settings_BTN");

    auto Credits_BTN = tgui::Button::create();
    Credits_BTN->setRenderer(blackTheme.getRenderer("Button"));
    Credits_BTN->setPosition(15, 145);
    Credits_BTN->setSize(250, 50);
    Credits_BTN->setText("Credits");
    Selection_PNL->add(Credits_BTN, "Credits_BTN");

    auto Quit_BTN = tgui::Button::create();
    Quit_BTN->setRenderer(blackTheme.getRenderer("Button"));
    Quit_BTN->setPosition(15, 205);
    Quit_BTN->setSize(250, 50);
    Quit_BTN->setText("Quit");
    Selection_PNL->add(Quit_BTN, "Quit_BTN");

    ////////////////////////////////////////////////////////

    enum GUI_SCENES_ENUM {
        MENU,
				MAIN,
        SETTINGS,
        CREDITS
    };

    GUI_SCENES_ENUM GUI_SCENES;
    GUI_SCENES = MENU;

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
            case MENU:
                break;
						case MAIN:
								break;

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

        
        window.clear(sf::Color(55, 165, 105));

        for(int i = 0; i < bulletVec.size(); i++) {
            window.draw(bulletVec[i]);
        }
        
        window.draw(player);
        
    //    window.draw(alienBG_S);

        gui.draw();


        window.display();
    }



    return EXIT_SUCCESS;
}
