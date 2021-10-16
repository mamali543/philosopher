
MakeDir = make
compile = gcc
FLAGS = -Wall -Wextra -Werror
NAME = philo

SRC = philo.c\
	  help_functions.c\
	  list.c\
	  init.c\
	  outils.c\
	  tools.c\
	  file.c

OBJS = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@$(compile) $(FLAGS) $(OBJS)  -o $(NAME) -fsanitize=address -g

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
