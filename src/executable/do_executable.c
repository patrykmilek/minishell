/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:31:26 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/04 19:48:16 by pmilek           ###   ########.fr       */
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

char	*check_if_executable(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (access(paths[i], X_OK) == 0)
			return (paths[i]);
		i++;
	}
	return (NULL);
}

int	execute_binary(char *path, char **argument, char **envp)
{
	execve(path, argument, envp);
	perror("minishell");
	exit(EXIT_FAILURE);
}

char	*prepare_executable(t_shell *shell, char *cmd, char ***paths)
{
	char	*path;

	path = find_path_in_env(shell);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (NULL);
	}
	*paths = ft_split(path, ':');
	add_cmd_to_paths(*paths, cmd);
	return (check_if_executable(*paths));
}
