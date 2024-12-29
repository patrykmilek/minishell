/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:21 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/29 13:36:16 by kubapyciarz      ###   ########.fr       */
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

int	handle_cd_oldpwd(t_shell *shell, char *current_pwd)
{
	char	*new_pwd;

	if (change_to_oldpwd(shell, current_pwd))
		return (free(current_pwd), 1);
	free(current_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("cd: getcwd error"), 1);
	update_pwd(shell, new_pwd);
	free(new_pwd);
	return (0);
}

int	handle_cd_home(t_shell *shell, char *current_pwd)
{
	char	*new_pwd;

	if (change_to_home(shell, current_pwd))
		return (free(current_pwd), 1);
	free(current_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("cd: getcwd error"), 1);
	update_pwd(shell, new_pwd);
	free(new_pwd);
	return (0);
}

int	do_cd(t_shell *shell, char **args)
{
	char	*current_pwd;
	char	*new_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (perror("cd: current pwd error"), 1);
	if (!args || !args[0] || !ft_strncmp(args[0], "", 1))
		return (handle_cd_home(shell, current_pwd));
	if (!ft_strncmp(args[0], "-", 2))
		return (handle_cd_oldpwd(shell, current_pwd));
	if (chdir(args[0]) == -1)
		return (free(current_pwd), perror("cd"), 1);
	get_old_pwd(shell, current_pwd);
	free(current_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("cd: getcwd error"), 1);
	update_pwd(shell, new_pwd);
	free(new_pwd);
	return (0);
}
