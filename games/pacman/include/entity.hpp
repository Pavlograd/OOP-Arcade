/*
** EPITECH PROJECT, 2020
** entity
** File description:
** entity
*/

#ifndef entity
#define entity

class Entity
{
public:
    Entity(int x, int y, int w, int h, int R, int G, int B) {
        _x = x;
        _y = y;
        _w = w;
        _h = h;
        _R = R;
        _G = G;
        _B = B;
    };
    ~Entity() {};

    //POSITION FOR THE DOUBLE ARRAY
    void setX(int x) {_x = x;};
    int getX() const {return _x;};
    void setY(int y) {_y = y;};
    int getY() const {return _y;};
    int getW() const {return _w;};
    int getH() const {return _h;};
    int getR() const {return _R;};
    int getG() const {return _G;};
    int getB() const {return _B;};

protected:
    int _x = -10;
    int _y = -10;
    int _w = 0;
    int _h = 0;
    int _R = 0;
    int _G = 0;
    int _B = 0;
};

#endif /* !entity */