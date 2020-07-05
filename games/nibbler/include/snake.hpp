/*
** EPITECH PROJECT, 2020
** Snake
** File description:
** Snake
*/

#ifndef snake
#define snake

#include "enum.hpp"

class Snake
{
public:
    Snake() {};
    ~Snake() {};

    //ALL POSITIONS
    void setPositionX(int positionX) {_positionX = positionX;};
    int getPositionX() const {return _positionX;};
    void setPositionY(int positionY) {_positionY = positionY;};
    int getPositionY() const {return _positionY;};

    //POSITION FOR THE DOUBLE ARRAY
    void setX(int x) {_x = x;};
    int getX() const {return _x;};
    void setY(int y) {_y = y;};
    int getY() const {return _y;};

protected:
    int _positionX;
    int _positionY;
    int _x = -10;
    int _y = -10;
};
#endif /* !Snake */