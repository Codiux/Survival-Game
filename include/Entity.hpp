#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Entity : public sf::Drawable, sf::Transformable
{
protected:
	sf::VertexArray m_vertices;
	sf::Texture* m_texture;

public:
	enum class Body
	{
		Static,
		Kinematic,
		Dynamic
	};
};

#endif
