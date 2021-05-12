#include "phong.h"

using namespace phong;

sf::Color getLightIntensity(PhongParameters parameters)
{
    sf::Color S = parameters.selfLuminance;
    sf::Color kd = parameters.diffuseReflection;
    sf::Color ks = parameters.specularReflection;
    sf::Color ka = parameters.ambientLight;
    sf::Color Ac = parameters.ambientLightIntensity;
    float g = parameters.glossiness;

    return S + ka * Ac;
}