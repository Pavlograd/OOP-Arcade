/*
** EPITECH PROJECT, 2020
** main sdl lib
** File description:
** main sdl lib
*/

#include "sdl.hpp"

int LIB_SDL2::getEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return 606;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                return 606;
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_l) // Touche l
            {
                return 'l';
            }
            if (event.key.keysym.sym == SDLK_m) // Touche m
            {
                return 'm';
            }
            if (event.key.keysym.sym == SDLK_b) // Touche b
            {
                return 'b';
            }
            if (event.key.keysym.sym == SDLK_n) // Touche n
            {
                return 'n';
            }
            if (event.key.keysym.sym == SDLK_z) // Touche z
            {
                return 'z';
            }
            if (event.key.keysym.sym == SDLK_q) // Touche q
            {
                return 'q';
            }
            if (event.key.keysym.sym == SDLK_d) // Touche d
            {
                return 'd';
            }
            if (event.key.keysym.sym == SDLK_s) // Touche s
            {
                return 's';
            }
            if (event.key.keysym.sym == SDLK_SPACE) // Touche
            {
                return ' ';
            }
            break;
        }
    }
    return 0;
}

void LIB_SDL2::printRectangle(SDL_Renderer *renderer, int x, int y, int w, int h, int R, int G, int B)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_SetRenderDrawColor(renderer, R, G, B, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
}

extern "C" IDisplayModule *createMyDisplay()
{
    return new LIB_SDL2();
}