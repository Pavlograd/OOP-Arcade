/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** score
*/

#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <vector>
#include "../include/score.hpp"

void chronoSet()
{
    std::chrono::system_clock::time_point a = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point b = std::chrono::system_clock::now();
    float real_fps = 60;
    float fps = 1000 / real_fps;

    while (true)
    {
        a = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> work_time = a - b;

        if (work_time.count() < fps)
        {
            std::chrono::duration<double, std::milli> delta_ms(fps - work_time.count());
            auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
            std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
        }

        b = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> sleep_time = b - a;
        std::cout << work_time.count() << std::endl;
        printf("Time: %f \n", (work_time + sleep_time).count());
    }
}

std::vector<std::string> getAllLine(std::vector<std::string> line)
{
    std::ifstream myfile("score.txt");

    if (myfile.is_open())
    {
        std::string tmp;
        while (getline(myfile, tmp))
            line.push_back(tmp);
    }
    myfile.close();
    return line;
}

void printBestScore(IGameModule *Game)
{
    std::vector<std::string> line;
    std::string bestName = "";
    std::string bestScore = "";

    (void) Game;
    line = getAllLine(line);
    for (int i = 0; i < int(line.size()); i++)
    {
        std::istringstream ss(line[i]);
        std::string temp;
        std::string score;
        std::string error;
        ss >> temp;
        ss >> score;
        ss >> error;
        if (temp.compare("") != 0 or score.compare("") != 0 || error.compare("") == 0)
        {
            if (i == 0 || std::stoi(score) > std::stoi(bestScore))
            {
                bestName = temp;
                bestScore = score;
            }
        }
    }
    std::cout << "The best player is: " << bestName << " with a score of " << bestScore << std::endl;
}

void writeScore(IGameModule *Game)
{
    std::string name = "";
    std::cout << "Please enter your name: ";
    std::getline(std::cin, name);
    std::vector<std::string> line;
    line = getAllLine(line);
    std::ofstream writefile("score.txt");

    if (line.size() == 0)
    {
        writefile << name;
        writefile << " ";
        writefile << std::to_string(Game->getScore()) << std::endl;
    }
    else
    {
        int found = 0;
        for (int i = 0; i < int(line.size()); i++)
        {
            std::istringstream ss(line[i]);
            std::string temp;
            std::string score;
            std::string error;
            ss >> temp;
            ss >> score;
            ss >> error;
            if (temp.compare("") != 0 or score.compare("") != 0 || (error.compare("") == 0 && writefile.is_open()))
            {
                if (temp.compare(name) == 0)
                {
                    if (Game->getScore() > std::stoi(score))
                    {
                        writefile << name;
                        writefile << " ";
                        writefile << std::to_string(Game->getScore()) << std::endl;
                    }
                    else
                    {
                        writefile << temp;
                        writefile << " ";
                        writefile << score << std::endl;
                    }
                    found = 1;
                }
                else
                {
                    writefile << temp;
                    writefile << " ";
                    writefile << score << std::endl;
                }
            }
        }
        if (!found)
        {
            writefile << name;
            writefile << " ";
            writefile << std::to_string(Game->getScore()) << std::endl;
        }
    }
    writefile.close();
}