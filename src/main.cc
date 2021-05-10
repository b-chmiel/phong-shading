#include "draw.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

const float width = 600;
const float height = 600;
const float radius = width / 5;

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(600.0f, 600.0f), "Phong shading");

    sf::Texture texture;
    texture.create(width, height);
    sf::Sprite sprite(texture);
    draw::printRender(width, height, radius, &texture);

    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
