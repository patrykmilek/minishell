/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:00:00 by pmilek            #+#    #+#             */
/*   Updated: 2024/12/20 17:31:47 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	add_special_token(t_token **tokens, int *count, char *line, int *i)
{
	tokens[*count] = malloc(sizeof(t_token));
	if (!tokens[*count])
		return ;
	if (line[*i] == '|')
		handle_pipe_token(tokens, count);
	else
		handle_redirection_token(tokens, count, line, i);
	(*i)++;
}

void	handle_pipe_token(t_token **tokens, int *count)
{
	tokens[*count]->type = PIPE;
	tokens[*count]->value = ft_strdup("|");
	(*count)++;
}

void	handle_redirection_token(t_token **tokens,
		int *count, char *line, int *i)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		tokens[*count]->type = HEREDOC;
		tokens[*count]->value = ft_strdup("<<");
		(*i)++;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		tokens[*count]->type = APPEND;
		tokens[*count]->value = ft_strdup(">>");
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		tokens[*count]->type = REDIR_IN;
		tokens[*count]->value = ft_strdup("<");
	}
	else if (line[*i] == '>')
	{
		tokens[*count]->type = REDIR_OUT;
		tokens[*count]->value = ft_strdup(">");
	}
	(*count)++;
}

void	link_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] && tokens[i + 1])
	{
		tokens[i]->next = tokens[i + 1];
		i++;
	}
	if (tokens[i])
		tokens[i]->next = NULL;
}
