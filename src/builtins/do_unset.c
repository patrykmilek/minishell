/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:32 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/14 19:21:02 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	remove_var(t_shell *shell, char *arg)
{
	t_env	*current;
	t_env	*prev;

	current = shell->env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, arg) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				shell->env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	do_unset(t_shell *shell, char **args)
{
	int	i;

	if (!args || !args[0])
		return (1);
	i = 0;
	while (args[i])
	{
		if (check_key(args[i]))
		{
			ft_putstr_fd("unset: not a valid identifier: ", STDERR_FILENO);
			ft_putendl_fd(args[i], STDERR_FILENO);
		}
		else
			remove_var(shell, args[i]);
		i++;
	}
	return (0);
}
