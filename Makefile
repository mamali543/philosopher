
MakeDir = make
compile = gcc
FLAGS = -Wall -Wextra -Werror -g
NAME = philo

SRC = philo.c\
	  help_functions.c\
	  list.c\
	  init.c\
	  outils.c	

SRCB=

all: $(NAME)

$(NAME): $(SRC)
	@$(compile) $(SRC)  -o $(NAME) -fsanitize=address -g

bonus: fclean
	@$(compile) $(SRCB) $(FLAGS) -o $(NAME)

fclean:
	@rm -rf $(NAME)

re: fclean all
