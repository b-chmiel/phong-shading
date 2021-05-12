#ifndef PARSER_H
#define PARSER_H

#include "../lib/inih/INIReader.h"
#include "phong.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <vector>

class Config {
public:
    int pointSources;
    sf::Vector2i outputDimensions;
    std::string fileName;
    int radius;
    phong::PhongParameters params;
    sf::Color background;

    Config(INIReader config);
};

#endif