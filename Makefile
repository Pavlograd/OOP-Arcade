##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## create gcc Makefile
##

CC					=	g++
SRC_DIR				=	./src
INCLUD				=	-I./core/include/ -I./assets/img -I./assets/music -I./Interfaces/
INCLUD				+=	-I./lib/ncurses/include -I./lib/sfml/include -I./lib/sdl/include -I./games/pacman/include -I./games/nibbler/include
CFLAGS				=	-Wall -Wextra -pedantic -std=c++17 -fPIC $(INCLUD) -g
LDFLAGS				=	-ldl
COR_DIR				=	./core
GAM_DIR				= 	./games
GRA_DIR				= 	./lib


## Arcade

NAME				=	arcade
SRC					=	$(COR_DIR)/src/core.cpp			\
						$(COR_DIR)/src/score.cpp			\
						$(COR_DIR)/src/loaderEncapsulation.cpp
OBJ					=	$(SRC:.cpp=.o)

##-------------------------------------------------------------------------------------------##
## ncurses LIB

NAME_AA				=	$(GRA_DIR)/lib_arcade_ncurses.so
SRC_AA				=	$(GRA_DIR)/ncurses/src/ncurses.cpp
OBJ_AA				=	$(SRC_AA:.cpp=.o)
LDFLAGS_AA			=	-shared -fPIC -lncurses

## SFML LIB

NAME_SFML			=	$(GRA_DIR)/lib_arcade_sfml.so
SRC_SFML			=	$(GRA_DIR)/sfml/src/sfml.cpp
OBJ_SFML			=	$(SRC_SFML:.cpp=.o)
LDFLAGS_SFML		=	-shared -fPIC -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio

## SDL LIB

NAME_SDL			=	$(GRA_DIR)/lib_arcade_sdl.so
SRC_SDL				=	$(GRA_DIR)/sdl/src/sdl.cpp
OBJ_SDL				=	$(SRC_SDL:.cpp=.o)
LDFLAGS_SDL			=	-shared -fPIC -lSDL2

##-------------------------------------------------------------------------------------------##
## PACMAN GAME

NAME_PACMAN			=	$(GAM_DIR)/lib_arcade_pacman.so
SRC_PACMAN			=	$(GAM_DIR)/pacman/src/game.cpp \
						$(GAM_DIR)/pacman/src/gameSimulate.cpp

OBJ_PACMAN			=	$(SRC_PACMAN:.cpp=.o)
LDFLAGS_PACMAN		=	-shared -fPIC

## NIBBLER GAME

NAME_NIBBLER		=	$(GAM_DIR)/lib_arcade_nibbler.so
SRC_NIBBLER			=	$(GAM_DIR)/nibbler/src/game.cpp

OBJ_NIBBLER			=	$(SRC_NIBBLER:.cpp=.o)
LDFLAGS_NIBBLER		=	-shared -fPIC

##-------------------------------------------------------------------------------------------##
## UTILS

all:				core games graphicals

core:				$(NAME)

games:				$(NAME_PACMAN) $(NAME_NIBBLER)

graphicals:			$(NAME_AA) $(NAME_SFML) $(NAME_SDL)

$(NAME_AA):			$(OBJ_AA)
					@$(CC) $(OBJ_AA) -o $(NAME_AA) $(LDFLAGS_AA)
					@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME_AA) | tr ' ' '.'

$(NAME_SFML):		$(OBJ_SFML)
					@$(CC) $(OBJ_SFML) -o $(NAME_SFML) $(LDFLAGS_SFML)
					@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME_SFML) | tr ' ' '.'

$(NAME_SDL):		$(OBJ_SDL)
					@$(CC) $(OBJ_SDL) -o $(NAME_SDL) $(LDFLAGS_SDL)
					@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME_SDL) | tr ' ' '.'

$(NAME_PACMAN):		$(OBJ_PACMAN)
					@$(CC) $(OBJ_PACMAN) -o $(NAME_PACMAN) $(LDFLAGS_PACMAN)
					@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME_PACMAN) | tr ' ' '.'

$(NAME_NIBBLER):	$(OBJ_NIBBLER)
					@$(CC) $(OBJ_NIBBLER) -o $(NAME_NIBBLER) $(LDFLAGS_NIBBLER)
					@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME_NIBBLER) | tr ' ' '.'

$(NAME):			$(OBJ)
					@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
					@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.'

clean:
					@$(RM) $(OBJ_AA) $(OBJ_SFML) $(OBJ_SDL) $(OBJ_PACMAN) $(OBJ_NIBBLER) $(OBJ)
					@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(OBJ_AA) $(OBJ_SFML) $(OBJ_SDL) $(OBJ_PACMAN) $(OBJ_NIBBLER) $(OBJ) | tr ' ' '.'

fclean:				clean
					@$(RM) $(NAME_AA) $(NAME_SFML) $(NAME_SDL) $(NAME_PACMAN) $(NAME_NIBBLER) $(NAME)
					@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(NAME_AA) $(NAME_SFML) $(NAME_SDL) $(NAME_PACMAN) $(NAME_NIBBLER) $(NAME) | tr ' ' '.'

re:					fclean all

.cpp.o:
					@$(CC) $(CFLAGS) -c $< -o $@
					@printf "[\033[0;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.'

.PHONY:				clean fclean re all
