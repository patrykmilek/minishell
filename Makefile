NAME = minishell
CC = gcc
CFLAGS = -Werror -Wall -Wextra -Iincludes -Ilibft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
SRC_DIR = src
BUILTINS_DIR = $(SRC_DIR)/builtins
ENV_DIR = $(SRC_DIR)/env
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(BUILTINS_DIR)/*.c) $(wildcard $(ENV_DIR)/*.c)
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
