/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:45:18 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/29 13:49:06 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>

# define NONE 0

typedef struct s_segment
{
	char				*command;
	char				**args;
	int					redir;
	char				*redir_target;
	int					relation;
	struct s_segment	*next;
}	t_segment;

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
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
}	t_token_type;
// -----------------------------
// Struktura tokena
// -----------------------------
typedef struct s_token
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
	t_env		*env;
	t_token		*tokens;
	t_segment	*segment;
	int			is_child;
	pid_t		pid;
}	t_shell;

typedef struct s_fork_data
{
	t_shell		*shell;
	t_segment	*current;
	int			old_input_fd;
	int			pipe_fd[2];
	int			is_last;
}	t_fork_data;

// -----------------------------
// Deklaracje builtins
// -----------------------------
int			do_exit(void);
int			do_echo(t_shell *shell, char **args);
int			do_builtins(t_shell *shell, t_token *current_token, char **args);
int			do_pwd(void);
int			do_env(t_shell *shell);
int			do_cd(t_shell *shell, char **args);
int			do_export(t_shell *shell, char **args);
int			do_unset(t_shell *shell, char **args);
void		add_env_variable(t_shell *shell, char *key, char *value);
int			change_to_home(t_shell *shell, char *current_pwd);
char		*find_home(t_shell *shell);
int			update_pwd(t_shell *shell, char *new_pwd);
extern void	rl_replace_line(const char *text, int clear_undo);
// -----------------------------
// pipes and redir
// -----------------------------
void		parse_tokens(t_shell *shell);
char		**append_arg(char **args, char *arg);
void		free_segments(t_segment *segments);
t_segment	*init_segment(void);
int			execute_segments(t_shell *shell);
void		redirect_io(t_fork_data *data);
void		handle_redirection(t_segment *segment);
// -----------------------------
// funkcje pomocnicze do do_export (do_export_helper(_2).c)
// -----------------------------
int			init_new_node(t_env **new_node, char *key, char *value);
void		add_node_to_env(t_shell *shell, t_env *new_node);
void		print_tab(char **tab);
char		**sort_env(t_shell *shell);
void		add_env_variable(t_shell *shell, char *key, char *value);
int			update_env_value(t_env *current, char *key, char *value);
int			add_new_node(t_shell *shell, char *key, char *value);
char		*remove_quotes(char *str);
int			check_key(char *key); // w do env.c - nie zmiescilo sie
// -----------------------------
// Wykonywanie poleceń z programow
// -----------------------------
int			do_executable(t_shell *shell, char *cmd, char **args);
char		**get_envp(t_shell *shell);
char		**combine_arguments(char **args, char *cmd);
void		free_list(char **envp);

// -----------------------------
// Wykonywanie poleceń
// -----------------------------
int			execute_commands(t_shell *shell, t_token **tokens);
int			is_builtin_command(char *cmd);
char		**create_arg_list(t_token *current_token);
// -----------------------------
// Inicjalizacja środowiska
// -----------------------------
void		init_env(t_shell *shell, char **env);
// -----------------------------
// Pomocnicze funkcje (helper.c)
// -----------------------------
int			count_args(char **args);
void		trim_newline(char *str);
t_env		*create_oldpwd_node(char *current_pwd);
void		add_oldpwd_if_missing(t_env *env, char *current_pwd);
char		*build_env_entry(t_env *env);
// -----------------------------
// Tokenizer
// -----------------------------
t_token		**tokenize_input(char *line);
int			is_special_char(char c);
void		add_special_token(t_token **tokens, int *count, char *line, int *i);
void		handle_redirection_token(t_token **tokens, int
				*count, char *line, int *i);
void		handle_pipe_token(t_token **tokens, int *count);
void		link_tokens(t_token **tokens);
char		*extract_word(char *line, int *i);
int			determine_token_type(t_token **tokens, int count);
char		*extract_quoted_word(char *line, int *i);
// -----------------------------
// Signals
// -----------------------------
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		setup_signals(void);
// -----------------------------
// debug
// -----------------------------
void		print_segments(t_segment *segment);
void		print_tokens(t_token *tokens);
// -----------------------------
// error handler
// -----------------------------

void		free_env(t_env *env);
void		free_tokens(t_token **tokens);
int			is_parent_builtin(char *cmd);

#endif