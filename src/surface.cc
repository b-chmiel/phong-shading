#include "surface.h"
#include "config.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

PreciseColor Surface::getSurfaceColor(const sf::Vector3f& position, const Config& config)
{
    if (config.pattern == Pattern::NONE) {
        return config.params.selfLuminance;
    }

    return getCheckerboard(position, config);
}

PreciseColor Surface::getCheckerboard(const sf::Vector3f& position, const Config& config)
{
    const float squareSize = 1;

    sf::Vector2i onPlane = transformFromSphereToPlane(position);

    if (IsSumEven(onPlane, squareSize)) {
        return PreciseColor(0, 0, 0, 0);
    }

    return PreciseColor(100, 100, 100, 100);
}

sf::Vector2i Surface::transformFromSphereToPlane(const sf::Vector3f& position)
{
    auto x = position.x;
    auto y = position.y;
    auto z = position.z;

    return sf::Vector2i(x / (1.0f - z), y / (1.0f - z));
}

bool Surface::IsSumEven(const sf::Vector2i& onPlane, float squareSize)
{
    int x = (int)onPlane.x / squareSize;
    int y = (int)onPlane.y / squareSize;

    return (x + y) % 2 == 0;
}
