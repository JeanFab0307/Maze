CC = gcc
INC = inc/*.h
SRC = src/*.c
NAME = maze
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -pedantic

all: compile

compile: $(SRC)
	$(CC) $(CFALGS) $(SRC) -o $(NAME) -lm -lSDL2

clean:
	$(RM) *~ $(NAME)

re: fclean all
