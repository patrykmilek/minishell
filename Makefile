# Nazwa projektu
NAME = minishell

# Kompilator i flagi
CC = gcc
CFLAGS = -Werror -Wall -Wextra -Iincludes -Ilibft

# Ścieżki do bibliotek
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Katalogi źródłowe
SRC_DIR = src
BUILTINS_DIR = $(SRC_DIR)/builtins
ENV_DIR = $(SRC_DIR)/env
TOKENIZER_DIR = $(SRC_DIR)/tokenizer
EXECUTE_DIR = $(SRC_DIR)/execute
EXECUTABLE_DIR = $(SRC_DIR)/executable
SIGNALS_DIR = $(SRC_DIR)/signals
DO_PIPES_AND_REDIR = $(SRC_DIR)/do_pipes_and_redir

# Katalog obiektów
OBJ_DIR = obj

# Pliki źródłowe
SRC = $(wildcard $(SRC_DIR)/*.c) \
      $(wildcard $(BUILTINS_DIR)/*.c) \
      $(wildcard $(ENV_DIR)/*.c) \
      $(wildcard $(TOKENIZER_DIR)/*.c) \
      $(wildcard $(EXECUTE_DIR)/*.c) \
      $(wildcard $(EXECUTABLE_DIR)/*.c) \
      $(wildcard $(SIGNALS_DIR)/*.c)\
      $(wildcard $(DO_PIPES_AND_REDIR)/*.c)

# Pliki obiektowe
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Flagi i biblioteki zależne od systemu
ifeq ($(shell uname), Darwin)  # macOS
    CFLAGS += -I/opt/homebrew/include
    LDFLAGS = -L/opt/homebrew/lib -L/opt/homebrew/Cellar/readline/8.2.13/lib
    LIBS = -lreadline -lhistory -lncurses
else  # Linux
    LIBS = -lreadline -lhistory
endif

# Reguła główna
all: $(LIBFT) $(NAME)

# Budowanie biblioteki libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Budowanie programu minishell
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) $(LDFLAGS) -o $(NAME)

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
