#include "../includes/minishell.h"

int	count_args(char **args)
{
	int	argscount;

	argscount = 0;
	while (args[argscount])
		argscount++;
	return (argscount);
}

void	trim_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
