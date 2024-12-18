/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:36 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/18 18:30:08 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_specific_env(t_shell *shell, char *arg)
{
	t_env	*current;
	char	*argument;

	if (!arg || arg[0] != '$')
		return ;
	argument = ft_strdup(arg + 1);
	if (!argument)
		return ;
	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->key, argument) == 0)
		{
			ft_putstr_fd(current->value, STDOUT_FILENO);
			break ;
		}
		current = current->next;
	}
	free(argument);
}

int	do_echo(t_shell *shell, char **args)
{
	int	args_count;
	int	is_new_line;

	is_new_line = 1;
	args_count = 0;
	if (args && args[0] && ft_strncmp(args[0],
			"-n", 2) == 0 && args[0][2] == '\0')
	{
		is_new_line = 0;
		args_count = 1;
	}
	while (args[args_count] != NULL)
	{
		if (args[args_count][0] == '$')
			print_specific_env(shell, args[args_count]);
		else
			ft_putstr_fd(args[args_count], STDOUT_FILENO);
		if (args[args_count + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		args_count++;
	}
	if (is_new_line == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}
