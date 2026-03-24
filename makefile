NAME_CLIENT = client
NAME_SERVER = server

SRC_CLIENT = client.c
SRC_SERVER = server.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(FT_PRINTF_DIR)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(FT_PRINTF) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(FT_PRINTF) -o $(NAME_SERVER)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	make -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	make -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
