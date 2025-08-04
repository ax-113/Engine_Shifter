#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "funtions.h"
#include <iostream>
#include <cmath>
#include <enet/enet.h>
#include <cstring>

int main()
{
    bool multiplayer = false;

    if (!multiplayer)
    {
        int gameWidth = 512; //game width in pixel size
        int gameHeight = 288; //game height in pixel size
        std::string name = "Game 1"; //game name
        std::string icon_path = "resources/flower.png"; // change the window icon (full path)
        //if you want a camera use this
        int cameraWidth = gameWidth; //camera width in pixel size
        int cameraHeight = gameHeight; //camera height in pixel size
        sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), name);

        sf::Image icon;
        if (!icon.loadFromFile(icon_path)) { std::cerr << "Failed to load image" << icon_path; }
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        sf::View camara(sf::FloatRect(0, 0, cameraWidth, cameraHeight));

        sf::Sprite red;
        sf::Texture red_tex = Engine_Shifter::load_sprite("resources/red.png");
        red.setTexture(red_tex);
        sf::Sprite blue;
        sf::Texture blue_tex = load_sprite("resources/blue.png");
        blue.setTexture(blue_tex);

        red.setPosition(gameWidth / 2.0f, gameHeight / 2.0f);
        blue.setPosition(gameWidth / 2.0f + 120.0f, gameHeight / 2.0f);
        float speed = 0.1;

        while (window.isOpen())
        {
            window.setView(camara);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (check_letter_down('d')) { red.move(speed, 0); }
            if (check_letter_down('a')) { red.move(-speed, 0); }
            if (check_letter_down('s')) { red.move(0, speed); }
            if (check_letter_down('w')) { red.move(0, -speed); }

            if (check_other_down(4)) { blue.move(speed, 0); }
            if (check_other_down(3)) { blue.move(-speed, 0); }
            if (check_other_down(2)) { blue.move(0, speed); }
            if (check_other_down(1)) { blue.move(0, -speed); }

            window.clear();
            sprite_draw(red, window);
            sprite_draw(blue, window);
            window.display();
        }
    }
    if (multiplayer)
    {
        char type = 'x';
        int gameWidth = 512;
        int gameHeight = 288;
        std::string name = "MULTIPLAYER";
        std::string icon_path = "resources/flower.png";
        int cameraWidth = gameWidth;
        int cameraHeight = gameHeight;
        bool blue_connected = false;
        sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), name);
        sf::Image icon;
        if (!icon.loadFromFile(icon_path)) { std::cerr << "Failed to load image" << icon_path; }
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        sf::View camara(sf::FloatRect(0, 0, cameraWidth, cameraHeight));
        
        bool onetime = true;
        
        sf::Sprite red;
        sf::Texture red_tex = load_sprite("resources/red.png");
        sf::Texture blue_tex = load_sprite("resources/blue.png");
        red.setTexture(red_tex);
        sf::Sprite button1;
        button1.setTexture(red_tex);
        sf::Sprite button2;
        button2.setTexture(blue_tex);

        const char* ip = ""; // FILL ====================================
        const int port = 1234; // FILL ==================================

        while (window.isOpen())
        {
            window.setView(camara);

            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            window.clear();

            window.display();
            if (type == 'c')
            {
                ENetAddress address;
                ENetEvent enet_event;
                ENetPeer* peer = nullptr;
                ENetHost* client = nullptr;
                if (onetime)
                {
                    window.setTitle("Client");
                    if (enet_initialize() != 0)
                    {
                        std::cerr << "failed to initialize enet on CLIENT\n";
                        return EXIT_FAILURE;
                    }
                    atexit(enet_deinitialize);

                    client = enet_host_create(NULL, 1, 1, 0, 0);
                    if (client == NULL)
                    {
                        std::cerr << "failed to create CLIENT\n";
                        return EXIT_FAILURE;
                    }
                    else { std::cerr << "Client Created succesfully\n"; }

                    enet_address_set_host(&address, ip);
                    address.port = port;

                    peer = enet_host_connect(client, &address, 1, 0);
                    if (peer == NULL)
                    {
                        std::cerr << "failed to connect\n";
                        return EXIT_FAILURE;
                    }

                    enet_host_flush(client);

                    if (enet_host_service(client, &enet_event, 5000) > 0 && enet_event.type == ENET_EVENT_TYPE_CONNECT)
                    {
                        std::cerr << "Conected succesfully\n";
                    }
                    else
                    {
                        enet_peer_reset(peer);
                        std::cerr << "Failed to connect\n";
                    }
                    onetime = false;
                }
                while (enet_host_service(client, &enet_event, 1000) > 0)
                {
                    switch (enet_event.type)
                    {
                    case ENET_EVENT_TYPE_RECEIVE:
                        break;
                    }
                    window.display();
                }
                enet_peer_disconnect(peer, 0);
                while (enet_host_service(client, &enet_event, 3000) > 0)
                {
                    switch (enet_event.type)
                    {
                    case ENET_EVENT_TYPE_RECEIVE:
                        enet_packet_destroy(enet_event.packet);
                        break;
                    case ENET_EVENT_TYPE_DISCONNECT:
                        std::cerr << "Disconnection succeded\n";
                    }
                }
            }
            if (type == 's')
            {
                ENetEvent enet_event;
                ENetHost* server = nullptr;
                ENetAddress address;
                if (onetime)
                {
                    window.setTitle("Server");
                    if (enet_initialize() != 0)
                    {
                        std::cerr << "failed to initialize enet on server\n";
                        return EXIT_FAILURE;
                    }
                    else
                    {
                        std::cerr << "server created\n";
                    }
                    atexit(enet_deinitialize);


                    address.host = ENET_HOST_ANY;
                    address.port = port;


                    server = enet_host_create(&address, 2, 1, 0, 0);
                    if (server == NULL)
                    {
                        std::cerr << "failed to start server";
                        return EXIT_FAILURE;
                    }
                    else
                    {
                        std::cerr << "server started\n";
                    }
                    onetime = false;
                }
                while (window.isOpen())
                {

                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }
                    window.clear();
                    window.display();
                }
                while (enet_host_service(server, &enet_event, 1000) > 0)
                {
                    switch (enet_event.type)
                    {
                    case ENET_EVENT_TYPE_CONNECT:

                    case ENET_EVENT_TYPE_RECEIVE:
                        enet_packet_destroy(enet_event.packet);
                        break;
                    case ENET_EVENT_TYPE_DISCONNECT:
                        std::cerr << "Disconnection succeded\n";
                    }
                }
                enet_host_destroy(server);
            }
        }

        return EXIT_SUCCESS;
    }
}