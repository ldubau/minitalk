NAME_CLIENT = client
NAME_SERVEUR = serveur

SRC_CLIENT = client.c
SRC_SERVEUR = serveur.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVEUR = $(SRC_SERVEUR:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME_CLIENT) $(NAME_SERVEUR)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)

$(NAME_SERVEUR): $(OBJ_SERVEUR)
	$(CC) $(CFLAGS) $(OBJ_SERVEUR) -o $(NAME_SERVEUR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVEUR)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVEUR)

re: fclean all

.PHONY: all clean fclean re
