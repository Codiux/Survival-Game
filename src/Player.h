#ifndef PLAYER_H
#define PLAYER_H

#include<SFML/Graphics.hpp>
#include<math.h>

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
        sf::FloatRect getGlobalBounds() {
            return pCollisionShape.getGlobalBounds();
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

#endif
