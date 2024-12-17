/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:00:00 by pmilek            #+#    #+#             */
/*   Updated: 2024/12/16 11:53:53 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*extract_word(char *line, int *i)
{
	int		start;
	char	*word;

	start = *i;
	while (line[*i] && line[*i] != ' ' && !is_special_char(line[*i]))
		(*i)++;
	word = ft_substr(line, start, *i - start);
	return (word);
}

static char	*extract_quoted_word(char *line, int *i)
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

static t_token_type	determine_token_type(t_token **tokens, int count)
{
	if (count == 0 || (tokens[count - 1]->type == PIPE))
		return (COMMAND);
	return (ARGUMENT);
}

static void	handle_word_token(t_token **tokens, int *count, char *line, int *i)
{
	tokens[*count] = malloc(sizeof(t_token));
	if (!tokens[*count])
		return ;
	tokens[*count]->value = extract_word(line, i);
	tokens[*count]->type = determine_token_type(tokens, *count);
	(*count)++;
}

static void	handle_quoted_token(t_token **tokens,
	int *count, char *line, int *i)
{
	tokens[*count] = malloc(sizeof(t_token));
	if (!tokens[*count])
		return ;
	tokens[*count]->value = extract_quoted_word(line, i);
	tokens[*count]->type = determine_token_type(tokens, *count);
	(*count)++;
}

t_token	**tokenize_input(char *line)
{
	t_token	**tokens;
	int		i;
	int		count;

	tokens = malloc(sizeof(t_token *) * 1024);
	if (!tokens)
		return (NULL);
	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '"' || line[i] == '\'')
			handle_quoted_token(tokens, &count, line, &i);
		else if (is_special_char(line[i]))
		{
			add_special_token(tokens, &count, line, &i);
		}
		else
			handle_word_token(tokens, &count, line, &i);
	}
	tokens[count] = NULL;
	link_tokens(tokens);
	return (tokens);
}
