#ifndef STATICBODY2D_H
#define STATICBODY2D_H

#include<SFML/Graphics.hpp>
#include<math.h>

class StaticBody2D : public sf::Drawable {
    public:
    StaticBody2D(float x, float y, sf::Vector2f size) 
    {
        pStaticBody2DShape.setSize(size);
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

#endif
