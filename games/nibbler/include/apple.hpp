/*
** EPITECH PROJECT, 2020
** Apple
** File description:
** Apple
*/

#ifndef apple
#define apple

#include <vector>
#include <iostream>
#include <ctime>

#include "enum.hpp"
#include "snake.hpp"

class Apple : public Snake
{
public:
    Apple(){};
    ~Apple(){};
    void createNewApple(std::vector<std::string> _nibblerArray)
    {
        srand(time(NULL));
        while (1)
        {
            int x = (rand() % 46) + 1;
            int y = (rand() % 18) + 1;
            if (_nibblerArray[y][x] == '-')
            {
                _x = x;
                _y = y;
                break;
            }
        }
    };

private:
};
#endif /* !apple */