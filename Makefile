CC = gcc
INC = *.h
SRC = *.c
OBJ = $(SRC:.c=.o)
NAME = game
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -pedantic

all: compile

compile: $(SRC)
	$(CC) $(CFALGS) $(SRC) -o $(NAME) -lm -lSDL2

clean:
	$(RM) *~ $(NAME)

re: fclean all
