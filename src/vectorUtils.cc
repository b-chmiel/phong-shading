#include "vectorUtils.h"
#include <math.h>

using namespace sf;

float utils::lengthOfVector(Vector3f vector)
{
    float x = vector.x;
    float y = vector.y;
    float z = vector.z;
    return sqrt(x * x + y * y + z * z);
}

float utils::distanceBetweenPoints(Vector3f a, Vector3f b)
{
    return utils::lengthOfVector(a - b);
}

float utils::dotProduct(Vector3f left, Vector3f right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector3f utils::divideComponentWise(Vector3f left, Vector3f right)
{
    return Vector3f(left.x / right.x, left.y / right.y, left.z / right.z);
}

Vector3f utils::unitVector(Vector3f vector)
{
    auto magnitude = lengthOfVector(vector);
    return divideComponentWise((vector), Vector3f(magnitude, magnitude, magnitude));
}