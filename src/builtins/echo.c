/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:36 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/17 22:39:37 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_echo(char **args)
{
	int	args_count;
	int	is_new_line;

	is_new_line = 1;
	args_count = 0;
	if (args && args[0] && ft_strncmp(args[0],
			"-n", 2) == 0 && args[0][2] == '\0')
	{
		is_new_line = 0;
		args_count = 1;
	}
	while (args[args_count] != NULL)
	{
		ft_putstr_fd(args[args_count], STDOUT_FILENO);
		if (args[args_count + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		args_count++;
	}
	if (is_new_line == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}
