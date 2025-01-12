/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:31:26 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/12 12:55:15 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
