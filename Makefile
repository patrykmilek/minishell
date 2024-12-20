NAME = minishell
CC = gcc
CFLAGS = -Werror -Wall -Wextra -Iincludes -Ilibft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
BUILTINS_DIR = $(SRC_DIR)/builtins
ENV_DIR = $(SRC_DIR)/env
TOKENIZER_DIR = $(SRC_DIR)/tokenizer
EXECUTE_DIR = $(SRC_DIR)/execute
EXECUTABLE_DIR = $(SRC_DIR)/executable
SIGNALS_DIR = $(SRC_DIR)/signals
OBJ_DIR = obj

# Dodaj wszystkie źródła, w tym signals.c
SRC = $(wildcard $(SRC_DIR)/*.c) \
      $(wildcard $(BUILTINS_DIR)/*.c) \
      $(wildcard $(ENV_DIR)/*.c) \
      $(wildcard $(TOKENIZER_DIR)/*.c) \
      $(wildcard $(EXECUTE_DIR)/*.c) \
      $(wildcard $(EXECUTABLE_DIR)/*.c) \
      $(wildcard $(SIGNALS_DIR)/*.c)

# Wygenerowanie plików obiektowych
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Reguła główna
all: $(LIBFT) $(NAME)

# Budowanie biblioteki libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Budowanie programu minishell
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

# Kompilacja poszczególnych plików obiektowych
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Czyszczenie plików obiektowych
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

# Pełne czyszczenie plików obiektowych i binarki
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# Przebudowa programu
re: fclean all
