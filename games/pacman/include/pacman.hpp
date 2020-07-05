/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Pacman
*/

#ifndef pacman
#define pacman

#include "enum.hpp"

class Pacman
{
public:
    Pacman() {};
    ~Pacman() {};

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
#endif /* !pacman */