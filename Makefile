
MakeDir = make
compile = gcc
FLAGS = -Wall -Wextra -Werror -g
NAME = philo

SRC = philo.c

SRCB=

all: $(NAME)

$(NAME): $(SRC)
	@$(compile) $(SRC)  -o $(NAME)

bonus: fclean
	@$(compile) $(SRCB) $(FLAGS) -o $(NAME)

fclean:
	@rm -rf $(NAME)

re: fclean all
