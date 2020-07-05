/*
** EPITECH PROJECT, 2020
** main sfml lib
** File description:
** main sfml lib
*/

#include "sfml.hpp"

int LIB_SFML::getEvent()
{
    sf::Event event;

    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            return 606;
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::W)
                return 606;
            if (event.key.code == sf::Keyboard::Z)
                return 'z';
            if (event.key.code == sf::Keyboard::Q)
                return 'q';
            if (event.key.code == sf::Keyboard::S)
                return 's';
            if (event.key.code == sf::Keyboard::D)
                return 'd';
            if (event.key.code == sf::Keyboard::L)
                return 'l';
            if (event.key.code == sf::Keyboard::M)
                return 'm';
            if (event.key.code == sf::Keyboard::N)
                return 'n';
            if (event.key.code == sf::Keyboard::B)
                return 'b';
            if (event.key.code == sf::Keyboard::Space)
                return ' ';
        }
    }
    return 0;
}

void LIB_SFML::printRectangle(int x, int y, int w, int h, int R, int G, int B)
{
    sf::RectangleShape rectangle(sf::Vector2f(w, h));

    rectangle.setPosition(sf::Vector2f(x, y));
    rectangle.setFillColor(sf::Color(G, B, R));
    window->draw(rectangle);
    return;
}

extern "C" IDisplayModule *createMyDisplay()
{
    return new LIB_SFML();
}