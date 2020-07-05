/*
** EPITECH PROJECT, 2020
** game
** File description:
** game
*/

#ifndef game
#define game

#include <vector>
#include <string>
#include <iostream>

#include "enum.hpp"
#include "player.hpp"
#include "apple.hpp"
#include "snake.hpp"

#include "../../../Interfaces/IGameModule.hpp"
#include "../../../Interfaces/gameStatus.hpp"
#include "../../../Interfaces/entity.hpp"

class Game : public IGameModule
{
public:
    Game()
    {
        std::string fullWall = "################################################";
        std::string EmptyLine = "#----------------------------------------------#";
        _nibblerArray = {fullWall,
                         EmptyLine, EmptyLine, EmptyLine, EmptyLine, EmptyLine,
                         EmptyLine, EmptyLine, EmptyLine, EmptyLine, EmptyLine,
                         EmptyLine, EmptyLine, EmptyLine, EmptyLine, EmptyLine,
                         EmptyLine, EmptyLine, EmptyLine, EmptyLine, EmptyLine,
                         fullWall};
        _nibblerArray[10][23] = 'X';
        _player->setY(10);
        _player->setX(23);
        _snakesArray.push_back(new Snake());
        _snakesArray.push_back(new Snake());
        _snakesArray.push_back(new Snake());
        _appleArray.push_back(new Apple());
        _appleArray.push_back(new Apple());
        _appleArray.push_back(new Apple());
        for (int i = 0; i < int(_appleArray.size()); i++)
        {
            _appleArray[i]->createNewApple(_nibblerArray);
            _nibblerArray[_appleArray[i]->getY()][_appleArray[i]->getX()] = 'o';
        }
        srand(time(NULL));
        int nb_obsatcle = (rand() % 40) + 15;
        for (int i = 0; i < nb_obsatcle; i++)
        {
            int x = (rand() % 46) + 1;
            int y = (rand() % 18) + 1;
            if (_nibblerArray[y][x] == '-')
            {
                _nibblerArray[y][x] = '#';
            }
        }
    };
    ~Game(){};
    void changeStatus(GameStatus status);
    void changeScene(Scene scene);
    GameStatus getStatus() const;
    Scene getScene() const;
    std::vector<std::string> getNibblerArray() const { return _nibblerArray; };
    void simulate();
    Player *getPlayer() const { return _player; };
    void simulateDirection(int x, int y, int x2, int y2);
    int getScore() const { return _score; };
    void growSnake();
    int getSizeSnake();
    void setSprint(int sprint)
    {
        if (_sprint)
            return;
        if (_boost == _boostLimit)
            _sprint = sprint;
    };
    int getSprint() const { return _sprint; };
    int getBoost() const { return _boost; };
    void rechargeBoost();
    void useBoost();
    int getSpeed() const { return _speed; };
    int getSpeedSprint() const { return _speedSprint; };
    void actionKey(int key);

    std::string getName() const { return "Nibbler"; };
    void setName(std::string name) { (void)name; };
    int getFpsText() const { return 10; };
    int getFpsGraphic() const {
        if (_sprint)
            return 30;
        return 10;
    };
    std::vector<Entity> getAllEntities()
    {
        std::vector<std::string> nibblerArray = getNibblerArray();
        std::vector<Entity> entities;

        for (int i = 0; i < int(nibblerArray.size()); i++)
        {
            for (int y = 0; y < int(nibblerArray[i].size()); y++)
            {
                if (nibblerArray[i][y] == '*')
                    entities.push_back(Entity(y * 40, i * 40, 40, 40, 0, 255, 0));
                if (nibblerArray[i][y] == 'X')
                    entities.push_back(Entity(y * 40, i * 40, 40, 40, 230, 255, 0));
                if (nibblerArray[i][y] == '#')
                    entities.push_back(Entity(y * 40, i * 40, 40, 40, 155, 155, 155));
                if (nibblerArray[i][y] == 'o')
                    entities.push_back(Entity(y * 40, i * 40, 40, 40, 255, 0, 0));
            }
        }
        return entities;
    };
    std::vector<std::string> getTextEntities() { return _nibblerArray; };
    GameStatus getGameState() const { return _status; };

private:
    int _score = 0;
    int _sprint = 0;
    int _boostLimit = 500;
    int _boost = _boostLimit;
    int _speed = 500;
    int _speedSprint = 150;
    Player *_player = new Player();
    GameStatus _status;
    Scene _scene;
    std::vector<std::string> _nibblerArray;
    std::vector<Snake *> _snakesArray;
    std::vector<Apple *> _appleArray;
};

#endif /* !game */