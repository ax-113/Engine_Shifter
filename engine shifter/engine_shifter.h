#pragma once
#include <SFML/Audio.hpp> // audio
#include <SFML/Graphics.hpp> // graphics
#include <box2d/box2d.h> //physics
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>

namespace Engine_Shifter {
	sf::Sprite load_animation_spritesheet(sf::Sprite sprite, int frame_width, int frame_height);
	void sprite_draw(sf::Sprite sprite, sf::RenderWindow& WINDOW);
	sf::Sprite load_tileset(sf::Sprite sprite, int tile_width, int tile_height);
	void tile_draw(sf::Sprite tilemap, sf::RenderWindow& WINDOW, int tile_width, int tile_height, int row, int column);
	std::unique_ptr<sf::Music> load_music(std::string& path);
	void music_play(std::unique_ptr<sf::Music> music);
	bool check_letter_down(char letter);
	bool click_on_sprite(int button, sf::Sprite& sprite, sf::RenderWindow& WINDOW);
	bool check_other_down(int key_id);
}

class object {
public:
	void set_type(int type);
	void set_density();
	void circle(b2Circle circle);
	void polygon(b2Polygon polygon);
	void set_pos(float x, float y);
	float get_pos_x();
	float get_pos_y();
	void move(float x, float y);
	void set_image(std::string path);
	void draw(sf::RenderWindow window);
};
class image {
public:
	void set_image(std::string path);
	sf::Sprite get_image();
	void draw(sf::RenderWindow window);
};