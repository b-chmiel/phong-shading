#include "draw.h"
#include "config.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <math.h>
#include <optional>

sf::Vector3f getProjectionPlaneVector(int i, int j, Config config);
std::optional<sf::Vector3f> intersectionWithSphere(sf::Vector3f current);
void saveToFile(int width, int height, sf::Uint8* pixels);
sf::Color getColor(sf::Vector3f intersection, Config config);

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
            sf::Color color = getColor(*intersection, config);
            pixels[i] = color.r;
            pixels[i + 1] = color.g;
            pixels[i + 2] = color.b;
            pixels[i + 3] = color.a;
        } else {
            pixels[i] = config.background.r;
            pixels[i + 1] = config.background.g;
            pixels[i + 2] = config.background.b;
            pixels[i + 3] = config.background.a;
        }
    }

    texture->update(pixels);

    saveToFile(width, height, pixels);

    delete[] pixels;
}

// TODO remove those * 2, It will enlarge sphere
sf::Vector3f getProjectionPlaneVector(int i, int j, Config config)
{
    int n = config.outputDimensions.x;
    int m = config.outputDimensions.y;
    int r = config.radius;

    double x = r * (((2 * i) / (double)(n - 1)) - 1) * 2;
    double y = r * (1 - ((2 * j) / (double)(m - 1))) * 2;

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

sf::Color getColor(sf::Vector3f intersection, Config config)
{
    return config.params.selfLuminance;
}

void saveToFile(int width, int height, sf::Uint8* pixels)
{
    sf::Image image;
    image.create(width, height, pixels);
    image.saveToFile("output/output.bmp");
}
