#include "draw.h"
#include "config.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>

bool isPointInCircle(sf::Vector2i current, sf::Vector2i origin, int radius)
{
    return utils::lengthOrVector(current - origin) <= radius;
}

void draw::printRender(Config config, sf::Texture* texture)
{
    int width = texture->getSize().x;
    int height = texture->getSize().y;

    const int colorCoeff = 4;
    const int pixelsLength = width * height * colorCoeff;
    sf::Uint8* pixels = new sf::Uint8[pixelsLength];

    sf::Vector2i origin(width / 2, height / 2);

    for (auto i = 0; i < pixelsLength - colorCoeff; i += colorCoeff) {
        int x = i / colorCoeff % (width);
        int y = (i / colorCoeff) / width;
        sf::Vector2i current(x, y);

        if (isPointInCircle(current, origin, config.radius)) {
            pixels[i] = config.surface.r;
            pixels[i + 1] = config.surface.g;
            pixels[i + 2] = config.surface.b;
            pixels[i + 3] = config.surface.a;
        } else {
            pixels[i] = 100;
            pixels[i + 1] = 100;
            pixels[i + 2] = 100;
            pixels[i + 3] = 100;
        }
    }

    texture->update(pixels);

    delete[] pixels;
}
