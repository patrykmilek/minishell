/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:21 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/17 22:39:22 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_old_pwd(t_shell *shell, char *current_pwd)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		if (ft_strncmp(current->key, "OLDPWD", 6) == 0)
		{
			free(current->value);
			current->value = ft_strdup(current_pwd);
			if (!current->value)
				perror("cd: malloc error");
			return ;
		}
		current = current->next;
	}
	add_oldpwd_if_missing(shell->env, current_pwd);
}

static char	*find_home(t_shell *shell)
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

static int	change_to_home(t_shell *shell, char *current_pwd)
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

static int	change_to_oldpwd(t_shell *shell, char *current_pwd)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		if (ft_strncmp(current->key, "OLDPWD", 6) == 0)
		{
			if (chdir(current->value) == -1)
				return (perror("cd"), free(current_pwd), 1);
			get_old_pwd(shell, current_pwd);
			return (0);
		}
		current = current->next;
	}
	ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
	free(current_pwd);
	return (1);
}

int	do_cd(t_shell *shell, char **args)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (perror("cd: current pwd error"), 1);
	if (!args[0] || !ft_strncmp(args[0], "", 1))
	{
		if (change_to_home(shell, current_pwd))
			return (1);
	}
	else if (!ft_strncmp(args[0], "-", 2))
	{
		if (change_to_oldpwd(shell, current_pwd))
			return (1);
	}
	else if (chdir(args[0]) == -1)
	{
		free(current_pwd);
		return (perror("cd"), 1);
	}
	get_old_pwd(shell, current_pwd);
	free(current_pwd);
	return (1);
}
