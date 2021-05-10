#include "utils.h"
#include <math.h>

int utils::lengthOrVector(sf::Vector2i vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}