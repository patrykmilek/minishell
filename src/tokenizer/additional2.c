/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:26:48 by pmilek            #+#    #+#             */
/*   Updated: 2024/12/20 17:32:52 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_word(char *line, int *i)
{
	int		start;
	char	*word;

	start = *i;
	while (line[*i] && line[*i] != ' ' && !is_special_char(line[*i]))
		(*i)++;
	word = ft_substr(line, start, *i - start);
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

t_token_type	determine_token_type(t_token **tokens, int count)
{
	if (count == 0 || tokens[count - 1]->type == PIPE)
		return (COMMAND);
	return (ARGUMENT);
}
