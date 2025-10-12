#include <SFML/Audio.hpp> // audio
#include <SFML/Graphics.hpp> // graphics
#include <box2d/box2d.h> //physics
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include "engine_shifter.h"

//classes
class object {
private:
	b2BodyDef bd = b2DefaultBodyDef();
	b2BodyId bd_id;
	b2ShapeDef shapeDef = b2DefaultShapeDef();
	sf::Texture tex;
	sf::Sprite spr;
	b2ShapeDef sd = b2DefaultShapeDef();
	b2ShapeId sh_id;
public:
	void set_type(int type) {
		switch (type) {
		case 0:
			bd.type = b2_dynamicBody;
			break;
		case 1:
			bd.type = b2_staticBody;
			break;
		case 2:
			bd.type = b2_kinematicBody;
			break;
		}
	}
	void set_density() {
		sd.density = 1.0f;
	}
	void circle(b2Circle circle) {
		b2CreateCircleShape(bd_id, &sd, &circle);
	}
	void polygon(b2Polygon polygon) {
		b2CreatePolygonShape(bd_id, &sd, &polygon);
	}
	void set_pos(float x, float y) {
		bd.position = b2Vec2{ x, y };
		spr.setPosition({ x,y });
	}
	float get_pos_x() {
		return bd.position.x;
	}
	float get_pos_y() {
		return bd.position.y;
	}
	void move(float x, float y) {
		bd.position = b2Vec2{ bd.position.x + x, bd.position.y + y };
		spr.move({ x, y });
	}
	void set_image(std::string path) {
		tex.loadFromFile(path);
		spr.setTexture(tex);
	}
	void draw(sf::RenderWindow window) {
		window.draw(spr);
	}
};
class image {
private:
	sf::Texture tex;
	sf::Sprite spr;
public:
	void set_image(std::string path){
		tex.loadFromFile(path);
		spr.setTexture(tex);
	}
	sf::Sprite get_image() {
		return spr;
	}
	void draw(sf::RenderWindow window) {
		window.draw(spr);
	}
};

//functions
namespace Engine_Shifter
{
	sf::Sprite load_animation_spritesheet(sf::Sprite sprite, int frame_width, int frame_height) {
		sprite.setTextureRect({ {0,0},{frame_width,frame_height} });
		sprite.setOrigin({ sprite.getTextureRect().size.x / 2.0f, sprite.getTextureRect().size.y / 2.0f });
		return sprite;
	}

	void sprite_draw(sf::Sprite sprite, sf::RenderWindow& WINDOW)
	{
		WINDOW.draw(sprite);
	}

	sf::Sprite load_tileset(sf::Sprite sprite, int tile_width, int tile_height)
	{
		sprite.setTextureRect({ {0,0},{tile_width,tile_height} });
		sprite.setOrigin({ sprite.getTextureRect().size.x / 2.0f, sprite.getTextureRect().size.y / 2.0f });
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
		music->play();
	}

	bool check_letter_down(char letter)
	{
		if (letter >= 'a' && letter <= 'z')
			letter = letter - 'a' + 'A';

		if (letter >= 'A' && letter <= 'Z') {
			sf::Keyboard::Scancode key = static_cast<sf::Keyboard::Scan>(static_cast<int>(sf::Keyboard::Scancode::A) + (letter - 'A'));
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

	bool check_other_down(int key_id)
	{
		switch (key_id)
		{
		case 1:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up);
			break;
		case 2:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down);
			break;
		case 3:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left);
			break;
		case 4:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right);
			break;
		case 5:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl);
			break;
		case 6:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift);
			break;
		case 7:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Tab);
			break;
		case 8:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter);
			break;
		case 9:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape);
			break;
		case 10:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space);
			break;
		}
		return false;
	}
}