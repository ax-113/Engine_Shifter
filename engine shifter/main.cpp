#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <enet/enet.h>
#include <cstring>
#include <chipmunk/chipmunk.h>
#include "engine_shifter.h"

int main()
{
    int gameWidth = 512;
    int gameHeight = 288;
    std::string name = "Game 3";
    std::string icon_path = "resources/flower.png";
    int cameraWidth = gameWidth;
    int cameraHeight = gameHeight;
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), name);

    sf::Image icon;
    if (!icon.loadFromFile(icon_path)) { std::cerr << "Failed to load image" << icon_path; }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::View camara(sf::FloatRect(0, 0, cameraWidth, cameraHeight));

    while (window.isOpen())
    {
        window.setView(camara);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        window.display();
    }
}