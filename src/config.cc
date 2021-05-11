#include "config.h"
#include "../lib/inih/INIReader.h"
#include "SFML/System/Vector2.hpp"
#include <sstream>

int getPointSources(INIReader config)
{
    return config.GetInteger("main", "pointSources", -1);
}

sf::Vector2i getDimensions(INIReader config)
{
    int width = config.GetInteger("main", "outputWidth", -1);
    int height = config.GetInteger("main", "outputHeight", -1);
    return sf::Vector2i(width, height);
}

std::string getFileName(INIReader config)
{
    return config.Get("main", "fileName", "UNKNOWN");
}

int getRadius(INIReader config)
{
    return config.GetInteger("main", "radius", -1);
}

sf::Color parseColor(INIReader config, std::string section)
{
    int red = config.GetInteger(section, "red", 0);
    int green = config.GetInteger(section, "green", 0);
    int blue = config.GetInteger(section, "blue", 0);
    int alpha = config.GetInteger(section, "alpha", 255);

    return sf::Color(red, green, blue, alpha);
}

LightSource getLightSource(INIReader config, std::string section)
{
    auto color = parseColor(config, section);
    int x = config.GetFloat(section, "x", 10);
    int y = config.GetFloat(section, "y", 10);

    sf::Vector2f location(x, y);

    return LightSource(color, location);
}

std::vector<LightSource> getLightSources(INIReader config, int sources)
{
    std::vector<LightSource> result;
    for (int i = 0; i < sources; i++) {
        std::stringstream ss;
        ss << "light" << i;

        result.push_back(getLightSource(config, ss.str()));
    }

    return result;
}

Config::Config(INIReader config)
{
    Config::pointSources = getPointSources(config);
    Config::outputDimensions = getDimensions(config);
    Config::fileName = getFileName(config);
    Config::radius = getRadius(config);
    Config::surface = parseColor(config, "sphereSurface");
    Config::ambientLight = parseColor(config, "ambientLight");
    Config::lightSources = getLightSources(config, Config::pointSources);
}
