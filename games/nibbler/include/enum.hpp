/*
** EPITECH PROJECT, 2020
** enum
** File description:
** enum
*/

#ifndef __enum__
#define __enum__

enum PlayerStatus
{
    UNDEFINED,
    ALIVE,
    DEAD,
    IDLE,
    MOVING
};
enum Scene
{
    UNDEFINED_SCENE,
    MENU,
    GAME,
    PAUSE_SCENE,
    WIN,
    GAME_OVER
};
enum Direction
{
    UNDEFINED_DIRECTION,
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

#endif /* !enum */