/*
** EPITECH PROJECT, 2020
** player
** File description:
** player
*/

#ifndef player
#define player

#include "enum.hpp"
#include "snake.hpp"

class Player : public Snake
{
public:
    Player(){};
    ~Player(){};

    int setLife();
    int getLife() const;
    void setStatus(PlayerStatus status) {_status = status;};
    PlayerStatus getStatus() const {return _status;};

    //DIRECTIONS
    void setDirection(Direction direction)
    {
        if (!_direction)
            _direction = direction;
        if (direction == Direction::TOP && _direction == Direction::BOTTOM)
            return;
        if (direction == Direction::BOTTOM && _direction == Direction::TOP)
            return;
        if (direction == Direction::LEFT && _direction == Direction::RIGHT)
            return;
        if (direction == Direction::RIGHT && _direction == Direction::LEFT)
            return;
        _direction = direction;
    };
    Direction getDirection() const { return _direction; };

private:
    int _life;
    PlayerStatus _status;
    Direction _direction;
};
#endif /* !player */