/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:34:51 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/12 12:56:45 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static int	init_arguments(char ***arguments, char *cmd, int count)
{
	*arguments = malloc((count + 2) * sizeof(char *));
	if (!*arguments)
		return (0);
	(*arguments)[0] = ft_strdup(cmd);
	if (!(*arguments)[0])
	{
		free(*arguments);
		return (0);
	}
	return (1);
}

char	**combine_arguments(char **args, char *cmd)
{
	char	**arguments;
	int		count;
	int		i;

	count = 0;
	while (args && args[count])
		count++;
	if (!init_arguments(&arguments, cmd, count))
		return (NULL);
	i = 0;
	while (i < count)
	{
		arguments[i + 1] = ft_strdup(args[i]);
		if (!arguments[i + 1])
		{
			free_list(arguments);
			return (NULL);
		}
		i++;
	}
	arguments[count + 1] = NULL;
	return (arguments);
}

int	do_executable(t_shell *shell, char *cmd, char **args)
{
	char	**paths;
	char	*path;
	char	**argument;
	char	**envp;
	char	*layer;

	path = prepare_executable(shell, cmd, &paths);
	if (!path)
		return (0);
	argument = combine_arguments(args, cmd);
	if (ft_strcmp(cmd, "./minishell") == 0)
	{
		layer = ft_itoa(shell->shell_layer);
		argument = append_arg(argument, layer);
		free(layer);
	}
	envp = get_envp(shell);
	execve(path, argument, envp);
	perror("minishell");
	exit(EXIT_FAILURE);
}
