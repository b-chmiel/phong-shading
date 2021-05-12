#ifndef PHONG_H
#define PHONG_H

#include "preciseColor.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

namespace phong {

class LightSource {
public:
    PreciseColor color;
    sf::Vector3f location;
    LightSource(PreciseColor color, sf::Vector3f location)
        : color(color)
        , location(location) {};
};

class PhongParameters {
public:
    PhongParameters() = default;
    PreciseColor diffuseReflection;
    PreciseColor specularReflection;
    float glossiness;
    PreciseColor ambientLight;
    PreciseColor ambientLightIntensity;
    PreciseColor selfLuminance;
    std::vector<LightSource> lightSources;
    float distance;
};

PreciseColor computeColor(sf::Vector3f intersection, PhongParameters params);

}

#endif