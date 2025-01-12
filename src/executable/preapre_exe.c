/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preapre_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:54:11 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/12 13:19:09 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_path_in_env(t_shell *shell)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static void	add_cmd_to_paths(char **paths, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(temp, cmd);
		free(temp);
		i++;
	}
}

char	*handle_absolute_path(t_shell *shell, char *cmd)
{
	if (access(cmd, X_OK) == 0)
	{
		shell->shell_layer++;
		return (ft_strdup(cmd));
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	return (NULL);
}

char	*handle_command_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	return (NULL);
}

char	*prepare_executable(t_shell *shell, char *cmd, char ***paths)
{
	char	*path_env;

	if (ft_strchr(cmd, '/'))
		return (handle_absolute_path(shell, cmd));
	path_env = find_path_in_env(shell);
	if (!path_env)
		return (handle_command_not_found(cmd));
	*paths = ft_split(path_env, ':');
	add_cmd_to_paths(*paths, cmd);
	return (check_if_executable(*paths));
}
