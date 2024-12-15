#include "../includes/minishell.h"

int	do_pwd(char **args)
{
	char	cwd[PATH_MAX];

	if (count_args(args) > 1)
	{
		ft_putendl_fd("pwd: too many arguments", STDERR_FILENO);
		return (1);
	}
	else if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, STDERR_FILENO);
		return (1);
	}
	else
		return (0);
}
