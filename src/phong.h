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

class LightAttenuation {
public:
    float c0;
    float c1;
    float c2;
    LightAttenuation() = default;
    LightAttenuation(float c0, float c1, float c2)
        : c0(c0)
        , c1(c1)
        , c2(c2) {};
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
    LightAttenuation attenuation;
};

class PhongShading {
public:
    PhongShading(PhongParameters params, sf::Vector3f position);

    PreciseColor computeColor();

private:
    PhongParameters params;
    sf::Vector3f position;

    PreciseColor diffuse();
    PreciseColor specular();
    float lightAttenuation(LightSource source);
    sf::Vector3f getUnitSurface();
    sf::Vector3f reflectedObserverUnitVector(sf::Vector3f observer);
};

}

#endif