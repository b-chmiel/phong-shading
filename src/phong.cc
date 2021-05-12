#include "phong.h"
#include "preciseColor.h"
#include "utils.h"
#include <algorithm>
#include <numeric>

using namespace phong;

PreciseColor diffuse(PhongParameters params, sf::Vector3f location);
PreciseColor specular(PhongParameters params);
float lightAttenuation(LightSource source, sf::Vector3f currentPosition);
sf::Vector3f getUnitSurface(sf::Vector3f location, PhongParameters params);

PreciseColor phong::computeColor(sf::Vector3f location, PhongParameters params)
{
    PreciseColor S = params.selfLuminance;
    PreciseColor kd = params.diffuseReflection;
    PreciseColor ks = params.specularReflection;
    PreciseColor ka = params.ambientLight;
    PreciseColor Ac = params.ambientLightIntensity;
    float g = params.glossiness;

    auto result = S + diffuse(params, location) + specular(params) + ka * Ac;
    return result;
}

PreciseColor diffuse(PhongParameters params, sf::Vector3f location)
{
    auto list = params.lightSources;
    auto N = getUnitSurface(location, params);
    auto kd = params.diffuseReflection;
    auto lambda = [&](PreciseColor total, LightSource light) {
        auto I = utils::unitVector(light.location, location);
        return total + lightAttenuation(light, location) * light.color * utils::dotProduct(N, I);
    };

    auto result = kd * std::accumulate(list.begin(), list.end(), PreciseColor(), lambda);
    return result;
}

PreciseColor specular(PhongParameters params)
{
    return PreciseColor();
}

float lightAttenuation(LightSource source, sf::Vector3f currentPosition)
{
    auto r = utils::distanceBetweenPoints(source.location, currentPosition);
    auto c0 = source.color.r;
    auto c1 = source.color.g;
    auto c2 = source.color.b;

    return std::min(1 / (c2 * r * r + c1 * r + c0), 1.0f);
}

sf::Vector3f getUnitSurface(sf::Vector3f location, PhongParameters params)
{
    float x = location.x / params.distance;
    float y = location.y / params.distance;
    float z = location.z / params.distance;

    return sf::Vector3f(x, y, z);
}
