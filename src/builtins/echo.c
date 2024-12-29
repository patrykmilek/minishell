/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:36 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/28 23:16:02 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_env_variable(t_shell *shell, const char *arg)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->key, (char *)(arg + 1)) == 0)
		{
			ft_putstr_fd(current->value, STDOUT_FILENO);
			return ;
		}
		current = current->next;
	}
}

static void	print_argument(t_shell *shell, const char *arg)
{
	if (arg[0] == '$' && ft_strlen(arg) > 1)
		print_env_variable(shell, arg);
	else
		ft_putstr_fd((char *)arg, STDOUT_FILENO);
}

int	do_echo(t_shell *shell, char **args)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 0;
	if (args && args[0] && ft_strcmp(args[0], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (args && args[i])
	{
		print_argument(shell, args[i]);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
