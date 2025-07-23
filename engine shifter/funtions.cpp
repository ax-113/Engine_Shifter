#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include "funtions.h"

void randomize() {
	std::srand(static_cast<unsigned int>(std::time(NULL)));
}

sf::Sprite load_animation_spritesheet(sf::Sprite sprite, int frame_width, int frame_height) {
	sprite.setTextureRect({ {0,0},{frame_width,frame_height} });
	sprite.setOrigin({ sprite.getTextureRect().width / 2.0f, sprite.getTextureRect().height / 2.0f });
	return sprite;
}	 

void animation_draw(int amount_sprites_in_column, int row_to_draw, int frame_width, int frame_height, sf::Sprite sprite, float maxTime, sf::RenderWindow WINDOW, int timer, int temp_val) {
	timer += 0.1;
	if (timer >= maxTime) {
		temp_val += frame_width;
		if (temp_val >= row_to_draw * frame_width) {
			temp_val = 0;
		}
		else {
			sprite.setTextureRect({ {row_to_draw * frame_width, amount_sprites_in_column * frame_height},{frame_width, frame_height} });

		}
	}
	WINDOW.draw(sprite);
}

sf::Texture load_sprite(std::string path)
{
	sf::Texture tex;
	if (!tex.loadFromFile(path)) { std::cerr << "Failed to load texture" << path; }
	return tex;
}

void sprite_draw(sf::Sprite sprite, sf::RenderWindow& WINDOW)
{
	WINDOW.draw(sprite);
}

sf::Sprite load_tileset(sf::Sprite sprite, int tile_width, int tile_height)
{
	sprite.setTextureRect({ {0,0},{tile_width,tile_height} });
	sprite.setOrigin({ sprite.getTextureRect().width / 2.0f, sprite.getTextureRect().height / 2.0f });
	return sprite;
}

void tile_draw(sf::Sprite tilemap, sf::RenderWindow& WINDOW, int tile_width, int tile_height, int row, int column)
{
	tilemap.setTextureRect({ {row * tile_width, column * tile_height},{tile_width, tile_height} });
	WINDOW.draw(tilemap);
}

std::unique_ptr<sf::Music> load_music(std::string& path) {
	auto music = std::make_unique<sf::Music>();
	if (!music->openFromFile(path)) { std::cerr << "Failed to load music: " << path; }
	return music;
}

void music_play(std::unique_ptr<sf::Music> music)
	{
		if (music->getStatus() != sf::SoundSource::Playing)
		{
			music->play();
		}
	}

bool check_letter_down(char letter)
{
		if (letter >= 'a' && letter <= 'z')
			letter = letter - 'a' + 'A';

		if (letter >= 'A' && letter <= 'Z') {
			sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(sf::Keyboard::A + (letter - 'A'));
			return sf::Keyboard::isKeyPressed(key);
		}
		return false;
}

bool click_on_sprite(int button, sf::Sprite& sprite, sf::RenderWindow& WINDOW) 
{
	sf::Vector2i mouse_position = sf::Mouse::getPosition(WINDOW);
	sf::Mouse::Button temp;
	switch (button) {
	case (1):
		temp = sf::Mouse::Button::Left;
		break;
	case (2):
		temp = sf::Mouse::Button::Right;
		break;
	case (3):
		temp = sf::Mouse::Button::Middle;
		break;
	}
	
	if (sf::Mouse::isButtonPressed(temp) && sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_position)))
	{
		return true;
	}

}

bool check_collision(sf::Sprite& spr_1, sf::Sprite& spr_2)
{
	return spr_1.getGlobalBounds().intersects(spr_2.getGlobalBounds());
}	

bool check_other_down(int key_id)
{
	switch (key_id)
	{
	case 1:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		break;
	case 2:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
		break;
	case 3:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		break;
	case 4:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		break;
	case 5:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
		break;
	case 6:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
		break;
	case 7:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Tab);
		break;
	case 8:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
		break;
	case 9:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
		break;
	}
	return false;
}

