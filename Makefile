##
## Makefile for Makefile in /home/ouranos27/my_desktop/C_Graphical_Prog/bswolf3d
## 
## Made by philippe kam
## Login   <philippe.kam@epitech.eu>
## 
## Started on  Wed Dec 21 19:57:42 2016 philippe kam
## Last update Fri Feb 24 10:34:11 2017 philippe kam
##

CC	=	gcc

INFLAGS =	-I./include
CFLAGS	+=	-Wall -Wextra -lc_graph_prog_full -lm $(INFLAGS)

SRC	=	raytracer/my_put_pixel.c	\
		raytracer/window.c		\
		raytracer/drawers.c		\
		raytracer/drawers_utils.c	\
		raytracer/moves.c		\
		raytracer/finders.c		\
		raytracer/my_put_obj.c		\
		src/plane.c			\
		src/calc_dir_vector.c		\
		src/sphere.c			\
		src/cylinder.c			\
		src/cone.c			\
		src/torus.c			\
		src/light.c			\
		src/utils.c			\
		src/translate.c			\
		src/rotate.c			\
		src/reflection.c


OBJ	=	$(SRC:.c=.o)

NAME    =       raytracer2

all:            $(NAME)

$(NAME):        $(OBJ)
		@$(CC) -g $(SRC) -o $(NAME) $(CFLAGS)

debug: 		CFLAGS += -g -g3
debug: 		fclean $(NAME)

clean:
		rm -f $(OBJ)

fclean:         clean
		rm -f $(NAME)

re:             fclean all

.PHONY:         re fclean all clean
