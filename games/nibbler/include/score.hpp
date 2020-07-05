/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** score
*/

#ifndef SCORE_HPP_
#define SCORE_HPP_

#include "game.hpp"

void chronoSet();
std::vector<std::string> getAllLine(std::vector<std::string> line);
void writeScore(IGameModule *Game);
void printBestScore(IGameModule *Game);

#endif /* !SCORE_HPP_ */