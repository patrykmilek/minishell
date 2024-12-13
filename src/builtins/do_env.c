#include "../includes/minishell.h"

int	do_env(t_shell *shell)
{
	t_env *current;

	current = shell->env;
	while (current)
	{
		if (current->key && current->value)
		{
			ft_putstr_fd(current->key, STDERR_FILENO);
			ft_putchar_fd('=', STDERR_FILENO);
			ft_putstr_fd(current->value, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		current = current->next;
	}
	return (1);
}