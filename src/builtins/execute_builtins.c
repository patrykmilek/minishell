#include "../includes/minishell.h"

int	do_builtins(t_shell *shell, char **args)
{
	int	is_done;

	is_done = 0;
	if (ft_strncmp(args[0], "exit", 4) == 0 && args[0][4] == '\0')
		is_done = do_exit(args);
	else if (ft_strncmp(args[0], "echo", 4) == 0 && args[0][4] == '\0')
		is_done = do_echo(args);
	else if (ft_strncmp(args[0], "pwd", 3) == 0 && args[0][3] == '\0')
		is_done = do_pwd(args);
	else if (ft_strncmp(args[0], "env", 3) == 0 && args[0][3] == '\0')
		is_done = do_env(shell);
	return (is_done);
}
