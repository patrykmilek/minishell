/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:00:00 by pmilek            #+#    #+#             */
/*   Updated: 2025/01/04 20:05:45 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token_array(t_token **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (tokens[i])
		{
			free(tokens[i]->value);
			free(tokens[i]);
		}
		i++;
	}
	free(tokens);
}

int	validate_line_start(char *line, t_token **tokens, int count)
{
	if (line[0] == '|')
	{
		ft_putendl_fd("ms: error near unexpected token `|'", STDERR_FILENO);
		free_token_array(tokens, count);
		return (0);
	}
	return (1);
}

int	is_assignment(char *line, int start)
{
	while (line[start] && line[start] != '=' && line[start] != ' ')
		start++;
	return (line[start] == '=');
}
