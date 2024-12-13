#include "minishell.h"
#include <stdio.h>
#include <fcntl.h>

static void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	main(int argc, char **argv, char **env)
{
	t_shell shell;
	char	*line;
	char	**args;
	int		status;

	(void)argc;
	(void)argv;
	init_env(&shell, env);
	while (1)
	{
		write(STDOUT_FILENO, "minishell> ", 12);
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			trim_newline(line);
			args = ft_split(line, ' ');
			status = do_builtins(&shell, args);
			if (status == 2)
				break ;
			free(line);
			free_args(args);
		}
		else
			break ;
	}
	return (0);
}
