#include "utils.h"
#include <math.h>

using namespace sf;

float utils::lengthOfVector(Vector3f vector)
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

float utils::distanceBetweenPoints(Vector3f a, Vector3f b)
{
    return utils::lengthOfVector(a - b);
}

float utils::dotProduct(Vector3f left, Vector3f right)
{
    return left.x * right.x + left.y * right.y + left.z + right.z;
}

Vector3f utils::absoluteValue(Vector3f vector)
{
    return Vector3f(abs(vector.x), abs(vector.y), abs(vector.z));
}

Vector3f utils::divideComponentWise(Vector3f left, Vector3f right)
{
    return Vector3f(left.x / right.x, left.y / right.y, left.z / right.z);
}

Vector3f utils::unitVector(Vector3f from, Vector3f to)
{
    return divideComponentWise((to - from), absoluteValue(to - from));
}