#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <limits.h>


// struktowa srodowiska
typedef struct s_env {
	char	*key;
	char	*value;
	struct s_env	*next;
} t_env;


// głowna struktora
typedef struct s_shell {
	t_env	*env;
} t_shell;


// builtins
int		do_exit(char **args);
int		do_echo(char **args);
int	do_builtins(t_shell *shell, char **args);
int		do_pwd(char **args);
int		do_env(t_shell *shell);

void	init_env(t_shell *shell, char **env);

// builtins/helper.c
int		count_args(char **args);
void	trim_newline(char *str);