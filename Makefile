NAME = minishell

CC = gcc
CFLAGS = -Werror -Wall -Wextra -g -Iincludes -Ilibft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
BUILTINS_DIR = $(SRC_DIR)/builtins
ENV_DIR = $(SRC_DIR)/env
TOKENIZER_DIR = $(SRC_DIR)/tokenizer
EXECUTE_DIR = $(SRC_DIR)/execute
EXECUTABLE_DIR = $(SRC_DIR)/executable
SIGNALS_DIR = $(SRC_DIR)/signals
DO_PIPES_AND_REDIR = $(SRC_DIR)/do_pipes_and_redir

OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c) \
      $(wildcard $(BUILTINS_DIR)/*.c) \
      $(wildcard $(ENV_DIR)/*.c) \
      $(wildcard $(TOKENIZER_DIR)/*.c) \
      $(wildcard $(EXECUTE_DIR)/*.c) \
      $(wildcard $(EXECUTABLE_DIR)/*.c) \
      $(wildcard $(SIGNALS_DIR)/*.c)\
      $(wildcard $(DO_PIPES_AND_REDIR)/*.c)

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

ifeq ($(shell uname), Darwin)
    CFLAGS += -I/opt/homebrew/include
    LDFLAGS = -L/opt/homebrew/lib -L/opt/homebrew/Cellar/readline/8.2.13/lib
    LIBS = -lreadline -lhistory -lncurses
else
    LIBS = -lreadline -lhistory
endif

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) $(LDFLAGS) -o $(NAME)

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
