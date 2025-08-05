#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

namespace Engine_Shifter {
	sf::Sprite load_animation_spritesheet(sf::Sprite sprite, int frame_width, int frame_height);
	sf::Sprite load_sprite(sf::Texture& tex, std::string path);
	void sprite_draw(sf::Sprite sprite, sf::RenderWindow& WINDOW);
	sf::Sprite load_tileset(sf::Sprite sprite, int tile_width, int tile_height);
	void tile_draw(sf::Sprite tilemap, sf::RenderWindow& WINDOW, int tile_width, int tile_height, int row, int column);
	std::unique_ptr<sf::Music> load_music(std::string& path);
	void music_play(std::unique_ptr<sf::Music> music);
	bool check_letter_down(char letter);
	bool click_on_sprite(int button, sf::Sprite& sprite, sf::RenderWindow& WINDOW);
	bool check_collision(sf::Sprite& spr_1, sf::Sprite& spr_2);
	bool check_other_down(int key_id);
}