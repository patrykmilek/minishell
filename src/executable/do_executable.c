/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:31:26 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/20 15:54:18 by pmilek           ###   ########.fr       */
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

static char	*check_if_executable(char **paths)
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

static void	execute_cmd(char *path, char **args, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(path, args, envp);
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("fork error");
}

int	do_executable(t_shell *shell, char *cmd, char **args)
{
	char	**paths;
	char	*path;
	char	**argument;
	char	**envp;

	path = find_path_in_env(shell);
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	add_cmd_to_paths(paths, cmd);
	path = check_if_executable(paths);
	argument = combine_arguments(args, cmd);
	envp = get_envp(shell);
	if (path)
		execute_cmd(path, argument, envp);
	else
		ft_putendl_fd("not executable", STDOUT_FILENO);
	free_list(paths);
	free_list(argument);
	free_list(envp);
	return (1);
}
