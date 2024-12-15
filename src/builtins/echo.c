#include "../includes/minishell.h"

static void	check_for_cmd_arg(char *arg, int *isnewline, int *argsiter)
{
	*isnewline = 0;
	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		*isnewline = 1;
		*argsiter = 2;
	}
	else
		*argsiter = 1;
}

int	do_echo(char **args)
{
	int	argsiter;
	int	isnewline;

	if (count_args(args) == 1)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		return (1);
	}
	else
	{
		check_for_cmd_arg(args[1], &isnewline, &argsiter);
		while (args[argsiter])
		{
			ft_putstr_fd(args[argsiter], STDERR_FILENO);
			if (args[argsiter + 1])
				ft_putchar_fd(' ', STDERR_FILENO);
			argsiter ++;
		}
		if (isnewline == 0)
			ft_putchar_fd('\n', STDERR_FILENO);
		return (1);
	}
	return (0);
}
