/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:26:48 by pmilek            #+#    #+#             */
/*   Updated: 2025/01/04 19:55:31 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	has_unclosed_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (quote == '\0')
				quote = line[i];
			else if (quote == line[i])
				quote = '\0';
		}
		i++;
	}
	return (quote != '\0');
}

char	*extract_word(char *line, int *i)
{
	int		start;
	char	*word;

	start = *i;
	while (line[*i] && line[*i] != ' ' && !is_special_char(line[*i]))
		(*i)++;
	word = ft_substr(line, start, *i - start);
	if (!word)
	{
		perror("Allocation failed in extract_word");
		return (NULL);
	}
	return (word);
}

char	*extract_quoted_word(char *line, int *i)
{
	char	quote;
	int		start;

	quote = line[*i];
	start = ++(*i);
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++;
	return (ft_substr(line, start, *i - start - 1));
}

int	determine_token_type(t_token **tokens, int count)
{
	if (count == 0 || tokens[count - 1]->type == PIPE)
		return (COMMAND);
	return (ARGUMENT);
}
