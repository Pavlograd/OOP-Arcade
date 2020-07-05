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
#include <chrono>

#include "enum.hpp"
#include "player.hpp"
#include "apple.hpp"
#include "pacman.hpp"
//#include "entity.hpp"

#include "../../../Interfaces/IGameModule.hpp"
#include "../../../Interfaces/gameStatus.hpp"
#include "../../../Interfaces/entity.hpp"

class Game : public IGameModule
{
public:
    Game ()
    {
        std::string fullWall = "################################################";
        std::string EmptyLine = "#----------------------------------------------#";
        _nibblerArray = {fullWall,
                         "#----------------------#-----------------------#",
                         "#-##-##########-######-#-###-##########-######-#",
                         "#-##-##########-######-#-###-##########-######-#",
                         EmptyLine,
                         "#-##-##-#######-############-########-#-######-#",
                         "#----##-#-------##----######--------#---######-#",
                         "##-######-########-##-##########-#############-#",
                         EmptyLine,
                         "##-#-##-#-##########-#####-#-#-#-#-#########-#-#",
                         "##-#-##-#-#--#######-#---#-###-#-#-######----#-#",
                         "##-#----#-##---------#---#-#---#-#-#----######-#",
                         "##-######-##########-#####-#-###-#-#-#########-#",
                         "------------------------------------------------",
                         "##-######-########-##-##########-#############-#",
                         "#----##-#-------##----######--------#---######-#",
                         "#-##-##-#######-############-########-#-######-#",
                         "#----------------------#-----------------------#",
                         "#-##-##########-######---###-##########-######-#",
                         "#-##-##########-######-#-###-##########-######-#",
                         "#----------------------#-----------------------#",
                         fullWall};
        _nibblerArray[13][23] = 'X';
        _player->setY(13);
        _player->setX(23);
        _player->setPositionX(_player->getX() * 40);
        _player->setPositionY(_player->getY() * 40);
        _redGhost->setY(10);
        _redGhost->setX(22);
        _redGhost->setPositionX(_redGhost->getX() * 40);
        _redGhost->setPositionY(_redGhost->getY() * 40);
        _purpleGhost->setY(11);
        _purpleGhost->setX(24);
        _purpleGhost->setPositionX(_purpleGhost->getX() * 40);
        _purpleGhost->setPositionY(_purpleGhost->getY() * 40);
        _purpleGhost->setSpeed(5);
        _purpleGhost->setRealSpeed(5);
        _cyanGhost->setY(10);
        _cyanGhost->setX(23);
        _cyanGhost->setPositionX(_cyanGhost->getX() * 40);
        _cyanGhost->setPositionY(_cyanGhost->getY() * 40);
        _cyanGhost->setSpeed(5);
        _cyanGhost->setRealSpeed(5);
        _greenGhost->setY(10);
        _greenGhost->setX(24);
        _greenGhost->setPositionX(_greenGhost->getX() * 40);
        _greenGhost->setPositionY(_greenGhost->getY() * 40);
        _greenGhost->setSpeed(5);
        _greenGhost->setRealSpeed(5);
        for (int i = 0; i < int(_nibblerArray.size()); i++)
        {
            for (int y = 0; y < int(_nibblerArray[i].size()); y++)
            {
                if (_nibblerArray[i][y] == '-')
                    _nibblerArray[i][y] = 'o';
            }
        }
        _nibblerArray[10][23] = 'G';
        _nibblerArray[11][23] = '-';
        _nibblerArray[10][22] = '-';
        _nibblerArray[10][22] = 'G';
        _nibblerArray[10][24] = 'G';
        _nibblerArray[11][22] = '-';
        _nibblerArray[11][24] = 'G';
        srand(time(NULL));
        int x = (rand() % 46) + 1;
        int y = (rand() % 18) + 1;
        for (int i = 0; i < 4; i++) {
            while (_nibblerArray[y][x] != 'o') {
                x = (rand() % 46) + 1;
                y = (rand() % 18) + 1;
            }
            _nibblerArray[y][x] = 'O';
        }
    };
    ~Game(){};
    void changeStatus(GameStatus status);
    void changeScene(Scene scene);
    int simulateGhost(Player *ghost);
    GameStatus getStatus() const;
    Scene getScene() const;
    std::vector<std::string> getNibblerArray() const { return _nibblerArray; };
    void simulate();
    Player *getPlayer() const { return _player; };
    void simulateDirection(int x, int y, int x2, int y2);
    void simulateEatingApple(int x, int y);
    void simulateBonus();
    void simulateEatingBonus(int x, int y);
    void simulateWin(int x, int y);
    void simulateDirectionGhost(Player *ghost, int x, int y, int x2, int y2);
    int getScore() const { return _score; };
    void setScore(int score) { _score = score; };
    void growPacman();
    int getSizePacman();
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
    int collisionWithMap(int x, int y);
    int simulateGhosts();
    void calculBestMovement(Player *ghost);
    void calculBestMovementBonus(Player *ghost);

    std::string getName() const { return "Pacman";};
    void setName(std::string name) { (void)name;};
    int getFpsText() const { return 50;};
    int getFpsGraphic() const { return 50;};
    std::vector<Entity> getAllEntities();
    std::vector<std::string> getTextEntities() { return _nibblerArray;};
    GameStatus getGameState() const { return _status;};

private:
    int _score = 0;
    int _sprint = 0;
    int _boostLimit = 500;
    int _boost = _boostLimit;
    int _speed = 500;
    int _speedSprint = 150;
    Player *_player = new Player();
    Player *_redGhost = new Player();
    Player *_purpleGhost = new Player();
    Player *_cyanGhost = new Player();
    Player *_greenGhost = new Player();
    GameStatus _status;
    Scene _scene;
    std::vector<std::string> _nibblerArray;
    std::vector<Apple *> _appleArray;
    time_t _chronoGates = time(NULL);
    time_t _chronoBonus = -1;
};

#endif /* !game */