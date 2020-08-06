#include "Projectile.hpp"

#include <SFML/Graphics.hpp>

#include <math.h>
#include <iostream>

Projectile::Projectile() {
  //default
}

Projectile::Projectile(int x, int y, sf::Vector2f collisionSize, sf::Vector2i mouse, float speed) {
	pCollisionShape.setPosition(x, y);
	pCollisionShape.setSize(collisionSize);

	pCollisionShape.setOrigin(pCollisionShape.getGlobalBounds().width / 2, pCollisionShape.getGlobalBounds().height / 2);

	sf::Vector2f distance(mouse.x - pCollisionShape.getPosition().x, mouse.y - pCollisionShape.getPosition().y);
			
	float length = sqrt(distance.x * distance.x + distance.y * distance.y);

	velocity = (distance / length) * speed;
}

void Projectile::setSize(sf::Vector2f size) {
  pCollisionShape.setSize(size);
  pCollisionShape.setOrigin(pCollisionShape.getGlobalBounds().width / 2, pCollisionShape.getGlobalBounds().height / 2);
}

void Projectile::setPosition(int x, int y) {
		pCollisionShape.setPosition(x, y);
}

void Projectile::update(float deltaTime) {
		sf::Vector2f amplifiedVelocity = sf::Vector2f(velocity.x, velocity.y);

		pCollisionShape.move(amplifiedVelocity * deltaTime);

		std::cout << "x = " << amplifiedVelocity.x << ", y = " << amplifiedVelocity.y << std::endl;
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
		target.draw(pCollisionShape, states);
}
