/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <iostream>
#include <vector>
#include "entity.hpp"
#include "gameStatus.hpp"

class IGameModule {
    public:
        virtual ~IGameModule() = 0;
        virtual void simulate() = 0;
        virtual void actionKey(int key) = 0;
        virtual std::string getName() const = 0;
        virtual void setName(std::string name) = 0;
        virtual int getFpsText() const = 0;
        virtual int getFpsGraphic() const = 0;
        virtual std::vector<Entity> getAllEntities() = 0;
        virtual std::vector<std::string> getTextEntities() = 0;
        virtual int getScore() const = 0;
        virtual GameStatus getGameState() const = 0;
};

typedef IGameModule * create_t();

#endif /* !IGAMEMODULE_HPP_ */