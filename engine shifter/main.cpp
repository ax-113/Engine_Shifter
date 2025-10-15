#include <SFML/Audio.hpp> // audio
#include <SFML/Graphics.hpp> // graphics
#include <box2d/box2d.h> //physics
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>

int main() {
	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");



	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear();

		window.display();
	}
	return 0;
}