#ifndef PROJECTILE_H
#define PROJECTILE_H

#include<SFML/Graphics.hpp>
#include<math.h>

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

#endif
