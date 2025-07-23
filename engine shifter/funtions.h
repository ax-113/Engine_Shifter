#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
void randomize();

sf::Sprite load_animation_spritesheet(sf::Sprite sprite, int frame_width, int frame_height);
void animation_draw(int amount_sprites_in_column, int row_to_draw, int frame_width, int frame_height, sf::Sprite sprite, float maxTime, sf::RenderWindow WINDOW, int timer, int temp_val);
sf::Texture load_sprite(std::string path);
void sprite_draw(sf::Sprite sprite, sf::RenderWindow& WINDOW);
sf::Sprite load_tileset(sf::Sprite sprite, int tile_width, int tile_height);
void tile_draw(sf::Sprite tilemap, sf::RenderWindow& WINDOW, int tile_width, int tile_height, int row, int column);
std::unique_ptr<sf::Music> load_music(std::string& path);
void music_play(std::unique_ptr<sf::Music> music);
bool check_letter_down(char letter);
bool click_on_sprite(int button, sf::Sprite& sprite, sf::RenderWindow& WINDOW);
bool check_collision(sf::Sprite& spr_1, sf::Sprite& spr_2);
bool check_other_down(int key_id);