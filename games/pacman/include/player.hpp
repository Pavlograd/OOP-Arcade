/*
** EPITECH PROJECT, 2020
** player
** File description:
** player
*/

#ifndef player
#define player

#include "enum.hpp"
#include "pacman.hpp"

class Player : public Pacman
{
public:
    Player(){};
    ~Player(){};

    int setLife();
    int getLife() const;
    void setSpeed(int speed) { _speed = speed;};
    void setRealSpeed(int speed) { _realSpeed = speed;};
    int getSpeed() const { return _speed;};
    int getRealSpeed() const { return _realSpeed;};
    void setStatus(PlayerStatus status) {_status = status;};
    PlayerStatus getStatus() const {return _status;};

    //DIRECTIONS
    void setDirection(Direction direction)
    {
        _direction = direction;
    };
    void setWantedDirection(Direction direction)
    {
        _wanted_direction = direction;
    };
    Direction getDirection() const { return _direction; };
    Direction getWantedDirection() const { return _wanted_direction; };

private:
    int _life;
    int _speed = 5;
    int _realSpeed = 5;
    PlayerStatus _status = PlayerStatus::ALIVE;
    Direction _direction = Direction::UNDEFINED_DIRECTION;
    Direction _wanted_direction;
};
#endif /* !player */