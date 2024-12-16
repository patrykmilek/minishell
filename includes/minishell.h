#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>


// -----------------------------
// Struktura zmiennych środowiska
// -----------------------------
typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

// -----------------------------
// Typy tokenów
// -----------------------------
typedef enum e_token_type {
    COMMAND,   // komenda (np. echo, ls)
    ARGUMENT,  // argument komendy (np. -l, test)
    PIPE,      // potok
    REDIR_IN,  // <
    REDIR_OUT, // >
    HEREDOC,   // <<
    APPEND     // >>
} t_token_type;

// -----------------------------
// Struktura tokena
// -----------------------------
typedef struct s_token {
	t_token_type	type;
	char			*value;
	struct s_token	*next;
} t_token;

// -----------------------------
// Główna struktura shella
// -----------------------------
typedef struct s_shell {
	t_env	*env;
	t_token	*tokens;
} t_shell;

// -----------------------------
// Deklaracje builtins
// -----------------------------
int		do_exit(char **args);
int		do_echo(char **args);
int		do_builtins(t_shell *shell, char **args);
int		do_pwd(char **args);
int		do_env(t_shell *shell);

// -----------------------------
// Inicjalizacja środowiska
// -----------------------------
void	init_env(t_shell *shell, char **env);

// -----------------------------
// Pomocnicze funkcje (helper.c)
// -----------------------------
int		count_args(char **args);
void	trim_newline(char *str);

// -----------------------------
// Tokenizer
// -----------------------------
t_token	**tokenize_input(char *line);
int		is_special_char(char c);
void	add_special_token(t_token **tokens, int *count, char *line, int *i);
void	handle_redirection_token(t_token **tokens, int *count, char *line, int *i);
void	handle_pipe_token(t_token **tokens, int *count);



#endif
