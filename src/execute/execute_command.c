/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:50 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/18 18:30:31 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_if_builtins(t_token *cur)
{
	if (ft_strncmp(cur->value, "exit", 4) == 0 && cur->value[4] == '\0')
		return (2);
	else if (ft_strncmp(cur->value, "echo", 4) == 0 && cur->value[4] == '\0')
	{
		return (1);
	}
	else if (ft_strncmp(cur->value, "pwd", 3) == 0 && cur->value[3] == '\0')
		return (1);
	else if (ft_strncmp(cur->value, "env", 3) == 0 && cur->value[3] == '\0')
		return (1);
	else if (ft_strncmp(cur->value, "cd", 2) == 0 && cur->value[2] == '\0')
		return (1);
	else if (ft_strncmp(cur->value, "export", 6) == 0 && cur->value[6] == '\0')
		return (1);
	else if (ft_strncmp(cur->value, "unset", 5) == 0 && cur->value[5] == '\0')
		return (1);
	return (0);
}

static void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

// Funkcja do wykonania polecenia w oparciu o tokeny
int	execute_commands(t_shell *shell, t_token **tokens)
{
	t_token	*current_token;
	char	**args;

	current_token = *tokens;
	while (current_token)
	{
		if (current_token->type == COMMAND)
		{
			args = create_arg_list(current_token->next);
			if (check_if_builtins(current_token) == 2)
				return (2);
			else if (check_if_builtins(current_token) == 1)
			{
				if (!args)
				{
					ft_putstr_fd("Error: Memory allocation failed\n",
						STDERR_FILENO);
					return (1);
				}
				if (do_builtins(shell, current_token, args) == 0)
					ft_putendl_fd("blad", STDERR_FILENO);
			}
			else if (do_executable(shell, current_token->value, args) == 0)
				ft_putendl_fd("unknown command", STDERR_FILENO);
			free_args(args);
		}
		current_token = current_token->next;
	}
	return (0);
}
