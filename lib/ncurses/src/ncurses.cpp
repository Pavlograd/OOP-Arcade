/*
** EPITECH PROJECT, 2020
** main aalib lib
** File description:
** main aalib lib
*/

#include "ncurses.hpp"

int LIB_NCURSES::getEvent()
{
    int ch = getch();

    if (ch == 'w')
        return 606;
    else
        return ch;
    return 0;
}

extern "C" IDisplayModule *createMyDisplay()
{
    return new LIB_NCURSES();
}