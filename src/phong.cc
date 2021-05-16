#include "phong.h"
#include "preciseColor.h"
#include "vectorUtils.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

using namespace phong;

PhongShading::PhongShading(PhongParameters params, sf::Vector3f position)
    : params(params)
    , position(position) {};

PreciseColor PhongShading::computeColor(PreciseColor& selfLuminance)
{
    PreciseColor ka = params.ambientLight;
    PreciseColor Ac = params.ambientLightIntensity;

    return selfLuminance + diffuse() + specular() + ka * Ac;
}

PreciseColor PhongShading::diffuse()
{
    auto lights = PhongShading::params.lightSources;
    auto N = getUnitSurface();
    auto kd = PhongShading::params.diffuseReflection;

    auto sum = [&](PreciseColor total, LightSource light) {
        auto I = utils::unitVector(light.location - PhongShading::position);
        auto dot = std::max(utils::dotProduct(N, I), 0.0f);
        return total + lightAttenuation(light) * light.color * dot;
    };

    return kd * std::accumulate(lights.begin(), lights.end(), PreciseColor(), sum);
}

PreciseColor PhongShading::specular()
{
    Vector3f observerLocation(0, 0, -1);
    auto lights = PhongShading::params.lightSources;
    auto ks = PhongShading::params.specularReflection;
    auto g = PhongShading::params.glossiness;
    auto Os = reflectedObserverUnitVector(observerLocation);

    auto sum = [&](PreciseColor total, LightSource light) {
        auto I = utils::unitVector(light.location - PhongShading::position);
        auto dot = std::max(utils::dotProduct(I, Os), 0.0f);
        return total + lightAttenuation(light) * light.color * pow(dot, g);
    };

    return ks * std::accumulate(lights.begin(), lights.end(), PreciseColor(), sum);
}

float PhongShading::lightAttenuation(LightSource source)
{
    auto r = utils::distanceBetweenPoints(source.location, PhongShading::position);
    auto c0 = PhongShading::params.attenuation.c0;
    auto c1 = PhongShading::params.attenuation.c1;
    auto c2 = PhongShading::params.attenuation.c2;

    return std::min(1 / (c2 * r * r + c1 * r + c0), 1.0f);
}

sf::Vector3f PhongShading::getUnitSurface()
{
    float x = PhongShading::position.x / params.distance;
    float y = PhongShading::position.y / params.distance;
    float z = PhongShading::position.z / params.distance;

    return sf::Vector3f(x, y, z);
}

sf::Vector3f PhongShading::reflectedObserverUnitVector(sf::Vector3f observer)
{
    auto surfaceUnit = getUnitSurface();
    auto surfaceObserver = utils::unitVector(observer - PhongShading::position);
    auto specularyReflect = surfaceObserver - 2 * (utils::dotProduct(surfaceObserver, surfaceUnit)) * surfaceUnit;

    return specularyReflect;
}