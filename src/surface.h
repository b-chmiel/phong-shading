#ifndef SURFACE_H
#define SURFACE_H

#include "config.h"
#include "phong.h"
#include "preciseColor.h"
#include <SFML/System/Vector3.hpp>

class Surface {
public:
    static PreciseColor getSurfaceColor(const sf::Vector3f& position, const Config& config);

private:
    static PreciseColor getCheckerboard(const sf::Vector3f& position, const Config& config);
    static bool isSumEven(const sf::Vector2f& onPlane, float squareSize);
    static sf::Vector2f transformFromSphereToPlane(const sf::Vector3f& position, int radius);
};

#endif