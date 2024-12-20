#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
#include <sys/wait.h>

// -----------------------------
// Struktura zmiennych środowiska
// -----------------------------

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// -----------------------------
// Typy tokenów
// -----------------------------

typedef enum e_token_type
{
	COMMAND,	// komenda (np. echo, ls)
	ARGUMENT,	// argument komendy (np. -l, test)
	PIPE,		// potok
	REDIR_IN,	// <
	REDIR_OUT,	// >
	HEREDOC,	// <<
	APPEND // >>
}	t_token_type;
// -----------------------------
// Struktura tokena
// -----------------------------
typedef	struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;
// -----------------------------
// Główna struktura shella
// -----------------------------
typedef struct s_shell
{
	t_env	*env;
	t_token	*tokens;
}	t_shell;
// -----------------------------
// Deklaracje builtins
// -----------------------------
int		do_exit(void);
int		do_echo(t_shell *shell, char **args);
int		do_builtins(t_shell *shell, t_token *current_token, char **args);
int		do_pwd(void);
int		do_env(t_shell *shell);
int		do_cd(t_shell *shell, char **args);
int		do_export(t_shell *shell, char **args);
int		do_unset(t_shell *shell, char **args);
// -----------------------------
// funkcje pomocnicze do do_export (do_export_helper(_2).c)
// -----------------------------
int		init_new_node(t_env **new_node, char *key, char *value);
void	add_node_to_env(t_shell *shell, t_env *new_node);
void	print_tab(char **tab);
char	**sort_env(t_shell *shell);
void	add_env_variable(t_shell *shell, char *key, char *value);
int		update_env_value(t_env *current, char *key, char *value);
int		add_new_node(t_shell *shell, char *key, char *value);
char	*remove_quotes(char *str);
int		check_key(char *key); // w do env.c - nie zmiescilo sie
// -----------------------------
// Wykonywanie poleceń z programow
// -----------------------------
int		do_executable(t_shell *shell, char *cmd, char **args);
char	**get_envp(t_shell *shell);
char	**combine_arguments(char **args, char *cmd);
void	free_list(char **envp);

// -----------------------------
// Wykonywanie poleceń
// -----------------------------
int		execute_commands(t_shell *shell, t_token **tokens);
char	**create_arg_list(t_token *current_token);
// -----------------------------
// Inicjalizacja środowiska
// -----------------------------
void	init_env(t_shell *shell, char **env);
// -----------------------------
// Pomocnicze funkcje (helper.c)
// -----------------------------
int		count_args(char **args);
void	trim_newline(char *str);
t_env	*create_oldpwd_node(char *current_pwd);
void	add_oldpwd_if_missing(t_env *env, char *current_pwd);
char	*build_env_entry(t_env *env);
// -----------------------------
// Tokenizer
// -----------------------------
t_token	**tokenize_input(char *line);
int		is_special_char(char c);
void	add_special_token(t_token **tokens, int *count, char *line, int *i);
void	handle_redirection_token(t_token **tokens, int *count, char *line, int *i);
void	handle_pipe_token(t_token **tokens, int *count);
void	link_tokens(t_token **tokens);
char	*extract_word(char *line, int *i);
char	*extract_quoted_word(char *line, int *i);
t_token_type	determine_token_type(t_token **tokens, int count);
// -----------------------------
// Signals
// -----------------------------
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	setup_signals(void);

#endif