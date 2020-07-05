/*
** EPITECH PROJECT, 2020
** game
** File description:
** game
*/

#include "../include/game.hpp"

void Game::useBoost()
{
    if (_boost > 0)
    {
        _boost -= 5;
    }
    if (_boost == 0)
    {
        _sprint = 0;
    }
}
void Game::rechargeBoost()
{
    if (_boost < 500)
        _boost += 10;
    if (_boost > 500)
        _boost = 500;
}
int Game::getSizeSnake()
{
    return _snakesArray.size() + 1;
}
void Game::growSnake()
{
    srand(time(NULL));
    int size = (rand() % 50) + 5;

    for (int i = 0; i < size; i++)
    {
        _snakesArray.push_back(new Snake());
    }
}
void Game::simulateDirection(int x, int y, int x2, int y2)
{
    (void) x2;
    (void) y2;
    if (_nibblerArray[y][x] == '-')
    {
        _nibblerArray[y][x] = 'X';
        //_nibblerArray[y2][x2] = '-';
        _player->setY(y);
        _player->setX(x);
    }
    else if (_nibblerArray[y][x] == 'o')
    {
        if (!_sprint)
            _score++;
        else
            _score += 5;
        _speed = 500 - ((_score / 10) * 30);
        _nibblerArray[y][x] = 'X';
        //_nibblerArray[y2][x2] = '-';
        _player->setY(y);
        _player->setX(x);
        int i = 0;
        for (; i < int(_appleArray.size()); i++)
        {
            if (_appleArray[i]->getX() == x && _appleArray[i]->getY() == y)
            {
                _appleArray[i]->createNewApple(_nibblerArray);
                break;
            }
        }
        _nibblerArray[_appleArray[i]->getY()][_appleArray[i]->getX()] = 'o';
        growSnake();
    }
    else
    {
        _player->setStatus(PlayerStatus::DEAD);
        _status = GameStatus::STOP;
    }
}
void Game::simulate()
{
    int x = _player->getX();
    int y = _player->getY();
    int xtemp = 0;
    int ytemp = 0;

    for (int i = 0; i < int(_snakesArray.size()); i++)
    {
        xtemp = _snakesArray[i]->getX();
        ytemp = _snakesArray[i]->getY();
        _snakesArray[i]->setX(x);
        _snakesArray[i]->setY(y);
        if (xtemp > 0 && ytemp > 0)
            _nibblerArray[ytemp][xtemp] = '-';
        if (x > 0 && y > 0)
            _nibblerArray[y][x] = '*';
        x = xtemp;
        y = ytemp;
    }
    if (_player->getDirection() == Direction::UNDEFINED_DIRECTION)
        return;
    if (_player->getDirection() == Direction::TOP)
        simulateDirection(_player->getX(), _player->getY() - 1, _player->getX(), _player->getY());
    if (_player->getDirection() == Direction::BOTTOM)
        simulateDirection(_player->getX(), _player->getY() + 1, _player->getX(), _player->getY());
    if (_player->getDirection() == Direction::LEFT)
        simulateDirection(_player->getX() - 1, _player->getY(), _player->getX(), _player->getY());
    if (_player->getDirection() == Direction::RIGHT)
        simulateDirection(_player->getX() + 1, _player->getY(), _player->getX(), _player->getY());
    if (_player->getStatus() == PlayerStatus::DEAD)
        //return 1;
        return;
    if (_sprint)
    {
        useBoost();
    }
    else
    {
        rechargeBoost();
    }
    return;
}
void Game::actionKey(int key)
{
    if (key == 'z')
    {
        _player->setDirection(Direction::TOP);
    }
    if (key == 's')
    {
        _player->setDirection(Direction::BOTTOM);
    }
    if (key == 'q')
    {
        _player->setDirection(Direction::LEFT);
    }
    if (key == 'd')
    {
        _player->setDirection(Direction::RIGHT);
    }
    if (key == ' ')
    {
        setSprint(1);
    }
}

extern "C" IGameModule *createMyGame()
{
    return new Game();
}