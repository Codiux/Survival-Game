#include "Player.hpp"

#include <math.h>

Player::Player() 
{
		// default..
}

Player::Player(int x, int y, sf::Vector2f collisionShapeSize) {
		pCollisionShape.setPosition(x, y);
  	pCollisionShape.setSize(collisionShapeSize);
    pCollisionShape.setOrigin(pCollisionShape.getGlobalBounds().width / 2, pCollisionShape.getGlobalBounds().height / 2);
		pCollisionShape.setOutlineThickness(-2);
		pCollisionShape.setOutlineColor(sf::Color(60, 60, 60));
}

void Player::setPosition(float x, float y) {
		pCollisionShape.setPosition(x, y);
}

sf::Vector2f Player::getPosition() {
		return pCollisionShape.getPosition();
}

void Player::move(float x, float y) {
		pCollisionShape.move(x, y);
}

void Player::look_at_mouse(sf::Vector2f mouse) {
    float angle = atan2(mouse.y - pCollisionShape.getPosition().y, mouse.x - pCollisionShape.getPosition().x) * 180 / 3.14159;

  	pCollisionShape.setRotation(angle);
}   

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
		target.draw(pCollisionShape, states);
}
