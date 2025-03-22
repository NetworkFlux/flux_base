NAME = uninstall
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = $(shell find src -type f -name "*.c")
OBJ = $(SRC:.c=.o)
INC = -Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

