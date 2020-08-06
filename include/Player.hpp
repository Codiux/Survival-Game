#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {
    public:
        Player(); 
        Player(int x, int y, sf::Vector2f collisionShapeSize);
        
				void setPosition(float x, float y);
        sf::Vector2f getPosition();
        
				void move(float x, float y);

        void look_at_mouse(sf::Vector2f mouse);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
				sf::RectangleShape pCollisionShape;
        sf::Vector2i velocity;
};

#endif
