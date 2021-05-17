#include "surface.h"
#include "config.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <cmath>
#include <math.h>

PreciseColor Surface::getSurfaceColor(const sf::Vector3f& position, const Config& config)
{
    if (config.pattern == Pattern::NONE) {
        return config.params.selfLuminance;
    }

    return getCheckerboard(position, config);
}

PreciseColor Surface::getCheckerboard(const sf::Vector3f& position, const Config& config)
{
    const float squareSize = 0.1;

    sf::Vector2f onPlane = transformFromSphereToPlane(position, config.radius);

    if (isSumEven(onPlane, squareSize)) {
        return PreciseColor(0, 0, 0, 0);
    }

    return PreciseColor(100, 100, 100, 100);
}

sf::Vector2f Surface::transformFromSphereToPlane(const sf::Vector3f& position, int radius)
{
    auto x = position.x;
    auto y = position.y;
    auto z = position.z;

    auto latitude = std::atan(std::sqrt(x * x + y * y) / z);
    auto longitude = std::atan(y / x);

    auto mercatorX = radius * longitude;
    auto mercatorY = radius * std::log((std::tan(M_PI / 4.0f + latitude / 2.0f)));

    return sf::Vector2f(mercatorX, mercatorY);
}

bool Surface::isSumEven(const sf::Vector2f& onPlane, float squareSize)
{
    int x = onPlane.x / squareSize;
    int y = onPlane.y / squareSize;

    return (x + y) % 2 == 0;
}