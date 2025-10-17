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

	//create and configure world: #IMPORTANT
	b2WorldDef wd = b2DefaultWorldDef();
	wd.gravity = { 0.0f, .0f };
	b2WorldId world = b2CreateWorld(&wd);

	sh::object player("resources/red.png"); // <- Create an object "player" & asign it an image #IMPORTANT
	player.set_type(0); // <- set type to dynamic
	player.set_density(1.0); // <- set the density
	player.create(world); // <- Create the body #IMPORTANT
	player.set_pos(0, 0, scale); // <- Set the position of the object
	player.circle(circle); // <- Add the shape #IMPORTANT

	sh::object enemy("resources/blue.png"); // <- Create an object "enemy" & asign it an image #IMPORTANT
	enemy.set_type(0); // <- set type to dynamic
	enemy.create(world); // <- Create the body #IMPORTANT
	enemy.set_pos(700, 500, scale); // <- Set the position of the object
	enemy.polygon(polygon); // <- Finalize with adding the shape #IMPORTANT
	sf::Sprite enemy_spr = enemy.get_spr();

	sh::image health("resources/flower.png"); // <- Create an image "health" #IMPORTANT
	health.set_pos(700, 0);

	sf::Clock clock;
	int player_spd = 100, enemy_spd = 15;
	float deltaTime;
	bool is_enemy_alive = true;

	while (window.isOpen()) { // <- game loop start #IMPORTANT
		deltaTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		//manage events & input: #IMPORTANT
		while (const std::optional event = window.pollEvent()) 
		{
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			if (event->is<sf::Event::KeyPressed>()) { // <- if any key is pressed
				if (sh::check_letter_down('w')) {
					player.move(0, -player_spd * deltaTime, scale);
				}if (sh::check_letter_down('s')) {
					player.move(0, player_spd * deltaTime, scale);
				}if (sh::check_letter_down('a')) {
					player.move(-player_spd * deltaTime, 0, scale);
				}if (sh::check_letter_down('d')) {
					player.move(player_spd * deltaTime, 0, scale);
				}
			}
			if (event->is<sf::Event::MouseButtonPressed>()) { // <- if any mouse button is pressed
				if (sh::click_on_sprite(0, enemy_spr, window)) {
					is_enemy_alive = false;
				}
			}
		}
		b2World_Step(world, step, 1); // <- make a step on the "physics world" #IMPORTANT
		//process data: #IMPORTANT
		diference_x = player.get_pos_x() - enemy.get_pos_x();
		diference_y = player.get_pos_y() - enemy.get_pos_y();
		if (diference_x > 0) {
			enemy.move(enemy_spd * deltaTime, 0, scale);
		}
		else if (diference_x < 0) {
			enemy.move(-enemy_spd * deltaTime, 0, scale);
		}
		if (diference_y > 0) {
			enemy.move(0, enemy_spd * deltaTime, scale);
		}
		else if (diference_y < 0) {
			enemy.move(0, -enemy_spd * deltaTime, scale);
		}
		//draw everything: #IMPORTANT
		window.clear();

		player.draw(window);
		if (is_enemy_alive) {
			enemy.draw(window);
		}
		health.draw(window);

		window.display();
	}// <- game loop end #IMPORTANT
	b2DestroyWorld(world); // <- cleanup #IMPORTANT
	return 0;
}