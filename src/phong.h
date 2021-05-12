#ifndef PHONG_H
#define PHONG_H

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

namespace phong {
class LightSource {
public:
    sf::Color color;
    sf::Vector3f location;
    LightSource(sf::Color color, sf::Vector3f location)
        : color(color)
        , location(location) {};
};

class PhongParameters {
public:
    PhongParameters() = default;
    sf::Color diffuseReflection;
    sf::Color specularReflection;
    float glossiness;
    sf::Color ambientLight;
    sf::Color ambientLightIntensity;
    sf::Color selfLuminance;
    std::vector<LightSource> lightSources;
};

sf::Color getLightIntensity(PhongParameters parameters);
}

#endif