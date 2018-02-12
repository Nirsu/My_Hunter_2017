##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

NAME	=	my_hunter

SRC	=	SRC/my_putchar.c	\
		SRC/my_putstr.c	\
		SRC/my_put_nbr.c	\
		SRC/help.c	\
		SRC/test.c

all:	$(NAME)

$(NAME): $(OBJ)
	gcc $(SRC) -l c_graph_prog
	mv a.out my_hunter

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
