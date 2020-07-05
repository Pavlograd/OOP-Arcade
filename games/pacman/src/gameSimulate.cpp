/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** gameSimulate
*/

#include "../include/game.hpp"

void Game::simulateDirectionGhost(Player *ghost, int x, int y, int x2, int y2)
{
    (void)x2;
    (void)y2;
    int collision = collisionWithMap(x, y);

    if (!collision)
    {
        if (x % 40 == 0 && y % 40 == 0)
        {
            ghost->setY(y / 40);
            ghost->setX(x / 40);
            _nibblerArray[y / 40][x / 40] = 'G';
        }
        ghost->setPositionX(x);
        ghost->setPositionY(y);
        if (ghost->getPositionX() <= -20)
        {
            ghost->setPositionX(1900);
            ghost->setPositionY(520);
            ghost->setX(40);
            ghost->setY(13);
        }
        if (ghost->getPositionX() >= 1940)
        {
            ghost->setPositionY(520);
            ghost->setPositionX(0);
            ghost->setX(0);
            ghost->setY(13);
        }
    }
    return;
}

void Game::simulateDirection(int x, int y, int x2, int y2)
{
    (void)x2;
    (void)y2;
    int collision = collisionWithMap(x, y);

    for (int i = 0; i < int(_nibblerArray.size()); i++)
    {
        for (int z = 0; z < int(_nibblerArray[i].size()); z++)
        {
            if (_nibblerArray[i][z] == 'X')
            {
                _nibblerArray[i][z] = '-';
                break;
            }
        }
    }
    if (!collision)
    {
        simulateWin(x, y);
        simulateEatingApple(x, y);
        simulateEatingBonus(x, y);
        if (x % 40 == 0 && y % 40 == 0)
        {
            _player->setY(y / 40);
            _player->setX(x / 40);
            _nibblerArray[y / 40][x / 40] = 'X';
        }
        _player->setPositionX(x);
        _player->setPositionY(y);
        if (_player->getPositionX() <= -20)
        {
            _player->setPositionX(1900);
            _player->setX(40);
        }
        if (_player->getPositionX() >= 1940)
        {
            _player->setPositionX(0);
            _player->setX(0);
        }
    }
    return;
    _player->setStatus(PlayerStatus::DEAD);
}

void Game::calculBestMovementBonus(Player *ghost)
{
    if (ghost->getPositionX() == 920 && ghost->getPositionY() == 320)
    {
        ghost->setStatus(PlayerStatus::ALIVE);
        return;
    }
    if (ghost->getPositionX() < 920 && ghost->getPositionY() == 320)
    {
        ghost->setWantedDirection(Direction::RIGHT);
    }
    else if (ghost->getPositionX() > 920 && ghost->getPositionY() == 320)
    {
        ghost->setWantedDirection(Direction::LEFT);
    }
    else if (ghost->getPositionX() == 920 && ghost->getPositionY() == 320)
    {
        ghost->setWantedDirection(Direction::RIGHT);
    }
    else if (ghost->getPositionX() == 920 && ghost->getPositionY() < 320)
    {
        ghost->setWantedDirection(Direction::BOTTOM);
    }
    else if (ghost->getPositionX() == 920 && ghost->getPositionY() > 320)
    {
        ghost->setWantedDirection(Direction::TOP);
    }
    else
    {
        calculBestMovement(ghost);
    }
}

int Game::simulateGhost(Player *ghost)
{
    int i = ghost->getPositionY() / 40;
    int z = ghost->getPositionX() / 40;

    if (((_player->getPositionY() >= i * 40 && _player->getPositionY() < i * 40 + 20) && (_player->getPositionX() >= z * 40 && _player->getPositionX() < z * 40 + 20)) ||
        ((_player->getPositionY() >= i * 40 && _player->getPositionY() < i * 40 + 20) && ((_player->getPositionX() + 40) > z * 40 && (_player->getPositionX() + 40) < z * 40 + 20)) ||
        ((_player->getPositionY() + 40 > i * 40 && _player->getPositionY() < i * 40 + 20) && (_player->getPositionX() >= z * 40 && _player->getPositionX() < z * 40 + 20)))
    {
        if (ghost->getStatus() == PlayerStatus::ALIVE)
        {
            return 1;
        }
        if (ghost->getStatus() == PlayerStatus::BONUS)
        {
            ghost->setStatus(PlayerStatus::DEAD);
        }
    }
    if (ghost->getDirection() == Direction::UNDEFINED_DIRECTION)
    {
        ghost->setDirection(Direction::TOP);
    }
    if (ghost->getStatus() == PlayerStatus::DEAD)
    {
        calculBestMovementBonus(ghost);
    }
    else
    {
        calculBestMovement(ghost);
    }
    if (ghost->getWantedDirection() == Direction::TOP)
    {
        if (!collisionWithMap(ghost->getPositionX(), ghost->getPositionY() - ghost->getSpeed()))
        {
            ghost->setDirection(Direction::TOP);
            ghost->setWantedDirection(Direction::UNDEFINED_DIRECTION);
        }
    }
    if (ghost->getWantedDirection() == Direction::BOTTOM)
    {
        if (!collisionWithMap(ghost->getPositionX(), ghost->getPositionY() + ghost->getSpeed()))
        {
            ghost->setDirection(Direction::BOTTOM);
            ghost->setWantedDirection(Direction::UNDEFINED_DIRECTION);
        }
    }
    if (ghost->getWantedDirection() == Direction::LEFT)
    {
        if (!collisionWithMap(ghost->getPositionX() - ghost->getSpeed(), ghost->getPositionY()))
        {
            ghost->setDirection(Direction::LEFT);
            ghost->setWantedDirection(Direction::UNDEFINED_DIRECTION);
        }
    }
    if (ghost->getWantedDirection() == Direction::RIGHT)
    {
        if (!collisionWithMap(ghost->getPositionX() + ghost->getSpeed(), ghost->getPositionY()))
        {
            ghost->setDirection(Direction::RIGHT);
            ghost->setWantedDirection(Direction::UNDEFINED_DIRECTION);
        }
    }
    if (ghost->getDirection() == Direction::TOP)
        simulateDirectionGhost(ghost, ghost->getPositionX(), ghost->getPositionY() - ghost->getSpeed(), ghost->getX(), ghost->getY() - 1);
    if (ghost->getDirection() == Direction::BOTTOM)
        simulateDirectionGhost(ghost, ghost->getPositionX(), ghost->getPositionY() + ghost->getSpeed(), ghost->getX(), ghost->getY() + 1);
    if (ghost->getDirection() == Direction::LEFT)
        simulateDirectionGhost(ghost, ghost->getPositionX() - ghost->getSpeed(), ghost->getPositionY(), ghost->getX() - 1, ghost->getY());
    if (ghost->getDirection() == Direction::RIGHT)
        simulateDirectionGhost(ghost, ghost->getPositionX() + ghost->getSpeed(), ghost->getPositionY(), ghost->getX() + 1, ghost->getY());
    return 0;
}

int Game::simulateGhosts()
{
    if (_chronoGates >= 0)
    {
        if (time(NULL) - _chronoGates >= 10)
        {
            _nibblerArray[9][23] = '-';
            _chronoGates = -1;
        }
    }
    if (simulateGhost(_redGhost))
    {
        _player->setStatus(PlayerStatus::DEAD);
        _status = GameStatus::STOP;
    }
    if (simulateGhost(_purpleGhost))
    {
        _player->setStatus(PlayerStatus::DEAD);
        _status = GameStatus::STOP;
    }
    if (simulateGhost(_cyanGhost))
    {
        _player->setStatus(PlayerStatus::DEAD);
        _status = GameStatus::STOP;
    }
    if (simulateGhost(_greenGhost))
    {
        _player->setStatus(PlayerStatus::DEAD);
        _status = GameStatus::STOP;
    }
    return 0;
}

void Game::simulateBonus()
{
    _redGhost->setSpeed(_redGhost->getRealSpeed());
    _purpleGhost->setSpeed(_purpleGhost->getRealSpeed());
    _cyanGhost->setSpeed(_cyanGhost->getRealSpeed());
    _greenGhost->setSpeed(_greenGhost->getRealSpeed());
    if (_chronoBonus != -1)
    {
        if (time(NULL) - _chronoBonus >= 15)
        {
            if (_redGhost->getStatus() == PlayerStatus::BONUS)
                _redGhost->setStatus(PlayerStatus::ALIVE);
            if (_purpleGhost->getStatus() == PlayerStatus::BONUS)
                _purpleGhost->setStatus(PlayerStatus::ALIVE);
            if (_cyanGhost->getStatus() == PlayerStatus::BONUS)
                _cyanGhost->setStatus(PlayerStatus::ALIVE);
            if (_greenGhost->getStatus() == PlayerStatus::BONUS)
                _greenGhost->setStatus(PlayerStatus::ALIVE);
            _chronoGates = -1;
            return;
        }
        if (time(NULL) - _chronoBonus < 2)
        {
            if (_redGhost->getStatus() != PlayerStatus::DEAD)
            {
                _redGhost->setStatus(PlayerStatus::BONUS);
                _redGhost->setSpeed(5);
            }
            if (_purpleGhost->getStatus() != PlayerStatus::DEAD)
            {
                _purpleGhost->setStatus(PlayerStatus::BONUS);
                _purpleGhost->setSpeed(5);
            }
            if (_cyanGhost->getStatus() != PlayerStatus::DEAD)
            {
                _cyanGhost->setStatus(PlayerStatus::BONUS);
                _cyanGhost->setSpeed(5);
            }
            if (_greenGhost->getStatus() != PlayerStatus::DEAD)
            {
                _greenGhost->setStatus(PlayerStatus::BONUS);
                _greenGhost->setSpeed(5);
            }
        }
    }
    if (_redGhost->getStatus() == PlayerStatus::DEAD)
    {
        _redGhost->setSpeed(20);
        if (_redGhost->getPositionY() == 320 && _redGhost->getPositionX() > 850 && _redGhost->getPositionX() < 1000)
            _redGhost->setSpeed(5);
    }
    if (_purpleGhost->getStatus() == PlayerStatus::DEAD)
    {
        _purpleGhost->setSpeed(20);
        if (_purpleGhost->getPositionY() == 320 && _purpleGhost->getPositionX() > 850 && _purpleGhost->getPositionX() < 1000)
            _purpleGhost->setSpeed(5);
    }
    if (_cyanGhost->getStatus() == PlayerStatus::DEAD)
    {
        _cyanGhost->setSpeed(20);
        if (_cyanGhost->getPositionY() == 320 && _cyanGhost->getPositionX() > 850 && _cyanGhost->getPositionX() < 1000)
            _cyanGhost->setSpeed(5);
    }
    if (_greenGhost->getStatus() == PlayerStatus::DEAD)
    {
        _greenGhost->setSpeed(20);
        if (_greenGhost->getPositionY() == 320 && _greenGhost->getPositionX() > 850 && _greenGhost->getPositionX() < 1000)
            _greenGhost->setSpeed(5);
    }
    if (_redGhost->getStatus() == PlayerStatus::BONUS)
    {
        _redGhost->setSpeed(5);
    }
    if (_purpleGhost->getStatus() == PlayerStatus::BONUS)
    {
        _purpleGhost->setSpeed(5);
    }
    if (_cyanGhost->getStatus() == PlayerStatus::BONUS)
    {
        _cyanGhost->setSpeed(5);
    }
    if (_greenGhost->getStatus() == PlayerStatus::BONUS)
    {
        _greenGhost->setSpeed(5);
    }
}

void Game::simulate()
{
    simulateBonus();
    if (_player->getWantedDirection() == Direction::TOP)
    {
        if (!collisionWithMap(_player->getPositionX(), _player->getPositionY() - _player->getSpeed()))
        {
            _player->setDirection(Direction::TOP);
            _player->setWantedDirection(Direction::UNDEFINED_DIRECTION);
        }
    }
    if (_player->getWantedDirection() == Direction::BOTTOM)
    {
        if (!collisionWithMap(_player->getPositionX(), _player->getPositionY() + _player->getSpeed()))
        {
            _player->setDirection(Direction::BOTTOM);
            _player->setWantedDirection(Direction::UNDEFINED_DIRECTION);
        }
    }
    if (_player->getWantedDirection() == Direction::LEFT)
    {
        if (!collisionWithMap(_player->getPositionX() - _player->getSpeed(), _player->getPositionY()))
        {
            _player->setDirection(Direction::LEFT);
            _player->setWantedDirection(Direction::UNDEFINED_DIRECTION);
        }
    }
    if (_player->getWantedDirection() == Direction::RIGHT)
    {
        if (!collisionWithMap(_player->getPositionX() + _player->getSpeed(), _player->getPositionY()))
        {
            _player->setDirection(Direction::RIGHT);
            _player->setWantedDirection(Direction::UNDEFINED_DIRECTION);
        }
    }
    if (_player->getDirection() == Direction::UNDEFINED_DIRECTION)
        return;
    if (_player->getDirection() == Direction::TOP)
        simulateDirection(_player->getPositionX(), _player->getPositionY() - _player->getSpeed(), _player->getX(), _player->getY() - 1);
    if (_player->getDirection() == Direction::BOTTOM)
        simulateDirection(_player->getPositionX(), _player->getPositionY() + _player->getSpeed(), _player->getX(), _player->getY() + 1);
    if (_player->getDirection() == Direction::LEFT)
        simulateDirection(_player->getPositionX() - _player->getSpeed(), _player->getPositionY(), _player->getX() - 1, _player->getY());
    if (_player->getDirection() == Direction::RIGHT)
        simulateDirection(_player->getPositionX() + _player->getSpeed(), _player->getPositionY(), _player->getX() + 1, _player->getY());
    simulateGhosts();
    if (_player->getStatus() == PlayerStatus::DEAD)
        //return 1;
        return;
    if (_player->getStatus() == PlayerStatus::WINNER)
    {
        _status = GameStatus::STOP;
        return;
    }
    if (_sprint)
    {
        useBoost();
    }
    else
    {
        rechargeBoost();
    }
    for (int i = 0; i < int(_nibblerArray.size()); i++)
    {
        for (int z = 0; z < int(_nibblerArray[i].size()); z++)
        {
            if (_nibblerArray[i][z] == 'G' &&
            (i != _redGhost->getPositionY() / 40 && z != _redGhost->getPositionX() / 40) &&
            (i != _purpleGhost->getPositionY() / 40 && z != _purpleGhost->getPositionX() / 40) &&
            (i != _cyanGhost->getPositionY() / 40 && z != _cyanGhost->getPositionX() / 40) &&
            (i != _greenGhost->getPositionY() / 40 && z != _greenGhost->getPositionX() / 40)
            )
            {
                _nibblerArray[i][z] = '-';
            }
        }
    }
    return;
}

void Game::simulateWin(int x, int y)
{
    (void)x;
    (void)y;
    int Apple = 0;
    for (int i = 0; i < int(_nibblerArray.size()); i++)
    {
        for (int z = 0; z < int(_nibblerArray[i].size()); z++)
        {
            if (_nibblerArray[i][z] == 'o')
            {
                Apple = 1;
                break;
            }
        }
    }
    if (!Apple)
    {
        //NO MORE APPLE
        _player->setStatus(PlayerStatus::WINNER);
        _status = GameStatus::STOP;
    }
}

void Game::simulateEatingBonus(int x, int y)
{
    for (int i = 0; i < int(_nibblerArray.size()); i++)
    {
        for (int z = 0; z < int(_nibblerArray[i].size()); z++)
        {
            if (_nibblerArray[i][z] == 'O' &&
                (((y >= i * 40 && y < i * 40 + 40) && (x >= z * 40 && x < z * 40 + 40)) ||
                 ((y >= i * 40 && y < i * 40 + 40) && ((x + 40) > z * 40 && (x + 40) < z * 40 + 40)) ||
                 ((y + 40 > i * 40 && y < i * 40 + 40) && (x >= z * 40 && x < z * 40 + 40))))
            {
                _nibblerArray[i][z] = '-';
                _score += 200;
                _chronoBonus = time(NULL);
            }
        }
    }
}

void Game::simulateEatingApple(int x, int y)
{
    for (int i = 0; i < int(_nibblerArray.size()); i++)
    {
        for (int z = 0; z < int(_nibblerArray[i].size()); z++)
        {
            if (_nibblerArray[i][z] == 'o' &&
                (((y >= i * 40 && y < i * 40 + 40) && (x >= z * 40 && x < z * 40 + 40)) ||
                 ((y >= i * 40 && y < i * 40 + 40) && ((x + 40) > z * 40 && (x + 40) < z * 40 + 40)) ||
                 ((y + 40 > i * 40 && y < i * 40 + 40) && (x >= z * 40 && x < z * 40 + 40))))
            {
                _nibblerArray[i][z] = '-';
                if (!_sprint)
                    _score++;
                else
                    _score += 5;
                _speed = 500 - ((_score / 10) * 30);
            }
        }
    }
}