/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:13:09 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/29 13:14:28 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_pwd(t_shell *shell, char *new_pwd)
{
	t_env	*current;

	if (!shell || !new_pwd)
		return (1);
	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(new_pwd);
			if (!current->value)
			{
				perror("cd: malloc error for PWD");
				return (1);
			}
			return (0);
		}
		current = current->next;
	}
	add_env_variable(shell, "PWD", new_pwd);
	return (0);
}

char	*find_home(t_shell *shell)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		if (ft_strncmp(current->key, "HOME", 4) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	change_to_home(t_shell *shell, char *current_pwd)
{
	char	*home;

	home = find_home(shell);
	if (!home)
	{
		free(current_pwd);
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(home) == -1)
	{
		free(current_pwd);
		perror("cd");
		return (1);
	}
	return (0);
}
