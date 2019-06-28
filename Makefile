##
## EPITECH PROJECT, 2018
## GroundHog Project
## File description:
## Makefile of GroundHog
##

CC			=	g++

NAME		=	groundhog

CFLAGS		=	-Wall -Wextra -Werror -g2

SRC			=	main.cpp

SRC			+=	src/GroundHog.cpp			\
				src/Calculations.cpp

OBJ			=	$(SRC:.c=.o)


$(NAME): $(OBJ)
	$(CC) $(SRC) -o $(NAME) $(CFLAGS)

all:				$(NAME)


clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY:
	fclean re clean
