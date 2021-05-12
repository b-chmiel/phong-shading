#ifndef PARSER_H
#define PARSER_H

#include "../lib/inih/INIReader.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <vector>

class LightSource {
public:
    sf::Color color;
    sf::Vector3f location;
    LightSource(sf::Color color, sf::Vector3f location)
        : color(color)
        , location(location) {};
};

class Config {
public:
    int pointSources;
    int radius;
    sf::Vector2i outputDimensions;
    sf::Color surface;
    sf::Color ambientLight;
    std::vector<LightSource> lightSources;
    std::string fileName;

    Config(INIReader config);
};

#endif