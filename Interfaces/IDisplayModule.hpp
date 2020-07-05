/*
** EPITECH PROJECT, 2020
** IDisplayModule
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include "IGameModule.hpp"

class IDisplayModule {
    public:
        virtual ~IDisplayModule() {};
        virtual void game_loop(IGameModule *game) = 0;
        virtual int getEvent() = 0;
        virtual void DestroyWindow() = 0;
};

typedef IDisplayModule * display_t();

#endif /* !IDISPLAYMODULE_HPP_ */