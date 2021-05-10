#include "draw.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>

void draw::printRender(int width, int height, int radius, sf::Texture* texture)
{
    const int pixelsLength = width * height * 4;
    sf::Uint8* pixels = new sf::Uint8[pixelsLength];

    sf::Vector2i origin(width / 2, height / 2);

    for (auto i = 0; i < pixelsLength - 4; i += 4) {
        int x = i / 4 % (width);
        int y = (i/ 4) / width;
        sf::Vector2i current(x, y);

        if (utils::lengthOrVector(current - origin) <= radius) {
            pixels[i] = 200;
            pixels[i + 1] = 200;
            pixels[i + 2] = 200;
            pixels[i + 3] = 255;
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
