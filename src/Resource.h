#ifndef RESOURCE_H
#define RESOURCE_H

#include<SFML/Graphics.hpp>
#include<math.h>

class Resource : public sf::Drawable {
    public:
    Resource() {
        // default..
    }
    Resource(float x, float y, sf::Vector2f size) 
    {
        pStaticBody2DShape.setPosition(x, y);
        pStaticBody2DShape.setSize(size);
        pStaticBody2DShape.setOutlineThickness(-2);
        pStaticBody2DShape.setOutlineColor(sf::Color(0, 0, 0));
    }   
    Resource(float x, float y, sf::Vector2f size, sf::Color color, float rotation) 
    {
        pStaticBody2DShape.setPosition(x, y);
        pStaticBody2DShape.setSize(size);
        pStaticBody2DShape.setFillColor(color);
        pStaticBody2DShape.setOutlineThickness(-2);
        pStaticBody2DShape.setOutlineColor(sf::Color(0, 0, 0));
        pStaticBody2DShape.setRotation(rotation);
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
    private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(pStaticBody2DShape);
    }
    sf::RectangleShape pStaticBody2DShape;
};

#endif
