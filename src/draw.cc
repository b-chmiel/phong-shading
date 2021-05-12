#include "draw.h"
#include "config.h"
#include "phong.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <math.h>
#include <optional>

sf::Vector3f getProjectionPlaneVector(int i, int j, Config config);
std::optional<sf::Vector3f> intersectionWithSphere(sf::Vector3f current);
PreciseColor getColor(sf::Vector3f intersection, phong::PhongParameters params);
void saveToFile(sf::Vector2i dimensions, sf::Uint8* pixels);

void draw::printRender(Config config, sf::Texture* texture)
{
    const int width = config.outputDimensions.x;
    const int height = config.outputDimensions.y;

    const int colorCoeff = 4;
    const int pixelsLength = width * height * colorCoeff;
    sf::Uint8* pixels = new sf::Uint8[pixelsLength];

    for (auto i = 0; i <= pixelsLength - colorCoeff; i += colorCoeff) {
        int x = i / colorCoeff % width;
        int y = (i / colorCoeff) / width;

        sf::Vector3f current = getProjectionPlaneVector(x, y, config);
        auto intersection = intersectionWithSphere(current);

        if (intersection) {
            PreciseColor color = getColor(*intersection, config.params);
            pixels[i] = (int)color.r;
            pixels[i + 1] = (int)color.g;
            pixels[i + 2] = (int)color.b;
            pixels[i + 3] = (int)color.a;
        } else {
            pixels[i] = (int)config.background.r;
            pixels[i + 1] = (int)config.background.g;
            pixels[i + 2] = (int)config.background.b;
            pixels[i + 3] = (int)config.background.a;
        }
    }

    texture->update(pixels);

    saveToFile(config.outputDimensions, pixels);

    delete[] pixels;
}

sf::Vector3f getProjectionPlaneVector(int i, int j, Config config)
{
    int n = config.outputDimensions.x;
    int m = config.outputDimensions.y;
    int r = config.radius;

    double x = r * (((2 * i) / (double)(n - 1)) - 1);
    double y = r * (1 - ((2 * j) / (double)(m - 1)));

    return sf::Vector3f(x, y, -r);
}

std::optional<sf::Vector3f> intersectionWithSphere(sf::Vector3f current)
{
    float x = current.x;
    float y = current.y;
    float r = current.z;

    double coeff = r * r - x * x - y * y;

    if (coeff < 0) {
        return std::nullopt;
    }

    return sf::Vector3f(x, y, sqrt(coeff));
}

PreciseColor getColor(sf::Vector3f intersection, phong::PhongParameters params)
{
    return phong::computeColor(intersection, params);
}

void saveToFile(sf::Vector2i dimensions, sf::Uint8* pixels)
{
    sf::Image image;
    image.create(dimensions.x, dimensions.y, pixels);
    image.saveToFile("output/output.bmp");
}
