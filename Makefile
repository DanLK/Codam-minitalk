NAME_CLIENT = client
NAME_SERVER = server
SRC_DIR = ./src
OBJ_DIR = ./obj
SRC = pid_validation.c
SRC_SERV = server.c
SRC_CLIENT = client.c
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_SERV = $(SRC_SERV:%.c=$(OBJ_DIR)/%.o)
OBJ_CLIENT = $(SRC_CLIENT:%.c=$(OBJ_DIR)/%.o)
CFLAGS += -Wall -Werror -Wextra

LIBFT_NAME = ./libft/libft.a
LIBFT_PATH = ./libft

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ) $(OBJ_SERV) $(LIBFT_NAME)
	$(CC) -o $(NAME_SERVER) $(OBJ_SERV) $(OBJ) $(LIBFT_NAME)

$(NAME_CLIENT): $(OBJ) $(OBJ_CLIENT) $(LIBFT_NAME)
	$(CC) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(OBJ) $(LIBFT_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_NAME): 
	$(MAKE) -C $(LIBFT_PATH)

clean:
	rm -f $(OBJ) 
	rm -f $(OBJ_SERV)
	rm -f $(OBJ_CLIENT)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME_SERVER)
	rm -f $(NAME_CLIENT)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re