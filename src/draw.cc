#include "draw.h"
#include "config.h"
#include "phong.h"
#include "vectorUtils.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <math.h>
#include <optional>
#include <sstream>

sf::Vector3f getProjectionPlaneVector(int i, int j, Config config);
std::optional<sf::Vector3f> intersectionWithSphere(sf::Vector3f current);
sf::Color getColor(sf::Vector3f intersection, phong::PhongParameters params);
void saveToFile(sf::Uint8* pixels, Config config);
std::string getFilePath(std::string fileName);

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
            auto color = getColor(*intersection, config.params);
            pixels[i] = color.r;
            pixels[i + 1] = color.g;
            pixels[i + 2] = color.b;
            pixels[i + 3] = color.a;
        } else {
            pixels[i] = (int)config.background.r;
            pixels[i + 1] = (int)config.background.g;
            pixels[i + 2] = (int)config.background.b;
            pixels[i + 3] = (int)config.background.a;
        }
    }

    texture->update(pixels);

    saveToFile(pixels, config);

    delete[] pixels;
}

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

sf::Color getColor(sf::Vector3f intersection, phong::PhongParameters params)
{
    auto shading = phong::PhongShading(params, intersection);
    PreciseColor precise = shading.computeColor();
    int r = abs(precise.r);
    int g = abs(precise.g);
    int b = abs(precise.b);
    int a = abs(precise.a);
    return sf::Color(r, g, b, a);
}

void saveToFile(sf::Uint8* pixels, Config config)
{
    sf::Image image;
    int width = config.outputDimensions.x;
    int height = config.outputDimensions.y;
    image.create(width, height, pixels);

    image.saveToFile(getFilePath(config.fileName));
}

std::string getFilePath(std::string fileName)
{
    const char* outDir = std::getenv("OUTDIR");
    if (outDir == nullptr) {
        outDir = "";
    }

    return outDir + fileName;
}
