#include "config.h"
#include "../lib/inih/INIReader.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"
#include <sstream>

int getPointSources(INIReader config);
sf::Vector2i getDimensions(INIReader config);
std::string getFileName(INIReader config);
int getRadius(INIReader config);
phong::PhongParameters getPhongParams(INIReader config, int pointSources);
float getGlossiness(INIReader config);
sf::Color parseColor(INIReader config, std::string section);
phong::LightSource getLightSource(INIReader config, std::string section);
std::vector<phong::LightSource> getLightSources(INIReader config, int sources);

Config::Config(INIReader config)
{
    Config::pointSources = getPointSources(config);
    Config::outputDimensions = getDimensions(config);
    Config::fileName = getFileName(config);
    Config::radius = getRadius(config);
    Config::params = getPhongParams(config, Config::pointSources);
    Config::background = parseColor(config, "background");
}

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

phong::PhongParameters getPhongParams(INIReader config, int pointSources)
{
    auto result = phong::PhongParameters();

    result.diffuseReflection = parseColor(config, "diffuseReflection");
    result.specularReflection = parseColor(config, "specularReflection");
    result.glossiness = getGlossiness(config);
    result.ambientLight = parseColor(config, "ambientLight");
    result.ambientLightIntensity = parseColor(config, "ambientLightIntensity");
    result.selfLuminance = parseColor(config, "selfLuminance");
    result.lightSources = getLightSources(config, pointSources);

    return result;
}

float getGlossiness(INIReader config)
{
    return config.GetFloat("glossiness", "g", 0);
}

sf::Color parseColor(INIReader config, std::string section)
{
    int red = config.GetInteger(section, "red", 0);
    int green = config.GetInteger(section, "green", 0);
    int blue = config.GetInteger(section, "blue", 0);
    int alpha = config.GetInteger(section, "alpha", 255);

    return sf::Color(red, green, blue, alpha);
}

phong::LightSource getLightSource(INIReader config, std::string section)
{
    auto color = parseColor(config, section);
    int x = config.GetFloat(section, "x", 10);
    int y = config.GetFloat(section, "y", 10);
    int z = config.GetFloat(section, "z", 10);

    sf::Vector3f location(x, y, z);

    return phong::LightSource(color, location);
}

std::vector<phong::LightSource> getLightSources(INIReader config, int sources)
{
    std::vector<phong::LightSource> result;
    for (int i = 0; i < sources; i++) {
        std::stringstream ss;
        ss << "light" << i;

        result.push_back(getLightSource(config, ss.str()));
    }

    return result;
}