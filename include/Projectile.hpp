#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

class Projectile : public sf::Drawable {
    public:
        Projectile();
        Projectile(int x, int y, sf::Vector2f collisionSize, sf::Vector2i mouse, float speed);
        
				void setSize(sf::Vector2f size);
        void setPosition(int x, int y);

        void update(float deltaTime);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
				sf::RectangleShape pCollisionShape;
        sf::Vector2f velocity;

        float speed;
};

#endif
