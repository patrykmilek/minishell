/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:34:51 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/28 22:03:32 by kubapyciarz      ###   ########.fr       */
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
