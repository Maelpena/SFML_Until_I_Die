#-----VARIABLES-----#

CC		=	g++

RM		=	rm -f

NAME	=	Until-I-Die

SFML	=	-lsfml-graphics -lsfml-window -lsfml-system

CFLAGS	=	-g -Wall -Wextra


SRC		=	bullet.cpp game.cpp		\
			main.cpp hud.cpp handgun.cpp		\
			player.cpp weapon.cpp zombie.cpp	\
			handgunammo.cpp shotgun.cpp			\
			shotgunammo.cpp rifle.cpp			\
			rifleammo.cpp collectible.cpp		\
			wave.cpp gameover.cpp menu.cpp		\
			redzombie.cpp lifecollectible.cpp   \
			greenzombie.cpp

OBJ		=	bullet.o game.o main.o		\
			hud.o handgun.o	handgunammo.o		\
			player.o weapon.o zombie.o rifle.o	\
			rifleammo.o shotgun.o shotgunammo.o	\
			collectible.o wave.o gameover.o 	\
			menu.o redzombie.o lifecollectible.o\
			greenzombie.o

MENUS	=	menu.cpp main_menu.cpp
MENUO	=	menu.o main_menu.o

GAMOS	=	gameover.cpp main_menu.cpp
GAMOO	=	gameover.o main_menu.o

#-----METHODS-----#

default: all


all: $(SRC) $(OBJ) $(SFML)
	echo "Compilation..."
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) -o $(NAME) $(OBJ) $(SFML)

menu: $(MENUS) $(MENUO) $(SFML)
	echo "Compilation menu..."
	$(CC) $(CFLAGS) -c $(MENUS)
	$(CC) -o $(NAME) $(MENUO) $(SFML)

gameover: $(GAMOS) $(GAMOO) $(SFML)
	echo "Compilation menu..."
	$(CC) $(CFLAGS) -c $(GAMOS)
	$(CC) -o $(NAME) $(GAMOO) $(SFML)

clean: 
	$(RM) *.o

fclean: 
	$(RM) Until-I-Die *.o