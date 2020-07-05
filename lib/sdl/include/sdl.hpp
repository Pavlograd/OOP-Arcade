/*
** EPITECH PROJECT, 2020
** Sdl
** File description:
** Sdl
*/

#ifndef __SDL_HPP__
# define __SDL_HPP__

#include "../../Interfaces/IDisplayModule.hpp"
#include <SDL2/SDL.h>

class LIB_SDL2 : public IDisplayModule
{
public:
    LIB_SDL2()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
            exit(84);
        }
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Arcade", 0, 0, 1920, 1080, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    };
    ~LIB_SDL2()
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    void DestroyWindow() {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    void printRectangle(SDL_Renderer *renderer, int x, int y, int w, int h, int R, int G, int B);
    void game_loop(IGameModule *game)
    {
        if (game == nullptr)
            return;
        if (window)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            _arrayEntities = game->getAllEntities();
            for (auto it = begin(_arrayEntities); it != end(_arrayEntities); ++it)
            {
                printRectangle(renderer, it->getX(), it->getY(), it->getW(), it->getH(), it->getR(), it->getG(), it->getB());
            }
            SDL_RenderPresent(renderer);
        }
        else
        {
            fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
            exit(84);
        }
    };
    int getEvent();

protected:
private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer;
    std::vector<Entity> _arrayEntities;
};

#endif /* __!SDL_HPP__ */