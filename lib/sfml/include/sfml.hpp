/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Pacman
*/

#ifndef __SFML_HPP__
#define __SFML_HPP__

#include "../../Interfaces/IDisplayModule.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class LIB_SFML : public IDisplayModule
{
public:
    LIB_SFML()
    {
        window->setFramerateLimit(60);
    }
    ~LIB_SFML()
    {
        window->close();
    }
    void DestroyWindow()
    {
        window->close();
    }
    void printRectangle(int x, int y, int w, int h, int R, int G, int B);
    void game_loop(IGameModule *game)
    {
        if (game == nullptr)
            return;
        if (window->isOpen())
        {
            window->clear();
            _arrayEntities = game->getAllEntities();
            for (auto it = begin(_arrayEntities); it != end(_arrayEntities); ++it)
            {
                printRectangle(it->getX(), it->getY(), it->getW(), it->getH(), it->getR(), it->getG(), it->getB());
            }
            window->display();
        }
        else
        {
            fprintf(stderr, "Erreur de création de la fenêtre.\n");
            exit(84);
        }
    };
    int getEvent();

protected:
private:
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade");
    std::vector<Entity> _arrayEntities;
};

#endif /* __!SFML_HPP__ */