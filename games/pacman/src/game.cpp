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
        _player->setSpeed(10);
        _boost -= 5;
    }
    if (_boost == 0)
    {
        _player->setSpeed(5);
        _sprint = 0;
    }
}
void Game::rechargeBoost()
{
    if (_boost < 500)
        _boost += 1;
    if (_boost > 500)
        _boost = 500;
}

int Game::collisionWithMap(int x, int y)
{
    for (int i = 0; i < int(_nibblerArray.size()); i++)
    {
        for (int z = 0; z < int(_nibblerArray[i].size()); z++)
        {
            if (_nibblerArray[i][z] == '#' &&
                (((y >= i * 40 && y < i * 40 + 40) && (x >= z * 40 && x < z * 40 + 40)) ||
                 ((y >= i * 40 && y < i * 40 + 40) && ((x + 40) > z * 40 && (x + 40) < z * 40 + 40)) ||
                 ((y + 40 > i * 40 && y < i * 40 + 40) && (x >= z * 40 && x < z * 40 + 40)) ||
                 ((y + 40 > i * 40 && y < i * 40 + 40) && (x + 40 > z * 40 && x < z * 40 + 40))))
            {
                return 1;
                break;
            }
        }
    }
    return 0;
}

Direction getRandomDirection()
{
    srand(time(NULL));
    Direction wantedDirection = Direction::TOP;
    int direction = (rand() % 3) + 1;

    if (direction == 2)
        wantedDirection = Direction::LEFT;
    if (direction == 3)
        wantedDirection = Direction::RIGHT;
    if (direction == 4)
        wantedDirection = Direction::BOTTOM;
    return wantedDirection;
}

void Game::calculBestMovement(Player *ghost)
{
    srand(time(NULL));
    int direction = (rand() % 2);

    if (ghost->getPositionX() == 920 && ghost->getPositionY() == 320)
    {
        if (direction)
            ghost->setWantedDirection(Direction::LEFT);
        else
            ghost->setWantedDirection(Direction::RIGHT);
        return;
    }
    if (ghost->getDirection() == Direction::TOP)
    {
        if (collisionWithMap(ghost->getPositionX(), ghost->getPositionY() - ghost->getSpeed()))
        {
            if (collisionWithMap(ghost->getPositionX() - ghost->getSpeed(), ghost->getPositionY()) &&
                collisionWithMap(ghost->getPositionX() + ghost->getSpeed(), ghost->getPositionY()))
            {
                ghost->setDirection(Direction::BOTTOM);
            }
            else if (collisionWithMap(ghost->getPositionX() - ghost->getSpeed(), ghost->getPositionY()))
            {
                ghost->setDirection(Direction::RIGHT);
            }
            else
            {
                ghost->setDirection(Direction::LEFT);
            }
            return;
        }
        if (direction == 0)
            ghost->setWantedDirection(Direction::RIGHT);
        else
            ghost->setWantedDirection(Direction::LEFT);
    }
    if (ghost->getDirection() == Direction::BOTTOM)
    {
        if (collisionWithMap(ghost->getPositionX(), ghost->getPositionY() + ghost->getSpeed()))
        {
            if (collisionWithMap(ghost->getPositionX() - ghost->getSpeed(), ghost->getPositionY()) &&
                collisionWithMap(ghost->getPositionX() + ghost->getSpeed(), ghost->getPositionY()))
            {
                ghost->setDirection(Direction::TOP);
            }
            else if (collisionWithMap(ghost->getPositionX() - ghost->getSpeed(), ghost->getPositionY()))
            {
                ghost->setDirection(Direction::RIGHT);
            }
            else
            {
                ghost->setDirection(Direction::LEFT);
            }
            return;
        }
        if (direction == 0)
            ghost->setWantedDirection(Direction::LEFT);
        else
            ghost->setWantedDirection(Direction::RIGHT);
    }
    if (ghost->getDirection() == Direction::RIGHT)
    {
        if (collisionWithMap(ghost->getPositionX() + ghost->getSpeed(), ghost->getPositionY()))
        {
            if (collisionWithMap(ghost->getPositionX(), ghost->getPositionY() - ghost->getSpeed()) &&
                collisionWithMap(ghost->getPositionX(), ghost->getPositionY() + ghost->getSpeed()))
            {
                ghost->setDirection(Direction::LEFT);
            }
            else if (collisionWithMap(ghost->getPositionX(), ghost->getPositionY() - ghost->getSpeed()))
            {
                ghost->setDirection(Direction::BOTTOM);
            }
            else
            {
                ghost->setDirection(Direction::TOP);
            }
            return;
        }
        if (direction == 0)
            ghost->setWantedDirection(Direction::TOP);
        else
            ghost->setWantedDirection(Direction::BOTTOM);
        if (ghost->getPositionX() >= 900 && ghost->getPositionX() <= 940 &&
            ghost->getPositionY() == 360)
        {
            ghost->setWantedDirection(Direction::TOP);
        }
    }
    if (ghost->getDirection() == Direction::LEFT)
    {
        if (collisionWithMap(ghost->getPositionX() - ghost->getSpeed(), ghost->getPositionY()))
        {
            if (collisionWithMap(ghost->getPositionX(), ghost->getPositionY() - ghost->getSpeed()) &&
                collisionWithMap(ghost->getPositionX(), ghost->getPositionY() + ghost->getSpeed()))
            {
                ghost->setDirection(Direction::RIGHT);
            }
            else if (collisionWithMap(ghost->getPositionX(), ghost->getPositionY() - ghost->getSpeed()))
            {
                ghost->setDirection(Direction::BOTTOM);
            }
            else
            {
                ghost->setDirection(Direction::TOP);
            }
            return;
        }
        if (direction == 0)
            ghost->setWantedDirection(Direction::BOTTOM);
        else
            ghost->setWantedDirection(Direction::TOP);
        if (ghost->getPositionX() >= 900 && ghost->getPositionX() <= 940 &&
            ghost->getPositionY() == 360)
        {
            ghost->setWantedDirection(Direction::TOP);
        }
    }
    if (ghost->getWantedDirection() == Direction::UNDEFINED_DIRECTION)
        ghost->setWantedDirection(Direction::TOP);
    return;
}

void Game::actionKey(int key)
{
    if (key == 'z')
    {
        _player->setWantedDirection(Direction::TOP);
    }
    if (key == 's')
    {
        _player->setWantedDirection(Direction::BOTTOM);
    }
    if (key == 'q')
    {
        _player->setWantedDirection(Direction::LEFT);
    }
    if (key == 'd')
    {
        _player->setWantedDirection(Direction::RIGHT);
    }
    if (key == ' ')
    {
        setSprint(1);
    }
}

std::vector<Entity> Game::getAllEntities()
{
    std::vector<Entity> _arrayEntities;

    for (int i = 0; i < int(_nibblerArray.size()); i++)
    {
        for (int y = 0; y < int(_nibblerArray[i].size()); y++)
        {
            if (_nibblerArray[i][y] == '#')
                _arrayEntities.push_back(Entity(y * 40, i * 40, 40, 40, 20, 20, 240));
            if (_nibblerArray[i][y] == 'o')
                _arrayEntities.push_back(Entity(y * 40 + 10, i * 40 + 10, 20, 20, 255, 0, 0));
            if (_nibblerArray[i][y] == 'O')
                _arrayEntities.push_back(Entity(y * 40 + 5, i * 40 + 5, 30, 30, 200, 200, 200));
        }
    }
    _arrayEntities.push_back(Entity(_player->getPositionX(), _player->getPositionY(), 40, 40, 255, 255, 0));
    if (_redGhost->getStatus() == PlayerStatus::ALIVE)
        _arrayEntities.push_back(Entity(_redGhost->getPositionX(), _redGhost->getPositionY(), 40, 40, 255, 0, 0));
    else
        _arrayEntities.push_back(Entity(_redGhost->getPositionX(), _redGhost->getPositionY(), 40, 40, 255, 255, 255));
    if (_purpleGhost->getStatus() == PlayerStatus::ALIVE)
        _arrayEntities.push_back(Entity(_purpleGhost->getPositionX(), _purpleGhost->getPositionY(), 40, 40, 255, 0, 255));
    else
        _arrayEntities.push_back(Entity(_purpleGhost->getPositionX(), _purpleGhost->getPositionY(), 40, 40, 255, 255, 255));
    if (_cyanGhost->getStatus() == PlayerStatus::ALIVE)
        _arrayEntities.push_back(Entity(_cyanGhost->getPositionX(), _cyanGhost->getPositionY(), 40, 40, 0, 255, 255));
    else
        _arrayEntities.push_back(Entity(_cyanGhost->getPositionX(), _cyanGhost->getPositionY(), 40, 40, 255, 255, 255));
    if (_greenGhost->getStatus() == PlayerStatus::ALIVE)
        _arrayEntities.push_back(Entity(_greenGhost->getPositionX(), _greenGhost->getPositionY(), 40, 40, 0, 255, 0));
    else
        _arrayEntities.push_back(Entity(_greenGhost->getPositionX(), _greenGhost->getPositionY(), 40, 40, 255, 255, 255));
    return _arrayEntities;
}

extern "C" IGameModule *createMyGame()
{
    return new Game();
}