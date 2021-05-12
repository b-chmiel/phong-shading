#include "preciseColor.h"
#include "SFML/Graphics.hpp"
#include <algorithm>

PreciseColor::PreciseColor(sf::Color color)
{
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->a = color.a;
}

PreciseColor::PreciseColor(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

PreciseColor operator+(const PreciseColor& left, const PreciseColor& right)
{
    return PreciseColor(std::min(left.r + right.r, 255.0f),
        std::min(left.g + right.g, 255.0f),
        std::min(left.b + right.b, 255.0f),
        std::min(left.a + right.a, 255.0f));
}

PreciseColor operator*(const PreciseColor& left, const PreciseColor& right)
{
    return PreciseColor(std::min(left.r * right.r, 255.0f),
        std::min(left.g * right.g, 255.0f),
        std::min(left.b * right.b, 255.0f),
        std::min(left.a * right.a, 255.0f));
}

PreciseColor operator*(const PreciseColor& left, const float right)
{
    return PreciseColor(right, right, right, right) * left;
}

PreciseColor operator*(const float left, const PreciseColor& right)
{
    return PreciseColor(left, left, left, left) * right;
}

PreciseColor operator+(const PreciseColor& left, const float right)
{
    return PreciseColor(right, right, right, right) + left;
}

PreciseColor operator+(const float left, const PreciseColor& right)
{
    return PreciseColor(left, left, left, left) + right;
}