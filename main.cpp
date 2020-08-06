#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Tily.h"

int main()
{
	sf::RenderWindow wnd;
	wnd.create(sf::VideoMode(800, 600), "TileTest");

	ty::Settings::TileSize = 64;
	ty::Settings::TextureSize = 512;
	ty::Settings::ChunkWidth = 16;
	ty::Settings::ChunkHeight = 16;

	ty::Map map;
	map.Create(320, 160, 2); // create 320*160 map with 2 layers (background and foreground)

	sf::Texture fg, bg;
	fg.loadFromFile("fg.png");
	bg.loadFromFile("bg.png");

	sf::Event event;

	while (wnd.isOpen()) {
		while (wnd.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				wnd.close();
			else if (event.type == sf::Event::Resized)
				wnd.setView(sf::View(sf::FloatRect(0, 0, wnd.getSize().x, wnd.getSize().y)));
			else if (event.type == sf::Event::KeyPressed) {
				// move the view around
				int dx = (event.key.code == sf::Keyboard::Right) - (event.key.code == sf::Keyboard::Left);
				int dy = (event.key.code == sf::Keyboard::Down) - (event.key.code == sf::Keyboard::Up);

				sf::View v = wnd.getView();
				v.move(dx*ty::Settings::TileSize, dy*ty::Settings::TileSize);
				wnd.setView(v);
			}
		}

		// place blocks button press
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mp = sf::Mouse::getPosition(wnd);
			sf::Vector2f ap = wnd.mapPixelToCoords(mp);
			map.Set(ap.x / ty::Settings::TileSize, ap.y / ty::Settings::TileSize, 1, sf::Mouse::isButtonPressed(sf::Mouse::Left));
		}


		wnd.clear();
		map.DrawLayer(0, wnd, sf::RenderStates(&bg));	// draw background
		map.DrawLayer(1, wnd, sf::RenderStates(&fg));	// draw foreground
		wnd.display();
	}

	return 0;
}

