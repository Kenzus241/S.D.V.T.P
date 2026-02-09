##
## EPITECH PROJECT, 2026
## S.D.V.T.P
## File description:
## this is the makefile of the project
##

CC      = epiclang

CFLAGS  = -Wall -Wextra -Iinclude -g

RAYLIB_FLAGS := $(shell pkg-config --cflags --libs raylib 2>/dev/null)
ifdef RAYLIB_FLAGS
	LDFLAGS := $(RAYLIB_FLAGS)
else
	LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

SRC_DIR = src
LIB_DIR = lib/my

SRC  = $(wildcard $(SRC_DIR)/*.c)
OBJ  = $(SRC:.c=.o)

LIBSRC = $(wildcard $(LIB_DIR)/*.c)
LIBOBJ = $(LIBSRC:.c=.o)

LIBMY = $(LIB_DIR)/libmy.a

NAME = S.D.V.T.P

all: $(LIBMY) $(NAME)

$(LIBMY): $(LIBOBJ)
	ar rc $(LIBMY) $(LIBOBJ)
	ar s $(LIBMY)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBMY) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(LIBOBJ)

fclean: clean
	$(RM) $(NAME) $(LIBMY)

re: fclean all
	$(RM) $(OBJ) $(LIBOBJ)

.PHONY: all clean fclean re
