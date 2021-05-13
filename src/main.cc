#include "../lib/inih/INIReader.h"
#include "config.h"
#include "draw.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <filesystem>
#include <iostream>

std::optional<Config> getConfig(int argc, char** argv)
{
    if (argc == 2 && std::filesystem::exists(argv[1])) {
        INIReader reader(argv[1]);
        return Config(reader);
    }

    return std::nullopt;
}

int main(int argc, char** argv)
{
    auto config = getConfig(argc, argv);
    if (!config) {
        printf("Cannot fetch config!\n");
        return 1;
    }

    sf::RenderWindow window;
    window.create(sf::VideoMode(config->outputDimensions.x, config->outputDimensions.y), "Phong shading");

    sf::Texture texture;
    texture.create(config->outputDimensions.x, config->outputDimensions.y);
    sf::Sprite sprite(texture);
    draw::printRender(*config, &texture);

    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
