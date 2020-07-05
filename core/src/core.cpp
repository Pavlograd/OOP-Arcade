/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include "IGameModule.hpp"
#include "IDisplayModule.hpp"
#include "score.hpp"
#include "core.hpp"
#include "loaderEncapsulation.hpp"
#include <chrono>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

IGameModule *createMyGame()
{
    return nullptr;
}

IDisplayModule *createMyDisplay()
{
    return nullptr;
}

IGameModule::~IGameModule() {}

std::vector<std::string> &Arcade::Core::readDirectory(const std::string &folder1, const std::string &folder2)
{

    auto files_lib = new std::vector<std::string>();
    auto files_game = new std::vector<std::string>();
    DIR *dirp_lib = Arcade::loaderEncapsulation::encapC_opendir(folder1.c_str());
    DIR *dirp_game = Arcade::loaderEncapsulation::encapC_opendir(folder2.c_str());
    std::cout << "check for read right on /games and /lib: ";

    if (dirp_lib == NULL) {
        std::cout << "Error(" << errno << ") opening " << folder1;
        exit(84);
    }
    struct dirent *dp_lib = Arcade::loaderEncapsulation::encapC_readdir(dirp_lib);
    if (dirp_game == NULL) {
        std::cout << "Error(" << errno << ") opening " << folder2;
        exit(84);
    }
    if (dirp_lib != NULL && dirp_game != NULL)
        std::cout << "OK!" << std::endl;
    else
        std::cout << std::endl;
    struct dirent *dp_game = Arcade::loaderEncapsulation::encapC_readdir(dirp_game);
    std::cout << "\nThese libs are available in ./lib: ";
	while (dp_lib != nullptr) {
		auto fileName_lib = std::string(dp_lib->d_name);
		if (fileName_lib != "." && fileName_lib != ".." && fileName_lib.substr(fileName_lib.find_last_of('.') + 1) == "so")
            std::cout << fileName_lib << ", ";
			files_lib->push_back(fileName_lib);
		dp_lib = Arcade::loaderEncapsulation::encapC_readdir(dirp_lib);
	}
	Arcade::loaderEncapsulation::encapC_closedir(dirp_lib);
    std::cout << "" << std::endl;
    std::cout << "These games are available in ./games: ";
    while (dp_game != nullptr) {
		auto fileName_game = std::string(dp_game->d_name);
		if (fileName_game != "." && fileName_game != ".." && fileName_game.substr(fileName_game.find_last_of('.') + 1) == "so")
            std::cout << fileName_game << ", ";
			files_game->push_back(fileName_game);
		dp_game = Arcade::loaderEncapsulation::encapC_readdir(dirp_game);
	}
	Arcade::loaderEncapsulation::encapC_closedir(dirp_game);
    std::cout << "\n" << std::endl;
    return (*files_lib);
}

int displayUsage(int ret)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t ./arcade ./lib/lib_arcade_lib.so" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\t dynamic library (ex: lib_arcade_XXXX.so) must be in ./lib/" << std::endl;
    exit(ret);
}

void *changeGraphicLib(const char *filename)
{
    void *handle = Arcade::loaderEncapsulation::encapC_dlopen(filename, RTLD_LAZY);
    char *error = Arcade::loaderEncapsulation::encapC_dlerror();

    if (!handle)
    {
        std::cerr << "Error while loading the graphic lib." << std::endl;
        exit(84);
    }
    if (error != NULL)
    {
        std::cerr << "Error while loading the graphic lib." << error << std::endl;
        exit(84);
    }
    return handle;
}

void *changeGameLib(const char *filename)
{
    void *handle = Arcade::loaderEncapsulation::encapC_dlopen(filename, RTLD_LAZY);
    char *error = Arcade::loaderEncapsulation::encapC_dlerror();

    if (!handle)
    {
        std::cerr << "Error while loading the game lib." << std::endl;
        exit(84);
    }
    if (error != NULL)
    {
        std::cerr << "Error while loading the game lib." << std::endl;
        exit(84);
    }
    return handle;
}

void errorArguments(int ac, char **av, char **env)
{
    if (*env == NULL)
    {
        exit(84);
    }
    if (ac != 2)
    {
        displayUsage(84);
    }
    else
    {
        if (std::strcmp("-h", av[1]) == 0)
            displayUsage(0);
        if (std::strcmp("--help", av[1]) == 0)
            displayUsage(0);
    }
}

int main(int ac, char **av, char **env)
{
    IGameModule *Game;
    IDisplayModule *Display;
    void *handleGame;
    void *handleDisplay;
    int lib = 0;
    char *error;
    display_t *getFunctionDisplay;
    create_t *getFunctionCreate;
    std::chrono::system_clock::time_point a = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point b = std::chrono::system_clock::now();
    Game = createMyGame();
    Display = createMyDisplay();
    errorArguments(ac, av, env);
    Arcade::Core::readDirectory("./lib", "./games");
    handleDisplay = changeGraphicLib(av[1]);
    getFunctionDisplay = (display_t *)Arcade::loaderEncapsulation::encapC_dlsym(handleDisplay, "createMyDisplay");
    error = Arcade::loaderEncapsulation::encapC_dlerror();
    if (error)
    {
        std::cerr << "Error while loading the graphic lib." << error << std::endl;
        exit(84);
    }
    Display = getFunctionDisplay();
    handleGame = changeGameLib("games/lib_arcade_nibbler.so");
    getFunctionCreate = (create_t *)Arcade::loaderEncapsulation::encapC_dlsym(handleGame, "createMyGame");
    error = Arcade::loaderEncapsulation::encapC_dlerror();
    if (error)
    {
        std::cerr << "Error while loading the game lib." << error << std::endl;
        exit(84);
    }
    if (std::strcmp(av[1], "./lib/lib_arcade_sdl.so") == 0)
    {
        lib = 0;
    }
    else if (std::strcmp(av[1], "lib/lib_arcade_sdl.so") == 0)
    {
        lib = 0;
    }
    else if (std::strcmp(av[1], "./lib/lib_arcade_ncurses.so") == 0)
    {
        lib = 1;
    }
    else if (std::strcmp(av[1], "lib/lib_arcade_ncurses.so") == 0)
    {
        lib = 1;
    }
    else if (std::strcmp(av[1], "./lib/lib_arcade_sfml.so") == 0)
    {
        lib = 2;
    }
    else if (std::strcmp(av[1], "lib/lib_arcade_sfml.so") == 0)
    {
        lib = 2;
    } else {
        std::cerr << "You are trying to use a forbidden library." << std::endl;
        exit(84);
    }
    Game = getFunctionCreate();
    std::cout << "Launching game: " << Game->getName() << std::endl;
    while (1)
    {
        float fps = 1000 / 60;
        if (Game != nullptr)
            fps = 1000 / Game->getFpsGraphic();
        a = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> work_time = a - b;
        Display->game_loop(Game);
        int key = Display->getEvent();
        if (key == 606)
        {
            break;
        }
        else if (key == 'l')
        {
            std::cout << "Changing graphic lib ";
            Display->DestroyWindow();
            if (lib == 0)
            {
                lib = 1;
                handleDisplay = changeGraphicLib("lib/lib_arcade_ncurses.so");
                std::cout << "ncurses";
            }
            else if (lib == 1)
            {
                lib = 2;
                handleDisplay = changeGraphicLib("lib/lib_arcade_sfml.so");
                std::cout << "sfml";
            }
            else
            {
                lib = 0;
                handleDisplay = changeGraphicLib("lib/lib_arcade_sdl.so");
                std::cout << "sdl";
            }
            std::cout << std::endl;
            if (!handleDisplay)
            {
                std::cerr << "Error while loading the graphic lib." << error << std::endl;
                exit(84);
            }
            getFunctionDisplay = (display_t *)Arcade::loaderEncapsulation::encapC_dlsym(handleDisplay, "createMyDisplay");
            error = Arcade::loaderEncapsulation::encapC_dlerror();
            if (error)
            {
                std::cerr << "Error while loading the game lib." << error << std::endl;
                exit(84);
            }
            Display = getFunctionDisplay();
            if (Display == nullptr)
            {
                std::cerr << "Error while loading graphic library!" << std::endl;
                exit(84);
            }
            std::cout << "Graphic lib has been changed." << std::endl;
        }
        else if (key == 'b' || key == 'n')
        {
            std::cout << "Changing game lib..." << std::endl;
            if (Game->getName().compare("Nibbler") == 0)
            {
                handleGame = changeGameLib("games/lib_arcade_pacman.so");
            }
            else
            {
                handleGame = changeGameLib("games/lib_arcade_nibbler.so");
            }
            if (!handleGame)
            {
                std::cerr << "Error while loading the game lib." << error << std::endl;
                exit(84);
            }
            getFunctionCreate = (create_t *)Arcade::loaderEncapsulation::encapC_dlsym(handleGame, "createMyGame");
            error = Arcade::loaderEncapsulation::encapC_dlerror();
            if (error)
            {
                std::cerr << "Error while loading the game lib." << error << std::endl;
                exit(84);
            }
            Game = getFunctionCreate();
            if (Game == nullptr)
            {
                std::cerr << "Error while loading the game lib." << error << std::endl;
                exit(84);
            }
            std::cout << "Game lib has been changed." << std::endl;
            std::cout << "New game is : " << Game->getName() << std::endl;
        }
        else if (Game != nullptr)
        {
            Game->actionKey(key);
        }
        if (work_time.count() >= fps)
        {
            b = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> sleep_time = b - a;
            if (Game != nullptr)
                Game->simulate();
        }
        if (Game != nullptr && Game->getGameState() == GameStatus::STOP)
        {
            break;
        }
    }
    Display->DestroyWindow();
    if (Game != nullptr)
    {
        writeScore(Game);
        printBestScore(Game);
    }
    return 0;
}