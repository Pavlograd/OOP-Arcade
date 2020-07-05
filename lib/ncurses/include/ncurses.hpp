/*
** EPITECH PROJECT, 2020
** AA LIB
** File description:
** AA LIB
*/

#ifndef __AALIB_HPP__
#define __AALIB_HPP__

#include "../../Interfaces/IDisplayModule.hpp"
#include <ncurses.h>

class LIB_NCURSES : public IDisplayModule
{
public:
    LIB_NCURSES()
    {
        initscr();
        keypad(stdscr, TRUE);
        noecho();
        wtimeout(stdscr, 30);
    };
    ~LIB_NCURSES()
    {
        endwin();
    }
    void DestroyWindow()
    {
        endwin();
    }
    void game_loop(IGameModule *game)
    {
        std::vector<std::string> line;

        clear();
        if (game == nullptr)
            return;
        line = game->getTextEntities();
        for (long unsigned int i = 0; i < line.size(); i++)
        {
            printw(line[i].c_str());
            printw("\n");
        }
        refresh();
    };
    int getEvent();
protected:
private:
};

#endif /* __!AALIB_HPP__ */