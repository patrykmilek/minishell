/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:00:00 by pmilek            #+#    #+#             */
/*   Updated: 2025/01/17 20:33:57 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token_array(t_token **tokens, int count)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (i < count)
	{
		if (tokens[i])
		{
			if (tokens[i]->value)
				free(tokens[i]->value);
			free(tokens[i]);
		}
		i++;
	}
	free(tokens);
}

int	validate_line_start(char *line)
{
	if (!line || line[0] == '|')
	{
		ft_putendl_fd("ms: error near unexpected token `|'", STDERR_FILENO);
		return (0);
	}
	if (line[ft_strlen(line) - 1] == '|')
	{
		ft_putendl_fd("ms: error near unexpected token `|'", STDERR_FILENO);
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
