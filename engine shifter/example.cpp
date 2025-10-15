#include <SFML/Audio.hpp> // audio #IMPORTANT
#include <SFML/Graphics.hpp> // graphics #IMPORTANT
#include <box2d/box2d.h> //physics #IMPORTANT
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include "engine_shifter.h" //engine #IMPORTANT

const int scale = 20;

int main() {
	//declare variables:
	std::string window_name = "Example";
	float step = 1.0f / 60.0f;
	b2Circle circle;
	circle.radius = 2.0f;
	b2Polygon polygon = b2MakeBox(5.0f, 5.0f);
	float diference_x, diference_y;

	sf::RenderWindow window(sf::VideoMode({800,600}), window_name); // <- create window #IMPORTANT
	//prepare stuff:

	//create and configure world:
	b2WorldDef wd = b2DefaultWorldDef();
	wd.gravity = { 0.0f, -10.0f };
	b2WorldId world = b2CreateWorld(&wd);

	sh::object player; // <- Create an object "player" #IMPORTANT
	player.set_type(0); // <- set type to dynamic
	player.set_density(1.0); // <- set the density
	player.set_image("resources/red.png"); // <- set image #IMPORTANT
	player.create(world); // <- Create the body #IMPORTANT
	player.set_pos(0, 0, scale); // <- Set the position of the object
	player.circle(circle); // <- Add the shape #IMPORTANT

	sh::object enemy; // <- Create an object "enemy" #IMPORTANT
	enemy.set_type(0); // <- set type to dynamic
	enemy.set_image("resources/blue.png"); // <- set image #IMPORTANT
	enemy.create(world); // <- Create the body #IMPORTANT
	enemy.set_pos(100, 100, scale); // <- Set the position of the object
	enemy.polygon(polygon); // <- Finalize with adding the shape #IMPORTANT

	sh::image health; // <- Create an image "health" #IMPORTANT
	health.set_image("resources/flower.png"); // <- set image #IMPORTANT
	health.set_pos(-100, -100);

	while (window.isOpen()) { // <- game loop start #IMPORTANT
		//manage events & input: #IMPORTANT
		while (const std::optional event = window.pollEvent()) 
		{
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			if (event->is<sf::Event::KeyPressed>()) { // <- if any key is pressed
				if (sh::check_letter_down('w')) {
					player.move(0, 1, scale);
				}if (sh::check_letter_down('s')) {
					player.move(0, -1, scale);
				}if (sh::check_letter_down('a')) {
					player.move(-1, 0, scale);
				}if (sh::check_letter_down('d')) {
					player.move(1, 0, scale);
				}
			}
		}
		b2World_Step(world, step, 1); // <- make a step on the "physics world" #IMPORTANT
		//process data: #IMPORTANT
		diference_x = player.get_pos_x() - enemy.get_pos_x();
		diference_y = player.get_pos_y() - enemy.get_pos_y();
		if (diference_x > 0) {
			enemy.move(1, 0, scale);
		}
		else if (diference_x < 0) {
			enemy.move(-1, 0, scale);
		}
		if (diference_y > 0) {
			enemy.move(0, 1, scale);
		}
		else if (diference_y < 0) {
			enemy.move(0, -1, scale);
		}

		//draw everything: #IMPORTANT
		window.clear();

		player.draw(window);
		enemy.draw(window);
		health.draw(window);

		window.display();
	}// <- game loop end #IMPORTANT
	b2DestroyWorld(world); // <- cleanup #IMPORTANT
	return 0;
}