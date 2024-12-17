/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:48 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/17 22:39:49 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_partial_args(char **args, int i)
{
	while (i > 0)
	{
		free(args[--i]);
	}
	free(args);
}

static int	get_args_size(t_token *current_token)
{
	int	args_size;

	args_size = 0;
	while (current_token && current_token->type == ARGUMENT)
	{
		args_size++;
		current_token = current_token->next;
	}
	return (args_size);
}

char	**create_arg_list(t_token *current_token)
{
	char	**args;
	int		args_size;
	int		i;

	args_size = get_args_size(current_token);
	args = malloc((args_size + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (current_token && current_token->type == ARGUMENT)
	{
		args[i] = malloc(ft_strlen(current_token->value) + 1);
		if (!args[i])
		{
			free_partial_args(args, i);
			return (NULL);
		}
		ft_strlcpy(args[i], current_token->value,
			ft_strlen(current_token->value) + 1);
		current_token = current_token->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
