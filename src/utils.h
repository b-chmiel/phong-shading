#ifndef UTILS_H
#define UTILS_H

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

using namespace sf;
namespace utils {

float lengthOfVector(Vector3f vector);
float distanceBetweenPoints(Vector3f a, Vector3f b);
float dotProduct(Vector3f left, Vector3f right);
Vector3f absoluteValue(Vector3f vector);
Vector3f unitVector(Vector3f from, Vector3f to);
Vector3f divideComponentWise(Vector3f left, Vector3f right);

}

#endif