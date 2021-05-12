#ifndef PRECISE_COLOR_H
#define PRECISE_COLOR_H

#include <SFML/Graphics.hpp>

class PreciseColor {
public:
    float r;
    float g;
    float b;
    float a;
    PreciseColor() = default;
    PreciseColor(sf::Color color);
    PreciseColor(float r, float g, float b, float a);
    friend PreciseColor operator+(const PreciseColor& left, const PreciseColor& right);
    friend PreciseColor operator*(const PreciseColor& left, const PreciseColor& right);
    friend PreciseColor operator+(const PreciseColor& left, const float right);
    friend PreciseColor operator+(const float left, const PreciseColor& right);
    friend PreciseColor operator*(const PreciseColor& left, const float right);
    friend PreciseColor operator*(const float left, const PreciseColor& right);
};

#endif