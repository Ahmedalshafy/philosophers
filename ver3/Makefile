NAME = philosophers
SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, main.c utils.c prog.c init.c checks.c)
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -O3 -pthread -g #-fsanitize=address
CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

%.o: %.c
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
